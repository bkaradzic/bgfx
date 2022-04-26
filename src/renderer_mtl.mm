/*
 * Copyright 2011-2016 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_METAL

#include "renderer_mtl.h"
#include "renderer.h"

#if BX_PLATFORM_OSX
#	include <Cocoa/Cocoa.h>
#endif

#import <Foundation/Foundation.h>

#define UNIFORM_BUFFER_SIZE (8*1024*1024)

namespace bgfx { namespace mtl
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
		MTLPrimitiveType m_type;
		uint32_t m_min;
		uint32_t m_div;
		uint32_t m_sub;
	};

	static const PrimInfo s_primInfo[] =
	{
		{ MTLPrimitiveTypeTriangle,      3, 3, 0 },
		{ MTLPrimitiveTypeTriangleStrip, 3, 1, 2 },
		{ MTLPrimitiveTypeLine,          2, 2, 0 },
		{ MTLPrimitiveTypeLineStrip,     2, 1, 1 },
		{ MTLPrimitiveTypePoint,         1, 1, 0 },
	};
	BX_STATIC_ASSERT(Topology::Count == BX_COUNTOF(s_primInfo) );

	static const char* s_attribName[] =
	{
		"a_position",
		"a_normal",
		"a_tangent",
		"a_bitangent",
		"a_color0",
		"a_color1",
		"a_color2",
		"a_color3",
		"a_indices",
		"a_weight",
		"a_texcoord0",
		"a_texcoord1",
		"a_texcoord2",
		"a_texcoord3",
		"a_texcoord4",
		"a_texcoord5",
		"a_texcoord6",
		"a_texcoord7",
	};
	BX_STATIC_ASSERT(Attrib::Count == BX_COUNTOF(s_attribName) );

	static const char* s_instanceDataName[] =
	{
		"i_data0",
		"i_data1",
		"i_data2",
		"i_data3",
		"i_data4",
	};
	BX_STATIC_ASSERT(BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT == BX_COUNTOF(s_instanceDataName) );

	static const MTLVertexFormat s_attribType[][4][2] = //type, count, normalized
	{
		// Uint8
		{
			{ MTLVertexFormatUChar2, MTLVertexFormatUChar2Normalized },
			{ MTLVertexFormatUChar2, MTLVertexFormatUChar2Normalized },
			{ MTLVertexFormatUChar3, MTLVertexFormatUChar3Normalized },
			{ MTLVertexFormatUChar4, MTLVertexFormatUChar4Normalized },
		},

		//Uint10
		//Note: unnormalized is handled as normalized now
		{
			{ MTLVertexFormatUInt1010102Normalized, MTLVertexFormatUInt1010102Normalized },
			{ MTLVertexFormatUInt1010102Normalized, MTLVertexFormatUInt1010102Normalized },
			{ MTLVertexFormatUInt1010102Normalized, MTLVertexFormatUInt1010102Normalized },
			{ MTLVertexFormatUInt1010102Normalized, MTLVertexFormatUInt1010102Normalized },
		},

		//Int16
		{
			{ MTLVertexFormatShort2, MTLVertexFormatShort2Normalized },
			{ MTLVertexFormatShort2, MTLVertexFormatShort2Normalized },
			{ MTLVertexFormatShort3, MTLVertexFormatShort3Normalized },
			{ MTLVertexFormatShort4, MTLVertexFormatShort4Normalized },
		},

		//Half
		{
			{ MTLVertexFormatHalf2, MTLVertexFormatHalf2 },
			{ MTLVertexFormatHalf2, MTLVertexFormatHalf2 },
			{ MTLVertexFormatHalf3, MTLVertexFormatHalf3 },
			{ MTLVertexFormatHalf4, MTLVertexFormatHalf4 },
		},

		//Float
		{
			{ MTLVertexFormatFloat,  MTLVertexFormatFloat  },
			{ MTLVertexFormatFloat2, MTLVertexFormatFloat2 },
			{ MTLVertexFormatFloat3, MTLVertexFormatFloat3 },
			{ MTLVertexFormatFloat4, MTLVertexFormatFloat4 },
		},
	};
	BX_STATIC_ASSERT(AttribType::Count == BX_COUNTOF(s_attribType) );

	static const MTLCullMode s_cullMode[] =
	{
		MTLCullModeNone,
		MTLCullModeFront,
		MTLCullModeBack,
		MTLCullModeNone
	};

	static const MTLBlendFactor s_blendFactor[][2] =
	{
		{ (MTLBlendFactor)0,                      (MTLBlendFactor)0                      }, // ignored
		{ MTLBlendFactorZero,                     MTLBlendFactorZero                     }, // ZERO
		{ MTLBlendFactorOne,                      MTLBlendFactorOne                      }, // ONE
		{ MTLBlendFactorSourceColor,              MTLBlendFactorSourceAlpha              }, // SRC_COLOR
		{ MTLBlendFactorOneMinusSourceColor,      MTLBlendFactorOneMinusSourceAlpha      }, // INV_SRC_COLOR
		{ MTLBlendFactorSourceAlpha,              MTLBlendFactorSourceAlpha              }, // SRC_ALPHA
		{ MTLBlendFactorOneMinusSourceAlpha,      MTLBlendFactorOneMinusSourceAlpha      }, // INV_SRC_ALPHA
		{ MTLBlendFactorDestinationAlpha,         MTLBlendFactorDestinationAlpha         }, // DST_ALPHA
		{ MTLBlendFactorOneMinusDestinationAlpha, MTLBlendFactorOneMinusDestinationAlpha }, // INV_DST_ALPHA
		{ MTLBlendFactorDestinationColor,         MTLBlendFactorDestinationAlpha         }, // DST_COLOR
		{ MTLBlendFactorOneMinusDestinationColor, MTLBlendFactorOneMinusDestinationAlpha }, // INV_DST_COLOR
		{ MTLBlendFactorSourceAlphaSaturated,     MTLBlendFactorOne                      }, // SRC_ALPHA_SAT
		{ MTLBlendFactorBlendColor,               MTLBlendFactorBlendColor               }, // FACTOR
		{ MTLBlendFactorOneMinusBlendColor,       MTLBlendFactorOneMinusBlendColor       }, // INV_FACTOR
	};

	static const MTLBlendOperation s_blendEquation[] =
	{
		MTLBlendOperationAdd,
		MTLBlendOperationSubtract,
		MTLBlendOperationReverseSubtract,
		MTLBlendOperationMin,
		MTLBlendOperationMax,
	};

	static const MTLCompareFunction s_cmpFunc[] =
	{
		MTLCompareFunctionAlways,
		MTLCompareFunctionLess,
		MTLCompareFunctionLessEqual,
		MTLCompareFunctionEqual,
		MTLCompareFunctionGreaterEqual,
		MTLCompareFunctionGreater,
		MTLCompareFunctionNotEqual,
		MTLCompareFunctionNever,
		MTLCompareFunctionAlways,
	};

	static const MTLStencilOperation s_stencilOp[] =
	{
		MTLStencilOperationZero,
		MTLStencilOperationKeep,
		MTLStencilOperationReplace,
		MTLStencilOperationIncrementWrap,
		MTLStencilOperationIncrementClamp,
		MTLStencilOperationDecrementWrap,
		MTLStencilOperationDecrementClamp,
		MTLStencilOperationInvert,
	};

	static const MTLSamplerAddressMode s_textureAddress[] =
	{
		MTLSamplerAddressModeRepeat,
		MTLSamplerAddressModeMirrorRepeat,
		MTLSamplerAddressModeClampToEdge,
		MTLSamplerAddressModeClampToZero,
	};

	static const MTLSamplerMinMagFilter s_textureFilterMinMag[] =
	{
		MTLSamplerMinMagFilterLinear,
		MTLSamplerMinMagFilterNearest,
		MTLSamplerMinMagFilterLinear,
	};

	static const MTLSamplerMipFilter s_textureFilterMip[] =
	{
		MTLSamplerMipFilterLinear,
		MTLSamplerMipFilterNearest,
	};

	struct TextureFormatInfo
	{
		MTLPixelFormat          m_fmt;
		MTLPixelFormat          m_fmtSrgb;
		MTLReadWriteTextureTier m_rwTier;
		bool                    m_autoGetMipmap;
	};

	static TextureFormatInfo s_textureFormat[] =
	{
		{ MTLPixelFormat(130/*BC1_RGBA*/),              MTLPixelFormat(131/*BC1_RGBA_sRGB*/),        MTLReadWriteTextureTierNone, false }, // BC1
		{ MTLPixelFormat(132/*BC2_RGBA*/),              MTLPixelFormat(133/*BC2_RGBA_sRGB*/),        MTLReadWriteTextureTierNone, false }, // BC2
		{ MTLPixelFormat(134/*BC3_RGBA*/),              MTLPixelFormat(135/*BC3_RGBA_sRGB*/),        MTLReadWriteTextureTierNone, false }, // BC3
		{ MTLPixelFormat(140/*BC4_RUnorm*/),            MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // BC4
		{ MTLPixelFormat(142/*BC5_RGUnorm*/),           MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // BC5
		{ MTLPixelFormat(150/*BC6H_RGBFloat*/),         MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // BC6H
		{ MTLPixelFormat(152/*BC7_RGBAUnorm*/),         MTLPixelFormat(153/*BC7_RGBAUnorm_sRGB*/),   MTLReadWriteTextureTierNone, false }, // BC7
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // ETC1
		{ MTLPixelFormat(180/*ETC2_RGB8*/),             MTLPixelFormat(181/*ETC2_RGB8_sRGB*/),       MTLReadWriteTextureTierNone, false }, // ETC2
		{ MTLPixelFormat(178/*EAC_RGBA8*/),             MTLPixelFormat(179/*EAC_RGBA8_sRGB*/),       MTLReadWriteTextureTierNone, false }, // ETC2A
		{ MTLPixelFormat(182/*ETC2_RGB8A1*/),           MTLPixelFormat(183/*ETC2_RGB8A1_sRGB*/),     MTLReadWriteTextureTierNone, false }, // ETC2A1
		{ MTLPixelFormat(160/*PVRTC_RGB_2BPP*/),        MTLPixelFormat(161/*PVRTC_RGB_2BPP_sRGB*/),  MTLReadWriteTextureTierNone, false }, // PTC12
		{ MTLPixelFormat(162/*PVRTC_RGB_4BPP*/),        MTLPixelFormat(163/*PVRTC_RGB_4BPP_sRGB*/),  MTLReadWriteTextureTierNone, false }, // PTC14
		{ MTLPixelFormat(164/*PVRTC_RGBA_2BPP*/),       MTLPixelFormat(165/*PVRTC_RGBA_2BPP_sRGB*/), MTLReadWriteTextureTierNone, false }, // PTC12A
		{ MTLPixelFormat(166/*PVRTC_RGBA_4BPP*/),       MTLPixelFormat(167/*PVRTC_RGBA_4BPP_sRGB*/), MTLReadWriteTextureTierNone, false }, // PTC14A
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // PTC22
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // PTC24
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // ATC
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // ATCE
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // ATCI
#if BX_PLATFORM_IOS && !TARGET_OS_MACCATALYST
		{ MTLPixelFormatASTC_4x4_LDR,                   MTLPixelFormatASTC_4x4_sRGB,                 MTLReadWriteTextureTierNone, false }, // ASTC4x4
		{ MTLPixelFormatASTC_5x5_LDR,                   MTLPixelFormatASTC_5x5_sRGB,                 MTLReadWriteTextureTierNone, false }, // ASTC5x5
		{ MTLPixelFormatASTC_6x6_LDR,                   MTLPixelFormatASTC_6x6_sRGB,                 MTLReadWriteTextureTierNone, false }, // ASTC6x6
		{ MTLPixelFormatASTC_8x5_LDR,                   MTLPixelFormatASTC_8x5_sRGB,                 MTLReadWriteTextureTierNone, false }, // ASTC8x5
		{ MTLPixelFormatASTC_8x6_LDR,                   MTLPixelFormatASTC_8x6_sRGB,                 MTLReadWriteTextureTierNone, false }, // ASTC8x6
		{ MTLPixelFormatASTC_10x5_LDR,                  MTLPixelFormatASTC_10x5_sRGB,                MTLReadWriteTextureTierNone, false }, // ASTC10x5
#else
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // ASTC4x4
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // ASTC5x5
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // ASTC6x6
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // ASTC8x5
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // ASTC8x6
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // ASTC10x5
#endif // BX_PLATFORM_IOS && !TARGET_OS_MACCATALYST
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // Unknown
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // R1
		{ MTLPixelFormatA8Unorm,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // A8
		{ MTLPixelFormatR8Unorm,                        MTLPixelFormat(11/*R8Unorm_sRGB*/),          MTLReadWriteTextureTier2,    true  }, // R8
		{ MTLPixelFormatR8Sint,                         MTLPixelFormatInvalid,                       MTLReadWriteTextureTier2,    false }, // R8I
		{ MTLPixelFormatR8Uint,                         MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // R8U
		{ MTLPixelFormatR8Snorm,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTier2,    true  }, // R8S
		{ MTLPixelFormatR16Unorm,                       MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, true  }, // R16
		{ MTLPixelFormatR16Sint,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTier2,    false }, // R16I
		{ MTLPixelFormatR16Uint,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTier2,    false }, // R16U
		{ MTLPixelFormatR16Float,                       MTLPixelFormatInvalid,                       MTLReadWriteTextureTier2,    true  }, // R16F
		{ MTLPixelFormatR16Snorm,                       MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, true  }, // R16S
		{ MTLPixelFormatR32Sint,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTier1,    false }, // R32I
		{ MTLPixelFormatR32Uint,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTier1,    false }, // R32U
		{ MTLPixelFormatR32Float,                       MTLPixelFormatInvalid,                       MTLReadWriteTextureTier1,    false }, // R32F
		{ MTLPixelFormatRG8Unorm,                       MTLPixelFormat(31/*RG8Unorm_sRGB*/),         MTLReadWriteTextureTierNone, true  }, // RG8
		{ MTLPixelFormatRG8Sint,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // RG8I
		{ MTLPixelFormatRG8Uint,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // RG8U
		{ MTLPixelFormatRG8Snorm,                       MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, true  }, // RG8S
		{ MTLPixelFormatRG16Unorm,                      MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, true  }, // RG16
		{ MTLPixelFormatRG16Sint,                       MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // RG16I
		{ MTLPixelFormatRG16Uint,                       MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // RG16U
		{ MTLPixelFormatRG16Float,                      MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, true  }, // RG16F
		{ MTLPixelFormatRG16Snorm,                      MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, true  }, // RG16S
		{ MTLPixelFormatRG32Sint,                       MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // RG32I
		{ MTLPixelFormatRG32Uint,                       MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // RG32U
		{ MTLPixelFormatRG32Float,                      MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // RG32F
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // RGB8
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // RGB8I
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // RGB8U
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // RGB8S
		{ MTLPixelFormatRGB9E5Float,                    MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // RGB9E5F
		{ MTLPixelFormatBGRA8Unorm,                     MTLPixelFormatBGRA8Unorm_sRGB,               MTLReadWriteTextureTierNone, false }, // BGRA8
		{ MTLPixelFormatRGBA8Unorm,                     MTLPixelFormatRGBA8Unorm_sRGB,               MTLReadWriteTextureTier2,    true  }, // RGBA8
		{ MTLPixelFormatRGBA8Sint,                      MTLPixelFormatInvalid,                       MTLReadWriteTextureTier2,    false }, // RGBA8I
		{ MTLPixelFormatRGBA8Uint,                      MTLPixelFormatInvalid,                       MTLReadWriteTextureTier2,    false }, // RGBA8U
		{ MTLPixelFormatRGBA8Snorm,                     MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, true  }, // RGBA8S
		{ MTLPixelFormatRGBA16Unorm,                    MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, true  }, // RGBA16
		{ MTLPixelFormatRGBA16Sint,                     MTLPixelFormatInvalid,                       MTLReadWriteTextureTier2,    false }, // RGBA16I
		{ MTLPixelFormatRGBA16Uint,                     MTLPixelFormatInvalid,                       MTLReadWriteTextureTier2,    false }, // RGBA16U
		{ MTLPixelFormatRGBA16Float,                    MTLPixelFormatInvalid,                       MTLReadWriteTextureTier2,    true  }, // RGBA16F
		{ MTLPixelFormatRGBA16Snorm,                    MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, true  }, // RGBA16S
		{ MTLPixelFormatRGBA32Sint,                     MTLPixelFormatInvalid,                       MTLReadWriteTextureTier2,    true  }, // RGBA32I
		{ MTLPixelFormatRGBA32Uint,                     MTLPixelFormatInvalid,                       MTLReadWriteTextureTier2,    true  }, // RGBA32U
		{ MTLPixelFormatRGBA32Float,                    MTLPixelFormatInvalid,                       MTLReadWriteTextureTier2,    true  }, // RGBA32F
		{ MTLPixelFormat(40/*B5G6R5Unorm*/),            MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, true  }, // R5G6B5
		{ MTLPixelFormat(42/*ABGR4Unorm*/),             MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, true  }, // RGBA4
		{ MTLPixelFormat(41/*A1BGR5Unorm*/),            MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, true  }, // RGB5A1
		{ MTLPixelFormatRGB10A2Unorm,                   MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, true  }, // RGB10A2
		{ MTLPixelFormatRG11B10Float,                   MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, true  }, // RG11B10F
		{ MTLPixelFormatInvalid,                        MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // UnknownDepth
		{ MTLPixelFormatDepth32Float,                   MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // D16
		{ MTLPixelFormatDepth32Float,                   MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // D24
		{ MTLPixelFormat(255/*Depth24Unorm_Stencil8*/), MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // D24S8
		{ MTLPixelFormatDepth32Float,                   MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // D32
		{ MTLPixelFormatDepth32Float,                   MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // D16F
		{ MTLPixelFormatDepth32Float,                   MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // D24F
		{ MTLPixelFormatDepth32Float,                   MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // D32F
		{ MTLPixelFormatStencil8,                       MTLPixelFormatInvalid,                       MTLReadWriteTextureTierNone, false }, // D0S8
	};
	BX_STATIC_ASSERT(TextureFormat::Count == BX_COUNTOF(s_textureFormat) );

	int32_t s_msaa[] =
	{
		 1,
		 2,
		 4,
		 8,
		16,
	};

	static UniformType::Enum convertMtlType(MTLDataType _type)
	{
		switch (_type)
		{
		case MTLDataTypeUInt:
		case MTLDataTypeInt:
			return UniformType::Sampler;

		case MTLDataTypeFloat:
		case MTLDataTypeFloat2:
		case MTLDataTypeFloat3:
		case MTLDataTypeFloat4:
			return UniformType::Vec4;

		case MTLDataTypeFloat3x3:
			return UniformType::Mat3;

		case MTLDataTypeFloat4x4:
			return UniformType::Mat4;

		default:
			break;
		};

		BX_ASSERT(false, "Unrecognized Mtl Data type 0x%04x.", _type);
		return UniformType::End;
	}

	static uint64_t getRegistryId(id<MTLDevice> _device)
	{
		return [_device respondsToSelector: @selector(registryID)] ? _device.registryID : 0;
	}

#if BX_PLATFORM_OSX
	static uint32_t getEntryProperty(io_registry_entry_t _entry, CFStringRef _propertyName)
	{
		uint32_t result = 0;

		CFTypeRef typeRef = IORegistryEntrySearchCFProperty(
			  _entry
			, kIOServicePlane
			, _propertyName
			, kCFAllocatorDefault
			, kIORegistryIterateRecursively | kIORegistryIterateParents
			);

		if (NULL != typeRef)
		{
			const uint32_t* value = (const uint32_t*)(CFDataGetBytePtr( (CFDataRef)typeRef) );
			if (NULL != value)
			{
				result = *value;
			}

			CFRelease(typeRef);
		}

		return result;
	}
#endif // BX_PLATFORM_OSX


static const char* s_accessNames[] = {
	"Access::Read",
	"Access::Write",
	"Access::ReadWrite",
};

BX_STATIC_ASSERT(BX_COUNTOF(s_accessNames) == Access::Count, "Invalid s_accessNames count");

#define SHADER_FUNCTION_NAME ("xlatMtlMain")
#define SHADER_UNIFORM_NAME  ("_mtl_u")

	struct RendererContextMtl;
	static RendererContextMtl* s_renderMtl;

	struct RendererContextMtl : public RendererContextI
	{
		RendererContextMtl()
			: m_bufferIndex(0)
			, m_numWindows(0)
			, m_rtMsaa(false)
			, m_capture(NULL)
			, m_captureSize(0)
		{
			bx::memSet(&m_windows, 0xff, sizeof(m_windows) );
		}

		~RendererContextMtl()
		{
		}

		bool init(const Init& _init)
		{
			BX_UNUSED(_init);
			BX_TRACE("Init.");

			m_fbh.idx = kInvalidHandle;
			bx::memSet(m_uniforms, 0, sizeof(m_uniforms) );
			bx::memSet(&m_resolution, 0, sizeof(m_resolution) );

			m_device = (id<MTLDevice>)g_platformData.context;

			if (NULL == m_device)
			{
				m_device = MTLCreateSystemDefaultDevice();
			}

			if (NULL == m_device)
			{
				BX_WARN(NULL != m_device, "Unable to create Metal device.");
				return false;
			}

			retain(m_device);

			m_mainFrameBuffer.create(
				  0
				, g_platformData.nwh
				, _init.resolution.width
				, _init.resolution.height
				, TextureFormat::Unknown
				, TextureFormat::UnknownDepth
				);
			m_numWindows = 1;

			if (NULL == m_mainFrameBuffer.m_swapChain->m_metalLayer)
			{
				release(m_device);
				return false;
			}

			m_cmd.init(m_device);
			BGFX_FATAL(NULL != m_cmd.m_commandQueue, Fatal::UnableToInitialize, "Unable to create Metal device.");

			m_renderPipelineDescriptor   = newRenderPipelineDescriptor();
			m_depthStencilDescriptor     = newDepthStencilDescriptor();
			m_frontFaceStencilDescriptor = newStencilDescriptor();
			m_backFaceStencilDescriptor  = newStencilDescriptor();
			m_vertexDescriptor  = newVertexDescriptor();
			m_textureDescriptor = newTextureDescriptor();
			m_samplerDescriptor = newSamplerDescriptor();

			for (uint8_t ii = 0; ii < BGFX_CONFIG_MAX_FRAME_LATENCY; ++ii)
			{
				m_uniformBuffers[ii] = m_device.newBufferWithLength(UNIFORM_BUFFER_SIZE, 0);
			}

			m_uniformBufferVertexOffset   = 0;
			m_uniformBufferFragmentOffset = 0;

			const char* vshSource =
				"using namespace metal;\n"
				"struct xlatMtlShaderOutput { float4 gl_Position [[position]]; float2 v_texcoord0; }; \n"
				"vertex xlatMtlShaderOutput xlatMtlMain (uint v_id [[ vertex_id ]]) \n"
				"{\n"
				"   xlatMtlShaderOutput _mtl_o;\n"
				"   if (v_id==0) { _mtl_o.gl_Position = float4(-1.0,-1.0,0.0,1.0); _mtl_o.v_texcoord0 = float2(0.0,1.0); } \n"
				"   else if (v_id==1) { _mtl_o.gl_Position = float4(3.0,-1.0,0.0,1.0); _mtl_o.v_texcoord0 = float2(2.0,1.0); } \n"
				"   else { _mtl_o.gl_Position = float4(-1.0,3.0,0.0,1.0); _mtl_o.v_texcoord0 = float2(0.0,-1.0); }\n"
				"   return _mtl_o;\n"
				"}\n"
				;

			 const char* fshSource =
				"using namespace metal;\n"
				"struct xlatMtlShaderInput { float2 v_texcoord0; };\n"
				"fragment half4 xlatMtlMain (xlatMtlShaderInput _mtl_i[[stage_in]], texture2d<float> s_texColor [[texture(0)]], sampler _mtlsmp_s_texColor [[sampler(0)]] )\n"
				"{\n"
				"   return half4(s_texColor.sample(_mtlsmp_s_texColor, _mtl_i.v_texcoord0) );\n"
				"}\n"
				;

			Library lib = m_device.newLibraryWithSource(vshSource);
			if (NULL != lib)
			{
				m_screenshotBlitProgramVsh.m_function = lib.newFunctionWithName(SHADER_FUNCTION_NAME);
				release(lib);
			}

			lib = m_device.newLibraryWithSource(fshSource);
			if (NULL != lib)
			{
				m_screenshotBlitProgramFsh.m_function = lib.newFunctionWithName(SHADER_FUNCTION_NAME);
				release(lib);
			}

			m_screenshotBlitProgram.create(&m_screenshotBlitProgramVsh, &m_screenshotBlitProgramFsh);

			reset(m_renderPipelineDescriptor);
			m_renderPipelineDescriptor.colorAttachments[0].pixelFormat = m_mainFrameBuffer.m_swapChain->m_metalLayer.pixelFormat;
			m_renderPipelineDescriptor.vertexFunction   = m_screenshotBlitProgram.m_vsh->m_function;
			m_renderPipelineDescriptor.fragmentFunction = m_screenshotBlitProgram.m_fsh->m_function;
			m_screenshotBlitRenderPipelineState         = m_device.newRenderPipelineStateWithDescriptor(m_renderPipelineDescriptor);

			{
				if ([m_device respondsToSelector: @selector(supportsFamily:)])
				{
					if ([m_device supportsFamily: MTLGPUFamily(1004) /*MTLGPUFamilyApple4*/])
					{
						g_caps.vendorId = BGFX_PCI_ID_APPLE;

						if ([m_device supportsFamily: MTLGPUFamily(1007) /*MTLGPUFamilyApple7*/])
						{
							g_caps.deviceId = 1007;
						}
						else if ([m_device supportsFamily: MTLGPUFamily(1006) /*MTLGPUFamilyApple6*/])
						{
							g_caps.deviceId = 1006;
						}
						else if ([m_device supportsFamily: MTLGPUFamily(1005) /*MTLGPUFamilyApple5*/])
						{
							g_caps.deviceId = 1005;
						}
						else
						{
							g_caps.deviceId = 1004;
						}
					}
				}

#if BX_PLATFORM_OSX
				if (0 == g_caps.vendorId)
				{
					io_registry_entry_t entry;

					uint64_t registryId = getRegistryId(m_device);

					if (0 != registryId)
					{
						entry = IOServiceGetMatchingService(mach_port_t(NULL), IORegistryEntryIDMatching(registryId) );

						if (0 != entry)
						{
							io_registry_entry_t parent;

							if (kIOReturnSuccess == IORegistryEntryGetParentEntry(entry, kIOServicePlane, &parent) )
							{
								g_caps.vendorId = getEntryProperty(parent, CFSTR("vendor-id") );
								g_caps.deviceId = getEntryProperty(parent, CFSTR("device-id") );

								IOObjectRelease(parent);
							}

							IOObjectRelease(entry);
						}
					}
				}
#endif // BX_PLATFORM_OSX
			}

			g_caps.numGPUs = 1;
			g_caps.gpu[0].vendorId = g_caps.vendorId;
			g_caps.gpu[0].deviceId = g_caps.deviceId;

			g_caps.supported |= (0
				| BGFX_CAPS_ALPHA_TO_COVERAGE
				| BGFX_CAPS_BLEND_INDEPENDENT
				| BGFX_CAPS_COMPUTE
				| BGFX_CAPS_FRAGMENT_DEPTH
				| BGFX_CAPS_INDEX32
				| BGFX_CAPS_INSTANCING
				| BGFX_CAPS_OCCLUSION_QUERY
				| BGFX_CAPS_SWAP_CHAIN
				| BGFX_CAPS_TEXTURE_2D_ARRAY
				| BGFX_CAPS_TEXTURE_3D
				| BGFX_CAPS_TEXTURE_BLIT
				| BGFX_CAPS_TEXTURE_COMPARE_ALL
				| BGFX_CAPS_TEXTURE_COMPARE_LEQUAL
				| BGFX_CAPS_TEXTURE_READ_BACK
				| BGFX_CAPS_VERTEX_ATTRIB_HALF
				| BGFX_CAPS_VERTEX_ATTRIB_UINT10
				| BGFX_CAPS_VERTEX_ID
				);

			if (BX_ENABLED(BX_PLATFORM_IOS) )
			{
				if (iOSVersionEqualOrGreater("9.0.0") )
				{
					g_caps.limits.maxTextureSize = m_device.supportsFeatureSet( (MTLFeatureSet)4 /* iOS_GPUFamily3_v1 */) ? 16384 : 8192;
				}
				else
				{
					g_caps.limits.maxTextureSize = 4096;
				}

				g_caps.limits.maxFBAttachments = uint8_t(bx::uint32_min(m_device.supportsFeatureSet( (MTLFeatureSet)1 /* MTLFeatureSet_iOS_GPUFamily2_v1 */) ? 8 : 4, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS) );

				g_caps.supported |= m_device.supportsFeatureSet( (MTLFeatureSet)4 /* MTLFeatureSet_iOS_GPUFamily3_v1 */)
					? BGFX_CAPS_DRAW_INDIRECT
					: 0
					;

				g_caps.supported |= m_device.supportsFeatureSet( (MTLFeatureSet)11 /* MTLFeatureSet_iOS_GPUFamily4_v1 */)
					? BGFX_CAPS_TEXTURE_CUBE_ARRAY
					: 0
					;
			}
			else if (BX_ENABLED(BX_PLATFORM_OSX) )
			{
				g_caps.limits.maxTextureSize   = 16384;
				g_caps.limits.maxFBAttachments = 8;
				g_caps.supported |= BGFX_CAPS_TEXTURE_CUBE_ARRAY;

				g_caps.supported |= m_device.supportsFeatureSet( (MTLFeatureSet)10001 /* MTLFeatureSet_macOS_GPUFamily1_v2 */)
					? BGFX_CAPS_DRAW_INDIRECT
					: 0
					;
			}

			g_caps.limits.maxTextureLayers = 2048;
			g_caps.limits.maxVertexStreams = BGFX_CONFIG_MAX_VERTEX_STREAMS;
			// Maximum number of entries in the buffer argument table, per graphics or compute function are 31.
			// It is decremented by 1 because 1 entry is used for uniforms.
			g_caps.limits.maxComputeBindings = bx::uint32_min(30, BGFX_MAX_COMPUTE_BINDINGS);

			m_hasPixelFormatDepth32Float_Stencil8 = false
				||  BX_ENABLED(BX_PLATFORM_OSX)
				|| (BX_ENABLED(BX_PLATFORM_IOS) && iOSVersionEqualOrGreater("9.0.0") )
				;

			m_hasStoreActionStoreAndMultisampleResolve = false
				|| (BX_ENABLED(BX_PLATFORM_OSX) && macOSVersionEqualOrGreater(10, 12, 0) )
				|| (BX_ENABLED(BX_PLATFORM_IOS) && iOSVersionEqualOrGreater("10.0.0") )
				;

			m_macOS11Runtime = true
				&& BX_ENABLED(BX_PLATFORM_OSX)
				&& macOSVersionEqualOrGreater(10, 11, 0)
				;

			m_iOS9Runtime = true
				&& BX_ENABLED(BX_PLATFORM_IOS)
				&& iOSVersionEqualOrGreater("9.0.0")
				;

			if (BX_ENABLED(BX_PLATFORM_OSX) )
			{
				s_textureFormat[TextureFormat::R8].m_fmtSrgb  = MTLPixelFormatInvalid;
				s_textureFormat[TextureFormat::RG8].m_fmtSrgb = MTLPixelFormatInvalid;
			}

			const MTLReadWriteTextureTier rwTier = [m_device readWriteTextureSupport];
			g_caps.supported |= rwTier != MTLReadWriteTextureTierNone
				? BGFX_CAPS_IMAGE_RW
				: 0
				;

			for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
			{
				uint16_t support = 0;

				support |= MTLPixelFormatInvalid != s_textureFormat[ii].m_fmt
					? BGFX_CAPS_FORMAT_TEXTURE_2D
					| BGFX_CAPS_FORMAT_TEXTURE_3D
					| BGFX_CAPS_FORMAT_TEXTURE_CUBE
					| BGFX_CAPS_FORMAT_TEXTURE_VERTEX
					: BGFX_CAPS_FORMAT_TEXTURE_NONE
					;

				support |= MTLPixelFormatInvalid != s_textureFormat[ii].m_fmtSrgb
					? BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB
					| BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB
					| BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB
					| BGFX_CAPS_FORMAT_TEXTURE_VERTEX
					: BGFX_CAPS_FORMAT_TEXTURE_NONE
					;

				if (!bimg::isCompressed(bimg::TextureFormat::Enum(ii) ) )
				{
					support |= 0
						| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
						| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
						;
				}

				support |= true
						&& s_textureFormat[ii].m_rwTier != MTLReadWriteTextureTierNone
						&& s_textureFormat[ii].m_rwTier <= rwTier
						? BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ
						| BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE
						: BGFX_CAPS_FORMAT_TEXTURE_NONE
						;

				support |= s_textureFormat[ii].m_autoGetMipmap
						? BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN
						: 0
						;

				g_caps.formats[ii] = support;
			}

			g_caps.formats[TextureFormat::A8     ] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER | BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			g_caps.formats[TextureFormat::RG32I  ] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			g_caps.formats[TextureFormat::RG32U  ] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			g_caps.formats[TextureFormat::RGBA32I] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			g_caps.formats[TextureFormat::RGBA32U] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);

			if (BX_ENABLED(BX_PLATFORM_IOS) )
			{
				s_textureFormat[TextureFormat::D24S8].m_fmt = MTLPixelFormatDepth32Float_Stencil8;

				g_caps.formats[TextureFormat::BC1 ] =
				g_caps.formats[TextureFormat::BC2 ] =
				g_caps.formats[TextureFormat::BC3 ] =
				g_caps.formats[TextureFormat::BC4 ] =
				g_caps.formats[TextureFormat::BC5 ] =
				g_caps.formats[TextureFormat::BC6H] =
				g_caps.formats[TextureFormat::BC7 ] = BGFX_CAPS_FORMAT_TEXTURE_NONE;

				g_caps.formats[TextureFormat::RG32F  ] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
				g_caps.formats[TextureFormat::RGBA32F] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			}

			if (BX_ENABLED(BX_PLATFORM_OSX) )
			{
				s_textureFormat[TextureFormat::D24S8].m_fmt = (MTLPixelFormat)(m_device.depth24Stencil8PixelFormatSupported()
					? 255 /* Depth24Unorm_Stencil8 */
					: MTLPixelFormatDepth32Float_Stencil8)
					;

				g_caps.formats[TextureFormat::ETC2  ] =
				g_caps.formats[TextureFormat::ETC2A ] =
				g_caps.formats[TextureFormat::ETC2A1] =
				g_caps.formats[TextureFormat::PTC12 ] =
				g_caps.formats[TextureFormat::PTC14 ] =
				g_caps.formats[TextureFormat::PTC12A] =
				g_caps.formats[TextureFormat::PTC14A] =
				g_caps.formats[TextureFormat::R5G6B5] =
				g_caps.formats[TextureFormat::RGBA4 ] =
				g_caps.formats[TextureFormat::RGB5A1] = BGFX_CAPS_FORMAT_TEXTURE_NONE;

				g_caps.formats[TextureFormat::RGB9E5F] &= ~(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER | BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA);
			}

			for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
			{
				if (BGFX_CAPS_FORMAT_TEXTURE_NONE == g_caps.formats[ii])
				{
					s_textureFormat[ii].m_fmt     = MTLPixelFormatInvalid;
					s_textureFormat[ii].m_fmtSrgb = MTLPixelFormatInvalid;
				}
			}

			for (uint32_t ii = 1, last = 0; ii < BX_COUNTOF(s_msaa); ++ii)
			{
				const int32_t sampleCount = 1<<ii;
				if (m_device.supportsTextureSampleCount(sampleCount) )
				{
					s_msaa[ii] = sampleCount;
					last = ii;
				}
				else
				{
					s_msaa[ii] = s_msaa[last];
				}
			}

			// Init reserved part of view name.
			for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
			{
				bx::snprintf(s_viewName[ii], BGFX_CONFIG_MAX_VIEW_NAME_RESERVED+1, "%3d   ", ii);
			}

			m_occlusionQuery.preReset();
			m_gpuTimer.init();

			g_internalData.context = m_device;

			return true;
		}

		void shutdown()
		{
			m_occlusionQuery.postReset();
			m_gpuTimer.shutdown();

			m_pipelineStateCache.invalidate();
			m_pipelineProgram.clear();

			m_depthStencilStateCache.invalidate();
			m_samplerStateCache.invalidate();

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_shaders); ++ii)
			{
				m_shaders[ii].destroy();
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_textures); ++ii)
			{
				m_textures[ii].destroy();
			}

			m_screenshotBlitProgramVsh.destroy();
			m_screenshotBlitProgramFsh.destroy();
			m_screenshotBlitProgram.destroy();
			MTL_RELEASE(m_screenshotBlitRenderPipelineState);

			captureFinish();

			MTL_RELEASE(m_depthStencilDescriptor);
			MTL_RELEASE(m_frontFaceStencilDescriptor);
			MTL_RELEASE(m_backFaceStencilDescriptor);
			MTL_RELEASE(m_renderPipelineDescriptor);
			MTL_RELEASE(m_vertexDescriptor);
			MTL_RELEASE(m_textureDescriptor);
			MTL_RELEASE(m_samplerDescriptor);

			m_mainFrameBuffer.destroy();

			for (uint8_t i=0; i < BGFX_CONFIG_MAX_FRAME_LATENCY; ++i)
			{
				MTL_RELEASE(m_uniformBuffers[i]);
			}
			m_cmd.shutdown();
			MTL_RELEASE(m_device);
		}

		RendererType::Enum getRendererType() const override
		{
			return RendererType::Metal;
		}

		const char* getRendererName() const override
		{
			return BGFX_RENDERER_METAL_NAME;
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
			for (PipelineProgramArray::iterator it = m_pipelineProgram.begin(); it != m_pipelineProgram.end();)
			{
				if (it->program.idx == _handle.idx)
				{
					m_pipelineStateCache.invalidate(it->key);
					it = m_pipelineProgram.erase(it);
				}
				else
				{
					++it;
				}
			}

			m_program[_handle.idx].destroy();
		}

		void* createTexture(TextureHandle _handle, const Memory* _mem, uint64_t _flags, uint8_t _skip) override
		{
			m_textures[_handle.idx].create(_mem, _flags, _skip);
			return NULL;
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
			const TextureMtl& texture = m_textures[_handle.idx];

#if BX_PLATFORM_OSX
			BlitCommandEncoder bce = s_renderMtl->getBlitCommandEncoder();
			bce.synchronizeTexture(texture.m_ptr, 0, _mip);
			endEncoding();
#endif  // BX_PLATFORM_OSX

			m_cmd.kick(false, true);
			m_commandBuffer = m_cmd.alloc();

			BX_ASSERT(_mip<texture.m_numMips,"Invalid mip: %d num mips:",_mip,texture.m_numMips);

			uint32_t srcWidth  = bx::uint32_max(1, texture.m_ptr.width()  >> _mip);
			uint32_t srcHeight = bx::uint32_max(1, texture.m_ptr.height() >> _mip);
			const uint8_t bpp  = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(texture.m_textureFormat) );

			MTLRegion region =
			{
				{        0,         0, 0 },
				{ srcWidth, srcHeight, 1 },
			};

			texture.m_ptr.getBytes(_data, srcWidth*bpp/8, 0, region, _mip, 0);
		}

		void resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, uint16_t _numLayers) override
		{
			TextureMtl& texture = m_textures[_handle.idx];

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

			texture.destroy();
			texture.create(mem, texture.m_flags, 0);

			release(mem);
		}

		void overrideInternal(TextureHandle _handle, uintptr_t _ptr) override
		{
			m_textures[_handle.idx].overrideInternal(_ptr);
		}

		uintptr_t getInternal(TextureHandle _handle) override
		{
			return uintptr_t(id<MTLTexture>(m_textures[_handle.idx].m_ptr) );
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

			uint16_t denseIdx   = m_numWindows++;
			m_windows[denseIdx] = _handle;

			FrameBufferMtl& fb = m_frameBuffers[_handle.idx];
			fb.create(denseIdx, _nwh, _width, _height, _format, _depthFormat);
			fb.m_swapChain->resize(m_frameBuffers[_handle.idx], _width, _height, m_resolution.reset, m_resolution.maxFrameLatency);
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
			BX_UNUSED(_handle);

			if (NULL == m_screenshotTarget)
			{
				return;
			}

#if BX_PLATFORM_OSX
            m_blitCommandEncoder = getBlitCommandEncoder();
            m_blitCommandEncoder.synchronizeResource(m_screenshotTarget);
            m_blitCommandEncoder.endEncoding();
            m_blitCommandEncoder = 0;
#endif  // BX_PLATFORM_OSX

			m_cmd.kick(false, true);
			m_commandBuffer = 0;

			uint32_t width  = m_screenshotTarget.width();
			uint32_t height = m_screenshotTarget.height();
			uint32_t length = width*height*4;
			uint8_t* data = (uint8_t*)BX_ALLOC(g_allocator, length);

			MTLRegion region = { { 0, 0, 0 }, { width, height, 1 } };

			m_screenshotTarget.getBytes(data, 4*width, 0, region, 0, 0);

			g_callback->screenShot(
				  _filePath
				, m_screenshotTarget.width()
				, m_screenshotTarget.height()
				, width*4
				, data
				, length
				, false
				);

			BX_FREE(g_allocator, data);

			m_commandBuffer = m_cmd.alloc();
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
			BX_UNUSED(_len);

			if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
			{
				m_renderCommandEncoder.insertDebugSignpost(_marker);
			}
		}

		virtual void setName(Handle _handle, const char* _name, uint16_t _len) override
		{
			BX_UNUSED(_len);

			switch (_handle.type)
			{
			case Handle::IndexBuffer:
				m_indexBuffers[_handle.idx].m_ptr.setLabel(_name);
				break;

			case Handle::Shader:
				m_shaders[_handle.idx].m_function.setLabel(_name);
				break;

			case Handle::Texture:
				m_textures[_handle.idx].m_ptr.setLabel(_name);
				break;

			case Handle::VertexBuffer:
				m_vertexBuffers[_handle.idx].m_ptr.setLabel(_name);
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
			BX_UNUSED(_blitter);
		}

		void blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices) override
		{
			const uint32_t numVertices = _numIndices*4/6;
			if (0 < numVertices)
			{
				m_indexBuffers [_blitter.m_ib->handle.idx].update(
					  0
					, bx::strideAlign(_numIndices*2, 4)
					, _blitter.m_ib->data
					, true
					);
				m_vertexBuffers[_blitter.m_vb->handle.idx].update(
					  0
					, numVertices*_blitter.m_layout.m_stride
					, _blitter.m_vb->data
					, true
					);

				endEncoding();

				uint32_t width  = m_resolution.width;
				uint32_t height = m_resolution.height;

				FrameBufferHandle fbh = BGFX_INVALID_HANDLE;

				RenderPassDescriptor renderPassDescriptor = newRenderPassDescriptor();

				setFrameBuffer(renderPassDescriptor, fbh);

				renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionLoad;
				renderPassDescriptor.colorAttachments[0].storeAction =
				NULL != renderPassDescriptor.colorAttachments[0].resolveTexture
				? MTLStoreActionMultisampleResolve
				: MTLStoreActionStore
				;

				RenderCommandEncoder rce = m_commandBuffer.renderCommandEncoderWithDescriptor(renderPassDescriptor);
				m_renderCommandEncoder = rce;
				m_renderCommandEncoderFrameBufferHandle = fbh;
				MTL_RELEASE(renderPassDescriptor);

				MTLViewport viewport = { 0.0f, 0.0f, (float)width, (float)height, 0.0f, 1.0f};
				rce.setViewport(viewport);
				MTLScissorRect rc = { 0,0,width,height };
				rce.setScissorRect(rc);
				rce.setCullMode(MTLCullModeNone);

				uint64_t state = 0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_DEPTH_TEST_ALWAYS
				;

				setDepthStencilState(state);

				PipelineStateMtl* pso = getPipelineState(
														 state
														 , 0
														 , fbh
														 , _blitter.m_vb->layoutHandle
														 , _blitter.m_program
														 , 0
														 );
				rce.setRenderPipelineState(pso->m_rps);

				const uint32_t vertexUniformBufferSize   = pso->m_vshConstantBufferSize;
				const uint32_t fragmentUniformBufferSize = pso->m_fshConstantBufferSize;

				if (vertexUniformBufferSize)
				{
					m_uniformBufferVertexOffset = bx::alignUp(
						  m_uniformBufferVertexOffset
						, pso->m_vshConstantBufferAlignment
						);
					rce.setVertexBuffer(m_uniformBuffer, m_uniformBufferVertexOffset, 0);
				}

				m_uniformBufferFragmentOffset = m_uniformBufferVertexOffset + vertexUniformBufferSize;

				if (0 != fragmentUniformBufferSize)
				{
					m_uniformBufferFragmentOffset = bx::alignUp(
						  m_uniformBufferFragmentOffset
						, pso->m_fshConstantBufferAlignment
						);
					rce.setFragmentBuffer(m_uniformBuffer, m_uniformBufferFragmentOffset, 0);
				}

				float proj[16];
				bx::mtxOrtho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f, 0.0f, false);

				PredefinedUniform& predefined = pso->m_predefined[0];
				uint8_t flags = predefined.m_type;
				setShaderUniform(flags, predefined.m_loc, proj, 4);

				m_textures[_blitter.m_texture.idx].commit(0, false, true);

				VertexBufferMtl& vb = m_vertexBuffers[_blitter.m_vb->handle.idx];
				m_renderCommandEncoder.setVertexBuffer(vb.m_ptr, 0, 1);

				m_renderCommandEncoder.drawIndexedPrimitives(
					  MTLPrimitiveTypeTriangle
					, _numIndices
					, MTLIndexTypeUInt16
					, m_indexBuffers[_blitter.m_ib->handle.idx].m_ptr
					, 0
					, 1
					);
			}
		}

		bool isDeviceRemoved() override
		{
			return false;
		}

		void flip() override
		{
			if (NULL == m_commandBuffer)
			{
				return;
			}

			for (uint32_t ii = 0, num = m_numWindows; ii < num; ++ii)
			{
				FrameBufferMtl& frameBuffer = ii == 0 ? m_mainFrameBuffer : m_frameBuffers[m_windows[ii].idx];
				if (NULL != frameBuffer.m_swapChain
				&&  frameBuffer.m_swapChain->m_drawableTexture)
				{
					MTL_RELEASE(frameBuffer.m_swapChain->m_drawableTexture);

					if (NULL != frameBuffer.m_swapChain->m_drawable)
					{
						m_commandBuffer.presentDrawable(frameBuffer.m_swapChain->m_drawable);
						MTL_RELEASE(frameBuffer.m_swapChain->m_drawable);
					}
				}
			}

			m_cmd.kick(true);
			m_commandBuffer = 0;
		}

		void updateResolution(const Resolution& _resolution)
		{
			m_mainFrameBuffer.m_swapChain->m_maxAnisotropy = !!(_resolution.reset & BGFX_RESET_MAXANISOTROPY)
				? 16
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
				MTLPixelFormat prevMetalLayerPixelFormat = m_mainFrameBuffer.m_swapChain->m_metalLayer.pixelFormat;

				m_resolution = _resolution;

				if (m_resolution.reset & BGFX_RESET_INTERNAL_FORCE
				&& m_mainFrameBuffer.m_swapChain->m_nwh != g_platformData.nwh)
				{
					m_mainFrameBuffer.m_swapChain->init(g_platformData.nwh);
				}
				m_resolution.reset &= ~BGFX_RESET_INTERNAL_FORCE;

				m_mainFrameBuffer.m_swapChain->resize(m_mainFrameBuffer, _resolution.width, _resolution.height, _resolution.reset, m_resolution.maxFrameLatency);

				for (uint32_t ii = 0; ii < BX_COUNTOF(m_frameBuffers); ++ii)
				{
					m_frameBuffers[ii].postReset();
				}

				updateCapture();

				m_textVideoMem.resize(false, _resolution.width, _resolution.height);
				m_textVideoMem.clear();

				if (prevMetalLayerPixelFormat != m_mainFrameBuffer.m_swapChain->m_metalLayer.pixelFormat)
				{
					MTL_RELEASE(m_screenshotBlitRenderPipelineState)
					reset(m_renderPipelineDescriptor);

					m_renderPipelineDescriptor.colorAttachments[0].pixelFormat = m_mainFrameBuffer.m_swapChain->m_metalLayer.pixelFormat;
					m_renderPipelineDescriptor.vertexFunction   = m_screenshotBlitProgram.m_vsh->m_function;
					m_renderPipelineDescriptor.fragmentFunction = m_screenshotBlitProgram.m_fsh->m_function;
					m_screenshotBlitRenderPipelineState = m_device.newRenderPipelineStateWithDescriptor(m_renderPipelineDescriptor);
				}
			}
		}

		void invalidateCompute()
		{
			if (m_computeCommandEncoder)
			{
				m_computeCommandEncoder.endEncoding();
				m_computeCommandEncoder = NULL;
			}
		}

		void updateCapture()
		{
			if (m_resolution.reset&BGFX_RESET_CAPTURE)
			{
				m_captureSize = m_resolution.width*m_resolution.height*4;
				m_capture = BX_REALLOC(g_allocator, m_capture, m_captureSize);
				g_callback->captureBegin(m_resolution.width, m_resolution.height, m_resolution.width*4, TextureFormat::BGRA8, false);
			}
			else
			{
				captureFinish();
			}
		}

		void capture()
		{
			if (NULL != m_capture)
			{
				if (NULL == m_screenshotTarget)
				{
					return;
				}

				m_renderCommandEncoder.endEncoding();

				m_cmd.kick(false, true);
				m_commandBuffer = 0;

				MTLRegion region = { { 0, 0, 0 }, { m_resolution.width, m_resolution.height, 1 } };

				m_screenshotTarget.getBytes(m_capture, 4*m_resolution.width, 0, region, 0, 0);

				m_commandBuffer = m_cmd.alloc();

				if (m_screenshotTarget.pixelFormat() == MTLPixelFormatRGBA8Uint)
				{
					bimg::imageSwizzleBgra8(
						  m_capture
						, m_resolution.width*4
						, m_resolution.width
						, m_resolution.height
						, m_capture
						, m_resolution.width*4
						);
				}

				g_callback->captureFrame(m_capture, m_captureSize);

				RenderPassDescriptor renderPassDescriptor = newRenderPassDescriptor();
				setFrameBuffer(renderPassDescriptor, m_renderCommandEncoderFrameBufferHandle);

				for (uint32_t ii = 0; ii < g_caps.limits.maxFBAttachments; ++ii)
				{
					MTLRenderPassColorAttachmentDescriptor* desc = renderPassDescriptor.colorAttachments[ii];

					if (NULL != desc.texture)
					{
						desc.loadAction  = MTLLoadActionLoad;
						desc.storeAction = desc.resolveTexture == nil
							? MTLStoreActionStore
							: MTLStoreActionMultisampleResolve
							;
					}
				}

				RenderPassDepthAttachmentDescriptor depthAttachment = renderPassDescriptor.depthAttachment;

				if (NULL != depthAttachment.texture)
				{
					depthAttachment.loadAction  = MTLLoadActionLoad;
					depthAttachment.storeAction = depthAttachment.resolveTexture == nil
						? MTLStoreActionStore
						: MTLStoreActionMultisampleResolve
						;
				}

				RenderPassStencilAttachmentDescriptor stencilAttachment = renderPassDescriptor.stencilAttachment;

				if (NULL != stencilAttachment.texture)
				{
					stencilAttachment.loadAction  = MTLLoadActionLoad;
					stencilAttachment.storeAction = stencilAttachment.resolveTexture == nil
						? MTLStoreActionStore
						: MTLStoreActionMultisampleResolve
						;
				}

				m_renderCommandEncoder = m_commandBuffer.renderCommandEncoderWithDescriptor(renderPassDescriptor);
				MTL_RELEASE(renderPassDescriptor);
			}
		}

		void captureFinish()
		{
			if (NULL != m_capture)
			{
				g_callback->captureEnd();
				BX_FREE(g_allocator, m_capture);
				m_capture     = NULL;
				m_captureSize = 0;
			}
		}


		void setShaderUniform(uint8_t _flags, uint32_t _loc, const void* _val, uint32_t _numRegs)
		{
			uint32_t offset = 0 != (_flags&kUniformFragmentBit)
				? m_uniformBufferFragmentOffset
				: m_uniformBufferVertexOffset
				;
			uint8_t* dst = (uint8_t*)m_uniformBuffer.contents();
			bx::memCopy(&dst[offset + _loc], _val, _numRegs*16);
		}

		void setShaderUniform4f(uint8_t _flags, uint32_t _loc, const void* _val, uint32_t _numRegs)
		{
			setShaderUniform(_flags, _loc, _val, _numRegs);
		}

		void setShaderUniform4x4f(uint8_t _flags, uint32_t _loc, const void* _val, uint32_t _numRegs)
		{
			setShaderUniform(_flags, _loc, _val, _numRegs);
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

				switch ( (uint32_t)type)
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
				case UniformType::Sampler | kUniformFragmentBit:
				case UniformType::Vec4:
				case UniformType::Vec4 | kUniformFragmentBit:
				case UniformType::Mat4:
				case UniformType::Mat4 | kUniformFragmentBit:
					{
						setShaderUniform(uint8_t(type), loc, data, num);
					}
					break;

				case UniformType::End:
					break;

				default:
					BX_TRACE("%4d: INVALID 0x%08x, t %d, l %d, n %d, c %d", _uniformBuffer.getPos(), opcode, type, loc, num, copy);
					break;
				}
			}
		}

		void clearQuad(ClearQuad& _clearQuad, const Rect& /*_rect*/, const Clear& _clear, const float _palette[][4])
		{
			uint32_t width;
			uint32_t height;

			if (isValid(m_fbh) )
			{
				const FrameBufferMtl& fb = m_frameBuffers[m_fbh.idx];
				width  = fb.m_width;
				height = fb.m_height;
			}
			else
			{
				width  = m_resolution.width;
				height = m_resolution.height;
			}

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

			setDepthStencilState(state, stencil);

			uint32_t numMrt = 1;
			FrameBufferHandle fbh = m_fbh;
			if (isValid(fbh) && m_frameBuffers[fbh.idx].m_swapChain == NULL)
			{
				const FrameBufferMtl& fb = m_frameBuffers[fbh.idx];
				numMrt = bx::uint32_max(1, fb.m_num);
			}

			const VertexLayout* layout = &_clearQuad.m_layout;
			const PipelineStateMtl* pso = getPipelineState(
				  state
				, 0
				, fbh
				, 1
				, &layout
				, _clearQuad.m_program[numMrt-1]
				, 0
				);
			m_renderCommandEncoder.setRenderPipelineState(pso->m_rps);

			const uint32_t vertexUniformBufferSize   = pso->m_vshConstantBufferSize;
			const uint32_t fragmentUniformBufferSize = pso->m_fshConstantBufferSize;

			if (0 != vertexUniformBufferSize)
			{
				m_uniformBufferVertexOffset = bx::alignUp(
					  m_uniformBufferVertexOffset
					, pso->m_vshConstantBufferAlignment
					);
				m_renderCommandEncoder.setVertexBuffer(m_uniformBuffer, m_uniformBufferVertexOffset, 0);
			}

			m_uniformBufferFragmentOffset = m_uniformBufferVertexOffset + vertexUniformBufferSize;
			if (fragmentUniformBufferSize)
			{
				m_uniformBufferFragmentOffset = bx::alignUp(
					  m_uniformBufferFragmentOffset
					, pso->m_fshConstantBufferAlignment
					);
				m_renderCommandEncoder.setFragmentBuffer(m_uniformBuffer, m_uniformBufferFragmentOffset, 0);
			}

			float mrtClearColor[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS][4];
			float mrtClearDepth[4] = { _clear.m_depth };

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

			bx::memCopy(
				  (uint8_t*)m_uniformBuffer.contents() + m_uniformBufferVertexOffset
				, mrtClearDepth
				, bx::uint32_min(vertexUniformBufferSize, sizeof(mrtClearDepth) )
				);

			bx::memCopy(
				  (uint8_t*)m_uniformBuffer.contents() + m_uniformBufferFragmentOffset
				, mrtClearColor
				, bx::uint32_min(fragmentUniformBufferSize, sizeof(mrtClearColor) )
				);

			m_uniformBufferFragmentOffset += fragmentUniformBufferSize;
			m_uniformBufferVertexOffset    = m_uniformBufferFragmentOffset;

			const VertexBufferMtl& vb = m_vertexBuffers[_clearQuad.m_vb.idx];

			m_renderCommandEncoder.setCullMode(MTLCullModeNone);
			m_renderCommandEncoder.setVertexBuffer(vb.m_ptr, 0, 1);
			m_renderCommandEncoder.drawPrimitives(MTLPrimitiveTypeTriangleStrip, 0, 4, 1);
		}

		void setAttachment(MTLRenderPassAttachmentDescriptor* _attachmentDescriptor, const Attachment& _at, uint8_t _textureType, bool _resolve)
		{
			_attachmentDescriptor.level = _at.mip;

			if (TextureMtl::Texture3D == _textureType)
			{
				_attachmentDescriptor.depthPlane = _at.layer;
			}
			else
			{
				_attachmentDescriptor.slice = _at.layer;
			}

			if (_resolve)
			{
				_attachmentDescriptor.resolveLevel = _at.mip;

				if (TextureMtl::Texture3D == _textureType)
				{
					_attachmentDescriptor.resolveDepthPlane = _at.layer;
				}
				else
				{
					_attachmentDescriptor.resolveSlice = _at.layer;
				}
			}
		}

		void setFrameBuffer(RenderPassDescriptor _renderPassDescriptor, FrameBufferHandle _fbh, bool _msaa = true)
		{
			// reslove framebuffer
			if (isValid(m_fbh) && m_fbh.idx != _fbh.idx)
			{
				FrameBufferMtl& frameBuffer = m_frameBuffers[m_fbh.idx];
				frameBuffer.resolve();
			}
			if (!isValid(_fbh)
			||  m_frameBuffers[_fbh.idx].m_swapChain)
			{
				SwapChainMtl* swapChain = !isValid(_fbh)
					? m_mainFrameBuffer.m_swapChain
					: m_frameBuffers[_fbh.idx].m_swapChain
					;

				if (NULL != swapChain->m_backBufferColorMsaa)
				{
					_renderPassDescriptor.colorAttachments[0].texture        = swapChain->m_backBufferColorMsaa;
					_renderPassDescriptor.colorAttachments[0].resolveTexture = NULL != m_screenshotTarget
						? m_screenshotTarget.m_obj
						: swapChain->currentDrawableTexture()
						;
				}
				else
				{
					_renderPassDescriptor.colorAttachments[0].texture = NULL != m_screenshotTarget
						? m_screenshotTarget.m_obj
						: swapChain->currentDrawableTexture()
						;
				}

				_renderPassDescriptor.depthAttachment.texture   = swapChain->m_backBufferDepth;
				_renderPassDescriptor.stencilAttachment.texture = swapChain->m_backBufferStencil;
			}
			else
			{
				FrameBufferMtl& frameBuffer = m_frameBuffers[_fbh.idx];

				for (uint32_t ii = 0; ii < frameBuffer.m_num; ++ii)
				{
					const TextureMtl& texture = m_textures[frameBuffer.m_colorHandle[ii].idx];
					_renderPassDescriptor.colorAttachments[ii].texture = texture.m_ptrMsaa
						? texture.m_ptrMsaa
						: texture.m_ptr
						;
					_renderPassDescriptor.colorAttachments[ii].resolveTexture = texture.m_ptrMsaa
						? texture.m_ptr.m_obj
						: NULL
						;

					setAttachment(_renderPassDescriptor.colorAttachments[ii], frameBuffer.m_colorAttachment[ii], texture.m_type, texture.m_ptrMsaa != NULL);
				}

				if (isValid(frameBuffer.m_depthHandle) )
				{
					const TextureMtl& texture = m_textures[frameBuffer.m_depthHandle.idx];
					_renderPassDescriptor.depthAttachment.texture = texture.m_ptrMsaa
						? texture.m_ptrMsaa
						: texture.m_ptr
						;
					_renderPassDescriptor.stencilAttachment.texture = texture.m_ptrStencil;

					setAttachment(_renderPassDescriptor.depthAttachment, frameBuffer.m_depthAttachment, texture.m_type, NULL != texture.m_ptrMsaa);
					setAttachment(_renderPassDescriptor.stencilAttachment, frameBuffer.m_depthAttachment, texture.m_type, NULL != texture.m_ptrMsaa);

					if (texture.m_textureFormat == TextureFormat::D24S8)
					{
						if (texture.m_ptr.pixelFormat() == 255 /* Depth24Unorm_Stencil8 */
						||  texture.m_ptr.pixelFormat() == 260 /* Depth32Float_Stencil8 */)
						{
							_renderPassDescriptor.stencilAttachment.texture = _renderPassDescriptor.depthAttachment.texture;
						}
						else
						{
							_renderPassDescriptor.stencilAttachment.texture = texture.m_ptrMsaa
								? texture.m_ptrMsaa
								: texture.m_ptrStencil
								;
						}
					}
				}
			}

			m_fbh    = _fbh;
			m_rtMsaa = _msaa;
		}

		void setDepthStencilState(uint64_t _state, uint64_t _stencil = 0)
		{
			_state &= BGFX_STATE_WRITE_Z|BGFX_STATE_DEPTH_TEST_MASK;

			uint32_t fstencil = unpackStencil(0, _stencil);
			uint32_t ref      = (fstencil&BGFX_STENCIL_FUNC_REF_MASK)>>BGFX_STENCIL_FUNC_REF_SHIFT;

			_stencil &= packStencil(~BGFX_STENCIL_FUNC_REF_MASK, ~BGFX_STENCIL_FUNC_REF_MASK);

			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(_state);
			murmur.add(_stencil);
			uint32_t hash = murmur.end();

			DepthStencilState dss = m_depthStencilStateCache.find(hash);
			if (NULL == dss)
			{
				DepthStencilDescriptor desc = m_depthStencilDescriptor;
				uint32_t func = (_state&BGFX_STATE_DEPTH_TEST_MASK)>>BGFX_STATE_DEPTH_TEST_SHIFT;
				desc.depthWriteEnabled = !!(BGFX_STATE_WRITE_Z & _state);
				desc.depthCompareFunction = s_cmpFunc[func];

				uint32_t bstencil = unpackStencil(1, _stencil);
				uint32_t frontAndBack = bstencil != BGFX_STENCIL_NONE && bstencil != fstencil;
				bstencil = frontAndBack ? bstencil : fstencil;

				if (0 != _stencil)
				{
					StencilDescriptor frontFaceDesc = m_frontFaceStencilDescriptor;
					StencilDescriptor backfaceDesc  = m_backFaceStencilDescriptor;

					uint32_t readMask  = (fstencil&BGFX_STENCIL_FUNC_RMASK_MASK)>>BGFX_STENCIL_FUNC_RMASK_SHIFT;
					uint32_t writeMask = 0xff;

					frontFaceDesc.stencilFailureOperation   = s_stencilOp[(fstencil&BGFX_STENCIL_OP_FAIL_S_MASK)>>BGFX_STENCIL_OP_FAIL_S_SHIFT];
					frontFaceDesc.depthFailureOperation     = s_stencilOp[(fstencil&BGFX_STENCIL_OP_FAIL_Z_MASK)>>BGFX_STENCIL_OP_FAIL_Z_SHIFT];
					frontFaceDesc.depthStencilPassOperation = s_stencilOp[(fstencil&BGFX_STENCIL_OP_PASS_Z_MASK)>>BGFX_STENCIL_OP_PASS_Z_SHIFT];
					frontFaceDesc.stencilCompareFunction    = s_cmpFunc[(fstencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT];
					frontFaceDesc.readMask  = readMask;
					frontFaceDesc.writeMask = writeMask;

					backfaceDesc.stencilFailureOperation    = s_stencilOp[(bstencil&BGFX_STENCIL_OP_FAIL_S_MASK)>>BGFX_STENCIL_OP_FAIL_S_SHIFT];
					backfaceDesc.depthFailureOperation      = s_stencilOp[(bstencil&BGFX_STENCIL_OP_FAIL_Z_MASK)>>BGFX_STENCIL_OP_FAIL_Z_SHIFT];
					backfaceDesc.depthStencilPassOperation  = s_stencilOp[(bstencil&BGFX_STENCIL_OP_PASS_Z_MASK)>>BGFX_STENCIL_OP_PASS_Z_SHIFT];
					backfaceDesc.stencilCompareFunction     = s_cmpFunc[(bstencil&BGFX_STENCIL_TEST_MASK)>>BGFX_STENCIL_TEST_SHIFT];
					backfaceDesc.readMask  = readMask;
					backfaceDesc.writeMask = writeMask;

					desc.frontFaceStencil = frontFaceDesc;
					desc.backFaceStencil  = backfaceDesc;
				}
				else
				{
					desc.backFaceStencil  = NULL;
					desc.frontFaceStencil = NULL;
				}

				dss = m_device.newDepthStencilStateWithDescriptor(desc);

				m_depthStencilStateCache.add(hash, dss);
			}

			m_renderCommandEncoder.setDepthStencilState(dss);
			m_renderCommandEncoder.setStencilReferenceValue(ref);
		}

		void processArguments(
			  PipelineStateMtl* ps
			, NSArray <MTLArgument *>* _vertexArgs
			, NSArray <MTLArgument *>* _fragmentArgs
			)
		{
			ps->m_numPredefined = 0;

			for (uint32_t shaderType = 0; shaderType < 2; ++shaderType)
			{
				UniformBuffer*& constantBuffer = shaderType == 0
					? ps->m_vshConstantBuffer
					: ps->m_fshConstantBuffer
					;
				const int8_t fragmentBit = (1 == shaderType ? kUniformFragmentBit : 0);

				for (MTLArgument* arg in (shaderType == 0 ? _vertexArgs : _fragmentArgs) )
				{
					BX_TRACE("arg: %s type:%d", utf8String(arg.name), arg.type);

					if (arg.active)
					{
						if (arg.type == MTLArgumentTypeBuffer
						&&  0 == bx::strCmp(utf8String(arg.name), SHADER_UNIFORM_NAME) )
						{
							BX_ASSERT(arg.index == 0, "Uniform buffer must be in the buffer slot 0.");
							BX_ASSERT(MTLDataTypeStruct == arg.bufferDataType, "%s's type must be a struct",SHADER_UNIFORM_NAME );

							if (MTLDataTypeStruct == arg.bufferDataType)
							{
								if (shaderType == 0)
								{
									ps->m_vshConstantBufferSize = uint32_t(arg.bufferDataSize);
									ps->m_vshConstantBufferAlignment = uint32_t(arg.bufferAlignment);
								}
								else
								{
									ps->m_fshConstantBufferSize = uint32_t(arg.bufferDataSize);
									ps->m_fshConstantBufferAlignment = uint32_t(arg.bufferAlignment);
								}

								for (MTLStructMember* uniform in arg.bufferStructType.members )
								{
									const char* name = utf8String(uniform.name);
									BX_TRACE("uniform: %s type:%d", name, uniform.dataType);

									MTLDataType dataType = uniform.dataType;
									uint32_t num = 1;

									if (dataType == MTLDataTypeArray)
									{
										dataType = uniform.arrayType.elementType;
										num = (uint32_t)uniform.arrayType.arrayLength;
									}

									switch (dataType)
									{
										case MTLDataTypeFloat4:   num *= 1; break;
										case MTLDataTypeFloat4x4: num *= 4; break;
										case MTLDataTypeFloat3x3: num *= 3; break;

										default:
											BX_WARN(0, "Unsupported uniform MTLDataType: %d", uniform.dataType);
											break;
									}

									const PredefinedUniform::Enum predefined = nameToPredefinedUniformEnum(name);

									if (PredefinedUniform::Count != predefined)
									{
										ps->m_predefined[ps->m_numPredefined].m_loc   = uint32_t(uniform.offset);
										ps->m_predefined[ps->m_numPredefined].m_count = uint16_t(num);
										ps->m_predefined[ps->m_numPredefined].m_type  = uint8_t(predefined|fragmentBit);
										++ps->m_numPredefined;
									}
									else
									{
										const UniformRegInfo* info = s_renderMtl->m_uniformReg.find(name);
										BX_WARN(NULL != info, "User defined uniform '%s' is not found, it won't be set.", name);

										if (NULL != info)
										{
											if (NULL == constantBuffer)
											{
												constantBuffer = UniformBuffer::create(1024);
											}

											UniformType::Enum type = convertMtlType(dataType);
											constantBuffer->writeUniformHandle( (UniformType::Enum)(type|fragmentBit), uint32_t(uniform.offset), info->m_handle, uint16_t(num) );
											BX_TRACE("store %s %d offset:%d", name, info->m_handle, uint32_t(uniform.offset) );
										}
									}
								}
							}
						}
						else if (arg.type == MTLArgumentTypeBuffer
							 && arg.index > 0
							 && NULL != arg.bufferStructType)
						{
							const char* name = utf8String(arg.name);
							BX_UNUSED(name);

							if (arg.index >= BGFX_CONFIG_MAX_TEXTURE_SAMPLERS)
							{
								BX_TRACE(
									  "Binding index is too large %d max is %d. "
									  "User defined uniform '%s' won't be set."
									, int32_t(arg.index - 1)
									, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS - 1
									, name
									);
							}
							else
							{
								ps->m_bindingTypes[arg.index-1] = fragmentBit
									? PipelineStateMtl::BindToFragmentShader
									: PipelineStateMtl::BindToVertexShader
									;
								BX_TRACE("Buffer %s index: %d", name, int32_t(arg.index-1) );
							}
						}
						else if (arg.type == MTLArgumentTypeTexture)
						{
							const char* name = utf8String(arg.name);
							if (arg.index >= BGFX_CONFIG_MAX_TEXTURE_SAMPLERS)
							{
								BX_WARN(false, "Binding index is too large %d max is %d. User defined uniform '%s' won't be set.", int(arg.index), BGFX_CONFIG_MAX_TEXTURE_SAMPLERS - 1, name);
							}
							else
							{
								ps->m_bindingTypes[arg.index] = fragmentBit ? PipelineStateMtl::BindToFragmentShader : PipelineStateMtl::BindToVertexShader;
								const UniformRegInfo* info = s_renderMtl->m_uniformReg.find(name);
								if (info)
								{
									BX_TRACE("texture %s %d index:%d", name, info->m_handle, uint32_t(arg.index) );
								}
								else
								{
									BX_TRACE("image %s index:%d", name, uint32_t(arg.index) );
								}
							}
						}
						else if (arg.type == MTLArgumentTypeSampler)
						{
							BX_TRACE("sampler: %s index:%d", utf8String(arg.name), arg.index);
						}
					}
				}

				if (NULL != constantBuffer)
				{
					constantBuffer->finish();
				}
			}
		}

		PipelineStateMtl* getPipelineState(
			  uint64_t _state
			, uint32_t _rgba
			, FrameBufferHandle _fbh
			, uint8_t _numStreams
			, const VertexLayout** _layouts
			, ProgramHandle _program
			, uint8_t _numInstanceData
			)
		{
			_state &= (0
				| BGFX_STATE_BLEND_MASK
				| BGFX_STATE_BLEND_EQUATION_MASK
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_BLEND_INDEPENDENT
				| BGFX_STATE_MSAA
				| BGFX_STATE_BLEND_ALPHA_TO_COVERAGE
				);

			const bool independentBlendEnable = !!(BGFX_STATE_BLEND_INDEPENDENT & _state);
			const ProgramMtl& program = m_program[_program.idx];

			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(_state);
			murmur.add(independentBlendEnable ? _rgba : 0);
			murmur.add(_numInstanceData);

			if (!isValid(_fbh) )
			{
				murmur.add(m_mainFrameBuffer.m_pixelFormatHash);
			}
			else
			{
				FrameBufferMtl& frameBuffer = m_frameBuffers[_fbh.idx];
				murmur.add(frameBuffer.m_pixelFormatHash);
			}

			murmur.add(program.m_vsh->m_hash);
			if (NULL != program.m_fsh)
			{
				murmur.add(program.m_fsh->m_hash);
			}

			for (uint8_t ii = 0; ii < _numStreams; ++ii)
			{
				murmur.add(_layouts[ii]->m_hash);
			}

			uint32_t hash = murmur.end();

			PipelineStateMtl* pso = m_pipelineStateCache.find(hash);

			if (NULL == pso)
			{
				pso = BX_NEW(g_allocator, PipelineStateMtl);

				RenderPipelineDescriptor pd = m_renderPipelineDescriptor;
				reset(pd);

				pd.alphaToCoverageEnabled = !!(BGFX_STATE_BLEND_ALPHA_TO_COVERAGE & _state);

				uint32_t frameBufferAttachment = 1;

				if (!isValid(_fbh)
				||  s_renderMtl->m_frameBuffers[_fbh.idx].m_swapChain)
				{
					SwapChainMtl* swapChain = !isValid(_fbh)
						? s_renderMtl->m_mainFrameBuffer.m_swapChain
						: s_renderMtl->m_frameBuffers[_fbh.idx].m_swapChain
						;
					pd.sampleCount = NULL != swapChain->m_backBufferColorMsaa
						? swapChain->m_backBufferColorMsaa.sampleCount()
						: 1
						;
					pd.colorAttachments[0].pixelFormat = swapChain->currentDrawableTexture().pixelFormat;
					pd.depthAttachmentPixelFormat      = swapChain->m_backBufferDepth.m_obj.pixelFormat;
					pd.stencilAttachmentPixelFormat    = swapChain->m_backBufferStencil.m_obj.pixelFormat;
				}
				else
				{
					const FrameBufferMtl& frameBuffer = m_frameBuffers[_fbh.idx];
					frameBufferAttachment = frameBuffer.m_num;

					for (uint32_t ii = 0; ii < frameBuffer.m_num; ++ii)
					{
						const TextureMtl& texture = m_textures[frameBuffer.m_colorHandle[ii].idx];
						pd.sampleCount = NULL != texture.m_ptrMsaa
							? texture.m_ptrMsaa.sampleCount()
							: 1
							;
						pd.colorAttachments[ii].pixelFormat = texture.m_ptr.m_obj.pixelFormat;
					}

					if (isValid(frameBuffer.m_depthHandle) )
					{
						const TextureMtl& texture = m_textures[frameBuffer.m_depthHandle.idx];
						pd.depthAttachmentPixelFormat = texture.m_ptr.m_obj.pixelFormat;
						pd.sampleCount = NULL != texture.m_ptrMsaa
							? texture.m_ptrMsaa.sampleCount()
							: 1
							;
						if (NULL != texture.m_ptrStencil)
						{
							pd.stencilAttachmentPixelFormat = texture.m_ptrStencil.m_obj.pixelFormat;
						}
						else
						{
							if (texture.m_textureFormat == TextureFormat::D24S8)
							{
								pd.stencilAttachmentPixelFormat = texture.m_ptr.m_obj.pixelFormat;
							}
						}
					}
				}

				const uint32_t blend    = uint32_t( (_state&BGFX_STATE_BLEND_MASK         )>>BGFX_STATE_BLEND_SHIFT);
				const uint32_t equation = uint32_t( (_state&BGFX_STATE_BLEND_EQUATION_MASK)>>BGFX_STATE_BLEND_EQUATION_SHIFT);

				const uint32_t srcRGB = (blend    )&0xf;
				const uint32_t dstRGB = (blend>> 4)&0xf;
				const uint32_t srcA   = (blend>> 8)&0xf;
				const uint32_t dstA   = (blend>>12)&0xf;

				const uint32_t equRGB = (equation   )&0x7;
				const uint32_t equA   = (equation>>3)&0x7;

				uint8_t writeMask = 0;
				writeMask |= (_state&BGFX_STATE_WRITE_R) ? MTLColorWriteMaskRed   : 0;
				writeMask |= (_state&BGFX_STATE_WRITE_G) ? MTLColorWriteMaskGreen : 0;
				writeMask |= (_state&BGFX_STATE_WRITE_B) ? MTLColorWriteMaskBlue  : 0;
				writeMask |= (_state&BGFX_STATE_WRITE_A) ? MTLColorWriteMaskAlpha : 0;

				for (uint32_t ii = 0; ii < (independentBlendEnable ? 1 : frameBufferAttachment); ++ii)
				{
					RenderPipelineColorAttachmentDescriptor drt = pd.colorAttachments[ii];

					drt.blendingEnabled = !!(BGFX_STATE_BLEND_MASK & _state);

					drt.sourceRGBBlendFactor        = s_blendFactor[srcRGB][0];
					drt.destinationRGBBlendFactor   = s_blendFactor[dstRGB][0];
					drt.rgbBlendOperation           = s_blendEquation[equRGB];

					drt.sourceAlphaBlendFactor      = s_blendFactor[srcA][1];
					drt.destinationAlphaBlendFactor = s_blendFactor[dstA][1];
					drt.alphaBlendOperation         = s_blendEquation[equA];

					drt.writeMask = writeMask;
				}

				if (independentBlendEnable)
				{
					for (uint32_t ii = 1, rgba = _rgba; ii < frameBufferAttachment; ++ii, rgba >>= 11)
					{
						RenderPipelineColorAttachmentDescriptor drt = pd.colorAttachments[ii];

						drt.blendingEnabled = 0 != (rgba&0x7ff);

						const uint32_t src           = (rgba   )&0xf;
						const uint32_t dst           = (rgba>>4)&0xf;
						const uint32_t equationIndex = (rgba>>8)&0x7;

						drt.sourceRGBBlendFactor      = s_blendFactor[src][0];
						drt.destinationRGBBlendFactor = s_blendFactor[dst][0];
						drt.rgbBlendOperation         = s_blendEquation[equationIndex];

						drt.sourceAlphaBlendFactor      = s_blendFactor[src][1];
						drt.destinationAlphaBlendFactor = s_blendFactor[dst][1];
						drt.alphaBlendOperation         = s_blendEquation[equationIndex];

						drt.writeMask = writeMask;
					}
				}

				pd.vertexFunction   = program.m_vsh->m_function;
				pd.fragmentFunction = program.m_fsh != NULL ? program.m_fsh->m_function : NULL;

				VertexDescriptor vertexDesc = m_vertexDescriptor;
				reset(vertexDesc);

				bool attrSet[Attrib::Count] = {};

				uint8_t stream = 0;
				for (; stream < _numStreams; ++stream)
				{
					const VertexLayout& layout = *_layouts[stream];
					bool streamUsed = false;
					for (uint32_t ii = 0; Attrib::Count != program.m_used[ii]; ++ii)
					{
						Attrib::Enum attr = Attrib::Enum(program.m_used[ii]);
						if (attrSet[attr])
							continue;
						const uint32_t loc = program.m_attributes[attr];

						uint8_t num;
						AttribType::Enum type;
						bool normalized;
						bool asInt;
						layout.decode(attr, num, type, normalized, asInt);
						BX_ASSERT(num <= 4, "num must be <= 4");

						if (UINT16_MAX != layout.m_attributes[attr])
						{
							vertexDesc.attributes[loc].format      = s_attribType[type][num-1][normalized?1:0];
							vertexDesc.attributes[loc].bufferIndex = stream+1;
							vertexDesc.attributes[loc].offset      = layout.m_offset[attr];

							BX_TRACE("attrib: %s format: %d offset: %d", s_attribName[attr], (int)vertexDesc.attributes[loc].format, (int)vertexDesc.attributes[loc].offset);

							attrSet[attr] = true;
							streamUsed = true;
						}
					}
					if (streamUsed) {
						vertexDesc.layouts[stream+1].stride       = layout.getStride();
						vertexDesc.layouts[stream+1].stepFunction = MTLVertexStepFunctionPerVertex;
					}
				}

				for (uint32_t ii = 0; Attrib::Count != program.m_used[ii]; ++ii)
				{
					Attrib::Enum attr = Attrib::Enum(program.m_used[ii]);
					const uint32_t loc = program.m_attributes[attr];
					if (!attrSet[attr])
					{
						vertexDesc.attributes[loc].format      = MTLVertexFormatUChar2;
						vertexDesc.attributes[loc].bufferIndex = 1;
						vertexDesc.attributes[loc].offset      = 0;
					}
				}

				if (0 < _numInstanceData)
				{
					for (uint32_t ii = 0; UINT16_MAX != program.m_instanceData[ii]; ++ii)
					{
						const uint32_t loc = program.m_instanceData[ii];
						vertexDesc.attributes[loc].format      = MTLVertexFormatFloat4;
						vertexDesc.attributes[loc].bufferIndex = stream+1;
						vertexDesc.attributes[loc].offset      = ii*16;
					}

					vertexDesc.layouts[stream+1].stride       = _numInstanceData * 16;
					vertexDesc.layouts[stream+1].stepFunction = MTLVertexStepFunctionPerInstance;
					vertexDesc.layouts[stream+1].stepRate     = 1;
				}

				pd.vertexDescriptor = vertexDesc;

				{
					RenderPipelineReflection reflection = NULL;
					pso->m_rps = m_device.newRenderPipelineStateWithDescriptor(pd, MTLPipelineOptionBufferTypeInfo, &reflection);

					if (NULL != reflection)
					{
						processArguments(pso, reflection.vertexArguments, reflection.fragmentArguments);
					}
				}

				m_pipelineStateCache.add(hash, pso);
				m_pipelineProgram.push_back({hash, _program});
			}

			return pso;
		}

		PipelineStateMtl* getPipelineState(
			  uint64_t _state
			, uint32_t _rgba
			, FrameBufferHandle _fbh
			, VertexLayoutHandle _layoutHandle
			, ProgramHandle _program
			, uint16_t _numInstanceData
			)
		{
			const VertexLayout* layout = &m_vertexLayouts[_layoutHandle.idx];
			return getPipelineState(
				  _state
				, _rgba
				, _fbh
				, 1
				, &layout
				, _program
				, _numInstanceData
				);
		}

		PipelineStateMtl* getComputePipelineState(ProgramHandle _program)
		{
			ProgramMtl& program = m_program[_program.idx];

			if (NULL == program.m_computePS)
			{
				PipelineStateMtl* pso = BX_NEW(g_allocator, PipelineStateMtl);
				program.m_computePS = pso;

				ComputePipelineReflection reflection = NULL;
				pso->m_cps = m_device.newComputePipelineStateWithFunction(program.m_vsh->m_function, MTLPipelineOptionBufferTypeInfo, &reflection);
				processArguments(pso, reflection.arguments, NULL);

				for (uint32_t ii = 0; ii < 3; ++ii)
				{
					pso->m_numThreads[ii] = program.m_vsh->m_numThreads[ii];
				}
			}

			return program.m_computePS;
		}


		SamplerState getSamplerState(uint32_t _flags)
		{
			_flags &= BGFX_SAMPLER_BITS_MASK;
			SamplerState sampler = m_samplerStateCache.find(_flags);

			if (NULL == sampler)
			{
				m_samplerDescriptor.sAddressMode = s_textureAddress[(_flags&BGFX_SAMPLER_U_MASK)>>BGFX_SAMPLER_U_SHIFT];
				m_samplerDescriptor.tAddressMode = s_textureAddress[(_flags&BGFX_SAMPLER_V_MASK)>>BGFX_SAMPLER_V_SHIFT];
				m_samplerDescriptor.rAddressMode = s_textureAddress[(_flags&BGFX_SAMPLER_W_MASK)>>BGFX_SAMPLER_W_SHIFT];
				m_samplerDescriptor.minFilter    = s_textureFilterMinMag[(_flags&BGFX_SAMPLER_MIN_MASK)>>BGFX_SAMPLER_MIN_SHIFT];
				m_samplerDescriptor.magFilter    = s_textureFilterMinMag[(_flags&BGFX_SAMPLER_MAG_MASK)>>BGFX_SAMPLER_MAG_SHIFT];
				m_samplerDescriptor.mipFilter    = s_textureFilterMip[(_flags&BGFX_SAMPLER_MIP_MASK)>>BGFX_SAMPLER_MIP_SHIFT];
				m_samplerDescriptor.lodMinClamp  = 0;
				m_samplerDescriptor.lodMaxClamp  = FLT_MAX;
				m_samplerDescriptor.normalizedCoordinates = TRUE;
				m_samplerDescriptor.maxAnisotropy =  (0 != (_flags & (BGFX_SAMPLER_MIN_ANISOTROPIC|BGFX_SAMPLER_MAG_ANISOTROPIC) ) ) ? m_mainFrameBuffer.m_swapChain->m_maxAnisotropy : 1;

				if (m_macOS11Runtime
				|| [m_device supportsFeatureSet:(MTLFeatureSet)4 /*MTLFeatureSet_iOS_GPUFamily3_v1*/])
				{
					const uint32_t cmpFunc = (_flags&BGFX_SAMPLER_COMPARE_MASK)>>BGFX_SAMPLER_COMPARE_SHIFT;
					m_samplerDescriptor.compareFunction = 0 == cmpFunc
						? MTLCompareFunctionNever
						: s_cmpFunc[cmpFunc]
						;
				}

				sampler = m_device.newSamplerStateWithDescriptor(m_samplerDescriptor);
				m_samplerStateCache.add(_flags, sampler);
			}

			return sampler;
		}

		bool isVisible(Frame* _render, OcclusionQueryHandle _handle, bool _visible)
		{
			m_occlusionQuery.resolve(_render);
			return _visible == (0 != _render->m_occlusion[_handle.idx]);
		}

		BlitCommandEncoder getBlitCommandEncoder()
		{
			if (NULL == m_blitCommandEncoder)
			{
				endEncoding();

				if (NULL == m_commandBuffer)
				{
					m_commandBuffer = m_cmd.alloc();
				}

				m_blitCommandEncoder = m_commandBuffer.blitCommandEncoder();
			}

			return m_blitCommandEncoder;
		}

		void endEncoding()
		{
			if (0 != m_renderCommandEncoder)
			{
				m_renderCommandEncoder.endEncoding();
				m_renderCommandEncoder = 0;
			}

			if (0 != m_computeCommandEncoder)
			{
				m_computeCommandEncoder.endEncoding();
				m_computeCommandEncoder = 0;
			}

			if (0 != m_blitCommandEncoder)
			{
				m_blitCommandEncoder.endEncoding();
				m_blitCommandEncoder = 0;
			}
		}

		Device            m_device;
		OcclusionQueryMTL m_occlusionQuery;
		TimerQueryMtl     m_gpuTimer;
		CommandQueueMtl   m_cmd;

		bool m_iOS9Runtime;
		bool m_macOS11Runtime;
		bool m_hasPixelFormatDepth32Float_Stencil8;
		bool m_hasStoreActionStoreAndMultisampleResolve;

		Buffer   m_uniformBuffer;
		Buffer   m_uniformBuffers[BGFX_CONFIG_MAX_FRAME_LATENCY];
		uint32_t m_uniformBufferVertexOffset;
		uint32_t m_uniformBufferFragmentOffset;

		uint8_t  m_bufferIndex;

		uint16_t          m_numWindows;
		FrameBufferHandle m_windows[BGFX_CONFIG_MAX_FRAME_BUFFERS];

		IndexBufferMtl  m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBufferMtl m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		ShaderMtl       m_shaders[BGFX_CONFIG_MAX_SHADERS];
		ProgramMtl      m_program[BGFX_CONFIG_MAX_PROGRAMS];
		TextureMtl      m_textures[BGFX_CONFIG_MAX_TEXTURES];
		FrameBufferMtl  m_mainFrameBuffer;
		FrameBufferMtl  m_frameBuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		VertexLayout    m_vertexLayouts[BGFX_CONFIG_MAX_VERTEX_LAYOUTS];
		UniformRegistry m_uniformReg;
		void*           m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];

		struct PipelineProgram
		{
			uint64_t      key;
			ProgramHandle program;
		};

		typedef stl::vector<PipelineProgram> PipelineProgramArray;

		PipelineProgramArray             m_pipelineProgram;

		StateCacheT<PipelineStateMtl*> m_pipelineStateCache;
		StateCacheT<DepthStencilState> m_depthStencilStateCache;
		StateCacheT<SamplerState>      m_samplerStateCache;

		TextVideoMem m_textVideoMem;

		FrameBufferHandle m_fbh;
		bool m_rtMsaa;

		Resolution m_resolution;
		void* m_capture;
		uint32_t m_captureSize;

		// descriptors
		RenderPipelineDescriptor m_renderPipelineDescriptor;
		DepthStencilDescriptor   m_depthStencilDescriptor;
		StencilDescriptor        m_frontFaceStencilDescriptor;
		StencilDescriptor        m_backFaceStencilDescriptor;
		VertexDescriptor         m_vertexDescriptor;
		TextureDescriptor        m_textureDescriptor;
		SamplerDescriptor        m_samplerDescriptor;

		// currently active objects data
		Texture              m_screenshotTarget;
		ShaderMtl            m_screenshotBlitProgramVsh;
		ShaderMtl            m_screenshotBlitProgramFsh;
		ProgramMtl           m_screenshotBlitProgram;
		RenderPipelineState  m_screenshotBlitRenderPipelineState;

		CommandBuffer         m_commandBuffer;
		BlitCommandEncoder    m_blitCommandEncoder;
		RenderCommandEncoder  m_renderCommandEncoder;
		ComputeCommandEncoder m_computeCommandEncoder;
		FrameBufferHandle     m_renderCommandEncoderFrameBufferHandle;
	};

	RendererContextI* rendererCreate(const Init& _init)
	{
		s_renderMtl = BX_NEW(g_allocator, RendererContextMtl);
		if (!s_renderMtl->init(_init) )
		{
			BX_DELETE(g_allocator, s_renderMtl);
			s_renderMtl = NULL;
		}
		return s_renderMtl;
	}

	void rendererDestroy()
	{
		s_renderMtl->shutdown();
		BX_DELETE(g_allocator, s_renderMtl);
		s_renderMtl = NULL;
	}

	void writeString(bx::WriterI* _writer, const char* _str)
	{
		bx::write(_writer, _str, (int32_t)bx::strLen(_str), bx::ErrorAssert{});
	}

	void ShaderMtl::create(const Memory* _mem)
	{
		bx::MemoryReader reader(_mem->data, _mem->size);

		bx::ErrorAssert err;

		uint32_t magic;
		bx::read(&reader, magic, &err);

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

		BX_TRACE("%s Shader consts %d"
			, getShaderTypeName(magic)
			, count
			);

		for (uint32_t ii = 0; ii < count; ++ii)
		{
			uint8_t nameSize;
			bx::read(&reader, nameSize, &err);

			char name[256];
			bx::read(&reader, &name, nameSize, &err);
			name[nameSize] = '\0';

			uint8_t type;
			bx::read(&reader, type, &err);

			uint8_t num;
			bx::read(&reader, num, &err);

			uint16_t regIndex;
			bx::read(&reader, regIndex, &err);

			uint16_t regCount;
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
		}

		if (isShaderType(magic, 'C') )
		{
			for (uint32_t ii = 0; ii < 3; ++ii)
			{
				bx::read(&reader, m_numThreads[ii], &err);
			}
		}

		uint32_t shaderSize;
		bx::read(&reader, shaderSize, &err);

		const char* code = (const char*)reader.getDataPtr();
		bx::skip(&reader, shaderSize+1);

		Library lib = s_renderMtl->m_device.newLibraryWithSource(code);

		if (NULL != lib)
		{
			m_function = lib.newFunctionWithName(SHADER_FUNCTION_NAME);
			release(lib);
		}

		BGFX_FATAL(NULL != m_function
			, bgfx::Fatal::InvalidShader
			, "Failed to create %s shader."
			, getShaderTypeName(magic)
			);

		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(hashIn);
		murmur.add(hashOut);
		murmur.add(code, shaderSize);
//		murmur.add(numAttrs);
//		murmur.add(m_attrMask, numAttrs);
		m_hash = murmur.end();
	}

	void ProgramMtl::create(const ShaderMtl* _vsh, const ShaderMtl* _fsh)
	{
		BX_ASSERT(NULL != _vsh->m_function.m_obj, "Vertex shader doesn't exist.");
		m_vsh = _vsh;
		m_fsh = _fsh;

		// get attributes
		bx::memSet(m_attributes, 0xff, sizeof(m_attributes) );
		uint32_t used = 0;
		uint32_t instUsed = 0;
		if (NULL != _vsh->m_function.m_obj)
		{
			for (MTLVertexAttribute* attrib in _vsh->m_function.m_obj.vertexAttributes)
			{
				if (attrib.active)
				{
					const char* name = utf8String(attrib.name);
					uint32_t loc = (uint32_t)attrib.attributeIndex;
					BX_TRACE("attr %s: %d", name, loc);

					for (uint8_t ii = 0; ii < Attrib::Count; ++ii)
					{
						if (0 == bx::strCmp(s_attribName[ii],name) )
						{
							m_attributes[ii] = loc;
							m_used[used++] = ii;
							break;
						}
					}

					for (uint32_t ii = 0; ii < BX_COUNTOF(s_instanceDataName); ++ii)
					{
						if (0 == bx::strCmp(s_instanceDataName[ii],name) )
						{
							m_instanceData[instUsed++] = loc;
						}
					}

				}
			}
		}

		m_used[used] = Attrib::Count;
		m_instanceData[instUsed] = UINT16_MAX;
	}

	void ProgramMtl::destroy()
	{
		m_vsh = NULL;
		m_fsh = NULL;
		if (NULL != m_computePS)
		{
			BX_DELETE(g_allocator, m_computePS);
			m_computePS = NULL;
		}
	}

	void BufferMtl::create(uint32_t _size, void* _data, uint16_t _flags, uint16_t _stride, bool _vertex)
	{
		BX_UNUSED(_stride);

		m_size   = _size;
		m_flags  = _flags;
		m_vertex = _vertex;

		if (NULL == _data)
		{
			m_ptr = s_renderMtl->m_device.newBufferWithLength(_size, 0);
		}
		else
		{
			m_ptr = s_renderMtl->m_device.newBufferWithBytes(_data, _size, 0);
		}
	}

	void BufferMtl::update(uint32_t _offset, uint32_t _size, void* _data, bool _discard)
	{
		BlitCommandEncoder bce = s_renderMtl->getBlitCommandEncoder();

		if (!m_vertex
		&&  !_discard)
		{
			if (NULL == m_dynamic)
			{
				m_dynamic = (uint8_t*)BX_ALLOC(g_allocator, m_size);
			}

			bx::memCopy(m_dynamic + _offset, _data, _size);
			uint32_t start = _offset & 4;
			uint32_t end   = bx::strideAlign(_offset + _size, 4);

			Buffer temp = s_renderMtl->m_device.newBufferWithBytes(m_dynamic, end - start, 0);
			bce.copyFromBuffer(temp, 0, m_ptr, start, end - start);
			s_renderMtl->m_cmd.release(temp);
		}
		else
		{
			Buffer temp = s_renderMtl->m_device.newBufferWithBytes(_data, _size, 0);
			bce.copyFromBuffer(temp, 0, m_ptr, _offset, _size);
			s_renderMtl->m_cmd.release(temp);
		}
	}

	void VertexBufferMtl::create(uint32_t _size, void* _data, VertexLayoutHandle _layoutHandle, uint16_t _flags)
	{
		m_layoutHandle = _layoutHandle;
		uint16_t stride = isValid(_layoutHandle)
			? s_renderMtl->m_vertexLayouts[_layoutHandle.idx].m_stride
			: 0
			;

		BufferMtl::create(_size, _data, _flags, stride, true);
	}

	void TextureMtl::create(const Memory* _mem, uint64_t _flags, uint8_t _skip)
	{
		m_sampler = s_renderMtl->getSamplerState(uint32_t(_flags) );

		bimg::ImageContainer imageContainer;

		if (bimg::imageParse(imageContainer, _mem->data, _mem->size) )
		{
			const bimg::ImageBlockInfo& blockInfo = getBlockInfo(bimg::TextureFormat::Enum(imageContainer.m_format) );
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

			m_flags  = _flags;
			m_width  = ti.width;
			m_height = ti.height;
			m_depth  = ti.depth;
			m_requestedFormat  = uint8_t(imageContainer.m_format);
			m_textureFormat    = uint8_t(getViableTextureFormat(imageContainer) );
			const bool convert = m_textureFormat != m_requestedFormat;
			const uint8_t bpp  = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat) );

			TextureDescriptor desc = s_renderMtl->m_textureDescriptor;

			if (1 < ti.numLayers)
			{
				if (imageContainer.m_cubeMap)
				{
					desc.textureType = MTLTextureType(6); // MTLTextureTypeCubeArray
					m_type = TextureCube;
				}
				else
				{
					desc.textureType = MTLTextureType2DArray;
					m_type = Texture2D;
				}
			}
			else if (imageContainer.m_cubeMap)
			{
				desc.textureType = MTLTextureTypeCube;
				m_type = TextureCube;
			}
			else if (1 < imageContainer.m_depth)
			{
				desc.textureType = MTLTextureType3D;
				m_type = Texture3D;
			}
			else
			{
				desc.textureType = MTLTextureType2D;
				m_type = Texture2D;
			}

			m_numMips = ti.numMips;
			const uint16_t numSides = ti.numLayers * (imageContainer.m_cubeMap ? 6 : 1);
			const bool compressed   = bimg::isCompressed(bimg::TextureFormat::Enum(m_textureFormat) );
			const bool writeOnly    = 0 != (_flags&BGFX_TEXTURE_RT_WRITE_ONLY);
			const bool computeWrite = 0 != (_flags&BGFX_TEXTURE_COMPUTE_WRITE);
			const bool renderTarget = 0 != (_flags&BGFX_TEXTURE_RT_MASK);
			const bool srgb         = 0 != (_flags&BGFX_TEXTURE_SRGB);

			BX_TRACE("Texture %3d: %s (requested: %s), layers %d, %dx%d%s RT[%c], WO[%c], CW[%c], sRGB[%c]"
				, this - s_renderMtl->m_textures
				, getName( (TextureFormat::Enum)m_textureFormat)
				, getName( (TextureFormat::Enum)m_requestedFormat)
				, ti.numLayers
				, ti.width
				, ti.height
				, imageContainer.m_cubeMap ? "x6" : ""
				, renderTarget ? 'x' : ' '
				, writeOnly    ? 'x' : ' '
				, computeWrite ? 'x' : ' '
				, srgb         ? 'x' : ' '
				);

			const uint32_t msaaQuality = bx::uint32_satsub( (_flags&BGFX_TEXTURE_RT_MSAA_MASK)>>BGFX_TEXTURE_RT_MSAA_SHIFT, 1);
			const int32_t  sampleCount = s_msaa[msaaQuality];

			MTLPixelFormat format = MTLPixelFormatInvalid;
			if (srgb)
			{
				format = s_textureFormat[m_textureFormat].m_fmtSrgb;
				BX_WARN(format != MTLPixelFormatInvalid
					, "sRGB not supported for texture format %d"
					, m_textureFormat
					);
			}

			if (format == MTLPixelFormatInvalid)
			{
				// not swizzled and not sRGB, or sRGB unsupported
				format = s_textureFormat[m_textureFormat].m_fmt;
			}

			desc.pixelFormat = format;
			desc.width  = ti.width;
			desc.height = ti.height;
			desc.depth  = bx::uint32_max(1,imageContainer.m_depth);
			desc.mipmapLevelCount = ti.numMips;
			desc.sampleCount      = 1;
			desc.arrayLength      = ti.numLayers;

			if (s_renderMtl->m_iOS9Runtime
			||  s_renderMtl->m_macOS11Runtime)
			{
				desc.cpuCacheMode = MTLCPUCacheModeDefaultCache;

				desc.storageMode = (MTLStorageMode)(false
					|| writeOnly
					|| bimg::isDepth(bimg::TextureFormat::Enum(m_textureFormat) )
					?     2 /* MTLStorageModePrivate */
					: (BX_ENABLED(BX_PLATFORM_IOS)
						? 0 /* MTLStorageModeShared  */
						: 1 /* MTLStorageModeManaged */
					) );

				desc.usage = MTLTextureUsageShaderRead;
				if (computeWrite)
				{
					desc.usage |= MTLTextureUsageShaderWrite;
				}

				if (renderTarget)
				{
					desc.usage |= MTLTextureUsageRenderTarget;
				}
			}

			m_ptr = s_renderMtl->m_device.newTextureWithDescriptor(desc);

			if (sampleCount > 1)
			{
				desc.textureType = MTLTextureType2DMultisample;
				desc.sampleCount = sampleCount;

				if (s_renderMtl->m_iOS9Runtime
				||  s_renderMtl->m_macOS11Runtime)
				{
					desc.storageMode = (MTLStorageMode)(2 /* MTLStorageModePrivate */);
				}

				m_ptrMsaa = s_renderMtl->m_device.newTextureWithDescriptor(desc);
			}

			if (m_requestedFormat == TextureFormat::D24S8
			&&  desc.pixelFormat  == MTLPixelFormatDepth32Float)
			{
				desc.pixelFormat = MTLPixelFormatStencil8;
				m_ptrStencil = s_renderMtl->m_device.newTextureWithDescriptor(desc);
			}

			uint8_t* temp = NULL;
			if (convert)
			{
				temp = (uint8_t*)BX_ALLOC(g_allocator, ti.width*ti.height*4);
			}

			for (uint16_t side = 0; side < numSides; ++side)
			{
				uint32_t width  = ti.width;
				uint32_t height = ti.height;
				uint32_t depth  = ti.depth;

				for (uint8_t lod = 0, num = ti.numMips; lod < num; ++lod)
				{
					width  = bx::max(1u, width);
					height = bx::max(1u, height);
					depth  = bx::max(1u, depth);

					bimg::ImageMip mip;
					if (bimg::imageGetRawData(imageContainer, side, lod+startLod, _mem->data, _mem->size, mip) )
					{
						const uint8_t* data = mip.m_data;

						if (convert)
						{
							bimg::imageDecodeToBgra8(
								  g_allocator
								, temp
								, mip.m_data
								, mip.m_width
								, mip.m_height
								, mip.m_width*4
								, mip.m_format
								);
							data = temp;
						}

						MTLRegion region = { { 0, 0, 0 }, { width, height, depth } };

						uint32_t bytesPerRow   = 0;
						uint32_t bytesPerImage = 0;

						if (compressed && !convert)
						{
							if (format >= 160 /*PVRTC_RGB_2BPP*/
							&&  format <= 167 /*PVRTC_RGBA_4BPP_sRGB*/)
							{
								bytesPerRow   = 0;
								bytesPerImage = 0;
							}
							else
							{
								bytesPerRow   = (mip.m_width / blockInfo.blockWidth)*mip.m_blockSize;
								bytesPerImage = desc.textureType == MTLTextureType3D
									? (mip.m_height/blockInfo.blockHeight)*bytesPerRow
									: 0
									;
							}
						}
						else
						{
							bytesPerRow   = width * bpp / 8;
							bytesPerImage = desc.textureType == MTLTextureType3D
								? bytesPerRow * height
								: 0
								;
						}

						m_ptr.replaceRegion(region, lod, side, data, bytesPerRow, bytesPerImage);
					}

					width  >>= 1;
					height >>= 1;
					depth  >>= 1;
				}
			}

			if (NULL != temp)
			{
				BX_FREE(g_allocator, temp);
			}
		}
	}

	void TextureMtl::update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem)
	{
		const uint32_t bpp       = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat) );
		uint32_t rectpitch  = _rect.m_width*bpp/8;
		if (bimg::isCompressed(bimg::TextureFormat::Enum(m_textureFormat) ) )
		{
			if (m_ptr.pixelFormat() >= 160 /*PVRTC_RGB_2BPP*/
			&&  m_ptr.pixelFormat() <= 167 /*PVRTC_RGBA_4BPP_sRGB*/)
			{
				rectpitch   = 0;
			}
			else
			{
				const bimg::ImageBlockInfo& blockInfo = bimg::getBlockInfo(bimg::TextureFormat::Enum(m_textureFormat) );
				rectpitch = (_rect.m_width / blockInfo.blockWidth)*blockInfo.blockSize;
			}
		}
		const uint32_t srcpitch  = UINT16_MAX == _pitch ? rectpitch : _pitch;
		const uint32_t slice     = ( (m_type == Texture3D) ? 0 : _side + _z * (m_type == TextureCube ? 6 : 1) );
		const uint16_t zz        = (m_type == Texture3D) ? _z : 0 ;

		const bool convert = m_textureFormat != m_requestedFormat;

		uint8_t* data = _mem->data;
		uint8_t* temp = NULL;

		if (convert)
		{
			temp = (uint8_t*)BX_ALLOC(g_allocator, rectpitch*_rect.m_height);
			bimg::imageDecodeToBgra8(
				  g_allocator
				, temp
				, data
				, _rect.m_width
				, _rect.m_height
				, srcpitch
				, bimg::TextureFormat::Enum(m_requestedFormat)
				);
			data = temp;
		}

		if (NULL != s_renderMtl->m_renderCommandEncoder)
		{
			s_renderMtl->m_cmd.finish(true);

			MTLRegion region =
			{
				{ _rect.m_x,     _rect.m_y,      zz     },
				{ _rect.m_width, _rect.m_height, _depth },
			};

			m_ptr.replaceRegion(region, _mip, slice, data, srcpitch, srcpitch * _rect.m_height);
		}
		else
		{
			BlitCommandEncoder bce = s_renderMtl->getBlitCommandEncoder();

			TextureDescriptor desc = s_renderMtl->m_textureDescriptor;
			desc.textureType = _depth > 1 ? MTLTextureType3D : MTLTextureType2D;
			desc.pixelFormat = m_ptr.pixelFormat();
			desc.width  = _rect.m_width;
			desc.height = _rect.m_height;
			desc.depth  = _depth;
			desc.mipmapLevelCount = 1;
			desc.sampleCount = 1;
			desc.arrayLength = 1;

			if (s_renderMtl->m_iOS9Runtime
			||  s_renderMtl->m_macOS11Runtime)
			{
				desc.cpuCacheMode = MTLCPUCacheModeDefaultCache;
				desc.storageMode  = BX_ENABLED(BX_PLATFORM_IOS)
					? (MTLStorageMode)0 // MTLStorageModeShared
					: (MTLStorageMode)1 // MTLStorageModeManaged
					;
				desc.usage        = 0;
			}

			Texture tempTexture = s_renderMtl->m_device.newTextureWithDescriptor(desc);
			MTLRegion region =
			{
				{ 0,     0,      0     },
				{ _rect.m_width, _rect.m_height, _depth },
			};
			tempTexture.replaceRegion(region, 0, 0, data, srcpitch, srcpitch * _rect.m_height);
			bce.copyFromTexture(tempTexture, 0, 0,  MTLOriginMake(0,0,0), MTLSizeMake(_rect.m_width, _rect.m_height, _depth),
								m_ptr, slice, _mip, MTLOriginMake(_rect.m_x, _rect.m_y, zz) );
			release(tempTexture);
		}

		if (NULL != temp)
		{
			BX_FREE(g_allocator, temp);
		}
	}

	void TextureMtl::commit(uint8_t _stage, bool _vertex, bool _fragment, uint32_t _flags, uint8_t _mip)
	{
		if (_vertex)
		{
			Texture p = _mip != UINT8_MAX ? getTextureMipLevel(_mip) : m_ptr;
			s_renderMtl->m_renderCommandEncoder.setVertexTexture(p, _stage);
			s_renderMtl->m_renderCommandEncoder.setVertexSamplerState(
				  0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & _flags)
					? s_renderMtl->getSamplerState(_flags)
					: m_sampler
				, _stage
				);
		}

		if (_fragment)
		{
			Texture p = _mip != UINT8_MAX ? getTextureMipLevel(_mip) : m_ptr;
			s_renderMtl->m_renderCommandEncoder.setFragmentTexture(p, _stage);
			s_renderMtl->m_renderCommandEncoder.setFragmentSamplerState(
				  0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & _flags)
					? s_renderMtl->getSamplerState(_flags)
					: m_sampler
				, _stage
				);
		}
	}

	Texture TextureMtl::getTextureMipLevel(int _mip)
	{
		if (_mip >= 0
		&&  _mip <  m_numMips
		&&  NULL != m_ptr)
		{
			if (NULL == m_ptrMips[_mip])
			{
				if (TextureCube == m_type)
				{
					m_ptrMips[_mip] = m_ptr.newTextureViewWithPixelFormat(
						  m_ptr.pixelFormat()
						, MTLTextureType2DArray
						, NSMakeRange(_mip,1)
						, NSMakeRange(0,m_ptr.arrayLength() * 6)
						);
				}
				else
				{
					m_ptrMips[_mip] = m_ptr.newTextureViewWithPixelFormat(
						  m_ptr.pixelFormat()
						, m_ptr.textureType()
						, NSMakeRange(_mip,1)
						, NSMakeRange(0,m_ptr.arrayLength() )
						);
				}
			}

			return m_ptrMips[_mip];
		}

		return 0;
	}

	SwapChainMtl::~SwapChainMtl()
	{
		MTL_RELEASE(m_metalLayer);
		MTL_RELEASE(m_drawable);
		MTL_RELEASE(m_drawableTexture);

		MTL_RELEASE(m_backBufferDepth);
		MTL_RELEASE(m_backBufferStencil);

		if (NULL != m_backBufferColorMsaa)
		{
			MTL_RELEASE(m_backBufferColorMsaa);
		}

	}

	void SwapChainMtl::init(void* _nwh)
	{
		if (m_metalLayer)
		{
			release(m_metalLayer);
		}
		if (NULL != NSClassFromString(@"MTKView") )
		{
			MTKView *view = (MTKView *)_nwh;
			if (NULL != view && [view isKindOfClass:NSClassFromString(@"MTKView")])
			{
				m_metalLayer = (CAMetalLayer *)view.layer;
			}
		}

		if (NULL != NSClassFromString(@"CAMetalLayer") )
		{
			if (NULL == m_metalLayer)
#if BX_PLATFORM_IOS
			{
				CAMetalLayer* metalLayer = (CAMetalLayer*)_nwh;
				if (NULL == metalLayer
				|| ![metalLayer isKindOfClass:NSClassFromString(@"CAMetalLayer")])
				{
					BX_WARN(false, "Unable to create Metal device. Please set platform data window to a CAMetalLayer");
					return;
				}

				m_metalLayer = metalLayer;
			}
#elif BX_PLATFORM_OSX
			{
				NSObject* nvh = (NSObject*)_nwh;
				if ([nvh isKindOfClass:[CAMetalLayer class]])
				{
					CAMetalLayer* metalLayer = (CAMetalLayer*)_nwh;
					m_metalLayer = metalLayer;
				}
				else
				{
					NSView *contentView;

					if ([nvh isKindOfClass:[NSView class]])
					{
						contentView = (NSView*)nvh;
					}
					else if ([nvh isKindOfClass:[NSWindow class]])
					{
						NSWindow* nsWindow = (NSWindow*)nvh;
						contentView = [nsWindow contentView];
					}
					else
					{
						BX_WARN(0, "Unable to create Metal device. Please set platform data window to an NSWindow, NSView, or CAMetalLayer");
						return;
					}

					void (^setLayer)(void) = ^{
						CALayer* layer = contentView.layer;
						if(NULL != layer && [layer isKindOfClass:NSClassFromString(@"CAMetalLayer")])
						{
							m_metalLayer = (CAMetalLayer*)layer;
						}
						else
						{
							[contentView setWantsLayer:YES];
							m_metalLayer = [CAMetalLayer layer];
							[contentView setLayer:m_metalLayer];
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

						CFRunLoopPerformBlock([[NSRunLoop mainRunLoop] getCFRunLoop],
											  kCFRunLoopCommonModes,
											  ^{
												  setLayer();
												  psemaphore->post();
											  });
						semaphore.wait();
					}
				}
			}
#endif // BX_PLATFORM_*
		}

		if (NULL == m_metalLayer)
		{
			BX_WARN(NULL != s_renderMtl->m_device, "Unable to create Metal device.");
			return;
		}

		m_metalLayer.device      = s_renderMtl->m_device;
		m_metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
		m_metalLayer.magnificationFilter = kCAFilterNearest;
		m_nwh = _nwh;
		retain(m_metalLayer);
	}

	void SwapChainMtl::resize(FrameBufferMtl &_frameBuffer, uint32_t _width, uint32_t _height, uint32_t _flags, uint32_t _maximumDrawableCount)
	{
		const int32_t sampleCount = s_msaa[(_flags&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT];

#if BX_PLATFORM_OSX
#if __MAC_OS_X_VERSION_MAX_ALLOWED >= 101300
		if (@available(macOS 10.13, *) )
		{
			m_metalLayer.displaySyncEnabled = 0 != (_flags&BGFX_RESET_VSYNC);
		}
		if (@available(macOS 10.13.2, *) )
		{
            m_metalLayer.maximumDrawableCount = bx::clamp<uint32_t>(_maximumDrawableCount != 0 ? _maximumDrawableCount : BGFX_CONFIG_MAX_FRAME_LATENCY, 2, 3);
		}
#endif // __MAC_OS_X_VERSION_MAX_ALLOWED >= 101300
#endif // BX_PLATFORM_OSX

		m_metalLayer.drawableSize = CGSizeMake(_width, _height);
		m_metalLayer.pixelFormat = (_flags & BGFX_RESET_SRGB_BACKBUFFER)
			? MTLPixelFormatBGRA8Unorm_sRGB
			: MTLPixelFormatBGRA8Unorm
			;

		TextureDescriptor desc = s_renderMtl->m_textureDescriptor;

		desc.textureType = sampleCount > 1 ? MTLTextureType2DMultisample : MTLTextureType2D;

		if (s_renderMtl->m_hasPixelFormatDepth32Float_Stencil8)
		{
			desc.pixelFormat = MTLPixelFormatDepth32Float_Stencil8;
		}
		else
		{
			desc.pixelFormat = MTLPixelFormatDepth32Float;
		}

		desc.width  = _width;
		desc.height = _height;
		desc.depth  = 1;
		desc.mipmapLevelCount = 1;
		desc.sampleCount = sampleCount;
		desc.arrayLength = 1;

		if (s_renderMtl->m_iOS9Runtime
		||  s_renderMtl->m_macOS11Runtime)
		{
			desc.cpuCacheMode = MTLCPUCacheModeDefaultCache;
			desc.storageMode  = MTLStorageModePrivate;
			desc.usage        = MTLTextureUsageRenderTarget;
		}

		if (NULL != m_backBufferDepth)
		{
			release(m_backBufferDepth);
		}

		m_backBufferDepth = s_renderMtl->m_device.newTextureWithDescriptor(desc);

		if (NULL != m_backBufferStencil)
		{
			release(m_backBufferStencil);
		}

		if (s_renderMtl->m_hasPixelFormatDepth32Float_Stencil8)
		{
			m_backBufferStencil = m_backBufferDepth;
			retain(m_backBufferStencil);
		}
		else
		{
			desc.pixelFormat = MTLPixelFormatStencil8;
			m_backBufferStencil = s_renderMtl->m_device.newTextureWithDescriptor(desc);
		}

		if (sampleCount > 1)
		{
			if (NULL != m_backBufferColorMsaa)
			{
				release(m_backBufferColorMsaa);
			}

			desc.pixelFormat = m_metalLayer.pixelFormat;
			m_backBufferColorMsaa = s_renderMtl->m_device.newTextureWithDescriptor(desc);
		}

		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(1);
		murmur.add( (uint32_t)m_metalLayer.pixelFormat);
		murmur.add( (uint32_t)m_backBufferDepth.pixelFormat() );
		murmur.add( (uint32_t)m_backBufferStencil.pixelFormat() );
		murmur.add( (uint32_t)sampleCount);
		_frameBuffer.m_pixelFormatHash = murmur.end();
	}

	id <MTLTexture> SwapChainMtl::currentDrawableTexture()
	{
		if (NULL == m_drawableTexture)
		{
			m_drawable = m_metalLayer.nextDrawable;
			if (m_drawable != NULL)
			{
				m_drawableTexture = m_drawable.texture;
				retain(m_drawableTexture);
				retain(m_drawable); // keep alive to be useable at 'flip'
			}
			else
			{
				TextureDescriptor desc = s_renderMtl->m_textureDescriptor;
				desc.textureType = MTLTextureType2D;
				desc.pixelFormat = m_metalLayer.pixelFormat;
				desc.width  = m_metalLayer.drawableSize.width;
				desc.height = m_metalLayer.drawableSize.height;
				desc.depth  = 1;
				desc.mipmapLevelCount = 1;
				desc.sampleCount = 1;
				desc.arrayLength = 1;

				if (s_renderMtl->m_iOS9Runtime
				||  s_renderMtl->m_macOS11Runtime)
				{
					desc.cpuCacheMode = MTLCPUCacheModeDefaultCache;
					desc.storageMode = BX_ENABLED(BX_PLATFORM_IOS)
						? (MTLStorageMode)0 // MTLStorageModeShared
						: (MTLStorageMode)1 // MTLStorageModeManaged
						;

					desc.usage = MTLTextureUsageRenderTarget;
				}

				m_drawableTexture = s_renderMtl->m_device.newTextureWithDescriptor(desc);
			}
		}

		return m_drawableTexture;
	}

	void FrameBufferMtl::create(uint8_t _num, const Attachment* _attachment)
	{
		m_swapChain = NULL;
		m_denseIdx  = UINT16_MAX;
		m_num       = 0;
		m_width     = 0;
		m_height    = 0;

		for (uint32_t ii = 0; ii < _num; ++ii)
		{
			const Attachment& at = _attachment[ii];
			TextureHandle handle = at.handle;

			if (isValid(handle) )
			{
				const TextureMtl& texture = s_renderMtl->m_textures[handle.idx];

				if (0 == m_width)
				{
					m_width = texture.m_width;
					m_height = texture.m_height;
				}

				if (bimg::isDepth(bimg::TextureFormat::Enum(texture.m_textureFormat) ) )
				{
					m_depthHandle = handle;
					m_depthAttachment = at;
				}
				else
				{
					m_colorHandle[m_num] = handle;
					m_colorAttachment[m_num] = at;
					m_num++;
				}
			}
		}

		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(m_num);

		for (uint32_t ii = 0; ii < m_num; ++ii)
		{
			const TextureMtl& texture = s_renderMtl->m_textures[m_colorHandle[ii].idx];
			murmur.add(uint32_t(texture.m_ptr.pixelFormat() ) );
		}

		if (!isValid(m_depthHandle) )
		{
			murmur.add(uint32_t(MTLPixelFormatInvalid) );
			murmur.add(uint32_t(MTLPixelFormatInvalid) );
		}
		else
		{
			const TextureMtl& depthTexture = s_renderMtl->m_textures[m_depthHandle.idx];
			murmur.add(uint32_t(depthTexture.m_ptr.pixelFormat() ) );
			murmur.add(NULL != depthTexture.m_ptrStencil
				? uint32_t(depthTexture.m_ptrStencil.pixelFormat() )
				: uint32_t(MTLPixelFormatInvalid)
				);
		}

		murmur.add(1); // SampleCount

		m_pixelFormatHash = murmur.end();
	}

	void FrameBufferMtl::create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat)
	{
		BX_UNUSED(_format, _depthFormat);
		m_swapChain = BX_NEW(g_allocator, SwapChainMtl);
		m_num = 0;
		m_width     = _width;
		m_height    = _height;
		m_nwh       = _nwh;
		m_denseIdx  = _denseIdx;

		m_swapChain->init(_nwh);
	}

	void FrameBufferMtl::postReset()
	{
	}

	uint16_t FrameBufferMtl::destroy()
	{
		if (NULL != m_swapChain)
		{
			BX_DELETE(g_allocator, m_swapChain);
			m_swapChain = NULL;
		}

		m_num = 0;
		m_nwh = NULL;
		m_depthHandle.idx = kInvalidHandle;

		uint16_t denseIdx = m_denseIdx;
		m_denseIdx = UINT16_MAX;

		return denseIdx;
	}

	void FrameBufferMtl::resolve()
	{
		BlitCommandEncoder bce = s_renderMtl->getBlitCommandEncoder();
		for (uint32_t ii = 0; ii < m_num; ++ii)
		{
			if (0 != (m_colorAttachment[ii].resolve & BGFX_RESOLVE_AUTO_GEN_MIPS))
			{
				const TextureMtl& texture = s_renderMtl->m_textures[m_colorHandle[ii].idx];
				const bool isRenderTarget = (texture.m_flags & BGFX_TEXTURE_RT_MASK);
				const bool fmtSupport = 0 != (g_caps.formats[texture.m_textureFormat] & BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN);
				if (isRenderTarget
					&& fmtSupport
					&& texture.m_numMips > 1)
				{
					bce.generateMipmapsForTexture(texture.m_ptr);
				}
			}
		}

        s_renderMtl->endEncoding();
	}

	void CommandQueueMtl::init(Device _device)
	{
		m_commandQueue = _device.newCommandQueue();
		m_framesSemaphore.post(BGFX_CONFIG_MAX_FRAME_LATENCY);
	}

	void CommandQueueMtl::shutdown()
	{
		finish(true);
		MTL_RELEASE(m_commandQueue);
	}

	CommandBuffer CommandQueueMtl::alloc()
	{
		m_activeCommandBuffer = m_commandQueue.commandBuffer();
		retain(m_activeCommandBuffer);
		return m_activeCommandBuffer;
	}

	inline void commandBufferFinishedCallback(void* _data)
	{
		CommandQueueMtl* queue = (CommandQueueMtl*)_data;

		if (queue)
		{
			queue->m_framesSemaphore.post();
		}
	}

	void CommandQueueMtl::kick(bool _endFrame, bool _waitForFinish)
	{
		if (m_activeCommandBuffer)
		{
			if (_endFrame)
			{
				m_releaseWriteIndex = (m_releaseWriteIndex + 1) % BGFX_CONFIG_MAX_FRAME_LATENCY;
				m_activeCommandBuffer.addCompletedHandler(commandBufferFinishedCallback, this);
			}

			m_activeCommandBuffer.commit();

			if (_waitForFinish)
			{
				m_activeCommandBuffer.waitUntilCompleted();
			}

			MTL_RELEASE(m_activeCommandBuffer);
		}
	}

	void CommandQueueMtl::finish(bool _finishAll)
	{
		if (_finishAll)
		{
			uint32_t count = m_activeCommandBuffer != NULL
				? 2
				: 3
				;

			for (uint32_t ii = 0; ii < count; ++ii)
			{
				consume();
			}

			m_framesSemaphore.post(count);
		}
		else
		{
			consume();
		}
	}

	void CommandQueueMtl::release(NSObject* _ptr)
	{
		m_release[m_releaseWriteIndex].push_back(_ptr);
	}

	void CommandQueueMtl::consume()
	{
		m_framesSemaphore.wait();
		m_releaseReadIndex = (m_releaseReadIndex + 1) % BGFX_CONFIG_MAX_FRAME_LATENCY;

		ResourceArray& ra = m_release[m_releaseReadIndex];

		for (ResourceArray::iterator it = ra.begin(), itEnd = ra.end(); it != itEnd; ++it)
		{
			bgfx::mtl::release(*it);
		}

		ra.clear();
	}

	void TimerQueryMtl::init()
	{
		m_frequency = bx::getHPFrequency();
	}

	void TimerQueryMtl::shutdown()
	{
	}

	uint32_t TimerQueryMtl::begin(uint32_t _resultIdx)
	{
		BX_UNUSED(_resultIdx);
		return 0;
	}

	void TimerQueryMtl::end(uint32_t _idx)
	{
		BX_UNUSED(_idx);
	}

	static void setTimestamp(void* _data)
	{
		*( (int64_t*)_data) = bx::getHPCounter();
	}

	void TimerQueryMtl::addHandlers(CommandBuffer& _commandBuffer)
	{
		while (0 == m_control.reserve(1) )
		{
			m_control.consume(1);
		}

		uint32_t offset = m_control.m_current;

		_commandBuffer.addScheduledHandler(setTimestamp, &m_result[offset].m_begin);
		_commandBuffer.addCompletedHandler(setTimestamp, &m_result[offset].m_end);
		m_control.commit(1);
	}

	bool TimerQueryMtl::get()
	{
		if (0 != m_control.available() )
		{
			uint32_t offset = m_control.m_read;
			m_begin = m_result[offset].m_begin;
			m_end   = m_result[offset].m_end;
			m_elapsed = m_end - m_begin;

			m_control.consume(1);

			return true;
		}

		return false;
	}

	void OcclusionQueryMTL::postReset()
	{
		MTL_RELEASE(m_buffer);
	}

	void OcclusionQueryMTL::preReset()
	{
		m_buffer = s_renderMtl->m_device.newBufferWithLength(BX_COUNTOF(m_query) * 8, 0);
	}

	void OcclusionQueryMTL::begin(RenderCommandEncoder& _rce, Frame* _render, OcclusionQueryHandle _handle)
	{
		while (0 == m_control.reserve(1) )
		{
			resolve(_render, true);
		}

		Query& query = m_query[m_control.m_current];
		query.m_handle  = _handle;
		uint32_t offset = _handle.idx * 8;
		_rce.setVisibilityResultMode(MTLVisibilityResultModeBoolean, offset);
	}

	void OcclusionQueryMTL::end(RenderCommandEncoder& _rce)
	{
		Query& query = m_query[m_control.m_current];
		uint32_t offset = query.m_handle.idx * 8;
		_rce.setVisibilityResultMode(MTLVisibilityResultModeDisabled, offset);
		m_control.commit(1);
	}

	void OcclusionQueryMTL::resolve(Frame* _render, bool _wait)
	{
		BX_UNUSED(_wait);

		while (0 != m_control.available() )
		{
			Query& query = m_query[m_control.m_read];

			if (isValid(query.m_handle) )
			{
				uint64_t result = ( (uint64_t*)m_buffer.contents() )[query.m_handle.idx];
				_render->m_occlusion[query.m_handle.idx] = int32_t(result);
			}

			m_control.consume(1);
		}
	}

	void OcclusionQueryMTL::invalidate(OcclusionQueryHandle _handle)
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

	void RendererContextMtl::submitBlit(BlitState& _bs, uint16_t _view)
	{
		if (!_bs.hasItem(_view) )
		{
			return;
		}

		endEncoding();

		m_blitCommandEncoder = getBlitCommandEncoder();

		while (_bs.hasItem(_view) )
		{
			const BlitItem& blit = _bs.advance();

			const TextureMtl& src = m_textures[blit.m_src.idx];
			const TextureMtl& dst = m_textures[blit.m_dst.idx];

#if BX_PLATFORM_OSX
			bool     readBack  = !!(dst.m_flags & BGFX_TEXTURE_READ_BACK);
#endif  // BX_PLATFORM_OSX

			if (MTLTextureType3D == src.m_ptr.textureType() )
			{
				m_blitCommandEncoder.copyFromTexture(
					  src.m_ptr
					, 0
					, 0
					, MTLOriginMake(blit.m_srcX, blit.m_srcY, blit.m_srcZ)
					, MTLSizeMake(blit.m_width, blit.m_height, bx::uint32_imax(blit.m_depth, 1) )
					, dst.m_ptr
					, 0
					, 0
					, MTLOriginMake(blit.m_dstX, blit.m_dstY, blit.m_dstZ)
					);
#if BX_PLATFORM_OSX
				if (m_macOS11Runtime
				&&  readBack)
				{
					m_blitCommandEncoder.synchronizeResource(dst.m_ptr);
				}
#endif  // BX_PLATFORM_OSX
			}
			else
			{
				m_blitCommandEncoder.copyFromTexture(
					  src.m_ptr
					, blit.m_srcZ
					, blit.m_srcMip
					, MTLOriginMake(blit.m_srcX, blit.m_srcY, 0)
					, MTLSizeMake(blit.m_width, blit.m_height, 1)
					, dst.m_ptr
					, blit.m_dstZ
					, blit.m_dstMip
					, MTLOriginMake(blit.m_dstX, blit.m_dstY, 0)
					);
#if BX_PLATFORM_OSX
				if (m_macOS11Runtime
				&&  readBack)
				{
					m_blitCommandEncoder.synchronizeTexture(dst.m_ptr, 0, blit.m_dstMip);
				}
#endif  // BX_PLATFORM_OSX
			}
		}

		if (0 != m_blitCommandEncoder)
		{
			m_blitCommandEncoder.endEncoding();
			m_blitCommandEncoder = 0;
		}
	}

	void RendererContextMtl::submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter)
	{
		m_cmd.finish(false);

		if (NULL == m_commandBuffer)
		{
			m_commandBuffer = m_cmd.alloc();
		}

		BGFX_MTL_PROFILER_BEGIN_LITERAL("rendererSubmit", kColorFrame);

		int64_t timeBegin = bx::getHPCounter();
		int64_t captureElapsed = 0;

		m_gpuTimer.addHandlers(m_commandBuffer);

		if (m_blitCommandEncoder)
		{
			m_blitCommandEncoder.endEncoding();
			m_blitCommandEncoder = 0;
		}

		updateResolution(_render->m_resolution);

		if (0 != _render->m_numScreenShots
		||  NULL != m_capture)
		{
			if (m_screenshotTarget)
			{
				if (m_screenshotTarget.width()  != m_resolution.width
				||  m_screenshotTarget.height() != m_resolution.height)
				{
					MTL_RELEASE(m_screenshotTarget);
				}
			}

			if (NULL == m_screenshotTarget)
			{
				m_textureDescriptor.textureType = MTLTextureType2D;
				m_textureDescriptor.pixelFormat = m_mainFrameBuffer.m_swapChain->m_metalLayer.pixelFormat;
				m_textureDescriptor.width  = m_resolution.width;
				m_textureDescriptor.height = m_resolution.height;
				m_textureDescriptor.depth  = 1;
				m_textureDescriptor.mipmapLevelCount = 1;
				m_textureDescriptor.sampleCount = 1;
				m_textureDescriptor.arrayLength = 1;

				if (m_iOS9Runtime
				||  m_macOS11Runtime)
				{
					m_textureDescriptor.cpuCacheMode = MTLCPUCacheModeDefaultCache;
					m_textureDescriptor.storageMode = BX_ENABLED(BX_PLATFORM_IOS)
						? (MTLStorageMode)0 // MTLStorageModeShared
						: (MTLStorageMode)1 // MTLStorageModeManaged
						;

					m_textureDescriptor.usage = 0
						| MTLTextureUsageRenderTarget
						| MTLTextureUsageShaderRead
						;
				}

				m_screenshotTarget = m_device.newTextureWithDescriptor(m_textureDescriptor);
			}
		}
		else
		{
			MTL_RELEASE(m_screenshotTarget);
		}

		m_uniformBuffer = m_uniformBuffers[m_bufferIndex];
		m_bufferIndex = (m_bufferIndex + 1) % BGFX_CONFIG_MAX_FRAME_LATENCY;
		m_uniformBufferVertexOffset = 0;
		m_uniformBufferFragmentOffset = 0;

		if (0 < _render->m_iboffset)
		{
			BGFX_PROFILER_SCOPE("bgfx/Update transient index buffer", kColorResource);
			TransientIndexBuffer* ib = _render->m_transientIb;
			m_indexBuffers[ib->handle.idx].update(0, bx::strideAlign(_render->m_iboffset,4), ib->data, true);
		}

		if (0 < _render->m_vboffset)
		{
			BGFX_PROFILER_SCOPE("bgfx/Update transient vertex buffer", kColorResource);
			TransientVertexBuffer* vb = _render->m_transientVb;
			m_vertexBuffers[vb->handle.idx].update(0, bx::strideAlign(_render->m_vboffset,4), vb->data, true);
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
		uint32_t blendFactor = 0;

		bool wireframe = !!(_render->m_debug&BGFX_DEBUG_WIREFRAME);

		ProgramHandle currentProgram = BGFX_INVALID_HANDLE;
		SortKey key;
		uint16_t view = UINT16_MAX;
		FrameBufferHandle fbh = { BGFX_CONFIG_MAX_FRAME_BUFFERS };

		BlitState bs(_render);

		const uint64_t primType = 0;
		uint8_t primIndex = uint8_t(primType>>BGFX_STATE_PT_SHIFT);
		PrimInfo prim = s_primInfo[primIndex];
		const uint32_t maxComputeBindings = g_caps.limits.maxComputeBindings;
		const uint32_t maxTextureSamplers = g_caps.limits.maxTextureSamplers;

		RenderCommandEncoder rce;
		PipelineStateMtl* currentPso = NULL;

		bool wasCompute     = false;
		bool viewHasScissor = false;
		Rect viewScissorRect;
		viewScissorRect.clear();

		uint32_t statsNumPrimsSubmitted[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumPrimsRendered[BX_COUNTOF(s_primInfo)]  = {};
		uint32_t statsNumInstances[BX_COUNTOF(s_primInfo)]      = {};
		uint32_t statsNumDrawIndirect[BX_COUNTOF(s_primInfo)]   = {};
		uint32_t statsNumIndices = 0;
		uint32_t statsKeyType[2] = {};

		Profiler<TimerQueryMtl> profiler(
			  _render
			, m_gpuTimer
			, s_viewName
			);

		m_occlusionQuery.resolve(_render);

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

				const uint32_t itemIdx       = _render->m_sortValues[item];
				const RenderItem& renderItem = _render->m_renderItem[itemIdx];
				const RenderBind& renderBind = _render->m_renderItemBind[itemIdx];
				++item;

				if (viewChanged
				|| (!isCompute && wasCompute) )
				{
					view = key.m_view;
					currentProgram = BGFX_INVALID_HANDLE;

					if (item > 1)
					{
						profiler.end();
					}

					BGFX_MTL_PROFILER_END();
					setViewType(view, "  ");
					BGFX_MTL_PROFILER_BEGIN(view, kColorView);

					profiler.begin(view);

					viewState.m_rect = _render->m_view[view].m_rect;

					submitBlit(bs, view);

					if (!isCompute)
					{
						const Rect& scissorRect = _render->m_view[view].m_scissor;
						viewHasScissor = !scissorRect.isZero();
						viewScissorRect = viewHasScissor ? scissorRect : viewState.m_rect;
						Clear& clr = _render->m_view[view].m_clear;

						Rect viewRect = viewState.m_rect;
						bool clearWithRenderPass = false;

						if (NULL == m_renderCommandEncoder
						||  fbh.idx != _render->m_view[view].m_fbh.idx)
						{
							endEncoding();

							RenderPassDescriptor renderPassDescriptor = newRenderPassDescriptor();
							renderPassDescriptor.visibilityResultBuffer = m_occlusionQuery.m_buffer;

							fbh = _render->m_view[view].m_fbh;

							uint32_t width  = m_resolution.width;
							uint32_t height = m_resolution.height;

							if (isValid(fbh) )
							{
								FrameBufferMtl& frameBuffer = m_frameBuffers[fbh.idx];
								width  = frameBuffer.m_width;
								height = frameBuffer.m_height;
							}

							clearWithRenderPass = true
								&& 0      == viewRect.m_x
								&& 0      == viewRect.m_y
								&& width  == viewRect.m_width
								&& height == viewRect.m_height
								;

							setFrameBuffer(renderPassDescriptor, fbh);

							if (clearWithRenderPass)
							{
								for (uint32_t ii = 0; ii < g_caps.limits.maxFBAttachments; ++ii)
								{
									MTLRenderPassColorAttachmentDescriptor* desc = renderPassDescriptor.colorAttachments[ii];

									if (desc.texture != NULL)
									{
										if (0 != (BGFX_CLEAR_COLOR & clr.m_flags) )
										{
											if (0 != (BGFX_CLEAR_COLOR_USE_PALETTE & clr.m_flags) )
											{
												uint8_t index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_COLOR_PALETTE-1, clr.m_index[ii]);
												const float* rgba = _render->m_colorPalette[index];
												const float rr = rgba[0];
												const float gg = rgba[1];
												const float bb = rgba[2];
												const float aa = rgba[3];
												desc.clearColor = MTLClearColorMake(rr, gg, bb, aa);
											}
											else
											{
												float rr = clr.m_index[0]*1.0f/255.0f;
												float gg = clr.m_index[1]*1.0f/255.0f;
												float bb = clr.m_index[2]*1.0f/255.0f;
												float aa = clr.m_index[3]*1.0f/255.0f;
												desc.clearColor = MTLClearColorMake(rr, gg, bb, aa);
											}

											desc.loadAction = MTLLoadActionClear;
										}
										else
										{
											desc.loadAction = MTLLoadActionLoad;
										}

										if (NULL != m_capture
										&&  !isValid(fbh)
										&&  m_hasStoreActionStoreAndMultisampleResolve)
										{
											desc.storeAction = desc.texture.sampleCount > 1 ? MTLStoreActionStoreAndMultisampleResolve : MTLStoreActionStore;

										}
										else
										{
											desc.storeAction = desc.texture.sampleCount > 1 ? MTLStoreActionMultisampleResolve : MTLStoreActionStore;
										}
									}
								}

								RenderPassDepthAttachmentDescriptor depthAttachment = renderPassDescriptor.depthAttachment;

								if (NULL != depthAttachment.texture)
								{
									depthAttachment.clearDepth = clr.m_depth;
									depthAttachment.loadAction = 0 != (BGFX_CLEAR_DEPTH & clr.m_flags)
										? MTLLoadActionClear
										: MTLLoadActionLoad
										;
										depthAttachment.storeAction = NULL != m_mainFrameBuffer.m_swapChain->m_backBufferColorMsaa
										? MTLStoreActionDontCare
										: MTLStoreActionStore
										;
								}

								RenderPassStencilAttachmentDescriptor stencilAttachment = renderPassDescriptor.stencilAttachment;

								if (NULL != stencilAttachment.texture)
								{
									stencilAttachment.clearStencil = clr.m_stencil;
									stencilAttachment.loadAction   = 0 != (BGFX_CLEAR_STENCIL & clr.m_flags)
										? MTLLoadActionClear
										: MTLLoadActionLoad
										;
									stencilAttachment.storeAction = NULL != m_mainFrameBuffer.m_swapChain->m_backBufferColorMsaa
										? MTLStoreActionDontCare
										: MTLStoreActionStore
										;
								}
							}
							else
							{
								for (uint32_t ii = 0; ii < g_caps.limits.maxFBAttachments; ++ii)
								{
									MTLRenderPassColorAttachmentDescriptor* desc = renderPassDescriptor.colorAttachments[ii];
									if (desc.texture != NULL)
									{
										desc.loadAction = MTLLoadActionLoad;

										if (NULL != m_capture
										&&  !isValid(fbh)
										&&  m_hasStoreActionStoreAndMultisampleResolve)
										{
											desc.storeAction = desc.texture.sampleCount > 1 ? MTLStoreActionStoreAndMultisampleResolve : MTLStoreActionStore;

										}
										else
										{
											desc.storeAction = desc.texture.sampleCount > 1 ? MTLStoreActionMultisampleResolve : MTLStoreActionStore;
										}
									}
								}

								RenderPassDepthAttachmentDescriptor depthAttachment = renderPassDescriptor.depthAttachment;

								if (NULL != depthAttachment.texture)
								{
									depthAttachment.loadAction  = MTLLoadActionLoad;
									depthAttachment.storeAction = MTLStoreActionStore;
								}

								RenderPassStencilAttachmentDescriptor stencilAttachment = renderPassDescriptor.stencilAttachment;

								if (NULL != stencilAttachment.texture)
								{
									stencilAttachment.loadAction  = MTLLoadActionLoad;
									stencilAttachment.storeAction = MTLStoreActionStore;
								}
							}

							rce = m_commandBuffer.renderCommandEncoderWithDescriptor(renderPassDescriptor);
							m_renderCommandEncoder = rce;
							m_renderCommandEncoderFrameBufferHandle = fbh;
							MTL_RELEASE(renderPassDescriptor);
						}
						else if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
						{
							rce.popDebugGroup();
						}

						if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
						{
							rce.pushDebugGroup(s_viewName[view]);
						}

						rce.setTriangleFillMode(wireframe ? MTLTriangleFillModeLines : MTLTriangleFillModeFill);

						MTLViewport vp;
						vp.originX = viewState.m_rect.m_x;
						vp.originY = viewState.m_rect.m_y;
						vp.width   = viewState.m_rect.m_width;
						vp.height  = viewState.m_rect.m_height;
						vp.znear   = 0.0f;
						vp.zfar    = 1.0f;
						rce.setViewport(vp);

						MTLScissorRect sciRect = {
							viewState.m_rect.m_x,
							viewState.m_rect.m_y,
							viewState.m_rect.m_width,
							viewState.m_rect.m_height
						};
						rce.setScissorRect(sciRect);

						if (BGFX_CLEAR_NONE != (clr.m_flags & BGFX_CLEAR_MASK)
							&& !clearWithRenderPass)
						{
							clearQuad(_clearQuad, viewState.m_rect, clr, _render->m_colorPalette);
						}
					}
				}

				if (isCompute)
				{
					if (!wasCompute)
					{
						wasCompute = true;

						endEncoding();
						rce = NULL;

						setViewType(view, "C");
						BGFX_MTL_PROFILER_END();
						BGFX_MTL_PROFILER_BEGIN(view, kColorCompute);

						m_computeCommandEncoder = m_commandBuffer.computeCommandEncoder();
					}
					else if (viewChanged && BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
					{
						m_computeCommandEncoder.popDebugGroup();
					}

					if (viewChanged
					&&  BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
					{
						s_viewName[view][3] = L'C';
						m_computeCommandEncoder.pushDebugGroup(s_viewName[view]);
						s_viewName[view][3] = L' ';
					}

					const RenderCompute& compute = renderItem.compute;

					bool programChanged = false;
					rendererUpdateUniforms(this, _render->m_uniformBuffer[compute.m_uniformIdx], compute.m_uniformBegin, compute.m_uniformEnd);

					if (key.m_program.idx != currentProgram.idx)
					{
						currentProgram = key.m_program;

						currentPso = getComputePipelineState(currentProgram);

						if (NULL == currentPso)
						{
							currentProgram = BGFX_INVALID_HANDLE;
							continue;
						}

						m_computeCommandEncoder.setComputePipelineState(currentPso->m_cps);
						programChanged = true;
					}

					if (isValid(currentProgram)
					&&  NULL != currentPso)
					{
						uint32_t vertexUniformBufferSize = currentPso->m_vshConstantBufferSize;

						if (0 != vertexUniformBufferSize)
						{
							m_uniformBufferVertexOffset = bx::alignUp(
								  m_uniformBufferVertexOffset
								, currentPso->m_vshConstantBufferAlignment
								);
							m_computeCommandEncoder.setBuffer(m_uniformBuffer, m_uniformBufferVertexOffset, 0);
						}

						UniformBuffer* vcb = currentPso->m_vshConstantBuffer;
						if (NULL != vcb)
						{
							commit(*vcb);
						}

						viewState.setPredefined<4>(this, view, *currentPso, _render, compute);

						m_uniformBufferVertexOffset += vertexUniformBufferSize;
					}
					BX_UNUSED(programChanged);

					for (uint8_t stage = 0; stage < maxComputeBindings; ++stage)
					{
						const Binding& bind = renderBind.m_bind[stage];
						if (kInvalidHandle != bind.m_idx)
						{
							switch (bind.m_type)
							{
								case Binding::Image:
								{
									TextureMtl& texture = m_textures[bind.m_idx];
									m_computeCommandEncoder.setTexture(texture.getTextureMipLevel(bind.m_mip), stage);
								}
								break;

								case Binding::Texture:
								{
									TextureMtl& texture = m_textures[bind.m_idx];
									uint32_t flags = bind.m_samplerFlags;

									m_computeCommandEncoder.setTexture(texture.m_ptr, stage);
									m_computeCommandEncoder.setSamplerState(
										0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & flags)
										? getSamplerState(flags)
										: texture.m_sampler
										, stage
										);
								}
								break;

								case Binding::IndexBuffer:
								case Binding::VertexBuffer:
								{
									const BufferMtl& buffer = Binding::IndexBuffer == bind.m_type
									? m_indexBuffers[bind.m_idx]
									: m_vertexBuffers[bind.m_idx]
									;
									m_computeCommandEncoder.setBuffer(buffer.m_ptr, 0, stage + 1);
								}
								break;
							}
						}
					}

					MTLSize threadsPerGroup = MTLSizeMake(
						  currentPso->m_numThreads[0]
						, currentPso->m_numThreads[1]
						, currentPso->m_numThreads[2]
						);

					if (isValid(compute.m_indirectBuffer) )
					{
						const VertexBufferMtl& vb = m_vertexBuffers[compute.m_indirectBuffer.idx];

						uint32_t numDrawIndirect = UINT16_MAX == compute.m_numIndirect
						? vb.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
						: compute.m_numIndirect
						;

						uint32_t args = compute.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
						for (uint32_t ii = 0; ii < numDrawIndirect; ++ii)
						{
							m_computeCommandEncoder.dispatchThreadgroupsWithIndirectBuffer(
								  vb.m_ptr
								, args
								, threadsPerGroup
								);
							args += BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
						}
					}
					else
					{
						m_computeCommandEncoder.dispatchThreadgroups(
							  MTLSizeMake(compute.m_numX, compute.m_numY, compute.m_numZ)
							, threadsPerGroup
							);
					}
					continue;
				}


				bool resetState = viewChanged || wasCompute;

				if (wasCompute)
				{
					wasCompute = false;
					currentProgram = BGFX_INVALID_HANDLE;

					setViewType(view, " ");
					BGFX_MTL_PROFILER_END();
					BGFX_MTL_PROFILER_BEGIN(view, kColorDraw);
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
				currentState.m_stateFlags = newFlags;

				const uint64_t newStencil = draw.m_stencil;
				uint64_t changedStencil = currentState.m_stencil ^ draw.m_stencil;
				currentState.m_stencil = newStencil;

				if (resetState)
				{
					currentState.clear();
					currentState.m_scissor = !draw.m_scissor;
					changedFlags = BGFX_STATE_MASK;
					changedStencil = packStencil(BGFX_STENCIL_MASK, BGFX_STENCIL_MASK);
					currentState.m_stateFlags = newFlags;
					currentState.m_stencil    = newStencil;

					currentBind.clear();

					currentProgram = BGFX_INVALID_HANDLE;
					setDepthStencilState(newFlags, packStencil(BGFX_STENCIL_DEFAULT, BGFX_STENCIL_DEFAULT) );

					const uint64_t pt = newFlags&BGFX_STATE_PT_MASK;
					primIndex = uint8_t(pt>>BGFX_STATE_PT_SHIFT);
				}

				if (prim.m_type != s_primInfo[primIndex].m_type)
				{
					prim = s_primInfo[primIndex];
				}

				uint16_t scissor = draw.m_scissor;
				if (currentState.m_scissor != scissor)
				{
					currentState.m_scissor = scissor;

					MTLScissorRect rc;
					if (UINT16_MAX == scissor)
					{
						if (viewHasScissor)
						{
							rc.x   = viewScissorRect.m_x;
							rc.y    = viewScissorRect.m_y;
							rc.width  = viewScissorRect.m_width;
							rc.height = viewScissorRect.m_height;
						}
						else
						{   // can't disable: set to view rect
							rc.x   = viewState.m_rect.m_x;
							rc.y    = viewState.m_rect.m_y;
							rc.width  = viewState.m_rect.m_width;
							rc.height = viewState.m_rect.m_height;
						}
					}
					else
					{
						Rect scissorRect;
						scissorRect.setIntersect(viewScissorRect, _render->m_frameCache.m_rectCache.m_cache[scissor]);

						rc.x      = scissorRect.m_x;
						rc.y      = scissorRect.m_y;
						rc.width  = scissorRect.m_width;
						rc.height = scissorRect.m_height;
					}

					rce.setScissorRect(rc);
				}

				if ( (0
					 | BGFX_STATE_WRITE_Z
					 | BGFX_STATE_DEPTH_TEST_MASK
					 ) & changedFlags
				|| 0 != changedStencil)
				{
					setDepthStencilState(newFlags,newStencil);
				}

				if ( (0
					 | BGFX_STATE_CULL_MASK
					 | BGFX_STATE_ALPHA_REF_MASK
					 | BGFX_STATE_PT_MASK
					 | BGFX_STATE_FRONT_CCW
					 ) & changedFlags)
				{
					if (BGFX_STATE_FRONT_CCW & changedFlags)
					{
						rce.setFrontFacingWinding( (newFlags&BGFX_STATE_FRONT_CCW)
							? MTLWindingCounterClockwise
							: MTLWindingClockwise
							);
					}

					if (BGFX_STATE_CULL_MASK & changedFlags)
					{
						const uint64_t pt = newFlags&BGFX_STATE_CULL_MASK;
						const uint8_t cullIndex = uint8_t(pt>>BGFX_STATE_CULL_SHIFT);
						rce.setCullMode(s_cullMode[cullIndex]);
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
					}
				}

				if (blendFactor != draw.m_rgba
				&& !(newFlags & BGFX_STATE_BLEND_INDEPENDENT) )
				{
					const uint32_t rgba = draw.m_rgba;
					float rr = ( (rgba>>24)     )/255.0f;
					float gg = ( (rgba>>16)&0xff)/255.0f;
					float bb = ( (rgba>> 8)&0xff)/255.0f;
					float aa = ( (rgba    )&0xff)/255.0f;
					rce.setBlendColor(rr,gg,bb,aa);

					blendFactor = draw.m_rgba;
				}

				bool programChanged = false;
				rendererUpdateUniforms(this, _render->m_uniformBuffer[draw.m_uniformIdx], draw.m_uniformBegin, draw.m_uniformEnd);

				bool vertexStreamChanged = hasVertexStreamChanged(currentState, draw);

				if (key.m_program.idx != currentProgram.idx
				||  vertexStreamChanged
				|| (0
				   | BGFX_STATE_BLEND_MASK
				   | BGFX_STATE_BLEND_EQUATION_MASK
				   | BGFX_STATE_WRITE_RGB
				   | BGFX_STATE_WRITE_A
				   | BGFX_STATE_BLEND_INDEPENDENT
				   | BGFX_STATE_MSAA
				   | BGFX_STATE_BLEND_ALPHA_TO_COVERAGE
				   ) & changedFlags
				|| ( (blendFactor != draw.m_rgba) && !!(newFlags & BGFX_STATE_BLEND_INDEPENDENT) ) )
				{
					currentProgram = key.m_program;

					currentState.m_streamMask             = draw.m_streamMask;
					currentState.m_instanceDataBuffer.idx = draw.m_instanceDataBuffer.idx;
					currentState.m_instanceDataOffset     = draw.m_instanceDataOffset;
					currentState.m_instanceDataStride     = draw.m_instanceDataStride;

					const VertexLayout* layouts[BGFX_CONFIG_MAX_VERTEX_STREAMS];

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

						currentState.m_stream[idx].m_layoutHandle   = draw.m_stream[idx].m_layoutHandle;
						currentState.m_stream[idx].m_handle         = draw.m_stream[idx].m_handle;
						currentState.m_stream[idx].m_startVertex    = draw.m_stream[idx].m_startVertex;

						const uint16_t handle = draw.m_stream[idx].m_handle.idx;
						const VertexBufferMtl& vb = m_vertexBuffers[handle];
						const uint16_t decl = isValid(draw.m_stream[idx].m_layoutHandle)
							? draw.m_stream[idx].m_layoutHandle.idx
							: vb.m_layoutHandle.idx;
						const VertexLayout& layout = m_vertexLayouts[decl];
						const uint32_t stride = layout.m_stride;

						layouts[numStreams] = &layout;

						numVertices = bx::uint32_min(UINT32_MAX == draw.m_numVertices
							? vb.m_size/stride
							: draw.m_numVertices
							, numVertices
							);
						const uint32_t offset = draw.m_stream[idx].m_startVertex * stride;

						rce.setVertexBuffer(vb.m_ptr, offset, idx+1);
					}

					if (!isValid(currentProgram) )
					{
						continue;
					}
					else
					{
						currentPso = NULL;

						if (0 < numStreams)
						{
							currentPso = getPipelineState(
								  newFlags
								, draw.m_rgba
								, fbh
								, numStreams
								, layouts
								, currentProgram
								, draw.m_instanceDataStride/16
								);
						}

						if (NULL == currentPso)
						{
							currentProgram = BGFX_INVALID_HANDLE;
							continue;
						}

						rce.setRenderPipelineState(currentPso->m_rps);
					}

					if (isValid(draw.m_instanceDataBuffer) )
					{
						const VertexBufferMtl& inst = m_vertexBuffers[draw.m_instanceDataBuffer.idx];
						rce.setVertexBuffer(inst.m_ptr, draw.m_instanceDataOffset, numStreams+1);
					}

					programChanged = true;
				}

				if (isValid(currentProgram) )
				{
					const uint32_t vertexUniformBufferSize   = currentPso->m_vshConstantBufferSize;
					const uint32_t fragmentUniformBufferSize = currentPso->m_fshConstantBufferSize;

					if (0 != vertexUniformBufferSize)
					{
						m_uniformBufferVertexOffset = bx::alignUp(
							  m_uniformBufferVertexOffset
							, currentPso->m_vshConstantBufferAlignment
							);
						rce.setVertexBuffer(m_uniformBuffer, m_uniformBufferVertexOffset, 0);
					}

					m_uniformBufferFragmentOffset = m_uniformBufferVertexOffset + vertexUniformBufferSize;
					if (0 != fragmentUniformBufferSize)
					{
						m_uniformBufferFragmentOffset = bx::alignUp(
							  m_uniformBufferFragmentOffset
							, currentPso->m_fshConstantBufferAlignment
							);
						rce.setFragmentBuffer(m_uniformBuffer, m_uniformBufferFragmentOffset, 0);
					}

					UniformBuffer* vcb = currentPso->m_vshConstantBuffer;
					if (NULL != vcb)
					{
						commit(*vcb);
					}

					UniformBuffer* fcb = currentPso->m_fshConstantBuffer;
					if (NULL != fcb)
					{
						commit(*fcb);
					}

					viewState.setPredefined<4>(this, view, *currentPso, _render, draw);

					m_uniformBufferFragmentOffset += fragmentUniformBufferSize;
					m_uniformBufferVertexOffset    = m_uniformBufferFragmentOffset;
				}

				if (isValid(currentProgram) )
				{
					uint8_t* bindingTypes = currentPso->m_bindingTypes;
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
								case Binding::Image:
								{
									if (bind.m_access == Access::ReadWrite && 0 == (g_caps.supported & BGFX_CAPS_IMAGE_RW))
									{
										BGFX_FATAL(false, Fatal::DebugCheck,
										"Failed to set image with access: Access::ReadWrite, device is not support image read&write");
									}

									if (
                                        (bind.m_access == Access::Read && (0 == (g_caps.formats[bind.m_format] & BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ)))
										|| (bind.m_access == Access::Write && (0 == (g_caps.formats[bind.m_format] & BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE)))
                                        || (bind.m_access == Access::ReadWrite && (0 == (g_caps.formats[bind.m_format] & (BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ|BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE))))
                                        )
									{
										BGFX_FATAL(false, Fatal::DebugCheck,
										"Failed to set image with access: %s, format:%s is not supoort", s_accessNames[bind.m_access], bimg::getName(bimg::TextureFormat::Enum(bind.m_format)));
									}
									TextureMtl& texture = m_textures[bind.m_idx];
									texture.commit(
										stage
										, 0 != (bindingTypes[stage] & PipelineStateMtl::BindToVertexShader)
										, 0 != (bindingTypes[stage] & PipelineStateMtl::BindToFragmentShader)
										, bind.m_samplerFlags
										, bind.m_mip
										);
								}
								break;
								case Binding::Texture:
									{
										TextureMtl& texture = m_textures[bind.m_idx];
										texture.commit(
											stage
											, 0 != (bindingTypes[stage] & PipelineStateMtl::BindToVertexShader)
											, 0 != (bindingTypes[stage] & PipelineStateMtl::BindToFragmentShader)
											, bind.m_samplerFlags
											);
									}
									break;

								case Binding::IndexBuffer:
								case Binding::VertexBuffer:
									{
										const BufferMtl& buffer = Binding::IndexBuffer == bind.m_type
											? m_indexBuffers[bind.m_idx]
											: m_vertexBuffers[bind.m_idx]
											;

										if (0 != (bindingTypes[stage] & PipelineStateMtl::BindToVertexShader) )
										{
											rce.setVertexBuffer(buffer.m_ptr, 0, stage + 1);
										}

										if (0 != (bindingTypes[stage] & PipelineStateMtl::BindToFragmentShader) )
										{
											rce.setFragmentBuffer(buffer.m_ptr, 0, stage + 1);
										}
									}
									break;
								}
							}
						}

						current = bind;
					}
				}

				if (0 != currentState.m_streamMask)
				{
					uint32_t numVertices = draw.m_numVertices;

					if (UINT32_MAX == numVertices)
					{
						const VertexBufferMtl& vb = m_vertexBuffers[currentState.m_stream[0].m_handle.idx];
						uint16_t decl = !isValid(vb.m_layoutHandle) ? draw.m_stream[0].m_layoutHandle.idx : vb.m_layoutHandle.idx;
						const VertexLayout& layout = m_vertexLayouts[decl];
						numVertices = vb.m_size/layout.m_stride;
					}

					uint32_t numIndices        = 0;
					uint32_t numPrimsSubmitted = 0;
					uint32_t numInstances      = 0;
					uint32_t numPrimsRendered  = 0;
					uint32_t numDrawIndirect   = 0;

					if (hasOcclusionQuery)
					{
						m_occlusionQuery.begin(rce, _render, draw.m_occlusionQuery);
					}

					if (isValid(draw.m_indirectBuffer) )
					{
						const VertexBufferMtl& vb = m_vertexBuffers[draw.m_indirectBuffer.idx];

						if (isValid(draw.m_indexBuffer) )
						{
							const bool isIndex16           = draw.isIndex16();
							const MTLIndexType indexFormat = isIndex16 ? MTLIndexTypeUInt16 : MTLIndexTypeUInt32;
							const IndexBufferMtl& ib       = m_indexBuffers[draw.m_indexBuffer.idx];

							numDrawIndirect = UINT16_MAX == draw.m_numIndirect
								? vb.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
								: draw.m_numIndirect
								;

							for (uint32_t ii = 0; ii < numDrawIndirect; ++ii)
							{
								rce.drawIndexedPrimitives(prim.m_type, indexFormat, ib.m_ptr, 0, vb.m_ptr, (draw.m_startIndirect + ii )* BGFX_CONFIG_DRAW_INDIRECT_STRIDE);
							}
						}
						else
						{
							numDrawIndirect = UINT16_MAX == draw.m_numIndirect
								? vb.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
								: draw.m_numIndirect
								;

							for (uint32_t ii = 0; ii < numDrawIndirect; ++ii)
							{
								rce.drawPrimitives(prim.m_type, vb.m_ptr, (draw.m_startIndirect + ii) * BGFX_CONFIG_DRAW_INDIRECT_STRIDE);
							}
						}
					}
					else
					{
						if (isValid(draw.m_indexBuffer) )
						{
							const bool isIndex16           = draw.isIndex16();
							const uint32_t indexSize       = isIndex16 ? 2 : 4;
							const MTLIndexType indexFormat = isIndex16 ? MTLIndexTypeUInt16 : MTLIndexTypeUInt32;
							const IndexBufferMtl& ib       = m_indexBuffers[draw.m_indexBuffer.idx];

							if (UINT32_MAX == draw.m_numIndices)
							{
								numIndices        = ib.m_size/indexSize;
								numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
								numInstances      = draw.m_numInstances;
								numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

								rce.drawIndexedPrimitives(prim.m_type, numIndices, indexFormat, ib.m_ptr, 0, draw.m_numInstances);
							}
							else if (prim.m_min <= draw.m_numIndices)
							{
								numIndices        = draw.m_numIndices;
								numPrimsSubmitted = numIndices/prim.m_div - prim.m_sub;
								numInstances      = draw.m_numInstances;
								numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

								rce.drawIndexedPrimitives(prim.m_type, numIndices, indexFormat, ib.m_ptr, draw.m_startIndex * indexSize,numInstances);
							}
						}
						else
						{
							numPrimsSubmitted = numVertices/prim.m_div - prim.m_sub;
							numInstances      = draw.m_numInstances;
							numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

							rce.drawPrimitives(prim.m_type, 0, numVertices, draw.m_numInstances);
						}
					}

					if (hasOcclusionQuery)
					{
						m_occlusionQuery.end(rce);
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
				invalidateCompute();

				setViewType(view, "C");
				BGFX_MTL_PROFILER_END();
				BGFX_MTL_PROFILER_BEGIN(view, kColorCompute);
			}

			submitBlit(bs, BGFX_CONFIG_MAX_VIEWS);

			if (0 < _render->m_numRenderItems)
			{
				captureElapsed = -bx::getHPCounter();
				capture();
				rce = m_renderCommandEncoder;
				captureElapsed += bx::getHPCounter();

				profiler.end();
			}
		}

		if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
		{
			if (0 < _render->m_numRenderItems)
			{
				rce.popDebugGroup();
			}
		}

		BGFX_MTL_PROFILER_END();

		int64_t timeEnd = bx::getHPCounter();
		int64_t frameTime = timeEnd - timeBegin;

		static int64_t min = frameTime;
		static int64_t max = frameTime;
		min = bx::min<int64_t>(min, frameTime);
		max = bx::max<int64_t>(max, frameTime);

		static uint32_t maxGpuLatency = 0;
		static double   maxGpuElapsed = 0.0f;
		double elapsedGpuMs = 0.0;

		do
		{
			double toGpuMs = 1000.0 / double(m_gpuTimer.m_frequency);
			elapsedGpuMs   = m_gpuTimer.m_elapsed * toGpuMs;
			maxGpuElapsed  = elapsedGpuMs > maxGpuElapsed ? elapsedGpuMs : maxGpuElapsed;
		}
		while (m_gpuTimer.get() );

		maxGpuLatency = bx::uint32_imax(maxGpuLatency, m_gpuTimer.m_control.available()-1);

		const int64_t timerFreq = bx::getHPFrequency();

		Stats& perfStats = _render->m_perfStats;
		perfStats.cpuTimeBegin  = timeBegin;
		perfStats.cpuTimeEnd    = timeEnd;
		perfStats.cpuTimerFreq  = timerFreq;
		perfStats.gpuTimeBegin  = m_gpuTimer.m_begin;
		perfStats.gpuTimeEnd    = m_gpuTimer.m_end;
		perfStats.gpuTimerFreq  = m_gpuTimer.m_frequency;
		perfStats.numDraw       = statsKeyType[0];
		perfStats.numCompute    = statsKeyType[1];
		perfStats.numBlit       = _render->m_numBlitItems;
		perfStats.maxGpuLatency = maxGpuLatency;
		bx::memCopy(perfStats.numPrims, statsNumPrimsRendered, sizeof(perfStats.numPrims) );
		perfStats.gpuMemoryMax  = -INT64_MAX;
		perfStats.gpuMemoryUsed = -INT64_MAX;

		rce.setTriangleFillMode(MTLTriangleFillModeFill);
		if (_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
			rce.pushDebugGroup("debugstats");

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
				tvm.printf(10, pos++, 0x8b, "    Submitted: %4d (draw %4d, compute %4d) / CPU %3.4f [ms] %c GPU %3.4f [ms] (latency %d)"
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
				double captureMs = double(captureElapsed)*toMs;
				tvm.printf(10, pos++, 0x8b, "     Capture: %3.4f [ms]", captureMs);

				uint8_t attr[2] = { 0x8c, 0x8a };
				uint8_t attrIndex = _render->m_waitSubmit < _render->m_waitRender;

				tvm.printf(10, pos++, attr[attrIndex    &1], " Submit wait: %3.4f [ms]", _render->m_waitSubmit*toMs);
				tvm.printf(10, pos++, attr[(attrIndex+1)&1], " Render wait: %3.4f [ms]", _render->m_waitRender*toMs);

				min = frameTime;
				max = frameTime;
			}

			blit(this, _textVideoMemBlitter, tvm);
			rce = m_renderCommandEncoder;

			rce.popDebugGroup();
		}
		else if (_render->m_debug & BGFX_DEBUG_TEXT)
		{
			rce.pushDebugGroup("debugtext");

			blit(this, _textVideoMemBlitter, _render->m_textVideoMem);
			rce = m_renderCommandEncoder;

			rce.popDebugGroup();
		}

		endEncoding();
		m_renderCommandEncoderFrameBufferHandle.idx = kInvalidHandle;

		if (m_screenshotTarget)
		{
			RenderPassDescriptor renderPassDescriptor = newRenderPassDescriptor();
			renderPassDescriptor.colorAttachments[0].texture = m_mainFrameBuffer.m_swapChain->currentDrawableTexture();
			renderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;

			rce =  m_commandBuffer.renderCommandEncoderWithDescriptor(renderPassDescriptor);

			MTL_RELEASE(renderPassDescriptor);

			rce.setCullMode(MTLCullModeNone);

			rce.setRenderPipelineState(m_screenshotBlitRenderPipelineState);

			rce.setFragmentSamplerState(getSamplerState(BGFX_SAMPLER_U_CLAMP|BGFX_SAMPLER_V_CLAMP|BGFX_SAMPLER_MIN_POINT|BGFX_SAMPLER_MAG_POINT|BGFX_SAMPLER_MIP_POINT), 0);
			rce.setFragmentTexture(m_screenshotTarget, 0);

			rce.drawPrimitives(MTLPrimitiveTypeTriangle, 0, 3, 1);

			rce.endEncoding();
		}
	}

} /* namespace mtl */ } // namespace bgfx

#else

namespace bgfx { namespace mtl
	{
		RendererContextI* rendererCreate(const Init& _init)
		{
			BX_UNUSED(_init);
			return NULL;
		}

		void rendererDestroy()
		{
		}
	} /* namespace mtl */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_METAL

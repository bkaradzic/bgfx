/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_VULKAN
#	include "renderer_vk.h"

#if BX_PLATFORM_OSX
#	import <Cocoa/Cocoa.h>
#	import <Foundation/Foundation.h>
#	import <QuartzCore/QuartzCore.h>
#	import <Metal/Metal.h>
#endif // BX_PLATFORM_OSX

namespace bgfx { namespace vk
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
		VkPrimitiveTopology m_topology;
		uint32_t m_min;
		uint32_t m_div;
		uint32_t m_sub;
	};

	static const PrimInfo s_primInfo[] =
	{
		{ VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,  3, 3, 0 },
		{ VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP, 3, 1, 2 },
		{ VK_PRIMITIVE_TOPOLOGY_LINE_LIST,      2, 2, 0 },
		{ VK_PRIMITIVE_TOPOLOGY_LINE_STRIP,     2, 1, 1 },
		{ VK_PRIMITIVE_TOPOLOGY_POINT_LIST,     1, 1, 0 },
		{ VK_PRIMITIVE_TOPOLOGY_MAX_ENUM,       0, 0, 0 },
	};
	BX_STATIC_ASSERT(Topology::Count == BX_COUNTOF(s_primInfo)-1);

	static const uint32_t s_checkMsaa[] =
	{
		0,
		2,
		4,
		8,
		16,
	};

	static MsaaSamplerVK s_msaa[] =
	{
		{  1, VK_SAMPLE_COUNT_1_BIT },
		{  2, VK_SAMPLE_COUNT_2_BIT },
		{  4, VK_SAMPLE_COUNT_4_BIT },
		{  8, VK_SAMPLE_COUNT_8_BIT },
		{ 16, VK_SAMPLE_COUNT_16_BIT },
	};

	static const VkBlendFactor s_blendFactor[][2] =
	{
		{ VkBlendFactor(0),                         VkBlendFactor(0)                         }, // ignored
		{ VK_BLEND_FACTOR_ZERO,                     VK_BLEND_FACTOR_ZERO                     }, // ZERO
		{ VK_BLEND_FACTOR_ONE,                      VK_BLEND_FACTOR_ONE                      }, // ONE
		{ VK_BLEND_FACTOR_SRC_COLOR,                VK_BLEND_FACTOR_SRC_ALPHA                }, // SRC_COLOR
		{ VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR,      VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA      }, // INV_SRC_COLOR
		{ VK_BLEND_FACTOR_SRC_ALPHA,                VK_BLEND_FACTOR_SRC_ALPHA                }, // SRC_ALPHA
		{ VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,      VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA      }, // INV_SRC_ALPHA
		{ VK_BLEND_FACTOR_DST_ALPHA,                VK_BLEND_FACTOR_DST_ALPHA                }, // DST_ALPHA
		{ VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA,      VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA      }, // INV_DST_ALPHA
		{ VK_BLEND_FACTOR_DST_COLOR,                VK_BLEND_FACTOR_DST_ALPHA                }, // DST_COLOR
		{ VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR,      VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA      }, // INV_DST_COLOR
		{ VK_BLEND_FACTOR_SRC_ALPHA,                VK_BLEND_FACTOR_ONE                      }, // SRC_ALPHA_SAT
		{ VK_BLEND_FACTOR_CONSTANT_COLOR,           VK_BLEND_FACTOR_CONSTANT_COLOR           }, // FACTOR
		{ VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR, VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR }, // INV_FACTOR
	};

	static const VkBlendOp s_blendEquation[] =
	{
		VK_BLEND_OP_ADD,
		VK_BLEND_OP_SUBTRACT,
		VK_BLEND_OP_REVERSE_SUBTRACT,
		VK_BLEND_OP_MIN,
		VK_BLEND_OP_MAX,
	};

	static const VkCompareOp s_cmpFunc[] =
	{
		VkCompareOp(0), // ignored
		VK_COMPARE_OP_LESS,
		VK_COMPARE_OP_LESS_OR_EQUAL,
		VK_COMPARE_OP_EQUAL,
		VK_COMPARE_OP_GREATER_OR_EQUAL,
		VK_COMPARE_OP_GREATER,
		VK_COMPARE_OP_NOT_EQUAL,
		VK_COMPARE_OP_NEVER,
		VK_COMPARE_OP_ALWAYS,
	};

	static const VkStencilOp s_stencilOp[] =
	{
		VK_STENCIL_OP_ZERO,
		VK_STENCIL_OP_KEEP,
		VK_STENCIL_OP_REPLACE,
		VK_STENCIL_OP_INCREMENT_AND_WRAP,
		VK_STENCIL_OP_INCREMENT_AND_CLAMP,
		VK_STENCIL_OP_DECREMENT_AND_WRAP,
		VK_STENCIL_OP_DECREMENT_AND_CLAMP,
		VK_STENCIL_OP_INVERT,
	};

	static const VkCullModeFlagBits s_cullMode[] =
	{
		VK_CULL_MODE_NONE,
		VK_CULL_MODE_FRONT_BIT,
		VK_CULL_MODE_BACK_BIT,
	};

	static const VkSamplerAddressMode s_textureAddress[] =
	{
		VK_SAMPLER_ADDRESS_MODE_REPEAT,
		VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT,
		VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
		VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,
	};

	struct PresentMode
	{
		VkPresentModeKHR mode;
		bool             vsync;
		const char*      name;
	};

	static const PresentMode s_presentMode[] =
	{
		{ VK_PRESENT_MODE_FIFO_KHR,         true,  "VK_PRESENT_MODE_FIFO_KHR"         },
		{ VK_PRESENT_MODE_FIFO_RELAXED_KHR, true,  "VK_PRESENT_MODE_FIFO_RELAXED_KHR" },
		{ VK_PRESENT_MODE_MAILBOX_KHR,      true,  "VK_PRESENT_MODE_MAILBOX_KHR"      },
		{ VK_PRESENT_MODE_IMMEDIATE_KHR,    false, "VK_PRESENT_MODE_IMMEDIATE_KHR"    },
	};

#define VK_IMPORT_FUNC(_optional, _func) PFN_##_func _func
#define VK_IMPORT_INSTANCE_FUNC VK_IMPORT_FUNC
#define VK_IMPORT_DEVICE_FUNC   VK_IMPORT_FUNC
VK_IMPORT
VK_IMPORT_INSTANCE
VK_IMPORT_DEVICE
#undef VK_IMPORT_DEVICE_FUNC
#undef VK_IMPORT_INSTANCE_FUNC
#undef VK_IMPORT_FUNC

	struct TextureFormatInfo
	{
		VkFormat m_fmt;
		VkFormat m_fmtSrv;
		VkFormat m_fmtDsv;
		VkFormat m_fmtSrgb;
		VkComponentMapping m_mapping;
	};

	static const TextureFormatInfo s_textureFormat[] =
	{
		{ VK_FORMAT_BC1_RGB_UNORM_BLOCK,       VK_FORMAT_BC1_RGB_UNORM_BLOCK,      VK_FORMAT_UNDEFINED,           VK_FORMAT_BC1_RGB_SRGB_BLOCK,       { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // BC1
		{ VK_FORMAT_BC2_UNORM_BLOCK,           VK_FORMAT_BC2_UNORM_BLOCK,          VK_FORMAT_UNDEFINED,           VK_FORMAT_BC2_SRGB_BLOCK,           { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // BC2
		{ VK_FORMAT_BC3_UNORM_BLOCK,           VK_FORMAT_BC3_UNORM_BLOCK,          VK_FORMAT_UNDEFINED,           VK_FORMAT_BC3_SRGB_BLOCK,           { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // BC3
		{ VK_FORMAT_BC4_UNORM_BLOCK,           VK_FORMAT_BC4_UNORM_BLOCK,          VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // BC4
		{ VK_FORMAT_BC5_UNORM_BLOCK,           VK_FORMAT_BC5_UNORM_BLOCK,          VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // BC5
		{ VK_FORMAT_BC6H_SFLOAT_BLOCK,         VK_FORMAT_BC6H_SFLOAT_BLOCK,        VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // BC6H
		{ VK_FORMAT_BC7_UNORM_BLOCK,           VK_FORMAT_BC7_UNORM_BLOCK,          VK_FORMAT_UNDEFINED,           VK_FORMAT_BC7_SRGB_BLOCK,           { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // BC7
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // ETC1
		{ VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK,   VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK,   { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // ETC2
		{ VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK, VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK, { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // ETC2A
		{ VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK, VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK, { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // ETC2A1
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // PTC12
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // PTC14
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // PTC12A
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // PTC14A
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // PTC22
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // PTC24
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // ATC
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // ATCE
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // ATCI
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // ASTC4x4
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // ASTC5x5
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // ASTC6x6
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // ASTC8x5
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // ASTC8x6
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // ASTC10x5
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // Unknown
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // R1
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // A8
		{ VK_FORMAT_R8_UNORM,                  VK_FORMAT_R8_UNORM,                 VK_FORMAT_UNDEFINED,           VK_FORMAT_R8_SRGB,                  { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // R8
		{ VK_FORMAT_R8_SINT,                   VK_FORMAT_R8_SINT,                  VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // R8I
		{ VK_FORMAT_R8_UINT,                   VK_FORMAT_R8_UINT,                  VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // R8U
		{ VK_FORMAT_R8_SNORM,                  VK_FORMAT_R8_SNORM,                 VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // R8S
		{ VK_FORMAT_R16_UNORM,                 VK_FORMAT_R16_UNORM,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // R16
		{ VK_FORMAT_R16_SINT,                  VK_FORMAT_R16_SINT,                 VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // R16I
		{ VK_FORMAT_R16_UNORM,                 VK_FORMAT_R16_UNORM,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // R16U
		{ VK_FORMAT_R16_SFLOAT,                VK_FORMAT_R16_SFLOAT,               VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // R16F
		{ VK_FORMAT_R16_SNORM,                 VK_FORMAT_R16_SNORM,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // R16S
		{ VK_FORMAT_R32_SINT,                  VK_FORMAT_R32_SINT,                 VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // R32I
		{ VK_FORMAT_R32_UINT,                  VK_FORMAT_R32_UINT,                 VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // R32U
		{ VK_FORMAT_R32_SFLOAT,                VK_FORMAT_R32_SFLOAT,               VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // R32F
		{ VK_FORMAT_R8G8_UNORM,                VK_FORMAT_R8G8_UNORM,               VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8_SRGB,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RG8
		{ VK_FORMAT_R8G8_SINT,                 VK_FORMAT_R8G8_SINT,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RG8I
		{ VK_FORMAT_R8G8_UINT,                 VK_FORMAT_R8G8_UINT,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RG8U
		{ VK_FORMAT_R8G8_SNORM,                VK_FORMAT_R8G8_SNORM,               VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RG8S
		{ VK_FORMAT_R16G16_UNORM,              VK_FORMAT_R16G16_UNORM,             VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RG16
		{ VK_FORMAT_R16G16_SINT,               VK_FORMAT_R16G16_SINT,              VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RG16I
		{ VK_FORMAT_R16G16_UINT,               VK_FORMAT_R16G16_UINT,              VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RG16U
		{ VK_FORMAT_R16G16_SFLOAT,             VK_FORMAT_R16G16_SFLOAT,            VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RG16F
		{ VK_FORMAT_R16G16_SNORM,              VK_FORMAT_R16G16_SNORM,             VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RG16S
		{ VK_FORMAT_R32G32_SINT,               VK_FORMAT_R32G32_SINT,              VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RG32I
		{ VK_FORMAT_R32G32_UINT,               VK_FORMAT_R32G32_UINT,              VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RG32U
		{ VK_FORMAT_R32G32_SFLOAT,             VK_FORMAT_R32G32_SFLOAT,            VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RG32F
		{ VK_FORMAT_R8G8B8_UNORM,              VK_FORMAT_R8G8B8_UNORM,             VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8B8_SRGB,              { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGB8
		{ VK_FORMAT_R8G8B8_SINT,               VK_FORMAT_R8G8B8_SINT,              VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8B8_SRGB,              { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGB8I
		{ VK_FORMAT_R8G8B8_UINT,               VK_FORMAT_R8G8B8_UINT,              VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8B8_SRGB,              { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGB8U
		{ VK_FORMAT_R8G8B8_SNORM,              VK_FORMAT_R8G8B8_SNORM,             VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGB8S
		{ VK_FORMAT_E5B9G9R9_UFLOAT_PACK32,    VK_FORMAT_E5B9G9R9_UFLOAT_PACK32,   VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGB9E5F
		{ VK_FORMAT_B8G8R8A8_UNORM,            VK_FORMAT_B8G8R8A8_UNORM,           VK_FORMAT_UNDEFINED,           VK_FORMAT_B8G8R8A8_SRGB,            { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // BGRA8
		{ VK_FORMAT_R8G8B8A8_UNORM,            VK_FORMAT_R8G8B8A8_UNORM,           VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8B8A8_SRGB,            { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGBA8
		{ VK_FORMAT_R8G8B8A8_SINT,             VK_FORMAT_R8G8B8A8_SINT,            VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8B8A8_SRGB,            { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGBA8I
		{ VK_FORMAT_R8G8B8A8_UINT,             VK_FORMAT_R8G8B8A8_UINT,            VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8B8A8_SRGB,            { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGBA8U
		{ VK_FORMAT_R8G8B8A8_SNORM,            VK_FORMAT_R8G8B8A8_SNORM,           VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGBA8S
		{ VK_FORMAT_R16G16B16A16_UNORM,        VK_FORMAT_R16G16B16A16_UNORM,       VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGBA16
		{ VK_FORMAT_R16G16B16A16_SINT,         VK_FORMAT_R16G16B16A16_SINT,        VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGBA16I
		{ VK_FORMAT_R16G16B16A16_UINT,         VK_FORMAT_R16G16B16A16_UINT,        VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGBA16U
		{ VK_FORMAT_R16G16B16A16_SFLOAT,       VK_FORMAT_R16G16B16A16_SFLOAT,      VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGBA16F
		{ VK_FORMAT_R16G16B16A16_SNORM,        VK_FORMAT_R16G16B16A16_SNORM,       VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGBA16S
		{ VK_FORMAT_R32G32B32A32_SINT,         VK_FORMAT_R32G32B32A32_SINT,        VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGBA32I
		{ VK_FORMAT_R32G32B32A32_UINT,         VK_FORMAT_R32G32B32A32_UINT,        VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGBA32U
		{ VK_FORMAT_R32G32B32A32_SFLOAT,       VK_FORMAT_R32G32B32A32_SFLOAT,      VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGBA32F
		{ VK_FORMAT_B5G6R5_UNORM_PACK16,       VK_FORMAT_B5G6R5_UNORM_PACK16,      VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // R5G6B5
		{ VK_FORMAT_B4G4R4A4_UNORM_PACK16,     VK_FORMAT_B4G4R4A4_UNORM_PACK16,    VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_G,        VK_COMPONENT_SWIZZLE_R,        VK_COMPONENT_SWIZZLE_A,        VK_COMPONENT_SWIZZLE_B        } }, // RGBA4
		{ VK_FORMAT_A1R5G5B5_UNORM_PACK16,     VK_FORMAT_A1R5G5B5_UNORM_PACK16,    VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGB5A1
		{ VK_FORMAT_A2R10G10B10_UNORM_PACK32,  VK_FORMAT_A2R10G10B10_UNORM_PACK32, VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RGB10A2
		{ VK_FORMAT_B10G11R11_UFLOAT_PACK32,   VK_FORMAT_B10G11R11_UFLOAT_PACK32,  VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // RG11B10F
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // UnknownDepth
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_R16_UNORM,                VK_FORMAT_D16_UNORM,           VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // D16
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_X8_D24_UNORM_PACK32,      VK_FORMAT_D24_UNORM_S8_UINT,   VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // D24
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_X8_D24_UNORM_PACK32,      VK_FORMAT_D24_UNORM_S8_UINT,   VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // D24S8
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_X8_D24_UNORM_PACK32,      VK_FORMAT_D24_UNORM_S8_UINT,   VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // D32
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_R32_SFLOAT,               VK_FORMAT_D32_SFLOAT,          VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // D16F
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_R32_SFLOAT,               VK_FORMAT_D32_SFLOAT,          VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // D24F
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_R32_SFLOAT,               VK_FORMAT_D32_SFLOAT,          VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // D32F
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_X8_D24_UNORM_PACK32,      VK_FORMAT_D24_UNORM_S8_UINT,   VK_FORMAT_UNDEFINED,                { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY } }, // D0S8
	};
	BX_STATIC_ASSERT(TextureFormat::Count == BX_COUNTOF(s_textureFormat) );

	struct LayerInfo
	{
		bool m_supported;
		bool m_initialize;
	};

	struct Layer
	{
		enum Enum
		{
			VK_LAYER_LUNARG_standard_validation,
			VK_LAYER_LUNARG_vktrace,
			VK_LAYER_KHRONOS_validation,

			Count
		};

		const char* m_name;
		uint32_t m_minVersion;
		LayerInfo m_instance;
		LayerInfo m_device;
	};


	// Layer registry
	//
	static Layer s_layer[] =
	{
		{ "VK_LAYER_LUNARG_standard_validation",  1, { false, BGFX_CONFIG_DEBUG }, { false, false             } },
		{ "VK_LAYER_LUNARG_vktrace",              1, { false, false             }, { false, false             } },
		{ "VK_LAYER_KHRONOS_validation",          1, { false, BGFX_CONFIG_DEBUG }, { false, BGFX_CONFIG_DEBUG } },
	};
	BX_STATIC_ASSERT(Layer::Count == BX_COUNTOF(s_layer) );

	void updateLayer(const char* _name, uint32_t _version, bool _instanceLayer)
	{
		bx::StringView lyr(_name);

		for (uint32_t ii = 0; ii < Layer::Count; ++ii)
		{
			Layer& layer = s_layer[ii];
			LayerInfo& layerInfo = _instanceLayer ? layer.m_instance : layer.m_device;
			if (!layerInfo.m_supported && layerInfo.m_initialize)
			{
				if (       0 == bx::strCmp(lyr, layer.m_name)
				&&  _version >= layer.m_minVersion)
				{
					layerInfo.m_supported = true;
					break;
				}
			}
		}
	}

	struct Extension
	{
		enum Enum
		{
			EXT_debug_utils,
			EXT_debug_report,
			EXT_memory_budget,
			KHR_get_physical_device_properties2,

			Count
		};

		const char* m_name;
		uint32_t m_minVersion;
		bool m_instanceExt;
		bool m_supported;
		bool m_initialize;
		Layer::Enum m_layer;
	};

	// Extension registry
	//
	static Extension s_extension[] =
	{
		{ "VK_EXT_debug_utils",                     1, false, false, BGFX_CONFIG_DEBUG_OBJECT_NAME, Layer::Count },
		{ "VK_EXT_debug_report",                    1, false, false, BGFX_CONFIG_DEBUG            , Layer::Count },
		{ "VK_EXT_memory_budget",                   1, false, false, true                         , Layer::Count },
		{ "VK_KHR_get_physical_device_properties2", 1, false, false, true                         , Layer::Count },
	};
	BX_STATIC_ASSERT(Extension::Count == BX_COUNTOF(s_extension) );

	bool updateExtension(const char* _name, uint32_t _version, bool _instanceExt)
	{
		bx::StringView ext(_name);

		bool supported = false;
		for (uint32_t ii = 0; ii < Extension::Count; ++ii)
		{
			Extension& extension = s_extension[ii];
			LayerInfo& layerInfo = _instanceExt
				? s_layer[extension.m_layer].m_instance
				: s_layer[extension.m_layer].m_device
				;

			if (!extension.m_supported
			&&   extension.m_initialize
			&&  (extension.m_layer == Layer::Count || layerInfo.m_supported) )
			{
				if (       0 == bx::strCmp(ext, extension.m_name)
				&&  _version >= extension.m_minVersion)
				{
					extension.m_supported   = true;
					extension.m_instanceExt = _instanceExt;
					supported = true;
					break;
				}
			}
		}

		return supported;
	}

	static const VkFormat s_attribType[][4][2] =
	{
		{ // Uint8
			{ VK_FORMAT_R8_UINT,                 VK_FORMAT_R8_UNORM                 },
			{ VK_FORMAT_R8G8_UINT,               VK_FORMAT_R8G8_UNORM               },
			{ VK_FORMAT_R8G8B8A8_UINT,           VK_FORMAT_R8G8B8A8_UNORM           },
			{ VK_FORMAT_R8G8B8A8_UINT,           VK_FORMAT_R8G8B8A8_UNORM           },
		},
		{ // Uint10
			{ VK_FORMAT_A2R10G10B10_UINT_PACK32, VK_FORMAT_A2R10G10B10_UNORM_PACK32 },
			{ VK_FORMAT_A2R10G10B10_UINT_PACK32, VK_FORMAT_A2R10G10B10_UNORM_PACK32 },
			{ VK_FORMAT_A2R10G10B10_UINT_PACK32, VK_FORMAT_A2R10G10B10_UNORM_PACK32 },
			{ VK_FORMAT_A2R10G10B10_UINT_PACK32, VK_FORMAT_A2R10G10B10_UNORM_PACK32 },
		},
		{ // Int16
			{ VK_FORMAT_R16_SINT,                VK_FORMAT_R16_SNORM                },
			{ VK_FORMAT_R16G16_SINT,             VK_FORMAT_R16G16_SNORM             },
			{ VK_FORMAT_R16G16B16_SINT,          VK_FORMAT_R16G16B16_SNORM          },
			{ VK_FORMAT_R16G16B16A16_SINT,       VK_FORMAT_R16G16B16A16_SNORM       },
		},
		{ // Half
			{ VK_FORMAT_R16_SFLOAT,              VK_FORMAT_R16_SFLOAT               },
			{ VK_FORMAT_R16G16_SFLOAT,           VK_FORMAT_R16G16_SFLOAT            },
			{ VK_FORMAT_R16G16B16_SFLOAT,        VK_FORMAT_R16G16B16_SFLOAT         },
			{ VK_FORMAT_R16G16B16A16_SFLOAT,     VK_FORMAT_R16G16B16A16_SFLOAT      },
		},
		{ // Float
			{ VK_FORMAT_R32_SFLOAT,              VK_FORMAT_R32_SFLOAT               },
			{ VK_FORMAT_R32G32_SFLOAT,           VK_FORMAT_R32G32_SFLOAT            },
			{ VK_FORMAT_R32G32B32_SFLOAT,        VK_FORMAT_R32G32B32_SFLOAT         },
			{ VK_FORMAT_R32G32B32A32_SFLOAT,     VK_FORMAT_R32G32B32A32_SFLOAT      },
		},
	};
	BX_STATIC_ASSERT(AttribType::Count == BX_COUNTOF(s_attribType) );

	void fillVertexLayout(const ShaderVK* _vsh, VkPipelineVertexInputStateCreateInfo& _vertexInputState, const VertexLayout& _layout)
	{
		uint32_t numBindings = _vertexInputState.vertexBindingDescriptionCount;
		uint32_t numAttribs  = _vertexInputState.vertexAttributeDescriptionCount;
		VkVertexInputBindingDescription*   inputBinding = const_cast<VkVertexInputBindingDescription*>(_vertexInputState.pVertexBindingDescriptions + numBindings);
		VkVertexInputAttributeDescription* inputAttrib  = const_cast<VkVertexInputAttributeDescription*>(_vertexInputState.pVertexAttributeDescriptions + numAttribs);

		inputBinding->binding   = numBindings;
		inputBinding->stride    = _layout.m_stride;
		inputBinding->inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		for (uint32_t attr = 0; attr < Attrib::Count; ++attr)
		{
			if (UINT16_MAX != _layout.m_attributes[attr])
			{
				inputAttrib->location = _vsh->m_attrRemap[attr];
				inputAttrib->binding  = numBindings;

				uint8_t num;
				AttribType::Enum type;
				bool normalized;
				bool asInt;
				_layout.decode(Attrib::Enum(attr), num, type, normalized, asInt);
				inputAttrib->format = s_attribType[type][num-1][normalized];
				inputAttrib->offset = _layout.m_offset[attr];

				++inputAttrib;
				++numAttribs;
			}
		}

		_vertexInputState.vertexBindingDescriptionCount   = numBindings + 1;
		_vertexInputState.vertexAttributeDescriptionCount = numAttribs;
	}

	void fillInstanceBinding(const ShaderVK* _vsh, VkPipelineVertexInputStateCreateInfo& _vertexInputState, uint32_t _numInstanceData)
	{
		BX_UNUSED(_vsh);

		uint32_t numBindings = _vertexInputState.vertexBindingDescriptionCount;
		uint32_t numAttribs  = _vertexInputState.vertexAttributeDescriptionCount;
		VkVertexInputBindingDescription*   inputBinding = const_cast<VkVertexInputBindingDescription*>(_vertexInputState.pVertexBindingDescriptions + numBindings);
		VkVertexInputAttributeDescription* inputAttrib  = const_cast<VkVertexInputAttributeDescription*>(_vertexInputState.pVertexAttributeDescriptions + numAttribs);

		inputBinding->binding   = numBindings;
		inputBinding->stride    = _numInstanceData * 16;
		inputBinding->inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;

		for (uint32_t inst = 0; inst < _numInstanceData; ++inst)
		{
			inputAttrib->location = numAttribs;
			inputAttrib->binding  = numBindings;
			inputAttrib->format   = VK_FORMAT_R32G32B32A32_SFLOAT;
			inputAttrib->offset   = inst * 16;

			++numAttribs;
			++inputAttrib;
		}

		_vertexInputState.vertexBindingDescriptionCount   = numBindings + 1;
		_vertexInputState.vertexAttributeDescriptionCount = numAttribs;
	}

	static const char* s_deviceTypeName[] =
	{
		"Other",
		"Integrated GPU",
		"Discrete GPU",
		"Virtual GPU",
		"CPU",

		"Unknown?!"
	};

	const char* getName(VkPhysicalDeviceType _type)
	{
		return s_deviceTypeName[bx::min<int32_t>(_type, BX_COUNTOF(s_deviceTypeName) )];
	}

	static const char* s_allocScopeName[] =
	{
		"vkCommand",
		"vkObject",
		"vkCache",
		"vkDevice",
		"vkInstance",
	};
	BX_STATIC_ASSERT(VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE == BX_COUNTOF(s_allocScopeName)-1);

	static void* VKAPI_PTR allocationFunction(void* _userData, size_t _size, size_t _alignment, VkSystemAllocationScope _allocationScope)
	{
		BX_UNUSED(_userData, _allocationScope);
		return bx::alignedAlloc(g_allocator, _size, _alignment, s_allocScopeName[_allocationScope]);
	}

	static void* VKAPI_PTR reallocationFunction(void* _userData, void* _original, size_t _size, size_t _alignment, VkSystemAllocationScope _allocationScope)
	{
		BX_UNUSED(_userData, _allocationScope);
		return bx::alignedRealloc(g_allocator, _original, _size, _alignment, s_allocScopeName[_allocationScope]);
	}

	static void VKAPI_PTR freeFunction(void* _userData, void* _memory)
	{
		BX_UNUSED(_userData);

		if (NULL == _memory)
		{
			return;
		}

		bx::alignedFree(g_allocator, _memory, 8);
	}

	static void VKAPI_PTR internalAllocationNotification(void* _userData, size_t _size, VkInternalAllocationType _allocationType, VkSystemAllocationScope _allocationScope)
	{
		BX_UNUSED(_userData, _size, _allocationType, _allocationScope);
	}

	static void VKAPI_PTR internalFreeNotification(void* _userData, size_t _size, VkInternalAllocationType _allocationType, VkSystemAllocationScope _allocationScope)
	{
		BX_UNUSED(_userData, _size, _allocationType, _allocationScope);
	}

	static VkAllocationCallbacks s_allocationCb =
	{
		NULL,
		allocationFunction,
		reallocationFunction,
		freeFunction,
		internalAllocationNotification,
		internalFreeNotification,
	};

	VkResult VKAPI_PTR stubSetDebugUtilsObjectNameEXT(VkDevice _device, const VkDebugUtilsObjectNameInfoEXT* _nameInfo)
	{
		BX_UNUSED(_device, _nameInfo);
		return VK_SUCCESS;
	}

	void VKAPI_PTR stubCmdInsertDebugUtilsLabelEXT(VkCommandBuffer _commandBuffer, const VkDebugUtilsLabelEXT* _labelInfo)
	{
		BX_UNUSED(_commandBuffer, _labelInfo);
	}

	void VKAPI_PTR stubCmdBeginDebugUtilsLabelEXT(VkCommandBuffer _commandBuffer, const VkDebugUtilsLabelEXT* _labelInfo)
	{
		BX_UNUSED(_commandBuffer, _labelInfo);
	}

	void VKAPI_PTR stubCmdEndDebugUtilsLabelEXT(VkCommandBuffer _commandBuffer)
	{
		BX_UNUSED(_commandBuffer);
	}

	static const char* s_debugReportObjectType[] =
	{
		"Unknown",
		"Instance",
		"PhysicalDevice",
		"Device",
		"Queue",
		"Semaphore",
		"CommandBuffer",
		"Fence",
		"DeviceMemory",
		"Buffer",
		"Image",
		"Event",
		"QueryPool",
		"BufferView",
		"ImageView",
		"ShaderModule",
		"PipelineCache",
		"PipelineLayout",
		"RenderPass",
		"Pipeline",
		"DescriptorSetLayout",
		"Sampler",
		"DescriptorPool",
		"DescriptorSet",
		"Framebuffer",
		"CommandPool",
		"SurfaceKHR",
		"SwapchainKHR",
		"DebugReport",
	};

	VkBool32 VKAPI_PTR debugReportCb(
		VkDebugReportFlagsEXT _flags,
		VkDebugReportObjectTypeEXT _objectType,
		uint64_t _object,
		size_t _location,
		int32_t _messageCode,
		const char* _layerPrefix,
		const char* _message,
		void* _userData
	)
	{
		BX_UNUSED(_flags
			, _objectType
			, _object
			, _location
			, _messageCode
			, _layerPrefix
			, _message
			, _userData
			, s_debugReportObjectType
		);

		// For more info about 'VUID-VkSwapchainCreateInfoKHR-imageExtent-01274'
		// check https://github.com/KhronosGroup/Vulkan-Docs/issues/1144
		if (!bx::strFind(_message, "PointSizeMissing").isEmpty()
		||  !bx::strFind(_message, "SwapchainTooManyImages").isEmpty()
		||  !bx::strFind(_message, "SwapchainImageNotAcquired").isEmpty()
		||  !bx::strFind(_message, "VUID-VkSwapchainCreateInfoKHR-imageExtent-01274").isEmpty() )
		{
			return VK_FALSE;
		}
		BX_TRACE("%c%c%c%c%c %19s, %s, %d: %s"
			, 0 != (_flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT        ) ? 'I' : '-'
			, 0 != (_flags & VK_DEBUG_REPORT_WARNING_BIT_EXT            ) ? 'W' : '-'
			, 0 != (_flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) ? 'P' : '-'
			, 0 != (_flags & VK_DEBUG_REPORT_ERROR_BIT_EXT              ) ? 'E' : '-'
			, 0 != (_flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT              ) ? 'D' : '-'
			, s_debugReportObjectType[_objectType]
			, _layerPrefix
			, _messageCode
			, _message
			);
		return VK_TRUE;
	}

	VkResult enumerateLayerProperties(VkPhysicalDevice _physicalDevice, uint32_t* _propertyCount, VkLayerProperties* _properties)
	{
		return (VK_NULL_HANDLE == _physicalDevice)
			? vkEnumerateInstanceLayerProperties(_propertyCount, _properties)
			: vkEnumerateDeviceLayerProperties(_physicalDevice, _propertyCount, _properties)
			;
	}

	VkResult enumerateExtensionProperties(VkPhysicalDevice _physicalDevice, const char* _layerName, uint32_t* _propertyCount, VkExtensionProperties* _properties)
	{
		return (VK_NULL_HANDLE == _physicalDevice)
			? vkEnumerateInstanceExtensionProperties(_layerName, _propertyCount, _properties)
			: vkEnumerateDeviceExtensionProperties(_physicalDevice, _layerName, _propertyCount, _properties)
			;
	}

	void dumpExtensions(VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE)
	{
		{ // Global extensions.
			uint32_t numExtensionProperties;
			VkResult result = enumerateExtensionProperties(_physicalDevice
				, NULL
				, &numExtensionProperties
				, NULL
				);

			if (VK_SUCCESS == result
			&&  0 < numExtensionProperties)
			{
				VkExtensionProperties extensionProperties[64];
				numExtensionProperties = bx::min<uint32_t>(numExtensionProperties, BX_COUNTOF(extensionProperties) );
				result = enumerateExtensionProperties(_physicalDevice
					, NULL
					, &numExtensionProperties
					, extensionProperties
					);

				BX_TRACE("Global extensions (%d):"
					, numExtensionProperties
					);

				for (uint32_t extension = 0; extension < numExtensionProperties; ++extension)
				{
					bool supported = updateExtension(
						  extensionProperties[extension].extensionName
						, extensionProperties[extension].specVersion
						, VK_NULL_HANDLE == _physicalDevice
						);

					BX_TRACE("\tv%-3d %s%s"
						, extensionProperties[extension].specVersion
						, extensionProperties[extension].extensionName
						, supported ? " (supported)" : "", extensionProperties[extension].extensionName // FIXME: maybe include here the layer name?
						);

					BX_UNUSED(supported);
				}
			}
		}

		// Layer extensions.
		uint32_t numLayerProperties;
		VkResult result = enumerateLayerProperties(_physicalDevice, &numLayerProperties, NULL);

		if (VK_SUCCESS == result
		&&  0 < numLayerProperties)
		{
			VkLayerProperties layerProperties[64];
			numLayerProperties = bx::min<uint32_t>(numLayerProperties, BX_COUNTOF(layerProperties) );
			result = enumerateLayerProperties(_physicalDevice, &numLayerProperties, layerProperties);

			char indent = VK_NULL_HANDLE == _physicalDevice ? '\0' : '\t';
			BX_UNUSED(indent);

			BX_TRACE("%cLayer extensions (%d):"
				, indent
				, numLayerProperties
				);
			for (uint32_t layer = 0; layer < numLayerProperties; ++layer)
			{
				updateLayer(
					layerProperties[layer].layerName
					, layerProperties[layer].implementationVersion
					, VK_NULL_HANDLE == _physicalDevice
					);

				BX_TRACE("%c\t%s (s: 0x%08x, i: 0x%08x), %s"
					, indent
					, layerProperties[layer].layerName
					, layerProperties[layer].specVersion
					, layerProperties[layer].implementationVersion
					, layerProperties[layer].description
					);
				uint32_t numExtensionProperties;
				result = enumerateExtensionProperties(_physicalDevice
					, layerProperties[layer].layerName
					, &numExtensionProperties
					, NULL
					);

				if (VK_SUCCESS == result
				&&  0 < numExtensionProperties)
				{
					VkExtensionProperties extensionProperties[64];
					numExtensionProperties = bx::min<uint32_t>(numExtensionProperties, BX_COUNTOF(extensionProperties) );
					result = enumerateExtensionProperties(_physicalDevice
						, layerProperties[layer].layerName
						, &numExtensionProperties
						, extensionProperties
						);

					for (uint32_t extension = 0; extension < numExtensionProperties; ++extension)
					{
						bool supported = updateExtension(
							  extensionProperties[extension].extensionName
							, extensionProperties[extension].specVersion
							, VK_NULL_HANDLE == _physicalDevice
							);

						BX_TRACE("%c\t\t%s (s: 0x%08x)"
							, indent
							, extensionProperties[extension].extensionName
							, extensionProperties[extension].specVersion
							, supported ? " (supported)" : "", extensionProperties[extension].extensionName
							);

						BX_UNUSED(supported);
					}
				}
			}
		}
	}

	const char* getName(VkResult _result)
	{
		switch (_result)
		{
#define VKENUM(_ty) case _ty: return #_ty
			VKENUM(VK_SUCCESS);
			VKENUM(VK_NOT_READY);
			VKENUM(VK_TIMEOUT);
			VKENUM(VK_EVENT_SET);
			VKENUM(VK_EVENT_RESET);
			VKENUM(VK_INCOMPLETE);
			VKENUM(VK_ERROR_OUT_OF_HOST_MEMORY);
			VKENUM(VK_ERROR_OUT_OF_DEVICE_MEMORY);
			VKENUM(VK_ERROR_INITIALIZATION_FAILED);
			VKENUM(VK_ERROR_DEVICE_LOST);
			VKENUM(VK_ERROR_MEMORY_MAP_FAILED);
			VKENUM(VK_ERROR_LAYER_NOT_PRESENT);
			VKENUM(VK_ERROR_EXTENSION_NOT_PRESENT);
			VKENUM(VK_ERROR_FEATURE_NOT_PRESENT);
			VKENUM(VK_ERROR_INCOMPATIBLE_DRIVER);
			VKENUM(VK_ERROR_TOO_MANY_OBJECTS);
			VKENUM(VK_ERROR_FORMAT_NOT_SUPPORTED);
			VKENUM(VK_ERROR_SURFACE_LOST_KHR);
			VKENUM(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR);
			VKENUM(VK_SUBOPTIMAL_KHR);
			VKENUM(VK_ERROR_OUT_OF_DATE_KHR);
			VKENUM(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
			VKENUM(VK_ERROR_VALIDATION_FAILED_EXT);
#undef VKENUM
			default: break;
		}

		BX_WARN(false, "Unknown VkResult? %x", _result);
		return "<VkResult?>";
	}

	template<typename Ty>
	VkObjectType getType();

	template<> VkObjectType getType<VkBuffer      >() { return VK_OBJECT_TYPE_BUFFER;        }
	template<> VkObjectType getType<VkShaderModule>() { return VK_OBJECT_TYPE_SHADER_MODULE; }

	template<typename Ty>
	static BX_NO_INLINE void setDebugObjectName(VkDevice _device, Ty _object, const char* _format, ...)
	{
		if (BX_ENABLED(BGFX_CONFIG_DEBUG_OBJECT_NAME) && s_extension[Extension::EXT_debug_utils].m_supported)
		{
			char temp[2048];
			va_list argList;
			va_start(argList, _format);
			int32_t size = bx::min<int32_t>(sizeof(temp)-1, bx::vsnprintf(temp, sizeof(temp), _format, argList) );
			va_end(argList);
			temp[size] = '\0';

			VkDebugUtilsObjectNameInfoEXT ni;
			ni.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
			ni.pNext = NULL;
			ni.objectType   = getType<Ty>();
			ni.objectHandle = uint64_t(_object.vk);
			ni.pObjectName  = temp;

			VK_CHECK(vkSetDebugUtilsObjectNameEXT(_device, &ni) );
		}
	}

	void setImageMemoryBarrier(VkCommandBuffer _commandBuffer, VkImage _image, VkImageAspectFlags _aspectMask, VkImageLayout _oldLayout, VkImageLayout _newLayout, uint32_t _levelCount, uint32_t _layerCount)
	{
		BX_ASSERT(true
			&& _newLayout != VK_IMAGE_LAYOUT_UNDEFINED
			&& _newLayout != VK_IMAGE_LAYOUT_PREINITIALIZED
			, "_newLayout cannot use VK_IMAGE_LAYOUT_UNDEFINED or VK_IMAGE_LAYOUT_PREINITIALIZED."
			);

		VkAccessFlags srcAccessMask = 0;
		VkAccessFlags dstAccessMask = 0;

		switch (_oldLayout)
		{
		case VK_IMAGE_LAYOUT_UNDEFINED:
//			srcAccessMask |= VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_GENERAL:
			break;

		case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
			srcAccessMask |= VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
			srcAccessMask |= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL:
			break;

		case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
			srcAccessMask |= VK_ACCESS_SHADER_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
			srcAccessMask |= VK_ACCESS_TRANSFER_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
			break;

		case VK_IMAGE_LAYOUT_PREINITIALIZED:
			srcAccessMask |= VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
			srcAccessMask |= VK_ACCESS_MEMORY_READ_BIT;
			break;

		default:
			break;
		}

		switch (_newLayout)
		{
		case VK_IMAGE_LAYOUT_UNDEFINED:
			break;

		case VK_IMAGE_LAYOUT_GENERAL:
			break;

		case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
			dstAccessMask |= VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
			dstAccessMask |= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			// aspectMask     = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
			break;

		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL:
			break;

		case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
			dstAccessMask |= VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
			dstAccessMask |= VK_ACCESS_SHADER_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
			dstAccessMask |= VK_ACCESS_TRANSFER_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_PREINITIALIZED:
			break;

		case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
			dstAccessMask |= VK_ACCESS_MEMORY_READ_BIT;
			break;

		default:
			break;
		}

		VkImageMemoryBarrier imb;
		imb.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		imb.pNext = NULL;
		imb.srcAccessMask = srcAccessMask;
		imb.dstAccessMask = dstAccessMask;
		imb.oldLayout = _oldLayout;
		imb.newLayout = _newLayout;
		imb.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		imb.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		imb.image = _image;
		imb.subresourceRange.aspectMask     = _aspectMask;
		imb.subresourceRange.baseMipLevel   = 0;
		imb.subresourceRange.levelCount     = _levelCount;
		imb.subresourceRange.baseArrayLayer = 0;
		imb.subresourceRange.layerCount     = _layerCount;
		vkCmdPipelineBarrier(_commandBuffer
			, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
			, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
			, 0
			, 0
			, NULL
			, 0
			, NULL
			, 1
			, &imb
			);
	}

	struct RendererContextVK : public RendererContextI
	{
		RendererContextVK()
			: m_allocatorCb(NULL)
			, m_renderDocDll(NULL)
			, m_vulkan1Dll(NULL)
			, m_maxAnisotropy(1)
			, m_depthClamp(false)
			, m_wireframe(false)
			, m_rtMsaa(false)
		{
		}

		~RendererContextVK()
		{
		}

		VkResult createSwapchain()
		{
			VkResult result = VK_SUCCESS;
			result = vkCreateSwapchainKHR(m_device, &m_sci, m_allocatorCb, &m_swapchain);
			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create swapchain error: vkCreateSwapchainKHR failed %d: %s.", result, getName(result) );
				return result;
			}

			result = vkGetSwapchainImagesKHR(m_device, m_swapchain, &m_numSwapchainImages, NULL);
			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create swapchain error: vkGetSwapchainImagesKHR failed %d: %s.", result, getName(result) );
				return result;
			}

			if (m_numSwapchainImages < m_sci.minImageCount)
			{
				BX_TRACE("Create swapchain error: vkGetSwapchainImagesKHR: numSwapchainImages %d < minImageCount %d."
					, m_numSwapchainImages
					, m_sci.minImageCount
					);
				return VK_ERROR_INITIALIZATION_FAILED;
			}

			if (m_numSwapchainImages > BX_COUNTOF(m_backBufferColorImage) )
			{
				BX_TRACE("Create swapchain error: vkGetSwapchainImagesKHR: numSwapchainImages %d > countof(m_backBufferColorImage) %d."
					, m_numSwapchainImages
					, BX_COUNTOF(m_backBufferColorImage)
					);
				return VK_ERROR_INITIALIZATION_FAILED;
			}

			result = vkGetSwapchainImagesKHR(m_device, m_swapchain, &m_numSwapchainImages, &m_backBufferColorImage[0]);
			if (VK_SUCCESS != result && VK_INCOMPLETE != result)
			{
				BX_TRACE("Create swapchain error: vkGetSwapchainImagesKHR failed %d: %s."
					, result
					, getName(result)
					);
				return result;
			}

			VkImageCreateInfo ici;
			ici.sType     = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			ici.pNext     = NULL;
			ici.flags     = 0;
			ici.imageType = VK_IMAGE_TYPE_2D;
			ici.format    = m_backBufferDepthStencilFormat;
			ici.extent.width  = m_sci.imageExtent.width;
			ici.extent.height = m_sci.imageExtent.height;
			ici.extent.depth  = 1;
			ici.mipLevels     = 1;
			ici.arrayLayers   = 1;
			ici.samples       = VK_SAMPLE_COUNT_1_BIT;
			ici.tiling        = VK_IMAGE_TILING_OPTIMAL;
			ici.usage = 0
				| VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
				| VK_IMAGE_USAGE_TRANSFER_SRC_BIT
				;
			ici.sharingMode   = VK_SHARING_MODE_EXCLUSIVE;
			ici.queueFamilyIndexCount = 0; //m_sci.queueFamilyIndexCount;
			ici.pQueueFamilyIndices   = NULL; //m_sci.pQueueFamilyIndices;
			ici.initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED;
			result = vkCreateImage(m_device, &ici, m_allocatorCb, &m_backBufferDepthStencilImage);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create swapchain error: vkCreateImage failed %d: %s.", result, getName(result) );
				return result;
			}

			VkMemoryRequirements mr;
			vkGetImageMemoryRequirements(m_device, m_backBufferDepthStencilImage, &mr);

			result = allocateMemory(&mr, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &m_backBufferDepthStencilMemory);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create swapchain error: vkAllocateMemory failed %d: %s.", result, getName(result) );
				return result;
			}

			result = vkBindImageMemory(m_device, m_backBufferDepthStencilImage, m_backBufferDepthStencilMemory, 0);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create swapchain error: vkBindImageMemory failed %d: %s.", result, getName(result) );
				return result;
			}

			VkImageViewCreateInfo ivci;
			ivci.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			ivci.pNext    = NULL;
			ivci.flags    = 0;
			ivci.image    = m_backBufferDepthStencilImage;
			ivci.viewType = VK_IMAGE_VIEW_TYPE_2D;
			ivci.format   = m_backBufferDepthStencilFormat;
			ivci.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			ivci.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			ivci.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			ivci.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			ivci.subresourceRange.aspectMask = 0
				| VK_IMAGE_ASPECT_DEPTH_BIT
				| VK_IMAGE_ASPECT_STENCIL_BIT
				;
			ivci.subresourceRange.baseMipLevel   = 0;
			ivci.subresourceRange.levelCount     = 1;
			ivci.subresourceRange.baseArrayLayer = 0;
			ivci.subresourceRange.layerCount     = 1;
			result = vkCreateImageView(m_device, &ivci, m_allocatorCb, &m_backBufferDepthStencilImageView);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create swapchain error: vkCreateImageView failed %d: %s.", result, getName(result) );
				return result;
			}

			for (uint32_t ii = 0; ii < m_numSwapchainImages; ++ii)
			{
				ivci.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				ivci.pNext    = NULL;
				ivci.flags    = 0;
				ivci.image    = m_backBufferColorImage[ii];
				ivci.viewType = VK_IMAGE_VIEW_TYPE_2D;
				ivci.format   = m_sci.imageFormat;
				ivci.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
				ivci.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
				ivci.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
				ivci.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
				ivci.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
				ivci.subresourceRange.baseMipLevel   = 0;
				ivci.subresourceRange.levelCount     = 1;
				ivci.subresourceRange.baseArrayLayer = 0;
				ivci.subresourceRange.layerCount     = 1;

				result = vkCreateImageView(m_device, &ivci, m_allocatorCb, &m_backBufferColorImageView[ii]);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Create swapchain error: vkCreateImageView failed %d: %s.", result, getName(result) );
					return result;
				}

				m_backBufferColorImageLayout[ii] = VK_IMAGE_LAYOUT_UNDEFINED;
			}

			m_needToRefreshSwapchain = false;

			return result;
		}

		void releaseSwapchain()
		{
			VK_CHECK(vkDeviceWaitIdle(m_device) );
			vkFreeMemory(m_device, m_backBufferDepthStencilMemory, m_allocatorCb);
			m_backBufferDepthStencilMemory = VK_NULL_HANDLE;
			vkDestroy(m_backBufferDepthStencilImageView);
			vkDestroy(m_backBufferDepthStencilImage);
			for (uint32_t ii = 0; ii < BX_COUNTOF(m_backBufferColorImageView); ++ii)
			{
				vkDestroy(m_backBufferColorImageView[ii]);
				m_backBufferColorImageLayout[ii] = VK_IMAGE_LAYOUT_UNDEFINED;
			}
			vkDestroy(m_swapchain);
		}

		VkResult createSwapchainFramebuffer()
		{
			VkResult result = VK_SUCCESS;
			for (uint32_t ii = 0; ii < m_numSwapchainImages; ++ii)
			{
				::VkImageView attachments[] =
				{
					m_backBufferColorImageView[ii],
					m_backBufferDepthStencilImageView,
				};

				VkFramebufferCreateInfo fci;
				fci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
				fci.pNext = NULL;
				fci.flags = 0;
				fci.renderPass = m_renderPass;
				fci.attachmentCount = BX_COUNTOF(attachments);
				fci.pAttachments = attachments;
				fci.width = m_sci.imageExtent.width;
				fci.height = m_sci.imageExtent.height;
				fci.layers = 1;

				result = vkCreateFramebuffer(m_device, &fci, m_allocatorCb, &m_backBufferColor[ii]);

				if (VK_SUCCESS != result)
				{
					return result;
				}
			}
			return result;
		}

		void releaseSwapchainFramebuffer()
		{
			for (uint32_t ii = 0; ii < BX_COUNTOF(m_backBufferColorImageView); ++ii)
			{
				vkDestroy(m_backBufferColor[ii]);
			}
		}

		VkResult createSwapchainRenderPass()
		{
			VkAttachmentDescription ad[2];
			ad[0].flags          = 0;
			ad[0].format         = m_sci.imageFormat;
			ad[0].samples        = VK_SAMPLE_COUNT_1_BIT;
			ad[0].loadOp         = VK_ATTACHMENT_LOAD_OP_LOAD;
			ad[0].storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
			ad[0].stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			ad[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			ad[0].initialLayout  = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			ad[0].finalLayout    = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			ad[1].flags          = 0;
			ad[1].format         = m_backBufferDepthStencilFormat;
			ad[1].samples        = VK_SAMPLE_COUNT_1_BIT;
			ad[1].loadOp         = VK_ATTACHMENT_LOAD_OP_LOAD;
			ad[1].storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
			ad[1].stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_LOAD;
			ad[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE;
			ad[1].initialLayout  = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
			ad[1].finalLayout    = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

			VkAttachmentReference colorAr[1];
			colorAr[0].attachment = 0;
			colorAr[0].layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

			VkAttachmentReference resolveAr[1];
			resolveAr[0].attachment = VK_ATTACHMENT_UNUSED;
			resolveAr[0].layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

			VkAttachmentReference depthAr[1];
			depthAr[0].attachment = 1;
			depthAr[0].layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

			VkSubpassDescription sd[1];
			sd[0].flags                   = 0;
			sd[0].pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS;
			sd[0].inputAttachmentCount    = 0;
			sd[0].pInputAttachments       = NULL;
			sd[0].colorAttachmentCount    = BX_COUNTOF(colorAr);
			sd[0].pColorAttachments       = colorAr;
			sd[0].pResolveAttachments     = resolveAr;
			sd[0].pDepthStencilAttachment = depthAr;
			sd[0].preserveAttachmentCount = 0;
			sd[0].pPreserveAttachments    = NULL;

			VkRenderPassCreateInfo rpi;
			rpi.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			rpi.pNext           = NULL;
			rpi.flags           = 0;
			rpi.attachmentCount = BX_COUNTOF(ad);
			rpi.pAttachments    = ad;
			rpi.subpassCount    = BX_COUNTOF(sd);
			rpi.pSubpasses      = sd;
			rpi.dependencyCount = 0;
			rpi.pDependencies   = NULL;

			return vkCreateRenderPass(m_device, &rpi, m_allocatorCb, &m_renderPass);
		}

		void releaseSwapchainRenderPass()
		{
			vkDestroy(m_renderPass);
		}

		void initSwapchainImageLayout()
		{
			VkCommandBuffer commandBuffer = beginNewCommand();

			setImageMemoryBarrier(
				  commandBuffer
				, m_backBufferDepthStencilImage
				, VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT
				, VK_IMAGE_LAYOUT_UNDEFINED
				, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
				, 1
				, 1
				);

			m_backBufferColorIdx = 0;
			submitCommandAndWait(commandBuffer);
		}

		bool init(const Init& _init)
		{
			BX_UNUSED(s_checkMsaa, s_textureAddress);

			struct ErrorState
			{
				enum Enum
				{
					Default,
					LoadedVulkan1,
					InstanceCreated,
					DeviceCreated,
					SurfaceCreated,
					SwapchainCreated,
					RenderPassCreated,
					FrameBufferCreated,
					CommandBuffersCreated,
					DescriptorCreated,
				};
			};

			ErrorState::Enum errorState = ErrorState::Default;

			m_fbh.idx = kInvalidHandle;
			bx::memSet(m_uniforms, 0, sizeof(m_uniforms) );
			bx::memSet(&m_resolution, 0, sizeof(m_resolution) );

			bool imported = true;
			VkResult result;
			m_qfiGraphics = UINT32_MAX;
			m_qfiCompute  = UINT32_MAX;

			if (_init.debug
			||  _init.profile)
			{
				m_renderDocDll = loadRenderDoc();
			}

			m_vulkan1Dll = bx::dlopen(
#if BX_PLATFORM_WINDOWS
				"vulkan-1.dll"
#elif BX_PLATFORM_ANDROID
				"libvulkan.so"
#elif BX_PLATFORM_OSX
				"libvulkan.dylib"
#else
				"libvulkan.so.1"
#endif // BX_PLATFORM_*
					);

			if (NULL == m_vulkan1Dll)
			{
				BX_TRACE("Init error: Failed to load vulkan dynamic library.");
				goto error;
			}

			errorState = ErrorState::LoadedVulkan1;

			BX_TRACE("Shared library functions:");

#define VK_IMPORT_FUNC(_optional, _func)                  \
	_func = (PFN_##_func)bx::dlsym(m_vulkan1Dll, #_func); \
	BX_TRACE("\t%p " #_func, _func);                      \
	imported &= _optional || NULL != _func

VK_IMPORT

#undef VK_IMPORT_FUNC

			if (!imported)
			{
				BX_TRACE("Init error: Failed to load shared library functions.");
				goto error;
			}

			{
				dumpExtensions();

				uint32_t numEnabledLayers = 0;

				const char* enabledLayer[Layer::Count];

				for (uint32_t ii = 0; ii < Layer::Count; ++ii)
				{
					const Layer& layer = s_layer[ii];

					if (layer.m_instance.m_supported
					&&  layer.m_instance.m_initialize)
					{
						enabledLayer[numEnabledLayers++] = layer.m_name;
						BX_TRACE("%d: %s", numEnabledLayers, layer.m_name);
					}
				}

				uint32_t numEnabledExtensions = 2;

				const char* enabledExtension[Extension::Count + 2] =
				{
					VK_KHR_SURFACE_EXTENSION_NAME,
					KHR_SURFACE_EXTENSION_NAME,
				};

				for (uint32_t ii = 0; ii < Extension::Count; ++ii)
				{
					const Extension& extension = s_extension[ii];
					const LayerInfo& layerInfo = s_layer[extension.m_layer].m_instance;

					const bool layerEnabled = false
						|| extension.m_layer == Layer::Count
						|| (layerInfo.m_supported && layerInfo.m_initialize)
						;

					if (extension.m_supported
					&&  extension.m_initialize
					&&  extension.m_instanceExt
					&&  layerEnabled)
					{
						enabledExtension[numEnabledExtensions++] = extension.m_name;
						BX_TRACE("%d: %s", numEnabledExtensions, extension.m_name);
					}
				}

				uint32_t vulkanApiVersionSelector;

				if (NULL != vkEnumerateInstanceVersion)
				{
					result = vkEnumerateInstanceVersion(&vulkanApiVersionSelector);

					if (VK_SUCCESS != result)
					{
						BX_TRACE(
							  "Init error: vkEnumerateInstanceVersion failed %d: %s."
							, result
							, getName(result)
							);
						goto error;
					}
				}
				else
				{
					vulkanApiVersionSelector = VK_API_VERSION_1_0;
				}

				VkApplicationInfo appInfo;
				appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
				appInfo.pNext = NULL;
				appInfo.pApplicationName   = "bgfx";
				appInfo.applicationVersion = BGFX_API_VERSION;
				appInfo.pEngineName        = "bgfx";
				appInfo.engineVersion      = BGFX_API_VERSION;
				appInfo.apiVersion         = vulkanApiVersionSelector;

				VkInstanceCreateInfo ici;
				ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
				ici.pNext = NULL;
				ici.flags = 0;
				ici.pApplicationInfo        = &appInfo;
				ici.enabledLayerCount       = numEnabledLayers;
				ici.ppEnabledLayerNames     = enabledLayer;
				ici.enabledExtensionCount   = numEnabledExtensions;
				ici.ppEnabledExtensionNames = enabledExtension;

				if (BX_ENABLED(BGFX_CONFIG_DEBUG) )
				{
					m_allocatorCb = &s_allocationCb;
					BX_UNUSED(s_allocationCb);
				}

				result = vkCreateInstance(
					  &ici
					, m_allocatorCb
					, &m_instance
					);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkCreateInstance failed %d: %s.", result, getName(result) );
					goto error;
				}

				m_instanceApiVersion = vulkanApiVersionSelector;

				BX_TRACE("Instance API Version Selected: %d.%d.%d"
					, VK_VERSION_MAJOR(m_instanceApiVersion)
					, VK_VERSION_MINOR(m_instanceApiVersion)
					, VK_VERSION_PATCH(m_instanceApiVersion)
					);
			}

			errorState = ErrorState::InstanceCreated;

			BX_TRACE("Instance functions:");

#define VK_IMPORT_INSTANCE_FUNC(_optional, _func)                           \
			_func = (PFN_##_func)vkGetInstanceProcAddr(m_instance, #_func); \
			BX_TRACE("\t%p " #_func, _func);                                \
			imported &= _optional || NULL != _func
VK_IMPORT_INSTANCE
#undef VK_IMPORT_INSTANCE_FUNC

			if (!imported)
			{
				BX_TRACE("Init error: Failed to load instance functions.");
				goto error;
			}

			m_debugReportCallback = VK_NULL_HANDLE;

			if (s_extension[Extension::EXT_debug_report].m_supported)
			{
				VkDebugReportCallbackCreateInfoEXT drcb;
				drcb.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
				drcb.pNext = NULL;
				drcb.pfnCallback = debugReportCb;
				drcb.pUserData   = NULL;
				drcb.flags       = 0
					| VK_DEBUG_REPORT_ERROR_BIT_EXT
					| VK_DEBUG_REPORT_WARNING_BIT_EXT
					;
				result = vkCreateDebugReportCallbackEXT(m_instance
					, &drcb
					, m_allocatorCb
					, &m_debugReportCallback
					);
				BX_WARN(VK_SUCCESS == result, "vkCreateDebugReportCallbackEXT failed %d: %s.", result, getName(result) );
			}

			{
				BX_TRACE("---");

				uint32_t numPhysicalDevices;
				result = vkEnumeratePhysicalDevices(m_instance
					, &numPhysicalDevices
					, NULL
					);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkEnumeratePhysicalDevices failed %d: %s.", result, getName(result) );
					goto error;
				}

				VkPhysicalDevice physicalDevices[4];
				numPhysicalDevices = bx::min<uint32_t>(numPhysicalDevices, BX_COUNTOF(physicalDevices) );
				result = vkEnumeratePhysicalDevices(m_instance
					, &numPhysicalDevices
					, physicalDevices
					);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkEnumeratePhysicalDevices failed %d: %s.", result, getName(result) );
					goto error;
				}

				m_physicalDevice = VK_NULL_HANDLE;

				for (uint32_t ii = 0; ii < numPhysicalDevices; ++ii)
				{
					VkPhysicalDeviceProperties pdp;
					vkGetPhysicalDeviceProperties(physicalDevices[ii], &pdp);
					BX_TRACE("Physical device %d:", ii);
					BX_TRACE("\t          Name: %s", pdp.deviceName);
					BX_TRACE("\t   API version: %d.%d.%d"
						, VK_VERSION_MAJOR(pdp.apiVersion)
						, VK_VERSION_MINOR(pdp.apiVersion)
						, VK_VERSION_PATCH(pdp.apiVersion) );
					BX_TRACE("\tDriver version: %x", pdp.driverVersion);
					BX_TRACE("\t      VendorId: %x", pdp.vendorID);
					BX_TRACE("\t      DeviceId: %x", pdp.deviceID);
					BX_TRACE("\t          Type: %d", pdp.deviceType);

					g_caps.gpu[ii].vendorId = uint16_t(pdp.vendorID);
					g_caps.gpu[ii].deviceId = uint16_t(pdp.deviceID);
					++g_caps.numGPUs;

					if ( (BGFX_PCI_ID_NONE != g_caps.vendorId ||            0 != g_caps.deviceId)
					&&   (BGFX_PCI_ID_NONE == g_caps.vendorId || pdp.vendorID == g_caps.vendorId)
					&&   (0 == g_caps.deviceId                || pdp.deviceID == g_caps.deviceId) )
					{
						m_physicalDevice = physicalDevices[ii];
					}

					VkPhysicalDeviceMemoryProperties pdmp;
					vkGetPhysicalDeviceMemoryProperties(physicalDevices[ii], &pdmp);

					BX_TRACE("\tMemory type count: %d", pdmp.memoryTypeCount);
					for (uint32_t jj = 0; jj < pdmp.memoryTypeCount; ++jj)
					{
						BX_TRACE("\t%3d: flags 0x%08x, index %d"
								, jj
								, pdmp.memoryTypes[jj].propertyFlags
								, pdmp.memoryTypes[jj].heapIndex
								);
					}

					BX_TRACE("\tMemory heap count: %d", pdmp.memoryHeapCount);
					for (uint32_t jj = 0; jj < pdmp.memoryHeapCount; ++jj)
					{
						char size[16];
						bx::prettify(size, BX_COUNTOF(size), pdmp.memoryHeaps[jj].size);
						BX_TRACE("\t%3d: flags 0x%08x, size %10s"
								, jj
								, pdmp.memoryHeaps[jj].flags
								, size
								);
					}

					dumpExtensions(physicalDevices[ii]);
				}

				if (VK_NULL_HANDLE == m_physicalDevice)
				{
					m_physicalDevice = physicalDevices[0];
				}

				vkGetPhysicalDeviceProperties(m_physicalDevice, &m_deviceProperties);
				g_caps.vendorId = uint16_t(m_deviceProperties.vendorID);
				g_caps.deviceId = uint16_t(m_deviceProperties.deviceID);

				g_caps.supported |= ( 0
					| BGFX_CAPS_ALPHA_TO_COVERAGE
					| BGFX_CAPS_BLEND_INDEPENDENT
					| BGFX_CAPS_COMPUTE
					| BGFX_CAPS_DRAW_INDIRECT
					| BGFX_CAPS_FRAGMENT_DEPTH
					| BGFX_CAPS_INDEX32
					| BGFX_CAPS_INSTANCING
					| BGFX_CAPS_TEXTURE_2D_ARRAY
					| BGFX_CAPS_TEXTURE_3D
					| BGFX_CAPS_TEXTURE_BLIT
					| BGFX_CAPS_TEXTURE_READ_BACK
					| BGFX_CAPS_TEXTURE_COMPARE_ALL
					| BGFX_CAPS_TEXTURE_CUBE_ARRAY
					| BGFX_CAPS_VERTEX_ATTRIB_HALF
					| BGFX_CAPS_VERTEX_ATTRIB_UINT10
					| BGFX_CAPS_VERTEX_ID
					| BGFX_CAPS_IMAGE_RW
					);

				g_caps.limits.maxTextureSize     = m_deviceProperties.limits.maxImageDimension2D;
				g_caps.limits.maxTextureLayers   = m_deviceProperties.limits.maxImageArrayLayers;
				g_caps.limits.maxFBAttachments   = bx::min(uint8_t(m_deviceProperties.limits.maxFragmentOutputAttachments), uint8_t(BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS) );
				g_caps.limits.maxComputeBindings = BGFX_MAX_COMPUTE_BINDINGS;
				g_caps.limits.maxVertexStreams   = BGFX_CONFIG_MAX_VERTEX_STREAMS;

				vkGetPhysicalDeviceFeatures(m_physicalDevice, &m_deviceFeatures);
				m_deviceFeatures.robustBufferAccess = VK_FALSE;

				{
					for (uint16_t ii = 0, last = 0; ii < BX_COUNTOF(s_msaa); ii++)
					{
						if ( (m_deviceProperties.limits.framebufferColorSampleCounts >= s_msaa[ii].Count) && (m_deviceProperties.limits.framebufferDepthSampleCounts >= s_msaa[ii].Count) )
							last = ii;
						else
							s_msaa[ii] = s_msaa[last];
					}
				}

				{
					struct ImageTest
					{
						VkImageType type;
						VkImageUsageFlags usage;
						VkImageCreateFlags flags;
						uint32_t formatCaps[2];
					};

					const ImageTest imageTest[] =
					{
						{ VK_IMAGE_TYPE_2D, VK_IMAGE_USAGE_SAMPLED_BIT,          0,                                   { BGFX_CAPS_FORMAT_TEXTURE_2D,          BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB     } },
						{ VK_IMAGE_TYPE_3D, VK_IMAGE_USAGE_SAMPLED_BIT,          0,                                   { BGFX_CAPS_FORMAT_TEXTURE_3D,          BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB     } },
						{ VK_IMAGE_TYPE_2D, VK_IMAGE_USAGE_SAMPLED_BIT,          VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT, { BGFX_CAPS_FORMAT_TEXTURE_CUBE,        BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB   } },
						{ VK_IMAGE_TYPE_2D, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, 0,                                   { BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER, BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER } },
						{ VK_IMAGE_TYPE_2D, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, 0,                           { BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER, BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER } },
						{ VK_IMAGE_TYPE_2D, VK_IMAGE_USAGE_STORAGE_BIT, 	     0,									  { BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ,  BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ  } },
						{ VK_IMAGE_TYPE_2D, VK_IMAGE_USAGE_STORAGE_BIT, 	     0,									  { BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE, BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE } },
					};

					for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
					{
						uint16_t support = BGFX_CAPS_FORMAT_TEXTURE_NONE;

						const bool depth = bimg::isDepth(bimg::TextureFormat::Enum(ii) );
						VkFormat fmt = depth
							? s_textureFormat[ii].m_fmtDsv
							: s_textureFormat[ii].m_fmt
							;

						for (uint32_t jj = 0, num = depth ? 1 : 2; jj < num; ++jj)
						{
							if (VK_FORMAT_UNDEFINED != fmt)
							{
								for (uint32_t test = 0; test < BX_COUNTOF(imageTest); ++test)
								{
									const ImageTest& it = imageTest[test];

									VkImageFormatProperties ifp;
									result = vkGetPhysicalDeviceImageFormatProperties(m_physicalDevice
										, fmt
										, it.type
										, VK_IMAGE_TILING_OPTIMAL
										, it.usage
										, it.flags
										, &ifp
										);

									if (VK_SUCCESS == result)
									{
										support |= it.formatCaps[jj];
										if (VK_SAMPLE_COUNT_1_BIT < ifp.sampleCounts)
										{
											support |= BGFX_CAPS_FORMAT_TEXTURE_MSAA;
										}
									}
								}
							}

							fmt = s_textureFormat[ii].m_fmtSrgb;
						}

						g_caps.formats[ii] = support;
					}
				}

				vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &m_memoryProperties);
			}

			{
				BX_TRACE("---");

				uint32_t queueFamilyPropertyCount = 0;
				vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice
					, &queueFamilyPropertyCount
					, NULL
					);

				VkQueueFamilyProperties queueFamilyPropertices[10];
				queueFamilyPropertyCount = bx::min<uint32_t>(queueFamilyPropertyCount, BX_COUNTOF(queueFamilyPropertices) );
				vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice
					, &queueFamilyPropertyCount
					, queueFamilyPropertices
					);

				for (uint32_t ii = 0; ii < queueFamilyPropertyCount; ++ii)
				{
					const VkQueueFamilyProperties& qfp = queueFamilyPropertices[ii];
					BX_UNUSED(qfp);
					BX_TRACE("Queue family property %d:", ii);
					BX_TRACE("\t  Queue flags: 0x%08x", qfp.queueFlags);
					BX_TRACE("\t  Queue count: %d", qfp.queueCount);
					BX_TRACE("\tTS valid bits: 0x%08x", qfp.timestampValidBits);
					BX_TRACE("\t    Min image: %d x %d x %d"
							, qfp.minImageTransferGranularity.width
							, qfp.minImageTransferGranularity.height
							, qfp.minImageTransferGranularity.depth
							);
				}

				for (uint32_t ii = 0; ii < queueFamilyPropertyCount; ++ii)
				{
					const VkQueueFamilyProperties& qfp = queueFamilyPropertices[ii];
					if (UINT32_MAX == m_qfiGraphics
					&&  VK_QUEUE_GRAPHICS_BIT & qfp.queueFlags)
					{
						m_qfiGraphics = ii;
					}

					if (UINT32_MAX == m_qfiCompute
					&&  VK_QUEUE_COMPUTE_BIT & qfp.queueFlags)
					{
						m_qfiCompute = ii;
					}

					if (UINT32_MAX != m_qfiGraphics
					&&  UINT32_MAX != m_qfiCompute)
					{
						break;
					}
				}

				if (UINT32_MAX == m_qfiGraphics)
				{
					BX_TRACE("Init error: Unable to find graphics queue.");
					goto error;
				}
			}

			if (m_qfiCompute != UINT32_MAX)
			{
				g_caps.supported |= BGFX_CAPS_COMPUTE;
			}

			{
				uint32_t numEnabledLayers = 0;

				const char* enabledLayer[Layer::Count];

				for (uint32_t ii = 0; ii < Layer::Count; ++ii)
				{
					const Layer& layer = s_layer[ii];

					if (layer.m_device.m_supported
					&&  layer.m_device.m_initialize)
					{
						enabledLayer[numEnabledLayers++] = layer.m_name;
						BX_TRACE("%d: %s", numEnabledLayers, layer.m_name);
					}
				}


				uint32_t numEnabledExtensions = 2;

				const char* enabledExtension[Extension::Count + 2] =
				{
					VK_KHR_SWAPCHAIN_EXTENSION_NAME,
					VK_KHR_MAINTENANCE1_EXTENSION_NAME
				};

				for (uint32_t ii = 0; ii < Extension::Count; ++ii)
				{
					const Extension& extension = s_extension[ii];

					bool layerEnabled = extension.m_layer == Layer::Count ||
										(s_layer[extension.m_layer].m_device.m_supported &&
										 s_layer[extension.m_layer].m_device.m_initialize);

					if (extension.m_supported
					&&  extension.m_initialize
					&& !extension.m_instanceExt
					&&  layerEnabled)
					{
						enabledExtension[numEnabledExtensions++] = extension.m_name;
						BX_TRACE("%d: %s", numEnabledExtensions, extension.m_name);
					}
				}

				float queuePriorities[1] = { 0.0f };
				VkDeviceQueueCreateInfo dcqi;
				dcqi.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				dcqi.pNext = NULL;
				dcqi.flags = 0;
				dcqi.queueFamilyIndex = m_qfiGraphics;
				dcqi.queueCount       = 1;
				dcqi.pQueuePriorities = queuePriorities;

				VkDeviceCreateInfo dci;
				dci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
				dci.pNext = NULL;
				dci.flags = 0;
				dci.queueCreateInfoCount = 1;
				dci.pQueueCreateInfos    = &dcqi;
				dci.enabledLayerCount    = numEnabledLayers;
				dci.ppEnabledLayerNames  = enabledLayer;
				dci.enabledExtensionCount   = numEnabledExtensions;
				dci.ppEnabledExtensionNames = enabledExtension;
				dci.pEnabledFeatures = &m_deviceFeatures;

				result = vkCreateDevice(
					  m_physicalDevice
					, &dci
					, m_allocatorCb
					, &m_device
					);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkCreateDevice failed %d: %s.", result, getName(result) );
					goto error;
				}
			}

			errorState = ErrorState::DeviceCreated;

			BX_TRACE("Device functions:");
#define VK_IMPORT_DEVICE_FUNC(_optional, _func)                         \
			_func = (PFN_##_func)vkGetDeviceProcAddr(m_device, #_func); \
			BX_TRACE("\t%p " #_func, _func);                            \
			imported &= _optional || NULL != _func
VK_IMPORT_DEVICE
#undef VK_IMPORT_DEVICE_FUNC

			if (!imported)
			{
				BX_TRACE("Init error: Failed to load device functions.");
				goto error;
			}

			vkGetDeviceQueue(m_device, m_qfiGraphics, 0, &m_queueGraphics);
			vkGetDeviceQueue(m_device, m_qfiCompute,  0, &m_queueCompute);

#if BX_PLATFORM_WINDOWS
			{
				VkWin32SurfaceCreateInfoKHR sci;
				sci.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
				sci.pNext = NULL;
				sci.flags     = 0;
				sci.hinstance = (HINSTANCE)GetModuleHandle(NULL);
				sci.hwnd      = (HWND)g_platformData.nwh;
				result = vkCreateWin32SurfaceKHR(m_instance, &sci, m_allocatorCb, &m_surface);
			}
#elif BX_PLATFORM_ANDROID
			{
				VkAndroidSurfaceCreateInfoKHR sci;
				sci.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
				sci.pNext = NULL;
				sci.flags = 0;
				sci.window = (ANativeWindow*)g_platformData.nwh;
				result = vkCreateAndroidSurfaceKHR(m_instance, &sci, m_allocatorCb, &m_surface);
			}
#elif BX_PLATFORM_LINUX
			{
				if (NULL != vkCreateXlibSurfaceKHR)
				{
					VkXlibSurfaceCreateInfoKHR sci;
					sci.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
					sci.pNext = NULL;
					sci.flags  = 0;
					sci.dpy    = (Display*)g_platformData.ndt;
					sci.window = (Window)g_platformData.nwh;
					result = vkCreateXlibSurfaceKHR(m_instance, &sci, m_allocatorCb, &m_surface);
				}
				else
				{
					result = VK_RESULT_MAX_ENUM;
				}

				if (VK_SUCCESS != result)
				{
					void* xcbdll = bx::dlopen("libX11-xcb.so.1");

					if (NULL != xcbdll)
					{
						typedef xcb_connection_t* (*PFN_XGETXCBCONNECTION)(Display*);
						PFN_XGETXCBCONNECTION XGetXCBConnection = (PFN_XGETXCBCONNECTION)bx::dlsym(xcbdll, "XGetXCBConnection");

						union { void* ptr; xcb_window_t window; } cast = { g_platformData.nwh };

						VkXcbSurfaceCreateInfoKHR sci;
						sci.sType      = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
						sci.pNext      = NULL;
						sci.flags      = 0;
						sci.connection = XGetXCBConnection( (Display*)g_platformData.ndt);
						sci.window     = cast.window;
						result = vkCreateXcbSurfaceKHR(m_instance, &sci, m_allocatorCb, &m_surface);

						bx::dlclose(xcbdll);
					}
				}
			}
#elif BX_PLATFORM_OSX
			{
				if (NULL != vkCreateMacOSSurfaceMVK)
				{
					NSWindow* window    = (NSWindow*)(g_platformData.nwh);
					NSView* contentView = (NSView*)window.contentView;
					CAMetalLayer* layer = [CAMetalLayer layer];

					if (_init.resolution.reset & BGFX_RESET_HIDPI)
					{
						layer.contentsScale = [window backingScaleFactor];
					}

					[contentView setWantsLayer : YES];
					[contentView setLayer : layer];

					VkMacOSSurfaceCreateInfoMVK sci;
					sci.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
					sci.pNext = NULL;
					sci.flags = 0;
					sci.pView = (__bridge void*)layer;
					result = vkCreateMacOSSurfaceMVK(m_instance, &sci, m_allocatorCb, &m_surface);
				}
				else
				{
					result = VK_RESULT_MAX_ENUM;
				}
			}
#else
#	error "Figure out KHR surface..."
#endif // BX_PLATFORM_

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Init error: vkCreateSurfaceKHR failed %d: %s.", result, getName(result) );
				goto error;
			}

			errorState = ErrorState::SurfaceCreated;

			{
				VkBool32 surfaceSupported;
				result = vkGetPhysicalDeviceSurfaceSupportKHR(m_physicalDevice, m_qfiGraphics, m_surface, &surfaceSupported);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkGetPhysicalDeviceSurfaceSupportKHR failed %d: %s.", result, getName(result) );
					goto error;
				}

				VkSurfaceCapabilitiesKHR surfaceCapabilities;
				result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physicalDevice, m_surface, &surfaceCapabilities);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkGetPhysicalDeviceSurfaceCapabilitiesKHR failed %d: %s.", result, getName(result) );
					goto error;
				}

				const uint32_t width = bx::clamp<uint32_t>(
					  _init.resolution.width
					, surfaceCapabilities.minImageExtent.width
					, surfaceCapabilities.maxImageExtent.width
					);
				const uint32_t height = bx::clamp<uint32_t>(
					  _init.resolution.height
					, surfaceCapabilities.minImageExtent.height
					, surfaceCapabilities.maxImageExtent.height
					);

				uint32_t numSurfaceFormats;
				result = vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, m_surface, &numSurfaceFormats, NULL);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkGetPhysicalDeviceSurfaceFormatsKHR failed %d: %s.", result, getName(result) );
					goto error;
				}

				VkSurfaceFormatKHR surfaceFormats[10];
				numSurfaceFormats = bx::min<uint32_t>(numSurfaceFormats, BX_COUNTOF(surfaceFormats) );
				vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, m_surface, &numSurfaceFormats, surfaceFormats);

				// find the best match...
				static const VkFormat preferredSurfaceFormat[] =
				{
					VK_FORMAT_R8G8B8A8_UNORM,
					VK_FORMAT_B8G8R8A8_UNORM
				};

				static const VkFormat preferredSurfaceFormatSrgb[] =
				{
					VK_FORMAT_R8G8B8A8_SRGB,
					VK_FORMAT_B8G8R8A8_SRGB
				};

				VkColorSpaceKHR preferredColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;

				uint32_t surfaceFormatIdx = numSurfaceFormats;
				uint32_t surfaceFormatSrgbIdx = numSurfaceFormats;

				for (uint32_t ii = 0; ii < numSurfaceFormats; ii++)
				{
					BX_TRACE("Supported surface format: %d", surfaceFormats[ii].format);

					if (preferredColorSpace == surfaceFormats[ii].colorSpace)
                    {
						for (uint32_t jj = 0; jj < BX_COUNTOF(preferredSurfaceFormat); jj++)
						{
							if (preferredSurfaceFormat[jj] == surfaceFormats[ii].format)
							{
								BX_TRACE("Preferred surface format found: %d", surfaceFormats[ii].format);
								surfaceFormatIdx = ii;
								break;
							}
						}

						for (uint32_t jj = 0; jj < BX_COUNTOF(preferredSurfaceFormatSrgb); jj++)
						{
							if (preferredSurfaceFormatSrgb[jj] == surfaceFormats[ii].format)
							{
								BX_TRACE("Preferred sRGB surface format found: %d", surfaceFormats[ii].format);
								surfaceFormatSrgbIdx = ii;
								break;
							}
						}

						if (surfaceFormatIdx     < numSurfaceFormats
						&&  surfaceFormatSrgbIdx < numSurfaceFormats)
						{ // found
							break;
						}
					}
				}

				BX_ASSERT(surfaceFormatIdx < numSurfaceFormats, "Cannot find preferred surface format from supported surface formats");
				BX_WARN(surfaceFormatSrgbIdx < numSurfaceFormats, "Cannot find preferred sRGB surface format from supported surface formats");

				m_backBufferColorFormat = surfaceFormats[surfaceFormatIdx];
				m_backBufferColorFormatSrgb = surfaceFormatSrgbIdx < numSurfaceFormats ? surfaceFormats[surfaceFormatSrgbIdx] : m_backBufferColorFormat;

				// find the best match...
				uint32_t presentModeIdx = findPresentMode(false);
				if (UINT32_MAX == presentModeIdx)
				{
					BX_TRACE("Unable to find present mode.");
					goto error;
				}

				m_backBufferDepthStencilFormat = 0 != (g_caps.formats[TextureFormat::D24S8] & BGFX_CAPS_FORMAT_TEXTURE_2D)
					? VK_FORMAT_D24_UNORM_S8_UINT
					: VK_FORMAT_D32_SFLOAT_S8_UINT
					;

				VkCompositeAlphaFlagBitsKHR compositeAlpha = (VkCompositeAlphaFlagBitsKHR)0;
				if (surfaceCapabilities.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR)
				{
					compositeAlpha = VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR;
				}
				else if (surfaceCapabilities.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR)
				{
					compositeAlpha = VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR;
				}
				else if (surfaceCapabilities.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR)
				{
					compositeAlpha = VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR;
				}
				else if (surfaceCapabilities.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR)
				{
					compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
				}

				m_sci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
				m_sci.pNext = NULL;
				m_sci.flags = 0;
				m_sci.surface = m_surface;
				m_sci.minImageCount   = surfaceCapabilities.minImageCount;
				m_sci.imageFormat     = m_backBufferColorFormat.format;
				m_sci.imageColorSpace = m_backBufferColorFormat.colorSpace;
				m_sci.imageExtent.width  = width;
				m_sci.imageExtent.height = height;
				m_sci.imageArrayLayers = 1;
				m_sci.imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
				m_sci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
				m_sci.queueFamilyIndexCount = 0;
				m_sci.pQueueFamilyIndices   = NULL;
				m_sci.preTransform   = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
				m_sci.compositeAlpha = compositeAlpha;
				m_sci.presentMode    = s_presentMode[presentModeIdx].mode;
				m_sci.clipped        = VK_TRUE;
				m_sci.oldSwapchain   = VK_NULL_HANDLE;

				for (uint32_t ii = 0; ii < BX_COUNTOF(m_backBufferColorImageView); ++ii)
				{
					m_backBufferColorImageView[ii] = VK_NULL_HANDLE;
					m_backBufferColorImage[ii]     = VK_NULL_HANDLE;
					m_backBufferColor[ii]          = VK_NULL_HANDLE;
					m_presentDone[ii]              = VK_NULL_HANDLE;
				}

				result = createSwapchain();
				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: creating swapchain and image view failed %d: %s", result, getName(result) );
					goto error;
				}

				VkSemaphoreCreateInfo sci;
				sci.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
				sci.pNext = NULL;
				sci.flags = 0;

				for (uint32_t ii = 0; ii < m_numSwapchainImages; ++ii)
				{
					result = vkCreateSemaphore(m_device, &sci, m_allocatorCb, &m_presentDone[ii]);
					if (VK_SUCCESS != result)
					{
						BX_TRACE("Init error: vkCreateSemaphore failed %d: %s.", result, getName(result) );
						goto error;
					}
				}
			}

			errorState = ErrorState::SwapchainCreated;

			{
				result = createSwapchainRenderPass();

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkCreateRenderPass failed %d: %s.", result, getName(result) );
					goto error;
				}
			}

			errorState = ErrorState::RenderPassCreated;

			// framebuffer creation
			result = createSwapchainFramebuffer();
			if (VK_SUCCESS != result)
			{
				BX_TRACE("Init error: vkCreateFramebuffer failed %d: %s.", result, getName(result) );
				goto error;
			}

			errorState = ErrorState::FrameBufferCreated;

			{
				VkFenceCreateInfo fci;
				fci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
				fci.pNext = NULL;
				fci.flags = 0;
				result = vkCreateFence(m_device, &fci, m_allocatorCb, &m_fence);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkCreateFence failed %d: %s.", result, getName(result) );
					goto error;
				}

				VkCommandPoolCreateInfo cpci;
				cpci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
				cpci.pNext = NULL;
				cpci.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
				cpci.queueFamilyIndex = m_qfiGraphics;
				result = vkCreateCommandPool(m_device, &cpci, m_allocatorCb, &m_commandPool);

				if (VK_SUCCESS != result)
				{
					vkDestroy(m_fence);
					BX_TRACE("Init error: vkCreateCommandPool failed %d: %s.", result, getName(result) );
					goto error;
				}

				VkCommandBufferAllocateInfo cbai;
				cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
				cbai.pNext = NULL;
				cbai.commandPool = m_commandPool;
				cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
				cbai.commandBufferCount = BX_COUNTOF(m_commandBuffers);

				result = vkAllocateCommandBuffers(m_device, &cbai, m_commandBuffers);

				if (VK_SUCCESS != result)
				{
					vkDestroy(m_commandPool);
					vkDestroy(m_fence);
					BX_TRACE("Init error: vkAllocateCommandBuffers failed %d: %s.", result, getName(result) );
					goto error;
				}

				initSwapchainImageLayout();

//				kick();
//				finishAll();

				VK_CHECK(vkResetCommandPool(m_device, m_commandPool, 0) );
			}

			errorState = ErrorState::CommandBuffersCreated;

			{
				VkDescriptorPoolSize dps[] =
				{
//					{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, (10 * BGFX_CONFIG_MAX_TEXTURE_SAMPLERS) << 10 },
					{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,          (10 * BGFX_CONFIG_MAX_TEXTURE_SAMPLERS) << 10 },
					{ VK_DESCRIPTOR_TYPE_SAMPLER,                (10 * BGFX_CONFIG_MAX_TEXTURE_SAMPLERS) << 10 },
					{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 10<<10                           },
					{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,         BGFX_CONFIG_MAX_TEXTURE_SAMPLERS << 10 },
					{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,          BGFX_CONFIG_MAX_TEXTURE_SAMPLERS << 10 },
				};

// 				VkDescriptorSetLayoutBinding dslb[] =
// 				{
// //					{ DslBinding::CombinedImageSampler,  VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, VK_SHADER_STAGE_ALL,          NULL },
// 					{ DslBinding::VertexUniformBuffer,   VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,         1,                                VK_SHADER_STAGE_ALL,          NULL },
// 					{ DslBinding::FragmentUniformBuffer, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,         1,                                VK_SHADER_STAGE_FRAGMENT_BIT, NULL },
// //					{ DslBinding::StorageBuffer,         VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,         BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, VK_SHADER_STAGE_ALL,          NULL },
// 				};

				VkDescriptorPoolCreateInfo dpci;
				dpci.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
				dpci.pNext = NULL;
				dpci.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
				dpci.maxSets       = 10<<10;
				dpci.poolSizeCount = BX_COUNTOF(dps);
				dpci.pPoolSizes    = dps;

				result = vkCreateDescriptorPool(m_device, &dpci, m_allocatorCb, &m_descriptorPool);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkCreateDescriptorPool failed %d: %s.", result, getName(result) );
					goto error;
				}

//				VkDescriptorSetLayoutCreateInfo dsl;
//				dsl.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
//				dsl.pNext = NULL;
//				dsl.flags = 0;
//				dsl.bindingCount = BX_COUNTOF(dslb);
//				dsl.pBindings    = dslb;
//				result = vkCreateDescriptorSetLayout(m_device, &dsl, m_allocatorCb, &m_descriptorSetLayout);
//
//				if (VK_SUCCESS != result)
//				{
//					BX_TRACE("Init error: vkCreateDescriptorSetLayout failed %d: %s.", result, getName(result) );
//					goto error;
//				}
//
//				VkPipelineLayoutCreateInfo pl;
//				pl.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
//				pl.pNext = NULL;
//				pl.flags = 0;
//				pl.setLayoutCount = 1;
//				pl.pSetLayouts    = &m_descriptorSetLayout;
//				pl.pushConstantRangeCount = 0;
//				pl.pPushConstantRanges    = NULL;
//				result = vkCreatePipelineLayout(m_device, &pl, m_allocatorCb, &m_pipelineLayout);
//
//				if (VK_SUCCESS != result)
//				{
//					BX_TRACE("Init error: vkCreatePipelineLayout failed %d: %s.", result, getName(result) );
//					goto error;
//				}

				VkPipelineCacheCreateInfo pcci;
				pcci.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
				pcci.pNext = NULL;
				pcci.flags = 0;
				pcci.initialDataSize = 0;
				pcci.pInitialData    = NULL;
				result = vkCreatePipelineCache(m_device, &pcci, m_allocatorCb, &m_pipelineCache);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkCreatePipelineCache failed %d: %s.", result, getName(result) );
					goto error;
				}
			}

			{
				const uint32_t align = uint32_t(m_deviceProperties.limits.nonCoherentAtomSize);
				const uint32_t size = bx::strideAlign(BGFX_CONFIG_MAX_DRAW_CALLS * 128, align);
				for (uint32_t ii = 0; ii < BX_COUNTOF(m_scratchBuffer); ++ii)
				{
					BX_TRACE("Create scratch buffer %d", ii);
					m_scratchBuffer[ii].create(size, 1024);
				}
			}

			errorState = ErrorState::DescriptorCreated;

			if (NULL == vkSetDebugUtilsObjectNameEXT)
			{
				vkSetDebugUtilsObjectNameEXT = stubSetDebugUtilsObjectNameEXT;
			}

			if (!s_extension[Extension::EXT_debug_utils].m_supported
			||  NULL == vkCmdBeginDebugUtilsLabelEXT
			||  NULL == vkCmdEndDebugUtilsLabelEXT
			   )
			{
				vkCmdBeginDebugUtilsLabelEXT = stubCmdBeginDebugUtilsLabelEXT;
				vkCmdEndDebugUtilsLabelEXT   = stubCmdEndDebugUtilsLabelEXT;
			}

			if (NULL == vkCmdInsertDebugUtilsLabelEXT)
			{
				vkCmdInsertDebugUtilsLabelEXT = stubCmdInsertDebugUtilsLabelEXT;
			}

			// Init reserved part of view name.
			for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
			{
				bx::snprintf(s_viewName[ii], BGFX_CONFIG_MAX_VIEW_NAME_RESERVED+1, "%3d   ", ii);
			}

			m_gpuTimer.init();

			g_internalData.context = m_device;
			return true;

		error:
			BX_TRACE("errorState %d", errorState);
			switch (errorState)
			{
			case ErrorState::DescriptorCreated:
				vkDestroy(m_pipelineCache);
//				vkDestroy(m_pipelineLayout);
//				vkDestroy(m_descriptorSetLayout);
				vkDestroy(m_descriptorPool);
				BX_FALLTHROUGH;

			case ErrorState::CommandBuffersCreated:
				vkFreeCommandBuffers(m_device, m_commandPool, BX_COUNTOF(m_commandBuffers), m_commandBuffers);
				vkDestroy(m_commandPool);
				vkDestroy(m_fence);
				BX_FALLTHROUGH;

			case ErrorState::FrameBufferCreated:
				releaseSwapchainFramebuffer();
				BX_FALLTHROUGH;

			case ErrorState::RenderPassCreated:
				releaseSwapchainRenderPass();
				BX_FALLTHROUGH;

			case ErrorState::SwapchainCreated:
				for (uint32_t ii = 0; ii < BX_COUNTOF(m_backBufferColorImageView); ++ii)
				{
					vkDestroy(m_presentDone[ii]);
				}
				releaseSwapchain();
				BX_FALLTHROUGH;

			case ErrorState::SurfaceCreated:
				vkDestroySurfaceKHR(m_instance, m_surface, m_allocatorCb);
				BX_FALLTHROUGH;

			case ErrorState::DeviceCreated:
				vkDestroyDevice(m_device, m_allocatorCb);
				BX_FALLTHROUGH;

			case ErrorState::InstanceCreated:
				if (VK_NULL_HANDLE != m_debugReportCallback)
				{
					vkDestroyDebugReportCallbackEXT(m_instance, m_debugReportCallback, m_allocatorCb);
				}

				vkDestroyInstance(m_instance, m_allocatorCb);
				BX_FALLTHROUGH;

			case ErrorState::LoadedVulkan1:
				bx::dlclose(m_vulkan1Dll);
				m_vulkan1Dll  = NULL;
				m_allocatorCb = NULL;
				unloadRenderDoc(m_renderDocDll);
				BX_FALLTHROUGH;

			case ErrorState::Default:
				break;
			};

			return false;
		}

		void shutdown()
		{
			VK_CHECK(vkQueueWaitIdle(m_queueGraphics) );
			VK_CHECK(vkDeviceWaitIdle(m_device) );

			m_gpuTimer.shutdown();

			m_pipelineStateCache.invalidate();
			m_descriptorSetLayoutCache.invalidate();
			m_renderPassCache.invalidate();
			m_samplerCache.invalidate();

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_scratchBuffer); ++ii)
			{
				m_scratchBuffer[ii].destroy();
			}

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

			vkDestroy(m_pipelineCache);
//			vkDestroy(m_pipelineLayout);
//			vkDestroy(m_descriptorSetLayout);
			vkDestroy(m_descriptorPool);

			vkFreeCommandBuffers(m_device, m_commandPool, BX_COUNTOF(m_commandBuffers), m_commandBuffers);
			vkDestroy(m_commandPool);
			vkDestroy(m_fence);

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_backBufferColorImageView); ++ii)
			{
				vkDestroy(m_presentDone[ii]);
			}
			releaseSwapchainFramebuffer();
			releaseSwapchain();

			vkDestroySurfaceKHR(m_instance, m_surface, m_allocatorCb);

			vkDestroy(m_renderPass);

			vkDestroyDevice(m_device, m_allocatorCb);

			if (VK_NULL_HANDLE != m_debugReportCallback)
			{
				vkDestroyDebugReportCallbackEXT(m_instance, m_debugReportCallback, m_allocatorCb);
			}

			vkDestroyInstance(m_instance, m_allocatorCb);

			bx::dlclose(m_vulkan1Dll);
			m_vulkan1Dll  = NULL;
			m_allocatorCb = NULL;
			unloadRenderDoc(m_renderDocDll);
		}

		RendererType::Enum getRendererType() const override
		{
			return RendererType::Vulkan;
		}

		const char* getRendererName() const override
		{
			return BGFX_RENDERER_VULKAN_NAME;
		}

		bool isDeviceRemoved() override
		{
			return false;
		}

		void flip() override
		{
			if (VK_NULL_HANDLE != m_swapchain)
			{
				VkPresentInfoKHR pi;
				pi.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
				pi.pNext = NULL;
				pi.waitSemaphoreCount = 0;
				pi.pWaitSemaphores    = NULL;
				pi.swapchainCount = 1;
				pi.pSwapchains    = &m_swapchain;
				pi.pImageIndices  = &m_backBufferColorIdx;
				pi.pResults       = NULL;
				VkResult result = vkQueuePresentKHR(m_queueGraphics, &pi);
				if (VK_ERROR_OUT_OF_DATE_KHR       == result
				||  VK_ERROR_VALIDATION_FAILED_EXT == result)
				{
					m_needToRefreshSwapchain = true;
				}
			}
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
//			BX_UNUSED(_handle, _offset, _size, _mem);
			m_indexBuffers[_handle.idx].update(/*m_commandBuffer*/NULL, _offset, bx::min<uint32_t>(_size, _mem->size), _mem->data);
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
//			BX_UNUSED(_handle, _offset, _size, _mem);
			m_vertexBuffers[_handle.idx].update(/*m_commandBuffer*/NULL, _offset, bx::min<uint32_t>(_size, _mem->size), _mem->data);
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
			m_textures[_handle.idx].update(m_commandPool, _side, _mip, _rect, _z, _depth, _pitch, _mem);
		}

		void updateTextureEnd() override
		{
		}

		void readTexture(TextureHandle _handle, void* _data, uint8_t _mip) override
		{
			const TextureVK& texture = m_textures[_handle.idx];

			VkImage srcImage = texture.m_textureImage;
			uint32_t srcWidth  = bx::uint32_max(1, texture.m_width  >> _mip);
			uint32_t srcHeight = bx::uint32_max(1, texture.m_height >> _mip);

			// Create the linear tiled destination image to copy to and to read the memory from
			VkImage dstImage = VK_NULL_HANDLE;
			VkImageCreateInfo ici;
			ici.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			ici.pNext = NULL;
			ici.flags = 0;
			ici.imageType = VK_IMAGE_TYPE_2D;
			ici.format = texture.m_format;
			ici.extent.width = srcWidth;
			ici.extent.height = srcHeight;
			ici.extent.depth = 1;
			ici.arrayLayers = 1;
			ici.mipLevels = 1;
			ici.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			ici.samples = VK_SAMPLE_COUNT_1_BIT;
			ici.tiling = VK_IMAGE_TILING_LINEAR;
			ici.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT;
			ici.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			ici.queueFamilyIndexCount = 0;
			ici.pQueueFamilyIndices = NULL;

			VK_CHECK(vkCreateImage(m_device, &ici, m_allocatorCb, &dstImage));

			// Create memory to back up the image
			VkMemoryRequirements memRequirements;
			vkGetImageMemoryRequirements(m_device, dstImage, &memRequirements);

			VkDeviceMemory dstImageMemory = VK_NULL_HANDLE;
			// Memory must be host visible to copy from
			VK_CHECK(allocateMemory(&memRequirements, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &dstImageMemory));
			VK_CHECK(vkBindImageMemory(m_device, dstImage, dstImageMemory, 0));

			VkCommandBuffer copyCmd = beginNewCommand();

			bgfx::vk::setImageMemoryBarrier(
				copyCmd
				, dstImage
				, texture.m_aspectMask
				, VK_IMAGE_LAYOUT_UNDEFINED
				, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
				, 1
				, 1
			);

			bgfx::vk::setImageMemoryBarrier(
				copyCmd
				, srcImage
				, texture.m_aspectMask
				, texture.m_currentImageLayout
				, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
				, 1
				, 1
			);

			VkImageCopy ic;

			ic.srcSubresource.aspectMask = texture.m_aspectMask;
			ic.srcSubresource.mipLevel = _mip;
			ic.srcSubresource.baseArrayLayer = 0;
			ic.srcSubresource.layerCount = 1;
			ic.srcOffset = { 0, 0, 0 };

			ic.dstSubresource.aspectMask = texture.m_aspectMask;
			ic.dstSubresource.mipLevel = 0;
			ic.dstSubresource.baseArrayLayer = 0;
			ic.dstSubresource.layerCount = 1;
			ic.dstOffset = { 0, 0, 0 };

			ic.extent = { srcWidth, srcHeight, 1 };

			vkCmdCopyImage(
				copyCmd
				, srcImage
				, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
				, dstImage
				, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
				, 1
				, &ic
			);

			// Transition destination image to general layout, which is the required layout for mapping the image memory later on
			bgfx::vk::setImageMemoryBarrier(
				copyCmd
				, dstImage
				, texture.m_aspectMask
				, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
				, VK_IMAGE_LAYOUT_GENERAL
				, 1
				, 1
			);

			bgfx::vk::setImageMemoryBarrier(
				copyCmd
				, srcImage
				, texture.m_aspectMask
				, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
				, texture.m_currentImageLayout
				, 1
				, 1
			);

			submitCommandAndWait(copyCmd);

			// Get layout of the image (including row pitch)
			const VkImageSubresource subResource{ VK_IMAGE_ASPECT_COLOR_BIT, 0, 0 };
			VkSubresourceLayout subResourceLayout;
			vkGetImageSubresourceLayout(m_device, dstImage, &subResource, &subResourceLayout);
			uint32_t srcPitch = uint32_t(subResourceLayout.rowPitch);

			const uint8_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(texture.m_textureFormat));
			uint8_t* dst = (uint8_t*)_data;
			uint32_t dstPitch = srcWidth*bpp/8;

			uint32_t pitch = bx::uint32_min(srcPitch, dstPitch);

			uint8_t* src;
			vkMapMemory(m_device, dstImageMemory, 0, VK_WHOLE_SIZE, 0, (void**)&src);
			src += subResourceLayout.offset;

			for (uint32_t yy = 0, height = srcHeight; yy < height; ++yy)
			{
				bx::memCopy(dst, src, pitch);

				src += srcPitch;
				dst += dstPitch;
			}

			// Clean up resources
			vkUnmapMemory(m_device, dstImageMemory);
			vkFreeMemory(m_device, dstImageMemory, m_allocatorCb);
			vkDestroyImage(m_device, dstImage, m_allocatorCb);
		}

		void resizeTexture(TextureHandle /*_handle*/, uint16_t /*_width*/, uint16_t /*_height*/, uint8_t /*_numMips*/, uint16_t /*_numLayers*/) override
		{
		}

		void overrideInternal(TextureHandle /*_handle*/, uintptr_t /*_ptr*/) override
		{
		}

		uintptr_t getInternal(TextureHandle /*_handle*/) override
		{
			return 0;
		}

		void destroyTexture(TextureHandle _handle) override
		{
		    m_textures[_handle.idx].destroy();
		}

		void createFrameBuffer(FrameBufferHandle _handle, uint8_t _num, const Attachment* _attachment) override
		{
			m_frameBuffers[_handle.idx].create(_num, _attachment);
		}

		void createFrameBuffer(FrameBufferHandle /*_handle*/, void* /*_nwh*/, uint32_t /*_width*/, uint32_t /*_height*/, TextureFormat::Enum /*_format*/, TextureFormat::Enum /*_depthFormat*/) override
		{
		}

		void destroyFrameBuffer(FrameBufferHandle _handle) override
		{
			m_frameBuffers[_handle.idx].destroy();
		}

		void createUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name) override
		{
			if (NULL != m_uniforms[_handle.idx])
			{
				BX_FREE(g_allocator, m_uniforms[_handle.idx]);
			}

			const uint32_t size = bx::alignUp(g_uniformTypeSize[_type] * _num, 16);
			void* data = BX_ALLOC(g_allocator, size);
			bx::memSet(data, 0, size);
			m_uniforms[_handle.idx] = data;
			m_uniformReg.add(_handle, _name);
		}

		void destroyUniform(UniformHandle _handle) override
		{
			BX_FREE(g_allocator, m_uniforms[_handle.idx]);
			m_uniforms[_handle.idx] = NULL;
		}

		void requestScreenShot(FrameBufferHandle _fbh, const char* _filePath) override
		{
			// Source for the copy is the last rendered swapchain image
			VkImage srcImage = m_backBufferColorImage[m_backBufferColorIdx];
			uint32_t width = m_sci.imageExtent.width, height = m_sci.imageExtent.height;

			if (isValid(_fbh) )
			{
				TextureVK& texture = m_textures[m_frameBuffers[_fbh.idx].m_attachment[0].handle.idx];
				srcImage = VK_NULL_HANDLE != texture.m_singleMsaaImage ? texture.m_singleMsaaImage : texture.m_textureImage;
			}

			// Create the linear tiled destination image to copy to and to read the memory from
			VkImage dstImage = VK_NULL_HANDLE;
			VkImageCreateInfo ici;
			ici.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			ici.pNext = NULL;
			ici.flags = 0;
			ici.imageType = VK_IMAGE_TYPE_2D;
			ici.format    = VK_FORMAT_R8G8B8A8_UNORM;
			ici.extent.width  = width;
			ici.extent.height = height;
			ici.extent.depth  = 1;
			ici.arrayLayers = 1;
			ici.mipLevels   = 1;
			ici.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			ici.samples = VK_SAMPLE_COUNT_1_BIT;
			ici.tiling  = VK_IMAGE_TILING_LINEAR;
			ici.usage   = VK_IMAGE_USAGE_TRANSFER_DST_BIT;
			ici.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			ici.queueFamilyIndexCount = 0;
			ici.pQueueFamilyIndices = NULL;
			// Create the image
			VK_CHECK(vkCreateImage(m_device, &ici, m_allocatorCb, &dstImage) );

			// Create memory to back up the image
			VkMemoryRequirements memRequirements;
			vkGetImageMemoryRequirements(m_device, dstImage, &memRequirements);

			VkDeviceMemory dstImageMemory = VK_NULL_HANDLE;
			// Memory must be host visible to copy from
			VK_CHECK(allocateMemory(&memRequirements, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &dstImageMemory) );
			VK_CHECK(vkBindImageMemory(m_device, dstImage, dstImageMemory, 0) );

			// Do the actual blit from the swapchain image to our host visible destination image
			VkCommandBuffer copyCmd = beginNewCommand();

			// Transition destination image to transfer destination layout
			bgfx::vk::setImageMemoryBarrier(
				  copyCmd
				, dstImage
				, VK_IMAGE_ASPECT_COLOR_BIT
				, VK_IMAGE_LAYOUT_UNDEFINED
				, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
				, 1
				, 1
				);

			// Transition swapchain image from present to transfer source layout
			bgfx::vk::setImageMemoryBarrier(
				  copyCmd
				, srcImage
				, VK_IMAGE_ASPECT_COLOR_BIT
				, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
				, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
				, 1
				, 1
				);

			VkImageCopy ic;

			ic.srcSubresource.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
			ic.srcSubresource.mipLevel       = 0;
			ic.srcSubresource.baseArrayLayer = 0;
			ic.srcSubresource.layerCount     = 1;
			ic.srcOffset = { 0, 0, 0 };

			ic.dstSubresource.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
			ic.dstSubresource.mipLevel       = 0;
			ic.dstSubresource.baseArrayLayer = 0;
			ic.dstSubresource.layerCount     = 1;
			ic.dstOffset = { 0, 0, 0 };

			ic.extent = { width, height, 1 };

			// Issue the copy command
			vkCmdCopyImage(
					copyCmd
				, srcImage
				, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
				, dstImage
				, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
				, 1
				, &ic
				);

			// Transition destination image to general layout, which is the required layout for mapping the image memory later on
			bgfx::vk::setImageMemoryBarrier(
				  copyCmd
				, dstImage
				, VK_IMAGE_ASPECT_COLOR_BIT
				, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
				, VK_IMAGE_LAYOUT_GENERAL
				, 1
				, 1
				);

			// Transition back the swap chain image after the blit is done
			bgfx::vk::setImageMemoryBarrier(
				  copyCmd
				, srcImage
				, VK_IMAGE_ASPECT_COLOR_BIT
				, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
				, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
				, 1
				, 1
				);

			submitCommandAndWait(copyCmd);

			// Get layout of the image (including row pitch)
			VkImageSubresource subResource{ VK_IMAGE_ASPECT_COLOR_BIT, 0, 0 };
			VkSubresourceLayout subResourceLayout;
			vkGetImageSubresourceLayout(m_device, dstImage, &subResource, &subResourceLayout);

			// Map image memory so we can start copying from it
			char* data;
			vkMapMemory(m_device, dstImageMemory, 0, VK_WHOLE_SIZE, 0, (void**)&data);
			data += subResourceLayout.offset;

			static const VkFormat unswizzledFormats[] =
			{
				VK_FORMAT_R8G8B8A8_UNORM,
				VK_FORMAT_R8G8B8A8_SRGB
			};

			for (uint32_t ii = 0; ii < BX_COUNTOF(unswizzledFormats); ii++)
			{
				if (m_sci.imageFormat == unswizzledFormats[ii])
				{
					bimg::imageSwizzleBgra8(
						  data
						, uint32_t(subResourceLayout.rowPitch)
						, width
						, height
						, data
						, uint32_t(subResourceLayout.rowPitch)
						);
					break;
				}
			}

			g_callback->screenShot(
				  _filePath
				, width
				, height
				, uint32_t(subResourceLayout.rowPitch)
				, data
				, height * uint32_t(subResourceLayout.rowPitch)
				, false
				);

			// Clean up resources
			vkUnmapMemory(m_device, dstImageMemory);
			vkFreeMemory(m_device, dstImageMemory, m_allocatorCb);
			vkDestroyImage(m_device, dstImage, m_allocatorCb);
		}

		void updateViewName(ViewId _id, const char* _name) override
		{
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
			BX_UNUSED(_handle);
		}

		void setMarker(const char* _marker, uint16_t _len) override
		{
			if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
			{
				BX_UNUSED(_len);

				VkDebugUtilsLabelEXT dul;
				dul.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
				dul.pNext = NULL;
				dul.pLabelName = _marker;
				dul.color[0] = 1.0f;
				dul.color[1] = 0.0f;
				dul.color[2] = 0.0f;
				dul.color[3] = 1.0f;
				vkCmdInsertDebugUtilsLabelEXT(m_commandBuffer, &dul);
			}
		}

		virtual void setName(Handle _handle, const char* _name, uint16_t _len) override
		{
			switch (_handle.type)
			{
			case Handle::IndexBuffer:
				setDebugObjectName(m_device, m_indexBuffers[_handle.idx].m_buffer, "%.*s", _len, _name);
				break;

			case Handle::Shader:
				setDebugObjectName(m_device, m_shaders[_handle.idx].m_module, "%.*s", _len, _name);
				break;

			case Handle::Texture:
//				setDebugObjectName(m_device, m_textures[_handle.idx].m_ptr, "%.*s", _len, _name);
				break;

			case Handle::VertexBuffer:
				setDebugObjectName(m_device, m_vertexBuffers[_handle.idx].m_buffer, "%.*s", _len, _name);
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
			const uint32_t width  = m_sci.imageExtent.width;
			const uint32_t height = m_sci.imageExtent.height;

			setFrameBuffer(BGFX_INVALID_HANDLE, false);

			VkViewport vp;
			vp.x        = 0.0f;
			vp.y        =  float(height);
			vp.width    =  float(width);
			vp.height   = -float(height);
			vp.minDepth = 0.0f;
			vp.maxDepth = 1.0f;
			vkCmdSetViewport(m_commandBuffer, 0, 1, &vp);

			VkRect2D rc;
			rc.offset.x      = 0;
			rc.offset.y      = 0;
			rc.extent.width  = width;
			rc.extent.height = height;
			vkCmdSetScissor(m_commandBuffer, 0, 1, &rc);

			const uint64_t state = 0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_DEPTH_TEST_ALWAYS
				;

			const VertexLayout* layout = &m_vertexLayouts[_blitter.m_vb->layoutHandle.idx];
			VkPipeline pso = getPipeline(state
				, packStencil(BGFX_STENCIL_DEFAULT, BGFX_STENCIL_DEFAULT)
				, 1
				, &layout
				, _blitter.m_program
				, 0
				);
			vkCmdBindPipeline(m_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pso);

			ProgramVK& program = m_program[_blitter.m_program.idx];
			float proj[16];
			bx::mtxOrtho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f, 0.0f, false);

			PredefinedUniform& predefined = m_program[_blitter.m_program.idx].m_predefined[0];
			uint8_t flags = predefined.m_type;
			setShaderUniform(flags, predefined.m_loc, proj, 4);

			UniformBuffer* vcb = program.m_vsh->m_constantBuffer;
			if (NULL != vcb)
			{
				commit(*vcb);
			}
			ScratchBufferVK& scratchBuffer = m_scratchBuffer[m_backBufferColorIdx];
			VkDescriptorSetLayout dsl = m_descriptorSetLayoutCache.find(program.m_descriptorSetLayoutHash);
			VkDescriptorSetAllocateInfo dsai;
			dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			dsai.pNext = NULL;
			dsai.descriptorPool = m_descriptorPool;
			dsai.descriptorSetCount = 1;
			dsai.pSetLayouts = &dsl;
			vkAllocateDescriptorSets(m_device, &dsai, &scratchBuffer.m_descriptorSet[scratchBuffer.m_currentDs]);

			const uint32_t align = uint32_t(m_deviceProperties.limits.minUniformBufferOffsetAlignment);
			TextureVK& texture = m_textures[_blitter.m_texture.idx];
			uint32_t samplerFlags = (uint32_t)(texture.m_flags & BGFX_SAMPLER_BITS_MASK);
			VkSampler sampler = getSampler(samplerFlags, 1);

			const uint32_t size = bx::strideAlign(program.m_vsh->m_size, align);
			uint32_t bufferOffset = scratchBuffer.m_pos;
			VkDescriptorBufferInfo bufferInfo;
			bufferInfo.buffer = scratchBuffer.m_buffer;
			bufferInfo.offset = 0;
			bufferInfo.range  = size;
			bx::memCopy(&scratchBuffer.m_data[scratchBuffer.m_pos], m_vsScratch, program.m_vsh->m_size);
			scratchBuffer.m_pos += size;

			VkWriteDescriptorSet wds[3];
			wds[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			wds[0].pNext = NULL;
			wds[0].dstSet = scratchBuffer.m_descriptorSet[scratchBuffer.m_currentDs];
			wds[0].dstBinding = program.m_vsh->m_uniformBinding;
			wds[0].dstArrayElement = 0;
			wds[0].descriptorCount = 1;
			wds[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
			wds[0].pImageInfo = NULL;
			wds[0].pBufferInfo = &bufferInfo;
			wds[0].pTexelBufferView = NULL;

			VkDescriptorImageInfo imageInfo;
			imageInfo.imageLayout = texture.m_currentImageLayout;
			imageInfo.imageView = texture.m_textureImageView;
			imageInfo.sampler = sampler;

			wds[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			wds[1].pNext = NULL;
			wds[1].dstSet = scratchBuffer.m_descriptorSet[scratchBuffer.m_currentDs];
			wds[1].dstBinding = program.m_fsh->m_bindInfo[0].binding;
			wds[1].dstArrayElement = 0;
			wds[1].descriptorCount = 1;
			wds[1].descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
			wds[1].pImageInfo = &imageInfo;
			wds[1].pBufferInfo = NULL;
			wds[1].pTexelBufferView = NULL;

			wds[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			wds[2].pNext = NULL;
			wds[2].dstSet = scratchBuffer.m_descriptorSet[scratchBuffer.m_currentDs];
			wds[2].dstBinding = program.m_fsh->m_bindInfo[0].samplerBinding;
			wds[2].dstArrayElement = 0;
			wds[2].descriptorCount = 1;
			wds[2].descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
			wds[2].pImageInfo = &imageInfo;
			wds[2].pBufferInfo = NULL;
			wds[2].pTexelBufferView = NULL;

			vkUpdateDescriptorSets(m_device, 3, wds, 0, NULL);
			vkCmdBindDescriptorSets(
				m_commandBuffer
				, VK_PIPELINE_BIND_POINT_GRAPHICS
				, program.m_pipelineLayout
				, 0
				, 1
				, &scratchBuffer.m_descriptorSet[scratchBuffer.m_currentDs]
				, 1
				, &bufferOffset
				);

			scratchBuffer.m_currentDs++;

			VertexBufferVK& vb  = m_vertexBuffers[_blitter.m_vb->handle.idx];
			VkDeviceSize offset = 0;
			vkCmdBindVertexBuffers(m_commandBuffer
				, 0
				, 1
				, &vb.m_buffer
				, &offset
				);

			BufferVK& ib = m_indexBuffers[_blitter.m_ib->handle.idx];
			vkCmdBindIndexBuffer(m_commandBuffer
				, ib.m_buffer
				, 0
				, VK_INDEX_TYPE_UINT16
				);
		}

		void blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices) override
		{
			const uint32_t numVertices = _numIndices*4/6;
			if (0 < numVertices)
			{
				m_indexBuffers[_blitter.m_ib->handle.idx].update(m_commandBuffer, 0, _numIndices*2, _blitter.m_ib->data);
				m_vertexBuffers[_blitter.m_vb->handle.idx].update(m_commandBuffer, 0, numVertices*_blitter.m_layout.m_stride, _blitter.m_vb->data, true);

				vkCmdDrawIndexed(m_commandBuffer
					, _numIndices
					, 1
					, 0
					, 0
					, 0
					);
			}
		}

		uint32_t findPresentMode(bool _vsync)
		{
			VkResult result;
			uint32_t numPresentModes;
			result = vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, m_surface, &numPresentModes, NULL);
			if (VK_SUCCESS != result)
			{
				BX_TRACE("findPresentMode error: vkGetPhysicalDeviceSurfacePresentModesKHR failed %d: %s.", result, getName(result) );
				return UINT32_MAX;
			}

			VkPresentModeKHR presentModes[16];
			numPresentModes = bx::min<uint32_t>(numPresentModes, BX_COUNTOF(presentModes) );
			result = vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, m_surface, &numPresentModes, presentModes);
			if (VK_SUCCESS != result)
			{
				BX_TRACE("Init error: vkGetPhysicalDeviceSurfacePresentModesKHR failed %d: %s.", result, getName(result) );
				return UINT32_MAX;
			}

			uint32_t idx = UINT32_MAX;

			for (uint32_t ii = 0; ii < BX_COUNTOF(s_presentMode) && UINT32_MAX == idx; ++ii)
			{
				for (uint32_t jj = 0; jj < numPresentModes; ++jj)
				{
					const PresentMode& pm = s_presentMode[ii];

					if (pm.mode  == presentModes[jj]
					&&  pm.vsync == _vsync)
					{
						idx = ii;
						break;
					}
				}
			}

			if (UINT32_MAX == idx)
			{
				idx = 0;
				BX_TRACE("Present mode not found! Defaulting to %s.", s_presentMode[idx].name);
			}

			return idx;
		}

		bool updateResolution(const Resolution& _resolution)
		{
			if (!!(_resolution.reset & BGFX_RESET_MAXANISOTROPY) )
			{
				m_maxAnisotropy = UINT32_MAX;
			}
			else
			{
				m_maxAnisotropy = 1;
			}

			bool depthClamp = !!(_resolution.reset & BGFX_RESET_DEPTH_CLAMP);

			if (m_depthClamp != depthClamp)
			{
				m_depthClamp = depthClamp;
				m_pipelineStateCache.invalidate();
			}

			uint32_t flags = _resolution.reset & ~(BGFX_RESET_MAXANISOTROPY | BGFX_RESET_DEPTH_CLAMP);

			if (m_resolution.width  != _resolution.width
			||  m_resolution.height != _resolution.height
			||  m_resolution.reset  != flags)
			{
				flags &= ~BGFX_RESET_INTERNAL_FORCE;

				const bool resize        = (m_resolution.reset & BGFX_RESET_MSAA_MASK      ) == (_resolution.reset & BGFX_RESET_MSAA_MASK      );
				const bool formatChanged = (m_resolution.reset & BGFX_RESET_SRGB_BACKBUFFER) == (_resolution.reset & BGFX_RESET_SRGB_BACKBUFFER);

				m_resolution = _resolution;
				m_resolution.reset = flags;

				m_textVideoMem.resize(false, _resolution.width, _resolution.height);
				m_textVideoMem.clear();

				if (resize
				||  formatChanged
				||  m_needToRefreshSwapchain)
				{
					for (uint32_t ii = 0; ii < BX_COUNTOF(m_backBufferColorImageView); ++ii)
					{
						vkDestroy(m_presentDone[ii]);
						m_presentDone[ii] = VK_NULL_HANDLE;
					}

					VK_CHECK(vkDeviceWaitIdle(m_device) );
					releaseSwapchainFramebuffer();
					releaseSwapchainRenderPass();
					releaseSwapchain();

					VkSurfaceFormatKHR surfaceFormat = (m_resolution.reset & BGFX_RESET_SRGB_BACKBUFFER)
						? m_backBufferColorFormatSrgb
						: m_backBufferColorFormat
						;
					m_sci.imageFormat = surfaceFormat.format;
					m_sci.imageColorSpace = surfaceFormat.colorSpace;

					const bool vsync = !!(flags & BGFX_RESET_VSYNC);
					const uint32_t presentModeIdx = findPresentMode(vsync);
					BGFX_FATAL(UINT32_MAX != presentModeIdx
						, bgfx::Fatal::DeviceLost
						, "Unable to find present mode."
						);

					m_sci.presentMode = s_presentMode[presentModeIdx].mode;

					VkSurfaceCapabilitiesKHR surfaceCapabilities;
					VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physicalDevice, m_surface, &surfaceCapabilities) );

					m_sci.imageExtent.width  = bx::clamp<uint32_t>(m_resolution.width
						, surfaceCapabilities.minImageExtent.width
						, surfaceCapabilities.maxImageExtent.width
						);
					m_sci.imageExtent.height = bx::clamp<uint32_t>(m_resolution.height
						, surfaceCapabilities.minImageExtent.height
						, surfaceCapabilities.maxImageExtent.height
						);

					// Prevent validation error when minimizing a window
					if (m_sci.imageExtent.width == 0 || m_sci.imageExtent.height == 0)
					{
						m_resolution.width = 0;
						m_resolution.height = 0;
						return true;
					}

					VK_CHECK(createSwapchain() );
					VK_CHECK(createSwapchainRenderPass() );
					VK_CHECK(createSwapchainFramebuffer() );

					VkSemaphoreCreateInfo sci;
					sci.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
					sci.pNext = NULL;
					sci.flags = 0;

					for (uint32_t ii = 0; ii < m_numSwapchainImages; ++ii)
					{
						VK_CHECK(vkCreateSemaphore(m_device, &sci, m_allocatorCb, &m_presentDone[ii]) );
					}

					initSwapchainImageLayout();

					BX_TRACE("Swapchain (%s): %dx%d%s"
						, s_presentMode[presentModeIdx].name
						, m_sci.imageExtent.width
						, m_sci.imageExtent.height
						, vsync ? " + vsync" : ""
						);
				}
			}

			if (m_needToRefreshSwapchain)
			{
				return true;
			}

			return false;
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

//		void commitShaderUniforms(VkCommandBuffer _commandBuffer, ProgramHandle _program)
//		{
//			ProgramVK& program = m_program[_program.idx];
//
//			const uint32_t align = uint32_t(m_deviceProperties.limits.minUniformBufferOffsetAlignment);
//			const uint32_t vsize = bx::strideAlign(program.m_vsh->m_size, align);
//			const uint32_t fsize = bx::strideAlign( (NULL != program.m_fsh ? program.m_fsh->m_size : 0), align);
//			const uint32_t total = vsize + fsize;
//
//			if (0 < total)
//			{
//				ScratchBufferVK& sb = m_scratchBuffer[m_backBufferColorIdx];
//
//				uint8_t* data = (uint8_t*)sb.allocUbv(vsize, fsize);
//
//				bx::memCopy(data, m_vsScratch, program.m_vsh->m_size);
//				data += vsize;
//
//				if (0 != fsize)
//				{
//					bx::memCopy(data, m_fsScratch, program.m_fsh->m_size);
//				}
//
//				vkCmdBindDescriptorSets(_commandBuffer
//					, VK_PIPELINE_BIND_POINT_GRAPHICS
//					, m_pipelineLayout
//					, program.m_pipelineLayout
//					, 0
//					, 1
//					, &sb.m_descriptorSet[sb.m_currentDs - 1]
//					, 0
//					, NULL
//					);
//			}
//		}

		void setFrameBuffer(FrameBufferHandle _fbh, bool _msaa = true)
		{
			BX_UNUSED(_msaa);

			if (isValid(m_fbh)
			&&  m_fbh.idx != _fbh.idx)
			{
				FrameBufferVK& frameBuffer = m_frameBuffers[m_fbh.idx];
				BX_UNUSED(frameBuffer);

				if (m_rtMsaa) frameBuffer.resolve();

				for (uint8_t ii = 0, num = frameBuffer.m_num; ii < num; ++ii)
				{
					TextureVK& texture = m_textures[frameBuffer.m_texture[ii].idx];
					texture.setImageMemoryBarrier(m_commandBuffer, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
				}

				if (isValid(frameBuffer.m_depth) )
				{
					TextureVK& texture = m_textures[frameBuffer.m_depth.idx];
					const bool writeOnly  = 0 != (texture.m_flags&BGFX_TEXTURE_RT_WRITE_ONLY);
					if (!writeOnly)
					{
						texture.setImageMemoryBarrier(m_commandBuffer, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
					}
				}
			}

			if (!isValid(_fbh) )
			{
//				m_rtvHandle = m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
//				uint32_t rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
//				m_rtvHandle.ptr += m_backBufferColorIdx * rtvDescriptorSize;
//				m_dsvHandle = m_dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
//
//				m_currentColor        = &m_rtvHandle;
//				m_currentDepthStencil = &m_dsvHandle;
//				m_commandList->OMSetRenderTargets(1, m_currentColor, true, m_currentDepthStencil);
			}
			else
			{
				const FrameBufferVK& frameBuffer = m_frameBuffers[_fbh.idx];
				BX_UNUSED(frameBuffer);

				if (0 < frameBuffer.m_num)
				{
//					D3D12_CPU_DESCRIPTOR_HANDLE rtvDescriptor = m_rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
//					uint32_t rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
//					m_rtvHandle.ptr = rtvDescriptor.ptr + (BX_COUNTOF(m_backBufferColor) + _fbh.idx * BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS) * rtvDescriptorSize;
//					m_currentColor  = &m_rtvHandle;
				}
				else
				{
//					m_currentColor = NULL;
				}

				if (isValid(frameBuffer.m_depth) )
				{
//					D3D12_CPU_DESCRIPTOR_HANDLE dsvDescriptor = m_dsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
//					uint32_t dsvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
//					m_dsvHandle.ptr = dsvDescriptor.ptr + (1 + _fbh.idx) * dsvDescriptorSize;
//					m_currentDepthStencil = &m_dsvHandle;
				}
				else
				{
//					m_currentDepthStencil = NULL;
				}

				for (uint8_t ii = 0, num = frameBuffer.m_num; ii < num; ++ii)
				{
					TextureVK& texture = m_textures[frameBuffer.m_texture[ii].idx];
					texture.setImageMemoryBarrier(m_commandBuffer, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
				}

				if (isValid(frameBuffer.m_depth) )
				{
					TextureVK& texture = m_textures[frameBuffer.m_depth.idx];
					texture.setImageMemoryBarrier(m_commandBuffer, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
				}

//				m_commandList->OMSetRenderTargets(frameBuffer.m_num
//												, m_currentColor
//												, true
//												, m_currentDepthStencil
//												);
			}

			m_fbh = _fbh;
			m_rtMsaa = _msaa;
		}

		void setBlendState(VkPipelineColorBlendStateCreateInfo& _desc, uint64_t _state, uint32_t _rgba = 0)
		{
			VkPipelineColorBlendAttachmentState* bas = const_cast<VkPipelineColorBlendAttachmentState*>(_desc.pAttachments);

			uint8_t writeMask = 0;
			writeMask |= (_state & BGFX_STATE_WRITE_R) ? VK_COLOR_COMPONENT_R_BIT : 0;
			writeMask |= (_state & BGFX_STATE_WRITE_G) ? VK_COLOR_COMPONENT_G_BIT : 0;
			writeMask |= (_state & BGFX_STATE_WRITE_B) ? VK_COLOR_COMPONENT_B_BIT : 0;
			writeMask |= (_state & BGFX_STATE_WRITE_A) ? VK_COLOR_COMPONENT_A_BIT : 0;

			bas->blendEnable = !!(BGFX_STATE_BLEND_MASK & _state);

			{
				const uint32_t blend    = uint32_t( (_state & BGFX_STATE_BLEND_MASK         ) >> BGFX_STATE_BLEND_SHIFT);
				const uint32_t equation = uint32_t( (_state & BGFX_STATE_BLEND_EQUATION_MASK) >> BGFX_STATE_BLEND_EQUATION_SHIFT);

				const uint32_t srcRGB = (blend      ) & 0xf;
				const uint32_t dstRGB = (blend >>  4) & 0xf;
				const uint32_t srcA   = (blend >>  8) & 0xf;
				const uint32_t dstA   = (blend >> 12) & 0xf;

				const uint32_t equRGB = (equation     ) & 0x7;
				const uint32_t equA   = (equation >> 3) & 0x7;

				bas->srcColorBlendFactor = s_blendFactor[srcRGB][0];
				bas->dstColorBlendFactor = s_blendFactor[dstRGB][0];
				bas->colorBlendOp        = s_blendEquation[equRGB];

				bas->srcAlphaBlendFactor = s_blendFactor[srcA][1];
				bas->dstAlphaBlendFactor = s_blendFactor[dstA][1];
				bas->alphaBlendOp        = s_blendEquation[equA];

				bas->colorWriteMask = writeMask;
			}

			uint32_t numAttachments = 1;
			if (isValid(m_fbh) )
			{
				const FrameBufferVK& frameBuffer = m_frameBuffers[m_fbh.idx];
				numAttachments = frameBuffer.m_num;
			}

			if (!!(BGFX_STATE_BLEND_INDEPENDENT & _state) && m_deviceFeatures.independentBlend )
			{
				for (uint32_t ii = 1, rgba = _rgba; ii < numAttachments; ++ii, rgba >>= 11)
				{
					++bas;
					bas->blendEnable =  0 != (rgba & 0x7ff);

					const uint32_t src      = (rgba     ) & 0xf;
					const uint32_t dst      = (rgba >> 4) & 0xf;
					const uint32_t equation = (rgba >> 8) & 0x7;

					bas->srcColorBlendFactor = s_blendFactor[src][0];
					bas->dstColorBlendFactor = s_blendFactor[dst][0];
					bas->colorBlendOp        = s_blendEquation[equation];

					bas->srcAlphaBlendFactor = s_blendFactor[src][1];
					bas->dstAlphaBlendFactor = s_blendFactor[dst][1];
					bas->alphaBlendOp        = s_blendEquation[equation];

					bas->colorWriteMask = writeMask;
				}
			}
			else
			{
				for (uint32_t ii = 1; ii < numAttachments; ++ii)
				{
					bx::memCopy(&bas[ii], bas, sizeof(VkPipelineColorBlendAttachmentState) );
				}
			}

			_desc.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
			_desc.pNext = NULL;
			_desc.flags = 0;
			_desc.logicOpEnable = VK_FALSE;
			_desc.logicOp       = VK_LOGIC_OP_CLEAR;
			_desc.attachmentCount = numAttachments;
			_desc.blendConstants[0] = 0.0f;
			_desc.blendConstants[1] = 0.0f;
			_desc.blendConstants[2] = 0.0f;
			_desc.blendConstants[3] = 0.0f;
		}

		void setRasterizerState(VkPipelineRasterizationStateCreateInfo& _desc, uint64_t _state, bool _wireframe = false)
		{
			const uint32_t cull = (_state&BGFX_STATE_CULL_MASK) >> BGFX_STATE_CULL_SHIFT;

			_desc.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
			_desc.pNext = NULL;
			_desc.flags = 0;
			_desc.depthClampEnable = m_depthClamp;
			_desc.rasterizerDiscardEnable = VK_FALSE;
			_desc.polygonMode = _wireframe
				? VK_POLYGON_MODE_LINE
				: VK_POLYGON_MODE_FILL
				;
			_desc.cullMode  = s_cullMode[cull];
			_desc.frontFace = (_state&BGFX_STATE_FRONT_CCW) ? VK_FRONT_FACE_COUNTER_CLOCKWISE : VK_FRONT_FACE_CLOCKWISE;
			_desc.depthBiasEnable = VK_FALSE;
			_desc.depthBiasConstantFactor = 0.0f;
			_desc.depthBiasClamp          = 0.0f;
			_desc.depthBiasSlopeFactor    = 0.0f;
			_desc.lineWidth               = 1.0f;
		}

		void setDepthStencilState(VkPipelineDepthStencilStateCreateInfo& _desc, uint64_t _state, uint64_t _stencil = 0)
		{
			const uint32_t fstencil = unpackStencil(0, _stencil);
			uint32_t func = (_state&BGFX_STATE_DEPTH_TEST_MASK)>>BGFX_STATE_DEPTH_TEST_SHIFT;

			_desc.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
			_desc.pNext = NULL;
			_desc.flags = 0;
			_desc.depthTestEnable  = 0 != func;
			_desc.depthWriteEnable = !!(BGFX_STATE_WRITE_Z & _state);
			_desc.depthCompareOp   = s_cmpFunc[func];
			_desc.depthBoundsTestEnable = VK_FALSE;

			_desc.stencilTestEnable = 0 != _stencil;

			uint32_t bstencil = unpackStencil(1, _stencil);
			uint32_t frontAndBack = bstencil != BGFX_STENCIL_NONE && bstencil != fstencil;
			bstencil = frontAndBack ? bstencil : fstencil;

			_desc.front.failOp      = s_stencilOp[(fstencil & BGFX_STENCIL_OP_FAIL_S_MASK) >> BGFX_STENCIL_OP_FAIL_S_SHIFT];
			_desc.front.passOp      = s_stencilOp[(fstencil & BGFX_STENCIL_OP_PASS_Z_MASK) >> BGFX_STENCIL_OP_PASS_Z_SHIFT];
			_desc.front.depthFailOp = s_stencilOp[(fstencil & BGFX_STENCIL_OP_FAIL_Z_MASK) >> BGFX_STENCIL_OP_FAIL_Z_SHIFT];
			_desc.front.compareOp   = s_cmpFunc[(fstencil & BGFX_STENCIL_TEST_MASK) >> BGFX_STENCIL_TEST_SHIFT];
			_desc.front.compareMask = UINT32_MAX;
			_desc.front.writeMask   = UINT32_MAX;
			_desc.front.reference   = 0;

			_desc.back.failOp       = s_stencilOp[(bstencil & BGFX_STENCIL_OP_FAIL_S_MASK) >> BGFX_STENCIL_OP_FAIL_S_SHIFT];
			_desc.back.passOp       = s_stencilOp[(bstencil & BGFX_STENCIL_OP_PASS_Z_MASK) >> BGFX_STENCIL_OP_PASS_Z_SHIFT];
			_desc.back.depthFailOp  = s_stencilOp[(bstencil & BGFX_STENCIL_OP_FAIL_Z_MASK) >> BGFX_STENCIL_OP_FAIL_Z_SHIFT];
			_desc.back.compareOp    = s_cmpFunc[(bstencil&BGFX_STENCIL_TEST_MASK) >> BGFX_STENCIL_TEST_SHIFT];
			_desc.back.compareMask  = UINT32_MAX;
			_desc.back.writeMask    = UINT32_MAX;
			_desc.back.reference    = 0;

			_desc.minDepthBounds = 0.0f;
			_desc.maxDepthBounds = 1.0f;
		}

		void setInputLayout(VkPipelineVertexInputStateCreateInfo& _vertexInputState, uint8_t _numStream, const VertexLayout** _layout, const ProgramVK& _program, uint8_t _numInstanceData)
		{
			_vertexInputState.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
			_vertexInputState.pNext = NULL;
			_vertexInputState.flags = 0;

			_vertexInputState.vertexBindingDescriptionCount   = 0;
			_vertexInputState.vertexAttributeDescriptionCount = 0;

			uint16_t unsettedAttr[Attrib::Count];
			bx::memCopy(unsettedAttr, _program.m_vsh->m_attrMask, sizeof(uint16_t) * Attrib::Count);
			for (uint8_t stream = 0; stream < _numStream; ++stream)
			{
				VertexLayout layout;
				bx::memCopy(&layout, _layout[stream], sizeof(VertexLayout) );
				const uint16_t* attrMask = _program.m_vsh->m_attrMask;

				for (uint32_t ii = 0; ii < Attrib::Count; ++ii)
				{
					uint16_t mask = attrMask[ii];
					uint16_t attr = (layout.m_attributes[ii] & mask);
					layout.m_attributes[ii] = attr == 0 || attr == UINT16_MAX ? UINT16_MAX : attr;
					if (unsettedAttr[ii] && attr != UINT16_MAX)
					{
						unsettedAttr[ii] = 0;
					}
				}

				fillVertexLayout(_program.m_vsh, _vertexInputState, layout);
			}

			for (uint32_t ii = 0; ii < Attrib::Count; ++ii)
			{
				if (0 < unsettedAttr[ii])
				{
					uint32_t numAttribs  = _vertexInputState.vertexAttributeDescriptionCount;
					VkVertexInputAttributeDescription* inputAttrib = const_cast<VkVertexInputAttributeDescription*>(_vertexInputState.pVertexAttributeDescriptions + numAttribs);
					inputAttrib->location = _program.m_vsh->m_attrRemap[ii];
					inputAttrib->binding  = 0;
					inputAttrib->format = VK_FORMAT_R32G32B32_SFLOAT;
					inputAttrib->offset = 0;
					_vertexInputState.vertexAttributeDescriptionCount++;
				}
			}

			if (0 < _numInstanceData)
			{
				fillInstanceBinding(_program.m_vsh, _vertexInputState, _numInstanceData);
			}
		}

		uint32_t getRenderPassHashkey(uint8_t _num, const Attachment* attachments)
		{
			if (_num == 0)
				return 0;
			bx::HashMurmur2A hash;
			hash.begin(0);
			for (uint8_t ii = 0; ii < _num; ++ii)
			{
				hash.add(attachments[ii].access);
				hash.add(attachments[ii].layer);
				hash.add(attachments[ii].mip);
				hash.add(attachments[ii].resolve);

				TextureVK& texture = m_textures[attachments[ii].handle.idx];
				hash.add(texture.m_textureFormat);
			}
			return hash.end();
		}

		VkRenderPass getRenderPass(uint8_t _num, const Attachment* _attachments)
		{
			VkRenderPass renderPass = VK_NULL_HANDLE;
			uint32_t hashKey = getRenderPassHashkey(_num, _attachments);
			renderPass = (VkRenderPass)m_renderPassCache.find(hashKey);
			if (renderPass != VK_NULL_HANDLE)
				return renderPass;

			// cache missed
			VkAttachmentDescription ad[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
			VkAttachmentReference colorAr[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
			VkAttachmentReference resolveAr[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
			VkAttachmentReference depthAr;
			uint32_t numColorAr = 0;

			depthAr.attachment   = VK_ATTACHMENT_UNUSED;
			depthAr.layout		 = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

			for (uint8_t ii = 0; ii < _num; ++ii)
			{
				TextureVK& texture = m_textures[_attachments[ii].handle.idx];
				ad[ii].flags          = 0;
				ad[ii].format         = texture.m_format;
				ad[ii].samples        = texture.m_sampler.Sample;

				if (texture.m_aspectMask & VK_IMAGE_ASPECT_COLOR_BIT)
				{
					ad[ii].loadOp                  = VK_ATTACHMENT_LOAD_OP_LOAD;
					ad[ii].storeOp                 = VK_ATTACHMENT_STORE_OP_STORE;
					ad[ii].stencilLoadOp           = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
					ad[ii].stencilStoreOp          = VK_ATTACHMENT_STORE_OP_DONT_CARE;
					ad[ii].initialLayout           = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
					ad[ii].finalLayout             = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
					colorAr[numColorAr].layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
					colorAr[numColorAr].attachment = ii;
					numColorAr++;
				}
				else if (texture.m_aspectMask & VK_IMAGE_ASPECT_DEPTH_BIT)
				{
					ad[ii].loadOp         = VK_ATTACHMENT_LOAD_OP_LOAD;
					ad[ii].storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
					ad[ii].stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_LOAD;
					ad[ii].stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE;
					ad[ii].initialLayout  = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
					ad[ii].finalLayout    = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
					depthAr.layout        = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
					depthAr.attachment    = ii;
				}

				resolveAr[ii].attachment = VK_ATTACHMENT_UNUSED;
				resolveAr[ii].layout     = ad[ii].initialLayout;
			}

			VkSubpassDescription sd[1];
			sd[0].flags                   = 0;
			sd[0].pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS;
			sd[0].inputAttachmentCount    = 0;
			sd[0].pInputAttachments       = NULL;
			sd[0].colorAttachmentCount    = numColorAr;
			sd[0].pColorAttachments       = colorAr;
			sd[0].pResolveAttachments     = resolveAr;
			sd[0].pDepthStencilAttachment = &depthAr;
			sd[0].preserveAttachmentCount = 0;
			sd[0].pPreserveAttachments    = NULL;

			VkRenderPassCreateInfo rpi;
			rpi.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			rpi.pNext           = NULL;
			rpi.flags           = 0;
			rpi.attachmentCount = _num;
			rpi.pAttachments    = ad;
			rpi.subpassCount    = BX_COUNTOF(sd);
			rpi.pSubpasses      = sd;
			rpi.dependencyCount = 0;
			rpi.pDependencies   = NULL;

			VK_CHECK( vkCreateRenderPass(m_device, &rpi, m_allocatorCb, &renderPass) );

			m_renderPassCache.add(hashKey, renderPass);
			return renderPass;
		}

		VkSampler getSampler(uint32_t _samplerFlags, uint32_t _mipLevels)
		{
			bx::HashMurmur2A hash;
			hash.begin();
			hash.add(_samplerFlags);
			hash.add(_mipLevels);
			uint32_t hashKey = hash.end();

			VkSampler sampler = m_samplerCache.find(hashKey);
			if (sampler != VK_NULL_HANDLE)
			{
				return sampler;
			}

			const uint32_t cmpFunc = (_samplerFlags&BGFX_SAMPLER_COMPARE_MASK)>>BGFX_SAMPLER_COMPARE_SHIFT;

			VkSamplerCreateInfo sci;
			sci.sType            = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			sci.pNext            = NULL;
			sci.flags            = 0;
			sci.magFilter        = VK_FILTER_LINEAR;
			sci.minFilter        = VK_FILTER_LINEAR;
			sci.mipmapMode       = VK_SAMPLER_MIPMAP_MODE_LINEAR;
			sci.addressModeU     = s_textureAddress[(_samplerFlags&BGFX_SAMPLER_U_MASK)>>BGFX_SAMPLER_U_SHIFT];
			sci.addressModeV     = s_textureAddress[(_samplerFlags&BGFX_SAMPLER_V_MASK)>>BGFX_SAMPLER_V_SHIFT];
			sci.addressModeW     = s_textureAddress[(_samplerFlags&BGFX_SAMPLER_W_MASK)>>BGFX_SAMPLER_W_SHIFT];
			sci.mipLodBias       = 0.0f;
			sci.anisotropyEnable = VK_FALSE;
			sci.maxAnisotropy    = 4.0f;
			sci.compareEnable    = 0 != cmpFunc;
			sci.compareOp        = s_cmpFunc[cmpFunc];
			sci.minLod           = 0.0f;
			sci.maxLod           = (float)_mipLevels;
			sci.borderColor      = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
			sci.unnormalizedCoordinates = VK_FALSE;

			switch (_samplerFlags & BGFX_SAMPLER_MAG_MASK)
			{
				case BGFX_SAMPLER_MAG_POINT:       sci.magFilter = VK_FILTER_NEAREST; break;
				case BGFX_SAMPLER_MAG_ANISOTROPIC: sci.anisotropyEnable = VK_TRUE;    break;
			}

			switch (_samplerFlags & BGFX_SAMPLER_MIN_MASK)
			{
				case BGFX_SAMPLER_MIN_POINT:       sci.minFilter = VK_FILTER_NEAREST; break;
				case BGFX_SAMPLER_MIN_ANISOTROPIC: sci.anisotropyEnable = VK_TRUE;    break;
			}

			uint32_t borderColor = ( (_samplerFlags & BGFX_SAMPLER_BORDER_COLOR_MASK) >> BGFX_SAMPLER_BORDER_COLOR_SHIFT);
			if (borderColor > 0)
			{
				sci.borderColor = VK_BORDER_COLOR_INT_OPAQUE_WHITE;
			}

			VK_CHECK(vkCreateSampler(m_device, &sci, m_allocatorCb, &sampler) );

			m_samplerCache.add(hashKey, sampler);
			return sampler;
		}

		VkPipeline getPipeline(ProgramHandle _program)
		{
			ProgramVK& program = m_program[_program.idx];

			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(program.m_vsh->m_hash);
			const uint32_t hash = murmur.end();

			VkPipeline pipeline = m_pipelineStateCache.find(hash);

			if (VK_NULL_HANDLE != pipeline)
			{
				return pipeline;
			}

			VkComputePipelineCreateInfo cpci;
			cpci.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
			cpci.pNext = NULL;
			cpci.flags = 0;

			cpci.stage.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			cpci.stage.pNext  = NULL;
			cpci.stage.flags  = 0;
			cpci.stage.stage  = VK_SHADER_STAGE_COMPUTE_BIT;
			cpci.stage.module = program.m_vsh->m_module;
			cpci.stage.pName  = "main";
			cpci.stage.pSpecializationInfo = NULL;

			cpci.layout             = program.m_pipelineLayout;
			cpci.basePipelineHandle = VK_NULL_HANDLE;
			cpci.basePipelineIndex  = 0;

			VK_CHECK( vkCreateComputePipelines(m_device, m_pipelineCache, 1, &cpci, m_allocatorCb, &pipeline) );

			m_pipelineStateCache.add(hash, pipeline);

			return pipeline;
		}

		VkPipeline getPipeline(uint64_t _state, uint64_t _stencil, uint8_t _numStreams, const VertexLayout** _layouts, ProgramHandle _program, uint8_t _numInstanceData)
		{
			ProgramVK& program = m_program[_program.idx];

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
				| BGFX_STATE_MSAA
				| BGFX_STATE_LINEAA
				| BGFX_STATE_CONSERVATIVE_RASTER
				| BGFX_STATE_PT_MASK
				;

			_stencil &= packStencil(~BGFX_STENCIL_FUNC_REF_MASK, ~BGFX_STENCIL_FUNC_REF_MASK);

			VertexLayout layout;
			if (0 < _numStreams)
			{
				bx::memCopy(&layout, _layouts[0], sizeof(VertexLayout) );
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
			murmur.add(program.m_vsh->m_hash);
			murmur.add(program.m_vsh->m_attrMask, sizeof(program.m_vsh->m_attrMask) );
			if (NULL != program.m_fsh)
			{
				murmur.add(program.m_fsh->m_hash);
			}
			for (uint8_t ii = 0; ii < _numStreams; ++ii)
			{
				murmur.add(_layouts[ii]->m_hash);
			}
			murmur.add(layout.m_attributes, sizeof(layout.m_attributes) );
			murmur.add(m_fbh.idx);
			murmur.add(_numInstanceData);
			const uint32_t hash = murmur.end();

			VkPipeline pipeline = m_pipelineStateCache.find(hash);

			if (VK_NULL_HANDLE != pipeline)
			{
				return pipeline;
			}

			VkPipelineColorBlendAttachmentState blendAttachmentState[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
			VkPipelineColorBlendStateCreateInfo colorBlendState;
			colorBlendState.pAttachments = blendAttachmentState;
			setBlendState(colorBlendState, _state);

			VkPipelineInputAssemblyStateCreateInfo inputAssemblyState;
			inputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
			inputAssemblyState.pNext = NULL;
			inputAssemblyState.flags = 0;
			inputAssemblyState.topology = s_primInfo[(_state&BGFX_STATE_PT_MASK) >> BGFX_STATE_PT_SHIFT].m_topology;
			inputAssemblyState.primitiveRestartEnable = VK_FALSE;

			VkPipelineRasterizationStateCreateInfo rasterizationState;
			setRasterizerState(rasterizationState, _state);

			VkPipelineDepthStencilStateCreateInfo depthStencilState;
			setDepthStencilState(depthStencilState, _state, _stencil);

			VkVertexInputBindingDescription  inputBinding[Attrib::Count + 1 + BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT];
			VkVertexInputAttributeDescription inputAttrib[Attrib::Count + 1 + BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT];

			VkPipelineVertexInputStateCreateInfo vertexInputState;
			vertexInputState.pVertexBindingDescriptions   = inputBinding;
			vertexInputState.pVertexAttributeDescriptions = inputAttrib;
			setInputLayout(vertexInputState, _numStreams, _layouts, program, _numInstanceData);

			const VkDynamicState dynamicStates[] =
			{
				VK_DYNAMIC_STATE_VIEWPORT,
				VK_DYNAMIC_STATE_SCISSOR,
				VK_DYNAMIC_STATE_BLEND_CONSTANTS,
				VK_DYNAMIC_STATE_STENCIL_REFERENCE,
			};

			VkPipelineDynamicStateCreateInfo dynamicState;
			dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
			dynamicState.pNext = NULL;
			dynamicState.flags = 0;
			dynamicState.dynamicStateCount = BX_COUNTOF(dynamicStates);
			dynamicState.pDynamicStates    = dynamicStates;

			VkPipelineShaderStageCreateInfo shaderStages[2];
			shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			shaderStages[0].pNext = NULL;
			shaderStages[0].flags = 0;
			shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
			shaderStages[0].module = program.m_vsh->m_module;
			shaderStages[0].pName  = "main";
			shaderStages[0].pSpecializationInfo = NULL;

			if (NULL != program.m_fsh)
			{
				shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				shaderStages[1].pNext = NULL;
				shaderStages[1].flags = 0;
				shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
				shaderStages[1].module = program.m_fsh->m_module;
				shaderStages[1].pName  = "main";
				shaderStages[1].pSpecializationInfo = NULL;
			}

			VkPipelineViewportStateCreateInfo viewportState;
			viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
			viewportState.pNext = NULL;
			viewportState.flags = 0;
			viewportState.viewportCount = 1;
			viewportState.pViewports    = NULL;
			viewportState.scissorCount  = 1;
			viewportState.pScissors     = NULL;

			VkSampleCountFlagBits rasterizerMsaa = (isValid(m_fbh) && !!(BGFX_STATE_MSAA & _state) ? m_textures[m_frameBuffers[m_fbh.idx].m_attachment[0].handle.idx].m_sampler.Sample : VK_SAMPLE_COUNT_1_BIT);

			VkPipelineMultisampleStateCreateInfo multisampleState;
			multisampleState.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
			multisampleState.pNext = NULL;
			multisampleState.flags = 0;
			multisampleState.rasterizationSamples  = rasterizerMsaa;
			multisampleState.sampleShadingEnable   = VK_FALSE;
			multisampleState.minSampleShading      = !!(BGFX_STATE_CONSERVATIVE_RASTER & _state) ? 1.0f : 0.0f;
			multisampleState.pSampleMask           = NULL;
			multisampleState.alphaToCoverageEnable = !!(BGFX_STATE_BLEND_ALPHA_TO_COVERAGE & _state);
			multisampleState.alphaToOneEnable      = VK_FALSE;

			VkGraphicsPipelineCreateInfo graphicsPipeline;
			graphicsPipeline.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
			graphicsPipeline.pNext = NULL;
			graphicsPipeline.flags = 0;
			graphicsPipeline.stageCount = NULL == program.m_fsh ? 1 : 2;
			graphicsPipeline.pStages    = shaderStages;
			graphicsPipeline.pVertexInputState   = &vertexInputState;
			graphicsPipeline.pInputAssemblyState = &inputAssemblyState;
			graphicsPipeline.pTessellationState  = NULL;
			graphicsPipeline.pViewportState      = &viewportState;
			graphicsPipeline.pRasterizationState = &rasterizationState;
			graphicsPipeline.pMultisampleState   = &multisampleState;
			graphicsPipeline.pDepthStencilState  = &depthStencilState;
			graphicsPipeline.pColorBlendState    = &colorBlendState;
			graphicsPipeline.pDynamicState       = &dynamicState;
//			graphicsPipeline.layout     = m_pipelineLayout;
			graphicsPipeline.layout     = program.m_pipelineLayout;
			graphicsPipeline.renderPass = isValid(m_fbh) ? m_frameBuffers[m_fbh.idx].m_renderPass : m_renderPass;
			graphicsPipeline.subpass    = 0;
			graphicsPipeline.basePipelineHandle = VK_NULL_HANDLE;
			graphicsPipeline.basePipelineIndex  = 0;

			uint32_t length = g_callback->cacheReadSize(hash);
			bool cached = length > 0;

			void* cachedData = NULL;

			VkPipelineCacheCreateInfo pcci;
			pcci.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
			pcci.pNext = NULL;
			pcci.flags = 0;
			pcci.initialDataSize = 0;
			pcci.pInitialData    = NULL;

			if (cached)
			{
				cachedData = BX_ALLOC(g_allocator, length);
				if (g_callback->cacheRead(hash, cachedData, length) )
				{
					BX_TRACE("Loading cached pipeline state (size %d).", length);
					bx::MemoryReader reader(cachedData, length);

					pcci.initialDataSize = (size_t)reader.remaining();
					pcci.pInitialData    = reader.getDataPtr();
				}
			}

			VkPipelineCache cache;
			VK_CHECK(vkCreatePipelineCache(m_device, &pcci, m_allocatorCb, &cache) );

			VK_CHECK(vkCreateGraphicsPipelines(m_device
				, cache
				, 1
				, &graphicsPipeline
				, m_allocatorCb
				, &pipeline
				) );
			m_pipelineStateCache.add(hash, pipeline);

			size_t dataSize;
			VK_CHECK(vkGetPipelineCacheData(m_device, cache, &dataSize, NULL) );

			if (0 < dataSize)
			{
				if (length < dataSize)
				{
					cachedData = BX_REALLOC(g_allocator, cachedData, dataSize);
				}
				VK_CHECK(vkGetPipelineCacheData(m_device, cache, &dataSize, cachedData) );
				g_callback->cacheWrite(hash, cachedData, (uint32_t)dataSize);
			}

			VK_CHECK(vkMergePipelineCaches(m_device, m_pipelineCache, 1, &cache) );
			vkDestroy(cache);

			if (NULL != cachedData)
			{
				BX_FREE(g_allocator, cachedData);
			}

			return pipeline;
		}

		void allocDescriptorSet(const ProgramVK& program, const RenderBind& renderBind, ScratchBufferVK& scratchBuffer)
		{
			VkDescriptorSetLayout dsl = m_descriptorSetLayoutCache.find(program.m_descriptorSetLayoutHash);
			VkDescriptorSetAllocateInfo dsai;
			dsai.sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			dsai.pNext              = NULL;
			dsai.descriptorPool     = m_descriptorPool;
			dsai.descriptorSetCount = 1;
			dsai.pSetLayouts        = &dsl;

			VkDescriptorSet& descriptorSet = scratchBuffer.m_descriptorSet[scratchBuffer.m_currentDs];
			vkAllocateDescriptorSets(m_device, &dsai, &descriptorSet);
			scratchBuffer.m_currentDs++;

			VkDescriptorImageInfo imageInfo[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
			VkDescriptorBufferInfo bufferInfo[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
			const int MAX_DESCRIPTOR_SETS = 2 * BGFX_CONFIG_MAX_TEXTURE_SAMPLERS + 2;
			VkWriteDescriptorSet wds[MAX_DESCRIPTOR_SETS];
			bx::memSet(wds, 0, sizeof(wds) );
			uint32_t wdsCount    = 0;
			uint32_t bufferCount = 0;
			uint32_t imageCount  = 0;

			for (uint32_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
			{
				const Binding& bind = renderBind.m_bind[stage];
				const BindInfo& bindInfo = program.m_bindInfo[stage];

				// bgfx does not seem to forbid setting a texture to a stage that a program does not use
				if (bind.m_type == Binding::Texture
				&& !isValid(program.m_bindInfo[stage].uniformHandle) )
					continue;

				if (kInvalidHandle != bind.m_idx)
				{
                    switch (bind.m_type)
                    {
                    case Binding::Image:
					{
						wds[wdsCount].sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
						wds[wdsCount].pNext            = NULL;
						wds[wdsCount].dstSet           = descriptorSet;
						wds[wdsCount].dstBinding       = bindInfo.binding;
						wds[wdsCount].dstArrayElement  = 0;
						wds[wdsCount].descriptorCount  = 1;
						wds[wdsCount].descriptorType   = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
						wds[wdsCount].pImageInfo       = NULL;
						wds[wdsCount].pBufferInfo      = NULL;
						wds[wdsCount].pTexelBufferView = NULL;

						TextureVK& texture = m_textures[bind.m_idx];
						VkSampler sampler = getSampler(
							(0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & bind.m_samplerFlags)
								? bind.m_samplerFlags
								: (uint32_t)texture.m_flags
							) & (BGFX_SAMPLER_BITS_MASK | BGFX_SAMPLER_BORDER_COLOR_MASK)
							, (uint32_t)texture.m_numMips);

						if (VK_IMAGE_LAYOUT_GENERAL != texture.m_currentImageLayout
						&&  VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL != texture.m_currentImageLayout)
						{
							texture.setImageMemoryBarrier(m_commandBuffer, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
						}

						imageInfo[imageCount].imageLayout = texture.m_currentImageLayout;
						imageInfo[imageCount].imageView   = VK_NULL_HANDLE != texture.m_textureImageStorageView
							? texture.m_textureImageStorageView
							: texture.m_textureImageView
							;
						imageInfo[imageCount].sampler     = sampler;
						wds[wdsCount].pImageInfo = &imageInfo[imageCount];
						++imageCount;

						++wdsCount;
					}
					break;
					case Binding::VertexBuffer:
					case Binding::IndexBuffer:
					{
						wds[wdsCount].sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
						wds[wdsCount].pNext            = NULL;
						wds[wdsCount].dstSet           = descriptorSet;
						wds[wdsCount].dstBinding       = bindInfo.binding;
						wds[wdsCount].dstArrayElement  = 0;
						wds[wdsCount].descriptorCount  = 1;
						wds[wdsCount].descriptorType   = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
						wds[wdsCount].pImageInfo       = NULL;
						wds[wdsCount].pBufferInfo      = NULL;
						wds[wdsCount].pTexelBufferView = NULL;

						BufferVK& sb = bind.m_type == Binding::VertexBuffer ? m_vertexBuffers[bind.m_idx] : m_indexBuffers[bind.m_idx];
						bufferInfo[bufferCount].buffer = sb.m_buffer;
						bufferInfo[bufferCount].offset = 0;
						bufferInfo[bufferCount].range  = sb.m_size;
						wds[wdsCount].pBufferInfo = &bufferInfo[bufferCount];
						++bufferCount;

						++wdsCount;
					}
					break;
					case Binding::Texture:
					{
						TextureVK& texture = m_textures[bind.m_idx];
						VkSampler sampler = getSampler(
							(0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & bind.m_samplerFlags)
								? bind.m_samplerFlags
								: (uint32_t)texture.m_flags
							) & (BGFX_SAMPLER_BITS_MASK | BGFX_SAMPLER_BORDER_COLOR_MASK)
							, (uint32_t)texture.m_numMips);

						if (VK_IMAGE_LAYOUT_GENERAL != texture.m_currentImageLayout
						&&  VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL != texture.m_currentImageLayout)
						{
							texture.setImageMemoryBarrier(m_commandBuffer, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
						}

						imageInfo[imageCount].imageLayout = texture.m_currentImageLayout;

						imageInfo[imageCount].imageView   = VK_NULL_HANDLE != texture.m_textureImageDepthView
							? texture.m_textureImageDepthView
							: texture.m_textureImageView
							;

						if (VK_NULL_HANDLE != texture.m_singleMsaaImageView)
						{
							imageInfo[imageCount].imageView = texture.m_singleMsaaImageView;
						}

						imageInfo[imageCount].sampler     = sampler;

						wds[wdsCount].sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
						wds[wdsCount].pNext            = NULL;
						wds[wdsCount].dstSet           = descriptorSet;
						wds[wdsCount].dstBinding       = bindInfo.binding;
						wds[wdsCount].dstArrayElement  = 0;
						wds[wdsCount].descriptorCount  = 1;
						wds[wdsCount].descriptorType   = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
						wds[wdsCount].pImageInfo       = &imageInfo[imageCount];
						wds[wdsCount].pBufferInfo      = NULL;
						wds[wdsCount].pTexelBufferView = NULL;
						++wdsCount;

						wds[wdsCount].sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
						wds[wdsCount].pNext            = NULL;
						wds[wdsCount].dstSet           = descriptorSet;
						wds[wdsCount].dstBinding       = bindInfo.samplerBinding;
						wds[wdsCount].dstArrayElement  = 0;
						wds[wdsCount].descriptorCount  = 1;
						wds[wdsCount].descriptorType   = VK_DESCRIPTOR_TYPE_SAMPLER;
						wds[wdsCount].pImageInfo       = &imageInfo[imageCount];
						wds[wdsCount].pBufferInfo      = NULL;
						wds[wdsCount].pTexelBufferView = NULL;
						++wdsCount;

						++imageCount;
					}
					break;
					}
				}
			}

			const uint32_t align = uint32_t(m_deviceProperties.limits.minUniformBufferOffsetAlignment);
			const uint32_t vsize = bx::strideAlign(program.m_vsh->m_size, align);
			const uint32_t fsize = bx::strideAlign( (NULL != program.m_fsh ? program.m_fsh->m_size : 0), align);
			const uint32_t total = vsize + fsize;

			if (0 < total)
			{
				uint32_t vsUniformBinding = program.m_vsh->m_uniformBinding;
				uint32_t fsUniformBinding = NULL != program.m_fsh ? program.m_fsh->m_uniformBinding : 0;

				if (vsize > 0)
				{
					bufferInfo[bufferCount].buffer = scratchBuffer.m_buffer;
					bufferInfo[bufferCount].offset = 0;
					bufferInfo[bufferCount].range  = vsize;

					wds[wdsCount].sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					wds[wdsCount].pNext            = NULL;
					wds[wdsCount].dstSet           = descriptorSet;
					wds[wdsCount].dstBinding       = vsUniformBinding;
					wds[wdsCount].dstArrayElement  = 0;
					wds[wdsCount].descriptorCount  = 1;
					wds[wdsCount].descriptorType   = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
					wds[wdsCount].pImageInfo       = NULL;
					wds[wdsCount].pBufferInfo      = &bufferInfo[bufferCount];
					wds[wdsCount].pTexelBufferView = NULL;
					++wdsCount;
					++bufferCount;
				}

				if (fsize > 0)
				{
					bufferInfo[bufferCount].buffer = scratchBuffer.m_buffer;
					bufferInfo[bufferCount].offset = 0;
					bufferInfo[bufferCount].range  = fsize;

					wds[wdsCount].sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					wds[wdsCount].pNext            = NULL;
					wds[wdsCount].dstSet           = descriptorSet;
					wds[wdsCount].dstBinding       = fsUniformBinding;
					wds[wdsCount].dstArrayElement  = 0;
					wds[wdsCount].descriptorCount  = 1;
					wds[wdsCount].descriptorType   = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
					wds[wdsCount].pImageInfo       = NULL;
					wds[wdsCount].pBufferInfo      = &bufferInfo[bufferCount];
					wds[wdsCount].pTexelBufferView = NULL;
					++wdsCount;
					++bufferCount;
				}
			}

			vkUpdateDescriptorSets(m_device, wdsCount, wds, 0, NULL);
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

#define CASE_IMPLEMENT_UNIFORM(_uniform, _dxsuffix, _type)                   \
				case UniformType::_uniform:                                  \
				case UniformType::_uniform|kUniformFragmentBit:         \
						{                                                    \
							setShaderUniform(uint8_t(type), loc, data, num); \
						}                                                    \
						break;

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
				case UniformType::Sampler|kUniformFragmentBit:
					// do nothing, but VkDescriptorSetImageInfo would be set before drawing
					break;
//				CASE_IMPLEMENT_UNIFORM(Sampler, I, int);
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

		void clearQuad(const Rect& _rect, const Clear& _clear, const float _palette[][4])
		{
			VkClearRect rect[1];
			rect[0].rect.offset.x      = _rect.m_x;
			rect[0].rect.offset.y      = _rect.m_y;
			rect[0].rect.extent.width  = _rect.m_width;
			rect[0].rect.extent.height = _rect.m_height;
			rect[0].baseArrayLayer = 0;
			rect[0].layerCount     = 1;

			uint32_t numMrt = 1;
			FrameBufferHandle fbh = m_fbh;
			if (isValid(fbh) )
			{
				const FrameBufferVK& fb = m_frameBuffers[fbh.idx];
				numMrt = fb.m_num;
			}

			VkClearAttachment attachments[BGFX_CONFIG_MAX_FRAME_BUFFERS];
			uint32_t mrt = 0;

			if (true //NULL != m_currentColor
			&&  BGFX_CLEAR_COLOR & _clear.m_flags)
			{
				if (BGFX_CLEAR_COLOR_USE_PALETTE & _clear.m_flags)
				{
					for (uint32_t ii = 0; ii < numMrt; ++ii)
					{
						attachments[mrt].colorAttachment = mrt;
						attachments[mrt].aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
						uint8_t index = bx::min<uint8_t>(BGFX_CONFIG_MAX_COLOR_PALETTE-1, _clear.m_index[ii]);
						bx::memCopy(&attachments[mrt].clearValue.color.float32, _palette[index], 16);
						++mrt;
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

					for (uint32_t ii = 0; ii < numMrt; ++ii)
					{
						attachments[mrt].colorAttachment = mrt;
						attachments[mrt].aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
						bx::memCopy(&attachments[mrt].clearValue.color.float32, frgba, 16);
						++mrt;
					}
				}
			}

			if (true //NULL != m_currentDepthStencil
			&& (BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL) & _clear.m_flags)
			{
				attachments[mrt].colorAttachment = mrt;
				attachments[mrt].aspectMask = 0;
				attachments[mrt].aspectMask |= (_clear.m_flags & BGFX_CLEAR_DEPTH  ) ? VK_IMAGE_ASPECT_DEPTH_BIT   : 0;
				attachments[mrt].aspectMask |= (_clear.m_flags & BGFX_CLEAR_STENCIL) ? VK_IMAGE_ASPECT_STENCIL_BIT : 0;

				attachments[mrt].clearValue.depthStencil.stencil = _clear.m_stencil;
				attachments[mrt].clearValue.depthStencil.depth   = _clear.m_depth;
				++mrt;
			}

			if (mrt > 0)
			{
				vkCmdClearAttachments(m_commandBuffer
					, mrt
					, attachments
					, BX_COUNTOF(rect)
					, rect
					);
			}
		}

		uint64_t kick(VkSemaphore _wait = VK_NULL_HANDLE, VkSemaphore _signal = VK_NULL_HANDLE)
		{
			VkPipelineStageFlags stageFlags = 0
				| VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT
				;

			VkSubmitInfo si;
			si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			si.pNext = NULL;
			si.waitSemaphoreCount = VK_NULL_HANDLE != _wait;
			si.pWaitSemaphores    = &_wait;
			si.pWaitDstStageMask  = &stageFlags;
			si.commandBufferCount = 1;
			si.pCommandBuffers    = &m_commandBuffers[m_backBufferColorIdx];
			si.signalSemaphoreCount = VK_NULL_HANDLE != _signal;
			si.pSignalSemaphores    = &_signal;

//			VK_CHECK(vkResetFences(m_device, 1, &m_fence) );
			VK_CHECK(vkQueueSubmit(m_queueGraphics, 1, &si, VK_NULL_HANDLE) );
			return 0;
		}

		void finish()
		{
			finishAll();
		}

		void finishAll()
		{
			VK_CHECK(vkQueueWaitIdle(m_queueGraphics) );
//			VK_CHECK(vkWaitForFences(m_device, 1, &m_fence, true, INT64_MAX) );
		}

		int32_t selectMemoryType(uint32_t _memoryTypeBits, uint32_t _propertyFlags, int32_t _startIndex = 0) const
		{
			for (int32_t ii = _startIndex, num = m_memoryProperties.memoryTypeCount; ii < num; ++ii)
			{
				const VkMemoryType& memType = m_memoryProperties.memoryTypes[ii];
				if ( (0 != ( (1<<ii) & _memoryTypeBits) )
				&& ( (memType.propertyFlags & _propertyFlags) == _propertyFlags) )
				{
					return ii;
				}
			}

			BX_TRACE("Failed to find memory that supports flags 0x%08x.", _propertyFlags);
			return -1;
		}

		VkResult allocateMemory(const VkMemoryRequirements* requirements, VkMemoryPropertyFlags propertyFlags, VkDeviceMemory* memory) const
		{
			VkMemoryAllocateInfo ma;
			ma.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			ma.pNext = NULL;
			ma.allocationSize = requirements->size;

			VkResult result = VK_ERROR_UNKNOWN;
			int32_t searchIndex = -1;
			do
			{
				searchIndex++;
				searchIndex = selectMemoryType(requirements->memoryTypeBits, propertyFlags, searchIndex);
				if (searchIndex >= 0)
				{
					ma.memoryTypeIndex = searchIndex;
					result = vkAllocateMemory(m_device
						, &ma
						, m_allocatorCb
						, memory
					);
				}
			}
			while (result != VK_SUCCESS && searchIndex >= 0);

			return result;
		}

		VkCommandBuffer beginNewCommand(VkCommandBufferUsageFlagBits commandBufferUsageFlag = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT)
		{
			VkCommandBufferAllocateInfo cbai;
			cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			cbai.pNext = NULL;
			cbai.commandPool = m_commandPool;
			cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			cbai.commandBufferCount = 1;

			VkCommandBuffer commandBuffer;
			VK_CHECK(vkAllocateCommandBuffers(m_device, &cbai, &commandBuffer) );

			VkCommandBufferBeginInfo cbbi;
			cbbi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			cbbi.pNext = NULL;
			cbbi.flags = commandBufferUsageFlag;
			cbbi.pInheritanceInfo = NULL;
			VK_CHECK(vkBeginCommandBuffer(commandBuffer, &cbbi) );

			return commandBuffer;
		}

		void submitCommandAndWait(VkCommandBuffer commandBuffer)
		{
			vkEndCommandBuffer(commandBuffer);

			VkSubmitInfo submitInfo;
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.pNext = NULL;
			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &commandBuffer;
			submitInfo.waitSemaphoreCount = 0;
			submitInfo.pWaitSemaphores = NULL;
			submitInfo.signalSemaphoreCount = 0;
			submitInfo.pSignalSemaphores = NULL;
			submitInfo.pWaitDstStageMask = NULL;

			VK_CHECK(vkQueueSubmit(m_queueGraphics, 1, &submitInfo, VK_NULL_HANDLE) );
			VK_CHECK(vkQueueWaitIdle(m_queueGraphics) );

			vkFreeCommandBuffers(m_device, m_commandPool, 1, &commandBuffer);
		}

#define NUM_SWAPCHAIN_IMAGE 4
		VkAllocationCallbacks*   m_allocatorCb;
		VkDebugReportCallbackEXT m_debugReportCallback;
		VkInstance       m_instance;
		VkPhysicalDevice m_physicalDevice;
		uint32_t         m_instanceApiVersion;

		VkPhysicalDeviceProperties       m_deviceProperties;
		VkPhysicalDeviceMemoryProperties m_memoryProperties;
		VkPhysicalDeviceFeatures         m_deviceFeatures;

		VkSwapchainCreateInfoKHR m_sci;
		VkSurfaceKHR       m_surface;
		VkSwapchainKHR     m_swapchain;
		uint32_t           m_numSwapchainImages;
		VkSurfaceFormatKHR m_backBufferColorFormat;
		VkSurfaceFormatKHR m_backBufferColorFormatSrgb;
		VkImageLayout      m_backBufferColorImageLayout[NUM_SWAPCHAIN_IMAGE];
		VkImage            m_backBufferColorImage[NUM_SWAPCHAIN_IMAGE];
		VkImageView        m_backBufferColorImageView[NUM_SWAPCHAIN_IMAGE];
		VkFramebuffer      m_backBufferColor[NUM_SWAPCHAIN_IMAGE];
		VkCommandBuffer    m_commandBuffers[NUM_SWAPCHAIN_IMAGE];
		VkCommandBuffer    m_commandBuffer;
		bool               m_needToRefreshSwapchain;

		VkFormat           m_backBufferDepthStencilFormat;
		VkDeviceMemory     m_backBufferDepthStencilMemory;
		VkImage            m_backBufferDepthStencilImage;
		VkImageView        m_backBufferDepthStencilImageView;

		ScratchBufferVK    m_scratchBuffer[NUM_SWAPCHAIN_IMAGE];
		VkSemaphore        m_presentDone[NUM_SWAPCHAIN_IMAGE];

		uint32_t m_qfiGraphics;
		uint32_t m_qfiCompute;

		VkDevice m_device;
		VkQueue  m_queueGraphics;
		VkQueue  m_queueCompute;
		VkFence  m_fence;
		VkRenderPass m_renderPass;
		VkDescriptorPool m_descriptorPool;
		VkPipelineCache m_pipelineCache;
		VkCommandPool m_commandPool;

		TimerQueryVK m_gpuTimer;

		void* m_renderDocDll;
		void* m_vulkan1Dll;

		IndexBufferVK m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBufferVK m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		ShaderVK m_shaders[BGFX_CONFIG_MAX_SHADERS];
		ProgramVK m_program[BGFX_CONFIG_MAX_PROGRAMS];
		TextureVK m_textures[BGFX_CONFIG_MAX_TEXTURES];
		VertexLayout m_vertexLayouts[BGFX_CONFIG_MAX_VERTEX_LAYOUTS];
		FrameBufferVK m_frameBuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		void* m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];
		Matrix4 m_predefinedUniforms[PredefinedUniform::Count];
		UniformRegistry m_uniformReg;

		StateCacheT<VkPipeline> m_pipelineStateCache;
		StateCacheT<VkDescriptorSetLayout> m_descriptorSetLayoutCache;
		StateCacheT<VkRenderPass> m_renderPassCache;
		StateCacheT<VkSampler> m_samplerCache;

		Resolution m_resolution;
		uint32_t m_maxAnisotropy;
		bool m_depthClamp;
		bool m_wireframe;
		bool m_rtMsaa;

		TextVideoMem m_textVideoMem;

		uint8_t m_fsScratch[64<<10];
		uint8_t m_vsScratch[64<<10];

		uint32_t m_backBufferColorIdx;
		FrameBufferHandle m_fbh;
	};

	static RendererContextVK* s_renderVK;

	RendererContextI* rendererCreate(const Init& _init)
	{
		s_renderVK = BX_NEW(g_allocator, RendererContextVK);
		if (!s_renderVK->init(_init) )
		{
			BX_DELETE(g_allocator, s_renderVK);
			s_renderVK = NULL;
		}
		return s_renderVK;
	}

	void rendererDestroy()
	{
		s_renderVK->shutdown();
		BX_DELETE(g_allocator, s_renderVK);
		s_renderVK = NULL;
	}

#define VK_DESTROY_FUNC(_name)                                                               \
			void vkDestroy(Vk##_name& _obj)                                                  \
			{                                                                                \
				if (VK_NULL_HANDLE != _obj)                                                  \
				{                                                                            \
					vkDestroy##_name(s_renderVK->m_device, _obj, s_renderVK->m_allocatorCb); \
					_obj = VK_NULL_HANDLE;                                                   \
				}                                                                            \
			}
VK_DESTROY
#undef VK_DESTROY_FUNC

	void ScratchBufferVK::create(uint32_t _size, uint32_t _maxDescriptors)
	{
		m_maxDescriptors = _maxDescriptors;
		m_currentDs = 0;
		m_descriptorSet  = (VkDescriptorSet*)BX_ALLOC(g_allocator, m_maxDescriptors * sizeof(VkDescriptorSet) );
		bx::memSet(m_descriptorSet, 0, sizeof(VkDescriptorSet) * m_maxDescriptors);

		VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;
		VkDevice device = s_renderVK->m_device;

		VkBufferCreateInfo bci;
		bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bci.pNext = NULL;
		bci.flags = 0;
		bci.size  = _size;
		bci.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
		bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		bci.queueFamilyIndexCount = 0;
		bci.pQueueFamilyIndices   = NULL;

		VK_CHECK(vkCreateBuffer(
			  device
			, &bci
			, allocatorCb
			, &m_buffer
			) );

		VkMemoryRequirements mr;
		vkGetBufferMemoryRequirements(
			  device
			, m_buffer
			, &mr
			);

		VK_CHECK(s_renderVK->allocateMemory(&mr, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, &m_deviceMem) );

		m_size = (uint32_t)mr.size;
		m_pos  = 0;

		VK_CHECK(vkBindBufferMemory(device, m_buffer, m_deviceMem, 0) );

		VK_CHECK(vkMapMemory(device, m_deviceMem, 0, m_size, 0, (void**)&m_data) );
	}

	void ScratchBufferVK::destroy()
	{
		VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;
		VkDevice device = s_renderVK->m_device;

		reset();
		BX_FREE(g_allocator, m_descriptorSet);

		vkUnmapMemory(device, m_deviceMem);
		vkDestroy(m_buffer);
		vkFreeMemory(device
			, m_deviceMem
			, allocatorCb
			);
	}

	void ScratchBufferVK::reset()
	{
		if (m_currentDs > 0)
		{
			vkFreeDescriptorSets(
				  s_renderVK->m_device
				, s_renderVK->m_descriptorPool
				, m_currentDs
				, m_descriptorSet
				);
		}

		bx::memSet(m_descriptorSet, 0, sizeof(VkDescriptorSet) * m_maxDescriptors);
		m_pos = 0;
		m_currentDs = 0;
	}

	VkResult ImageVK::create(VkFormat _format, const VkExtent3D& _extent)
	{
		VkResult result;

		VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;
		VkDevice device = s_renderVK->m_device;

		VkImageCreateInfo ici;
		ici.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		ici.pNext = NULL;
		ici.flags = 0;
		ici.imageType = VK_IMAGE_TYPE_2D;
		ici.format = _format;
		ici.extent = _extent;
		ici.mipLevels   = 1;
		ici.arrayLayers = 1;
		ici.samples = VK_SAMPLE_COUNT_1_BIT;
		ici.tiling  = VK_IMAGE_TILING_OPTIMAL;
		ici.usage   = 0
			| VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
			| VK_IMAGE_USAGE_TRANSFER_SRC_BIT
			;
		ici.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		ici.queueFamilyIndexCount = 0;
		ici.pQueueFamilyIndices   = 0;
		ici.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		result = vkCreateImage(device, &ici, allocatorCb, &m_image);

		if (VK_SUCCESS != result)
		{
			BX_TRACE("vkCreateImage failed %d: %s.", result, getName(result) );
			return result;
		}

		VkMemoryRequirements mr;
		vkGetImageMemoryRequirements(device, m_image, &mr);

		result = s_renderVK->allocateMemory(&mr, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &m_memory);

		if (VK_SUCCESS != result)
		{
			BX_TRACE("vkAllocateMemory failed %d: %s.", result, getName(result) );
			destroy();
			return result;
		}

		result = vkBindImageMemory(device, m_image, m_memory, 0);

		if (VK_SUCCESS != result)
		{
			BX_TRACE("vkBindImageMemory failed %d: %s.", result, getName(result) );
			destroy();
			return result;
		}

		VkImageViewCreateInfo ivci;
		ivci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		ivci.pNext = NULL;
		ivci.flags = 0;
		ivci.image    = m_image;
		ivci.viewType = VK_IMAGE_VIEW_TYPE_2D;
		ivci.format   = _format;
		ivci.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		ivci.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		ivci.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		ivci.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		ivci.subresourceRange.aspectMask = 0
			| VK_IMAGE_ASPECT_DEPTH_BIT
			| VK_IMAGE_ASPECT_STENCIL_BIT
			;
		ivci.subresourceRange.baseMipLevel   = 0;
		ivci.subresourceRange.levelCount     = 1;
		ivci.subresourceRange.baseArrayLayer = 0;
		ivci.subresourceRange.layerCount     = 1;
		result = vkCreateImageView(device, &ivci, allocatorCb, &m_imageView);

		if (VK_SUCCESS != result)
		{
			BX_TRACE("vkCreateImageView failed %d: %s.", result, getName(result) );
			destroy();
			return result;
		}

		return VK_SUCCESS;
	}

	void ImageVK::destroy()
	{
		vkDestroy(m_imageView);
		vkDestroy(m_image);
		if (VK_NULL_HANDLE != m_memory)
		{
			vkFreeMemory(s_renderVK->m_device, m_memory, s_renderVK->m_allocatorCb);
			m_memory = VK_NULL_HANDLE;
		}
	}

	void BufferVK::create(uint32_t _size, void* _data, uint16_t _flags, bool _vertex, uint32_t _stride)
	{
		BX_UNUSED(_stride);

		m_size    = _size;
		m_flags   = _flags;
		m_dynamic = NULL == _data;

		bool storage  = m_flags & BGFX_BUFFER_COMPUTE_READ_WRITE;
		bool indirect = m_flags & BGFX_BUFFER_DRAW_INDIRECT;
		VkBufferCreateInfo bci;
		bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bci.pNext = NULL;
		bci.flags = 0;
		bci.size  = _size;
		bci.usage = 0
//			| (m_dynamic            ? VK_BUFFER_USAGE_TRANSFER_DST_BIT    : 0)
			| (_vertex              ? VK_BUFFER_USAGE_VERTEX_BUFFER_BIT   : VK_BUFFER_USAGE_INDEX_BUFFER_BIT)
			| (storage || indirect  ? VK_BUFFER_USAGE_STORAGE_BUFFER_BIT  : 0)
			| (indirect             ? VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT : 0)
			| VK_BUFFER_USAGE_TRANSFER_DST_BIT
			;
		bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		bci.queueFamilyIndexCount = 0;
		bci.pQueueFamilyIndices   = NULL;

		VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;
		VkDevice device = s_renderVK->m_device;
		VK_CHECK(vkCreateBuffer(device
			, &bci
			, allocatorCb
			, &m_buffer
			) );

		VkMemoryRequirements mr;
		vkGetBufferMemoryRequirements(device, m_buffer, &mr);

		VK_CHECK(s_renderVK->allocateMemory(&mr, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &m_deviceMem) );

		VK_CHECK(vkBindBufferMemory(device, m_buffer, m_deviceMem, 0) );

		if (!m_dynamic)
		{
//			void* dst;
//			VK_CHECK(vkMapMemory(device, m_deviceMem, 0, ma.allocationSize, 0, &dst) );
//			bx::memCopy(dst, _data, _size);
//			vkUnmapMemory(device, m_deviceMem);

			// staging buffer
			VkBuffer stagingBuffer;
			VkDeviceMemory stagingMem;
			bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bci.pNext = NULL;
			bci.flags = 0;
			bci.size = _size;
			bci.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
			bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			bci.queueFamilyIndexCount = 0;
			bci.pQueueFamilyIndices = NULL;

			VK_CHECK(vkCreateBuffer(device
				, &bci
				, allocatorCb
				, &stagingBuffer
			) );

			vkGetBufferMemoryRequirements(device, stagingBuffer, &mr);

			VK_CHECK(s_renderVK->allocateMemory(&mr, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &stagingMem) );

			VK_CHECK(vkBindBufferMemory(device, stagingBuffer, stagingMem, 0) );

			void* dst;
			VK_CHECK(vkMapMemory(device, stagingMem, 0, mr.size, 0, &dst) );
			bx::memCopy(dst, _data, _size);
			vkUnmapMemory(device, stagingMem);

			VkCommandBuffer commandBuffer = s_renderVK->beginNewCommand();
			// copy buffer to buffer
			{
				VkBufferCopy region;
				region.srcOffset = 0;
				region.dstOffset = 0;
				region.size      = _size;

				vkCmdCopyBuffer(commandBuffer, stagingBuffer, m_buffer, 1, &region);
			}
			s_renderVK->submitCommandAndWait(commandBuffer);

			vkFreeMemory(device, stagingMem, allocatorCb);
			vkDestroy(stagingBuffer);
		}
	}

	void BufferVK::update(VkCommandBuffer _commandBuffer, uint32_t _offset, uint32_t _size, void* _data, bool _discard)
	{
		BX_UNUSED(_commandBuffer, _discard);
//		void* dst;
//		VkDevice device = s_renderVK->m_device;
//		VK_CHECK(vkMapMemory(device, m_deviceMem, _offset, _size, 0, &dst) );
//		bx::memCopy(dst, _data, _size);
//		vkUnmapMemory(device, m_deviceMem);

		// staging buffer
		VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;
		VkDevice device = s_renderVK->m_device;
		VkBuffer stagingBuffer;
		VkDeviceMemory stagingMem;
		VkBufferCreateInfo bci;
		bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bci.pNext = NULL;
		bci.flags = 0;
		bci.size = _size;
		bci.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
		bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		bci.queueFamilyIndexCount = 0;
		bci.pQueueFamilyIndices = NULL;

		VK_CHECK(vkCreateBuffer(device
			, &bci
			, allocatorCb
			, &stagingBuffer
		) );

		VkMemoryRequirements mr;
		vkGetBufferMemoryRequirements(device
			, stagingBuffer
			, &mr
		);

		VK_CHECK(s_renderVK->allocateMemory(&mr, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &stagingMem) );

		VK_CHECK(vkBindBufferMemory(device, stagingBuffer, stagingMem, 0) );

		void* dst;
		VK_CHECK(vkMapMemory(device, stagingMem, 0, mr.size, 0, &dst) );
		bx::memCopy(dst, _data, _size);
		vkUnmapMemory(device, stagingMem);

		VkCommandBuffer commandBuffer = s_renderVK->beginNewCommand();

		// copy buffer to buffer
		{
			VkBufferCopy region;
			region.srcOffset = 0;
			region.dstOffset = _offset;
			region.size      = _size;

			vkCmdCopyBuffer(commandBuffer, stagingBuffer, m_buffer, 1, &region);
		}

		s_renderVK->submitCommandAndWait(commandBuffer);

		vkFreeMemory(device, stagingMem, allocatorCb);
		vkDestroy(stagingBuffer);
	}

	void BufferVK::destroy()
	{
		if (VK_NULL_HANDLE != m_buffer)
		{
			VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;
			VkDevice device = s_renderVK->m_device;

			vkDestroy(m_buffer);
			vkFreeMemory(device
				, m_deviceMem
				, allocatorCb
				);
			m_dynamic = false;
		}
	}

	void VertexBufferVK::create(uint32_t _size, void* _data, VertexLayoutHandle _layoutHandle, uint16_t _flags)
	{
		BufferVK::create(_size, _data, _flags, true);
		m_layoutHandle = _layoutHandle;
	}

	void ShaderVK::create(const Memory* _mem)
	{
		bx::MemoryReader reader(_mem->data, _mem->size);

		uint32_t magic;
		bx::read(&reader, magic);

		VkShaderStageFlagBits shaderStage;
		BX_UNUSED(shaderStage);

		if (isShaderType(magic, 'C') )
		{
			shaderStage = VK_SHADER_STAGE_COMPUTE_BIT;
		}
		else if (isShaderType(magic, 'F') )
		{
			shaderStage = VK_SHADER_STAGE_FRAGMENT_BIT;
		}
		else if (isShaderType(magic, 'V') )
		{
			shaderStage = VK_SHADER_STAGE_VERTEX_BIT;
		}

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

		uint8_t fragmentBit = fragment ? kUniformFragmentBit : 0;

		for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++ii)
		{
			m_bindInfo[ii].uniformHandle  = BGFX_INVALID_HANDLE;
			m_bindInfo[ii].type           = BindType::Count;
			m_bindInfo[ii].binding        = 0;
			m_bindInfo[ii].samplerBinding = 0;
		}

		if (0 < count)
		{
			for (uint32_t ii = 0; ii < count; ++ii)
			{
				uint8_t nameSize = 0;
				bx::read(&reader, nameSize);

				char name[256];
				bx::read(&reader, &name, nameSize);
				name[nameSize] = '\0';

				uint8_t type = 0;
				bx::read(&reader, type);

				uint8_t num;
				bx::read(&reader, num);

				uint16_t regIndex;
				bx::read(&reader, regIndex);

				uint16_t regCount;
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
				else if (UniformType::End == (~kUniformMask & type) )
				{
					// regCount is used for descriptor type
					const bool  isBuffer = regCount == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
					const uint16_t stage = regIndex - (isBuffer ? 16 : 32) - (fragment ? 48 : 0);  // regIndex is used for buffer binding index

					m_bindInfo[stage].type = isBuffer ? BindType::Buffer : BindType::Image;
					m_bindInfo[stage].uniformHandle  = { 0 };
					m_bindInfo[stage].binding        = regIndex;

					kind = "storage";
				}
				else if (UniformType::Sampler == (~kUniformMask & type) )
				{
					const uint16_t stage = regIndex - 16 - (fragment ? 48 : 0); // regIndex is used for image/sampler binding index

					const UniformRegInfo* info = s_renderVK->m_uniformReg.find(name);
					BX_ASSERT(NULL != info, "User defined uniform '%s' is not found, it won't be set.", name);

					m_bindInfo[stage].uniformHandle    = info->m_handle;
					m_bindInfo[stage].type             = BindType::Sampler;
					m_bindInfo[stage].binding          = regIndex;
					m_bindInfo[stage].samplerBinding   = regIndex + 16;

					kind = "sampler";
				}
				else
				{
					const UniformRegInfo* info = s_renderVK->m_uniformReg.find(name);
					BX_ASSERT(NULL != info, "User defined uniform '%s' is not found, it won't be set.", name);

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

		m_code = alloc(shaderSize);
		bx::memCopy(m_code->data, code, shaderSize);

		VkShaderModuleCreateInfo smci;
		smci.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		smci.pNext = NULL;
		smci.flags = 0;
		smci.codeSize = m_code->size;
		smci.pCode    = (const uint32_t*)m_code->data;

//		disassemble(bx::getDebugOut(), m_code->data, m_code->size);

		VK_CHECK(vkCreateShaderModule(
			  s_renderVK->m_device
			, &smci
			, s_renderVK->m_allocatorCb
			, &m_module
			) );

		bx::memSet(m_attrMask,  0, sizeof(m_attrMask) );
		bx::memSet(m_attrRemap, 0, sizeof(m_attrRemap) );

		bx::read(&reader, m_numAttrs);

		for (uint8_t ii = 0; ii < m_numAttrs; ++ii)
		{
			uint16_t id;
			bx::read(&reader, id);

			Attrib::Enum attr = idToAttrib(id);

			if (Attrib::Count != attr)
			{
				m_attrMask[attr]  = UINT16_MAX;
				m_attrRemap[attr] = ii;
			}
		}

		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(hashIn);
		murmur.add(hashOut);
		murmur.add(m_code->data, m_code->size);
		murmur.add(m_numAttrs);
		murmur.add(m_attrMask,  m_numAttrs);
		murmur.add(m_attrRemap, m_numAttrs);
		m_hash = murmur.end();

		bx::read(&reader, m_size);

		// fill binding description with uniform informations
		uint16_t bidx = 0;
		if (m_size > 0)
		{
			m_uniformBinding = fragment ? 48 : 0;

			VkDescriptorSetLayoutBinding& binding = m_bindings[bidx];
			binding.stageFlags = VK_SHADER_STAGE_ALL;
			binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
			binding.binding = m_uniformBinding;
			binding.pImmutableSamplers = NULL;
			binding.descriptorCount = 1;
			bidx++;
		}

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_bindInfo); ++ii)
		{
			switch (m_bindInfo[ii].type)
			{
				case BindType::Buffer:
				case BindType::Image:
				{
					VkDescriptorSetLayoutBinding& binding = m_bindings[bidx];
					binding.stageFlags = VK_SHADER_STAGE_ALL;
					binding.descriptorType = BindType::Buffer == m_bindInfo[ii].type
						? VK_DESCRIPTOR_TYPE_STORAGE_BUFFER
						: VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
					binding.binding = m_bindInfo[ii].binding;
					binding.pImmutableSamplers = NULL;
					binding.descriptorCount = 1;
					bidx++;
				}
				break;

				case BindType::Sampler:
				{
					VkDescriptorSetLayoutBinding& textureBinding = m_bindings[bidx];
					textureBinding.stageFlags = VK_SHADER_STAGE_ALL;
					textureBinding.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
					textureBinding.binding = m_bindInfo[ii].binding;
					textureBinding.pImmutableSamplers = NULL;
					textureBinding.descriptorCount = 1;
					bidx++;

					VkDescriptorSetLayoutBinding& samplerBinding = m_bindings[bidx];
					samplerBinding.stageFlags = VK_SHADER_STAGE_ALL;
					samplerBinding.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
					samplerBinding.binding = m_bindInfo[ii].samplerBinding;
					samplerBinding.pImmutableSamplers = NULL;
					samplerBinding.descriptorCount = 1;
					bidx++;
				}
				break;

				default:
					break;
			}
		}

		m_numBindings = bidx;
	}

	void ShaderVK::destroy()
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

		if (VK_NULL_HANDLE != m_module)
		{
			vkDestroy(m_module);
		}
	}

	void ProgramVK::create(const ShaderVK* _vsh, const ShaderVK* _fsh)
	{
		BX_ASSERT(NULL != _vsh->m_code, "Vertex shader doesn't exist.");
		m_vsh = _vsh;
		bx::memCopy(
			  &m_predefined[0]
			, _vsh->m_predefined
			, _vsh->m_numPredefined * sizeof(PredefinedUniform)
			);
		m_numPredefined = _vsh->m_numPredefined;

		if (NULL != _fsh)
		{
			BX_ASSERT(NULL != _fsh->m_code, "Fragment shader doesn't exist.");
			m_fsh = _fsh;
			bx::memCopy(
				  &m_predefined[m_numPredefined]
				, _fsh->m_predefined
				, _fsh->m_numPredefined * sizeof(PredefinedUniform)
				);
			m_numPredefined += _fsh->m_numPredefined;
		}

		for (uint8_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
		{
			if (isValid(m_vsh->m_bindInfo[stage].uniformHandle) )
			{
				m_bindInfo[stage] = m_vsh->m_bindInfo[stage];
			}
			else if (NULL != m_fsh && isValid(m_fsh->m_bindInfo[stage].uniformHandle) )
			{
				m_bindInfo[stage] = m_fsh->m_bindInfo[stage];
			}
		}

		// create exact pipeline layout
		VkDescriptorSetLayout dsl = VK_NULL_HANDLE;

		uint32_t numBindings = m_vsh->m_numBindings + (m_fsh ? m_fsh->m_numBindings : 0);
		if (0 < numBindings)
		{
			// generate descriptor set layout hash
			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(m_vsh->m_bindings, sizeof(VkDescriptorSetLayoutBinding) * m_vsh->m_numBindings);
			if (NULL != m_fsh)
			{
				murmur.add(m_fsh->m_bindings, sizeof(VkDescriptorSetLayoutBinding) * m_fsh->m_numBindings);
			}
			m_descriptorSetLayoutHash = murmur.end();

			dsl = s_renderVK->m_descriptorSetLayoutCache.find(m_descriptorSetLayoutHash);

			if (NULL == dsl)
			{
				VkDescriptorSetLayoutBinding bindings[64];
				bx::memCopy(
					  bindings
					, m_vsh->m_bindings
					, sizeof(VkDescriptorSetLayoutBinding) * m_vsh->m_numBindings
					);
				if (NULL != m_fsh)
				{
					bx::memCopy(
						  bindings + m_vsh->m_numBindings
						, m_fsh->m_bindings
						, sizeof(VkDescriptorSetLayoutBinding) * m_fsh->m_numBindings
						);
				}

				VkDescriptorSetLayoutCreateInfo dslci;
				dslci.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				dslci.pNext = NULL;
				dslci.flags = 0;
				dslci.bindingCount = numBindings;
				dslci.pBindings = bindings;

				VK_CHECK(vkCreateDescriptorSetLayout(
					  s_renderVK->m_device
					, &dslci
					, s_renderVK->m_allocatorCb
					, &dsl
					) );

				s_renderVK->m_descriptorSetLayoutCache.add(m_descriptorSetLayoutHash, dsl);
			}
		}

		VkPipelineLayoutCreateInfo plci;
		plci.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		plci.pNext = NULL;
		plci.flags = 0;
		plci.pushConstantRangeCount = 0;
		plci.pPushConstantRanges = NULL;
		plci.setLayoutCount = (dsl == VK_NULL_HANDLE ? 0 : 1);
		plci.pSetLayouts = &dsl;

		VK_CHECK(vkCreatePipelineLayout(
			  s_renderVK->m_device
			, &plci
			, s_renderVK->m_allocatorCb
			, &m_pipelineLayout
			) );
	}

	void ProgramVK::destroy()
	{
		vkDestroy(m_pipelineLayout);
		m_numPredefined = 0;
		m_vsh = NULL;
		m_fsh = NULL;
	}

	void* TextureVK::create(const Memory* _mem, uint64_t _flags, uint8_t _skip)
	{
		bimg::ImageContainer imageContainer;

		if (bimg::imageParse(imageContainer, _mem->data, _mem->size) )
		{
			VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;
			VkDevice device = s_renderVK->m_device;

			const bimg::ImageBlockInfo& blockInfo = bimg::getBlockInfo(imageContainer.m_format);
			const uint8_t startLod = bx::min<uint8_t>(_skip, imageContainer.m_numMips - 1);

			bimg::TextureInfo ti;
			bimg::imageGetSize(
				  &ti
				, uint16_t(imageContainer.m_width >> startLod)
				, uint16_t(imageContainer.m_height >> startLod)
				, uint16_t(imageContainer.m_depth >> startLod)
				, imageContainer.m_cubeMap
				, 1 < imageContainer.m_numMips
				, imageContainer.m_numLayers
				, imageContainer.m_format
				);

			ti.numMips = bx::min<uint8_t>(imageContainer.m_numMips - startLod, ti.numMips);

			m_flags     = _flags;
			m_width     = ti.width;
			m_height    = ti.height;
			m_depth     = ti.depth;
			m_numLayers = ti.numLayers;
			m_requestedFormat = uint8_t(imageContainer.m_format);
			m_textureFormat   = uint8_t(getViableTextureFormat(imageContainer) );
			m_format = bimg::isDepth(bimg::TextureFormat::Enum(m_textureFormat) )
				? s_textureFormat[m_textureFormat].m_fmtDsv
				: (m_flags & BGFX_TEXTURE_SRGB) ? s_textureFormat[m_textureFormat].m_fmtSrgb : s_textureFormat[m_textureFormat].m_fmt
				;
			m_components = s_textureFormat[m_textureFormat].m_mapping;

			const bool convert = m_textureFormat != m_requestedFormat;
			const uint8_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat) );
			m_aspectMask = bimg::isDepth(bimg::TextureFormat::Enum(m_textureFormat) )
				? VK_IMAGE_ASPECT_DEPTH_BIT
				: VK_IMAGE_ASPECT_COLOR_BIT
				;

			m_sampler = s_msaa[bx::uint32_satsub( (m_flags & BGFX_TEXTURE_RT_MSAA_MASK) >> BGFX_TEXTURE_RT_MSAA_SHIFT, 1)];

			if (m_format == VK_FORMAT_S8_UINT
			||  m_format == VK_FORMAT_D16_UNORM_S8_UINT
			||  m_format == VK_FORMAT_D24_UNORM_S8_UINT
			||  m_format == VK_FORMAT_D32_SFLOAT_S8_UINT)
			{
				m_aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
			}

			if (imageContainer.m_cubeMap)
			{
				m_type = VK_IMAGE_VIEW_TYPE_CUBE;
			}
			else if (imageContainer.m_depth > 1)
			{
				m_type = VK_IMAGE_VIEW_TYPE_3D;
			}
			else
			{
				m_type = VK_IMAGE_VIEW_TYPE_2D;
			}

			m_numMips = ti.numMips;
			m_numSides = ti.numLayers * (imageContainer.m_cubeMap ? 6 : 1);
			const uint16_t numSides = ti.numLayers * (imageContainer.m_cubeMap ? 6 : 1);
			const uint32_t numSrd = numSides * ti.numMips;

			uint32_t kk = 0;

			const bool compressed = bimg::isCompressed(bimg::TextureFormat::Enum(m_textureFormat) );
			const bool swizzle = TextureFormat::BGRA8 == m_textureFormat && 0 != (m_flags & BGFX_TEXTURE_COMPUTE_WRITE);

			const bool writeOnly    = 0 != (m_flags & BGFX_TEXTURE_RT_WRITE_ONLY);
			const bool computeWrite = 0 != (m_flags & BGFX_TEXTURE_COMPUTE_WRITE);
			const bool renderTarget = 0 != (m_flags & BGFX_TEXTURE_RT_MASK);
			const bool blit         = 0 != (m_flags & BGFX_TEXTURE_BLIT_DST);

			const bool needResolve = true
				&& 1 < m_sampler.Count
				&& 0 == (m_flags & BGFX_TEXTURE_MSAA_SAMPLE)
				&& !writeOnly
				;

			BX_UNUSED(swizzle, writeOnly, computeWrite, renderTarget, blit);

			BX_TRACE(
				  "Texture %3d: %s (requested: %s), %dx%dx%d%s RT[%c], BO[%c], CW[%c]%s."
				, (int)(this - s_renderVK->m_textures)
				, getName( (TextureFormat::Enum)m_textureFormat)
				, getName( (TextureFormat::Enum)m_requestedFormat)
				, ti.width
				, ti.height
				, ti.depth
				, imageContainer.m_cubeMap ? "x6" : ""
				, renderTarget ? 'x' : ' '
				, writeOnly ? 'x' : ' '
				, computeWrite ? 'x' : ' '
				, swizzle ? " (swizzle BGRA8 -> RGBA8)" : ""
				);

			// decode images
			struct ImageInfo
			{
				uint8_t* data;
				uint32_t width;
				uint32_t height;
				uint32_t depth;
				uint32_t pitch;
				uint32_t slice;
				uint32_t size;
				uint8_t mipLevel;
				uint8_t layer;
			};

			ImageInfo* imageInfos = (ImageInfo*)BX_ALLOC(g_allocator, sizeof(ImageInfo) * numSrd);
			bx::memSet(imageInfos, 0, sizeof(ImageInfo) * numSrd);
			uint32_t alignment = 1; // tightly aligned buffer
			for (uint8_t side = 0; side < numSides; ++side)
			{
				for (uint8_t lod = 0; lod < ti.numMips; ++lod)
				{
					bimg::ImageMip mip;
					if (bimg::imageGetRawData(imageContainer, side, lod + startLod, _mem->data, _mem->size, mip) )
					{
						if (convert)
						{
							const uint32_t pitch = bx::strideAlign(bx::max<uint32_t>(mip.m_width, 4) * bpp / 8, alignment);
							const uint32_t slice = bx::strideAlign(bx::max<uint32_t>(mip.m_height, 4) * pitch, alignment);
							const uint32_t size = slice * mip.m_depth;

							uint8_t* temp = (uint8_t*)BX_ALLOC(g_allocator, size);
							bimg::imageDecodeToBgra8(
								  g_allocator
								, temp
								, mip.m_data
								, mip.m_width
								, mip.m_height
								, pitch
								, mip.m_format
								);

							imageInfos[kk].data = temp;
							imageInfos[kk].width = mip.m_width;
							imageInfos[kk].height = mip.m_height;
							imageInfos[kk].depth = mip.m_depth;
							imageInfos[kk].pitch = pitch;
							imageInfos[kk].slice = slice;
							imageInfos[kk].size = size;
							imageInfos[kk].mipLevel = lod;
							imageInfos[kk].layer = side;
						}
						else if (compressed)
						{
							const uint32_t pitch = bx::strideAlign( (mip.m_width / blockInfo.blockWidth) * mip.m_blockSize, alignment);
							const uint32_t slice = bx::strideAlign( (mip.m_height / blockInfo.blockHeight) * pitch, alignment);
							const uint32_t size = slice * mip.m_depth;

							uint8_t* temp = (uint8_t*)BX_ALLOC(g_allocator, size);
							bimg::imageCopy(
								  temp
								, mip.m_height / blockInfo.blockHeight
								, (mip.m_width / blockInfo.blockWidth) * mip.m_blockSize
								, mip.m_depth
								, mip.m_data
								, pitch
								);

							imageInfos[kk].data = temp;
							imageInfos[kk].width = mip.m_width;
							imageInfos[kk].height = mip.m_height;
							imageInfos[kk].depth = mip.m_depth;
							imageInfos[kk].pitch = pitch;
							imageInfos[kk].slice = slice;
							imageInfos[kk].size = size;
							imageInfos[kk].mipLevel = lod;
							imageInfos[kk].layer = side;
						}
						else
						{
							const uint32_t pitch = bx::strideAlign(mip.m_width * mip.m_bpp / 8, alignment);
							const uint32_t slice = bx::strideAlign(mip.m_height * pitch, alignment);
							const uint32_t size = slice * mip.m_depth;

							uint8_t* temp = (uint8_t*)BX_ALLOC(g_allocator, size);
							bimg::imageCopy(temp
								, mip.m_height
								, mip.m_width * mip.m_bpp / 8
								, mip.m_depth
								, mip.m_data
								, pitch
							);

							imageInfos[kk].data = temp;
							imageInfos[kk].width = mip.m_width;
							imageInfos[kk].height = mip.m_height;
							imageInfos[kk].depth = mip.m_depth;
							imageInfos[kk].pitch = pitch;
							imageInfos[kk].slice = slice;
							imageInfos[kk].size = size;
							imageInfos[kk].mipLevel = lod;
							imageInfos[kk].layer = side;
						}
					}
					++kk;
				}
			}

			uint32_t totalMemSize = 0;
			VkBufferImageCopy* bufferCopyInfo = (VkBufferImageCopy*)BX_ALLOC(g_allocator, sizeof(VkBufferImageCopy) * numSrd);
			for (uint32_t ii = 0; ii < numSrd; ++ii)
			{
				uint32_t idealWidth  = bx::max<uint32_t>(1, m_width  >> imageInfos[ii].mipLevel);
				uint32_t idealHeight = bx::max<uint32_t>(1, m_height >> imageInfos[ii].mipLevel);
				bufferCopyInfo[ii].bufferOffset      = totalMemSize;
				bufferCopyInfo[ii].bufferRowLength   = 0; // assume that image data are tightly aligned
				bufferCopyInfo[ii].bufferImageHeight = 0; // assume that image data are tightly aligned
				bufferCopyInfo[ii].imageSubresource.aspectMask     = m_aspectMask;
				bufferCopyInfo[ii].imageSubresource.mipLevel       = imageInfos[ii].mipLevel;
				bufferCopyInfo[ii].imageSubresource.baseArrayLayer = imageInfos[ii].layer;
				bufferCopyInfo[ii].imageSubresource.layerCount     = 1;
				bufferCopyInfo[ii].imageOffset = { 0, 0, 0 };
				bufferCopyInfo[ii].imageExtent = { idealWidth, idealHeight, imageInfos[ii].depth };
				totalMemSize += imageInfos[ii].size;
			}

			VkBuffer stagingBuffer = VK_NULL_HANDLE;
			VkDeviceMemory stagingDeviceMem = VK_NULL_HANDLE;
			if (totalMemSize > 0)
			{
				// staging buffer creation
				VkBufferCreateInfo bci;
				bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
				bci.pNext = NULL;
				bci.flags = 0;
				bci.size = totalMemSize;
				bci.queueFamilyIndexCount = 0;
				bci.pQueueFamilyIndices = NULL;
				bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
				bci.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
				VK_CHECK(vkCreateBuffer(
					  device
					, &bci
					, allocatorCb
					, &stagingBuffer
					) );

				VkMemoryRequirements mr;
				vkGetBufferMemoryRequirements(
					  device
					, stagingBuffer
					, &mr
					);

				VK_CHECK(s_renderVK->allocateMemory(&mr, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &stagingDeviceMem) );

				VK_CHECK(vkBindBufferMemory(
					  device
					, stagingBuffer
					, stagingDeviceMem
					, 0
					) );
				VK_CHECK(vkMapMemory(
					  device
					, stagingDeviceMem
					, 0
					, mr.size
					, 0
					, (void**)& m_directAccessPtr
					) );

				uint8_t* mappedMemory = (uint8_t*)m_directAccessPtr;

				// copy image to staging buffer
				for (uint32_t ii = 0; ii < numSrd; ++ii)
				{
					bx::memCopy(mappedMemory, imageInfos[ii].data, imageInfos[ii].size);
					mappedMemory += imageInfos[ii].size;
				}

				vkUnmapMemory(device, stagingDeviceMem);
			}

			// create texture and allocate its device memory
			VkImageCreateInfo ici;
			ici.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			ici.pNext = NULL;
			ici.flags = VK_IMAGE_VIEW_TYPE_CUBE == m_type
				? VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT
				: 0
				;
			ici.pQueueFamilyIndices   = NULL;
			ici.queueFamilyIndexCount = 0;
			ici.initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED;
			ici.sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
			ici.usage                 = 0
				| VK_IMAGE_USAGE_TRANSFER_SRC_BIT
				| VK_IMAGE_USAGE_TRANSFER_DST_BIT
				| VK_IMAGE_USAGE_SAMPLED_BIT
				| (_flags & BGFX_TEXTURE_RT_MASK
					? (bimg::isDepth( (bimg::TextureFormat::Enum)m_textureFormat)
						? VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
						: VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
					: 0
					)
				| (_flags & BGFX_TEXTURE_COMPUTE_WRITE ? VK_IMAGE_USAGE_STORAGE_BIT : 0)
				;
			ici.format        = m_format;
			ici.samples       = m_sampler.Sample;
			ici.mipLevels     = m_numMips;
			ici.arrayLayers   = m_numSides;
			ici.extent.width  = m_width;
			ici.extent.height = m_height;
			ici.extent.depth  = m_depth;
			ici.imageType     = VK_IMAGE_VIEW_TYPE_3D == m_type
				? VK_IMAGE_TYPE_3D
				: VK_IMAGE_TYPE_2D
				;
			ici.tiling        = VK_IMAGE_TILING_OPTIMAL;

			VK_CHECK(vkCreateImage(device, &ici, allocatorCb, &m_textureImage) );

			VkMemoryRequirements imageMemReq;
			vkGetImageMemoryRequirements(device, m_textureImage, &imageMemReq);

			VK_CHECK(s_renderVK->allocateMemory(&imageMemReq, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &m_textureDeviceMem) );

			vkBindImageMemory(device, m_textureImage, m_textureDeviceMem, 0);

			if (stagingBuffer)
			{
				copyBufferToTexture(stagingBuffer, numSrd, bufferCopyInfo);
			}
			else
			{
				VkCommandBuffer commandBuffer = s_renderVK->beginNewCommand();
				setImageMemoryBarrier(
					  commandBuffer
					, (m_flags & BGFX_TEXTURE_COMPUTE_WRITE
						? VK_IMAGE_LAYOUT_GENERAL
						: VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
					  )
					);
				s_renderVK->submitCommandAndWait(commandBuffer);
			}

			vkFreeMemory(device, stagingDeviceMem, allocatorCb);
			vkDestroy(stagingBuffer);

			BX_FREE(g_allocator, bufferCopyInfo);
			for (uint32_t ii = 0; ii < numSrd; ++ii)
			{
				BX_FREE(g_allocator, imageInfos[ii].data);
			}
			BX_FREE(g_allocator, imageInfos);

			// image view creation
			{
				VkImageViewCreateInfo viewInfo;
				viewInfo.sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				viewInfo.pNext      = NULL;
				viewInfo.flags      = 0;
				viewInfo.image      = m_textureImage;
				viewInfo.viewType   = m_type;
				viewInfo.format     = m_format;
				viewInfo.components = m_components;
				viewInfo.subresourceRange.aspectMask     = m_aspectMask;
				viewInfo.subresourceRange.baseMipLevel   = 0;
				viewInfo.subresourceRange.levelCount     = m_numMips;
				viewInfo.subresourceRange.baseArrayLayer = 0;
				viewInfo.subresourceRange.layerCount     = m_numSides;
				VK_CHECK(vkCreateImageView(
					  device
					, &viewInfo
					, allocatorCb
					, &m_textureImageView
					) );
			}

			if ( (m_aspectMask & VK_IMAGE_ASPECT_DEPTH_BIT)
			&&   (m_aspectMask & VK_IMAGE_ASPECT_STENCIL_BIT) )
			{
				VkImageViewCreateInfo viewInfo;
				viewInfo.sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				viewInfo.pNext      = NULL;
				viewInfo.flags      = 0;
				viewInfo.image      = m_textureImage;
				viewInfo.viewType   = m_type;
				viewInfo.format     = m_format;
				viewInfo.components = m_components;
				viewInfo.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_DEPTH_BIT;
				viewInfo.subresourceRange.baseMipLevel   = 0;
				viewInfo.subresourceRange.levelCount     = m_numMips;
				viewInfo.subresourceRange.baseArrayLayer = 0;
				viewInfo.subresourceRange.layerCount     = m_numSides;
				VK_CHECK(vkCreateImageView(
					device
					, &viewInfo
					, allocatorCb
					, &m_textureImageDepthView
					) );
			}

			// image view creation for storage if needed
			if (m_flags & BGFX_TEXTURE_COMPUTE_WRITE)
			{
				VkImageViewCreateInfo viewInfo;
				viewInfo.sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				viewInfo.pNext      = NULL;
				viewInfo.flags      = 0;
				viewInfo.image      = m_textureImage;
				viewInfo.viewType   = m_type == VK_IMAGE_VIEW_TYPE_CUBE
					? VK_IMAGE_VIEW_TYPE_2D_ARRAY
					: m_type
					;
				viewInfo.format     = m_format;
				viewInfo.components = m_components;
				viewInfo.subresourceRange.aspectMask     = m_aspectMask;
				viewInfo.subresourceRange.baseMipLevel   = 0;
				viewInfo.subresourceRange.levelCount     = m_numMips;
				viewInfo.subresourceRange.baseArrayLayer = 0;
				viewInfo.subresourceRange.layerCount     = m_numSides;
				VK_CHECK(vkCreateImageView(
					  device
					, &viewInfo
					, allocatorCb
					, &m_textureImageStorageView
					) );
			}

			if (needResolve)
			{
				{
					VkImageCreateInfo ici_resolve = ici;
					ici_resolve.samples = s_msaa[0].Sample;
					ici_resolve.usage &= ~(VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT);

					VK_CHECK(vkCreateImage(device, &ici_resolve, allocatorCb, &m_singleMsaaImage) );

					VkMemoryRequirements imageMemReq_resolve;
					vkGetImageMemoryRequirements(device, m_singleMsaaImage, &imageMemReq_resolve);

					VK_CHECK(s_renderVK->allocateMemory(&imageMemReq_resolve, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &m_singleMsaaDeviceMem) );

					vkBindImageMemory(device, m_singleMsaaImage, m_singleMsaaDeviceMem, 0);
				}

				{
					VkCommandBuffer commandBuffer = s_renderVK->beginNewCommand();

					bgfx::vk::setImageMemoryBarrier(commandBuffer
						, m_singleMsaaImage
						, m_aspectMask
						, VK_IMAGE_LAYOUT_UNDEFINED
						, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
						, m_numMips
						, m_numSides
					);

					s_renderVK->submitCommandAndWait(commandBuffer);
				}

				{
					VkImageViewCreateInfo viewInfo;
					viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
					viewInfo.pNext = NULL;
					viewInfo.flags = 0;
					viewInfo.image = m_singleMsaaImage;
					viewInfo.viewType = m_type;
					viewInfo.format = m_format;
					viewInfo.components = m_components;
					viewInfo.subresourceRange.aspectMask = m_aspectMask;
					viewInfo.subresourceRange.baseMipLevel = 0;
					viewInfo.subresourceRange.levelCount = m_numMips;
					viewInfo.subresourceRange.baseArrayLayer = 0;
					viewInfo.subresourceRange.layerCount = m_numSides;
					VK_CHECK(vkCreateImageView(
						device
						, &viewInfo
						, allocatorCb
						, &m_singleMsaaImageView
					) );
				}
			}
		}

		return m_directAccessPtr;
	}

	void TextureVK::destroy()
	{
		VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;
		VkDevice device = s_renderVK->m_device;

		if (m_textureImage)
		{
			vkFreeMemory(device, m_textureDeviceMem, allocatorCb);

			vkDestroy(m_textureImageStorageView);
			vkDestroy(m_textureImageDepthView);
			vkDestroy(m_textureImageView);
			vkDestroy(m_textureImage);
		}

		if (m_singleMsaaImage)
		{
			vkFreeMemory(device, m_singleMsaaDeviceMem, allocatorCb);

			vkDestroy(m_singleMsaaImageView);
			vkDestroy(m_singleMsaaImage);
		}

		m_currentImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	}

	void TextureVK::update(VkCommandPool _commandPool, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem)
	{
		BX_UNUSED(_commandPool);

		const uint32_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat) );
		uint32_t rectpitch = _rect.m_width * bpp / 8;
		uint32_t slicepitch = rectpitch * _rect.m_height;
		if (bimg::isCompressed(bimg::TextureFormat::Enum(m_textureFormat) ) )
		{
			const bimg::ImageBlockInfo& blockInfo = bimg::getBlockInfo(bimg::TextureFormat::Enum(m_textureFormat) );
			rectpitch = (_rect.m_width / blockInfo.blockWidth) * blockInfo.blockSize;
			slicepitch = (_rect.m_height / blockInfo.blockHeight) * rectpitch;
		}
		const uint32_t srcpitch = UINT16_MAX == _pitch ? rectpitch : _pitch;
		const uint32_t size     = UINT16_MAX == _pitch ? slicepitch  * _depth: _rect.m_height * _pitch * _depth;
		const bool convert = m_textureFormat != m_requestedFormat;

		uint8_t* data = _mem->data;
		uint8_t* temp = NULL;

		if (convert)
		{
			temp = (uint8_t*)BX_ALLOC(g_allocator, slicepitch);
			bimg::imageDecodeToBgra8(g_allocator, temp, data, _rect.m_width, _rect.m_height, srcpitch, bimg::TextureFormat::Enum(m_requestedFormat) );
			data = temp;
		}

		VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;
		VkDevice device = s_renderVK->m_device;

		VkBuffer stagingBuffer = VK_NULL_HANDLE;
		VkDeviceMemory stagingDeviceMem = VK_NULL_HANDLE;

		// staging buffer creation
		VkBufferCreateInfo bci;
		bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bci.pNext = NULL;
		bci.flags = 0;
		bci.size = size;
		bci.queueFamilyIndexCount = 0;
		bci.pQueueFamilyIndices = NULL;
		bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		bci.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
		VK_CHECK(vkCreateBuffer(
			  device
			, &bci
			, allocatorCb
			, &stagingBuffer
			) );

		VkMemoryRequirements mr;
		vkGetBufferMemoryRequirements(
			  device
			, stagingBuffer
			, &mr
			);

		VK_CHECK(s_renderVK->allocateMemory(&mr, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &stagingDeviceMem) );

		void* directAccessPtr = NULL;
		VK_CHECK(vkBindBufferMemory(device, stagingBuffer, stagingDeviceMem, 0) );
		VK_CHECK(vkMapMemory(device, stagingDeviceMem, 0, size, 0, (void**)&directAccessPtr) );
		bx::memCopy(directAccessPtr, data, size);
		vkUnmapMemory(device, stagingDeviceMem);

		VkBufferImageCopy region;
		region.bufferOffset      = 0;
		region.bufferRowLength   = (_pitch == UINT16_MAX ? 0 : _pitch * 8 / bpp);
		region.bufferImageHeight = 0;
		region.imageSubresource.aspectMask     = m_aspectMask;
		region.imageSubresource.mipLevel       = _mip;
		region.imageSubresource.baseArrayLayer = _side;
		region.imageSubresource.layerCount     = 1;
		region.imageOffset = { _rect.m_x, _rect.m_y, _z };
		region.imageExtent = { _rect.m_width, _rect.m_height, _depth };

		copyBufferToTexture(stagingBuffer, 1, &region);

		vkFreeMemory(device, stagingDeviceMem, allocatorCb);
		vkDestroy(stagingBuffer);

		if (NULL != temp)
		{
			BX_FREE(g_allocator, temp);
		}
	}

	void TextureVK::resolve(uint8_t _resolve)
	{
		BX_UNUSED(_resolve);

		bool needResolve = VK_NULL_HANDLE != m_singleMsaaImage;
		if (needResolve)
		{
			VkCommandBuffer commandBuffer = s_renderVK->beginNewCommand();

			VkImageResolve blitInfo;
			blitInfo.srcOffset.x = 0;
			blitInfo.srcOffset.y = 0;
			blitInfo.srcOffset.z = 0;
			blitInfo.dstOffset.x = 0;
			blitInfo.dstOffset.y = 0;
			blitInfo.dstOffset.z = 0;
			blitInfo.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			blitInfo.srcSubresource.mipLevel = 0;
			blitInfo.srcSubresource.baseArrayLayer = 0;
			blitInfo.srcSubresource.layerCount = 1;
			blitInfo.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			blitInfo.dstSubresource.mipLevel = 0;
			blitInfo.dstSubresource.baseArrayLayer = 0;
			blitInfo.dstSubresource.layerCount = 1;
			blitInfo.extent.width = m_width;
			blitInfo.extent.height = m_height;
			blitInfo.extent.depth = 1;

			vkCmdResolveImage(commandBuffer,
				m_textureImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
				m_singleMsaaImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				1, &blitInfo);

			s_renderVK->submitCommandAndWait(commandBuffer);
		}

		const bool renderTarget = 0 != (m_flags & BGFX_TEXTURE_RT_MASK);
		if (renderTarget
			&& 1 < m_numMips
			&& 0 != (_resolve & BGFX_RESOLVE_AUTO_GEN_MIPS) )
		{
			VkCommandBuffer commandBuffer = s_renderVK->beginNewCommand();

			int32_t mipWidth = m_width;
			int32_t mipHeight = m_height;

			for (uint32_t i = 1; i < m_numMips; i++) {
				bgfx::vk::setImageMemoryBarrier(commandBuffer
					, needResolve ? m_singleMsaaImage : m_textureImage
					, m_aspectMask
					, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
					, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
					, i - 1
					, 1
				);

				VkImageBlit blit{};
				blit.srcOffsets[0] = { 0, 0, 0 };
				blit.srcOffsets[1] = { mipWidth, mipHeight, 1 };
				blit.srcSubresource.aspectMask = m_aspectMask;
				blit.srcSubresource.mipLevel = i - 1;
				blit.srcSubresource.baseArrayLayer = 0;
				blit.srcSubresource.layerCount = 1;
				blit.dstOffsets[0] = { 0, 0, 0 };
				blit.dstOffsets[1] = { mipWidth > 1 ? mipWidth / 2 : 1, mipHeight > 1 ? mipHeight / 2 : 1, 1 };
				blit.dstSubresource.aspectMask = m_aspectMask;
				blit.dstSubresource.mipLevel = i;
				blit.dstSubresource.baseArrayLayer = 0;
				blit.dstSubresource.layerCount = 1;

				vkCmdBlitImage(commandBuffer,
					needResolve ? m_singleMsaaImage : m_textureImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
					needResolve ? m_singleMsaaImage : m_textureImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
					1, &blit,
					VK_FILTER_LINEAR);

				bgfx::vk::setImageMemoryBarrier(commandBuffer
					, needResolve ? m_singleMsaaImage : m_textureImage
					, m_aspectMask
					, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
					, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
					, i - 1
					, 1
				);

				if (mipWidth > 1) mipWidth /= 2;
				if (mipHeight > 1) mipHeight /= 2;
			}

			bgfx::vk::setImageMemoryBarrier(commandBuffer
				, needResolve ? m_singleMsaaImage : m_textureImage
				, m_aspectMask
				, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
				, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
				, m_numMips - 1
				, 1
			);

			s_renderVK->submitCommandAndWait(commandBuffer);
		}
	}

	void TextureVK::copyBufferToTexture(VkBuffer stagingBuffer, uint32_t bufferImageCopyCount, VkBufferImageCopy* bufferImageCopy)
	{
		VkCommandBuffer commandBuffer = s_renderVK->beginNewCommand();

		// image Layout transition into destination optimal
		setImageMemoryBarrier(commandBuffer, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

		// copy buffer to image
		vkCmdCopyBufferToImage(
			  commandBuffer
			, stagingBuffer
			, m_textureImage
			, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
			, bufferImageCopyCount
			, bufferImageCopy
			);

		setImageMemoryBarrier(commandBuffer, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
		s_renderVK->submitCommandAndWait(commandBuffer);
	}

	void TextureVK::setImageMemoryBarrier(VkCommandBuffer commandBuffer, VkImageLayout newImageLayout)
	{
		if (m_currentImageLayout == newImageLayout)
			return;
		bgfx::vk::setImageMemoryBarrier(commandBuffer
			, m_textureImage
			, m_aspectMask
			, m_currentImageLayout
			, newImageLayout
			, m_numMips
			, m_numSides
			);
		m_currentImageLayout = newImageLayout;
	}

	void FrameBufferVK::create(uint8_t _num, const Attachment* _attachment)
	{
		// create frame buffer object
		m_numAttachment = _num;
		bx::memCopy(m_attachment, _attachment, sizeof(Attachment) * _num);

		VkDevice device = s_renderVK->m_device;
		VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;
		VkRenderPass renderPass = s_renderVK->getRenderPass(_num, _attachment);

		TextureVK& firstTexture = s_renderVK->m_textures[m_attachment[0].handle.idx];
		::VkImageView textureImageViews[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];

		m_depth.idx = bx::kInvalidHandle;
		m_num = 0;
		for (uint8_t ii = 0; ii < m_numAttachment; ++ii)
		{
			TextureVK& texture = s_renderVK->m_textures[m_attachment[ii].handle.idx];
			textureImageViews[ii] = texture.m_textureImageView;
			if (texture.m_aspectMask & VK_IMAGE_ASPECT_COLOR_BIT)
			{
				m_texture[m_num] = m_attachment[ii].handle;
				m_num++;
			}
			else if (texture.m_aspectMask & VK_IMAGE_ASPECT_DEPTH_BIT)
			{
				m_depth = m_attachment[ii].handle;
			}
		}

		VkFramebufferCreateInfo fci;
		fci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		fci.pNext = NULL;
		fci.flags = 0;
		fci.renderPass      = renderPass;
		fci.attachmentCount = m_numAttachment;
		fci.pAttachments    = textureImageViews;
		fci.width  = firstTexture.m_width >> m_attachment[0].mip;
		fci.height = firstTexture.m_height >> m_attachment[0].mip;
		fci.layers = firstTexture.m_numSides;
		VK_CHECK( vkCreateFramebuffer(device, &fci, allocatorCb, &m_framebuffer) );
		m_renderPass = renderPass;
	}

	void FrameBufferVK::resolve()
	{
		if (0 < m_numAttachment)
		{
			for (uint32_t ii = 0; ii < m_numAttachment; ++ii)
			{
				const Attachment& at = m_attachment[ii];

				if (isValid(at.handle) )
				{
					TextureVK& texture = s_renderVK->m_textures[at.handle.idx];
					texture.resolve(at.resolve);
				}
			}
		}
	}

	void FrameBufferVK::destroy()
	{
		vkDestroy(m_framebuffer);
	}

	void RendererContextVK::submitBlit(BlitState& _bs, uint16_t _view)
	{
		TextureHandle currentSrc = { kInvalidHandle };
		TextureHandle currentDst = { kInvalidHandle };
		VkImageLayout oldSrcLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		VkImageLayout oldDstLayout = VK_IMAGE_LAYOUT_UNDEFINED;

		VkCommandBuffer commandBuffer = beginNewCommand();
		while (_bs.hasItem(_view) )
		{
			const BlitItem& blit = _bs.advance();

			TextureVK& src = m_textures[blit.m_src.idx];
			TextureVK& dst = m_textures[blit.m_dst.idx];

			if (currentSrc.idx != blit.m_src.idx)
			{
				if (oldSrcLayout != VK_IMAGE_LAYOUT_UNDEFINED)
				{
					m_textures[currentSrc.idx].setImageMemoryBarrier(commandBuffer, oldSrcLayout);
				}

				oldSrcLayout = src.m_currentImageLayout;
				src.setImageMemoryBarrier(commandBuffer, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
				currentSrc = blit.m_src;
			}

			if (currentDst.idx != blit.m_dst.idx)
			{
				if (oldDstLayout != VK_IMAGE_LAYOUT_UNDEFINED)
				{
					m_textures[currentDst.idx].setImageMemoryBarrier(commandBuffer, oldDstLayout);
				}

				oldDstLayout = dst.m_currentImageLayout;
				dst.setImageMemoryBarrier(commandBuffer, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
				currentDst = blit.m_dst;
			}

			uint32_t srcZ = (VK_IMAGE_VIEW_TYPE_CUBE == src.m_type ? 0 : blit.m_srcZ);
			uint32_t dstZ = (VK_IMAGE_VIEW_TYPE_CUBE == dst.m_type ? 0 : blit.m_dstZ);
			uint32_t srcLayer = (VK_IMAGE_VIEW_TYPE_CUBE == src.m_type ? blit.m_srcZ : 0);
			uint32_t dstLayer = (VK_IMAGE_VIEW_TYPE_CUBE == dst.m_type ? blit.m_dstZ : 0);
			uint32_t depth = (blit.m_depth == UINT16_MAX ? 1 : blit.m_depth);

			VkImageBlit blitInfo;
			blitInfo.srcSubresource.aspectMask     = src.m_aspectMask;
			blitInfo.srcSubresource.mipLevel       = blit.m_srcMip;
			blitInfo.srcSubresource.baseArrayLayer = srcLayer;
			blitInfo.srcSubresource.layerCount     = 1;
			blitInfo.srcOffsets[0].x = blit.m_srcX;
			blitInfo.srcOffsets[0].y = blit.m_srcY;
			blitInfo.srcOffsets[0].z = srcZ;
			blitInfo.srcOffsets[1].x = blit.m_srcX + blit.m_width;
			blitInfo.srcOffsets[1].y = blit.m_srcY + blit.m_height;
			blitInfo.srcOffsets[1].z = bx::max<int32_t>(srcZ + depth, 1);
			blitInfo.dstSubresource.aspectMask     = dst.m_aspectMask;
			blitInfo.dstSubresource.mipLevel       = blit.m_dstMip;
			blitInfo.dstSubresource.baseArrayLayer = dstLayer;
			blitInfo.dstSubresource.layerCount     = 1;
			blitInfo.dstOffsets[0].x = blit.m_dstX;
			blitInfo.dstOffsets[0].y = blit.m_dstY;
			blitInfo.dstOffsets[0].z = dstZ;
			blitInfo.dstOffsets[1].x = blit.m_dstX + blit.m_width;
			blitInfo.dstOffsets[1].y = blit.m_dstY + blit.m_height;
			blitInfo.dstOffsets[1].z = bx::max<int32_t>(dstZ + depth, 1);
			VkFilter filter = bimg::isDepth(bimg::TextureFormat::Enum(src.m_textureFormat) ) ? VK_FILTER_NEAREST : VK_FILTER_LINEAR;
			vkCmdBlitImage(
				  commandBuffer
				, VK_NULL_HANDLE != src.m_singleMsaaImage ? src.m_singleMsaaImage : src.m_textureImage
				, src.m_currentImageLayout
				, dst.m_textureImage
				, dst.m_currentImageLayout
				, 1
				, &blitInfo
				, filter
				);
		}

		if (oldSrcLayout != VK_IMAGE_LAYOUT_UNDEFINED)
		{
			m_textures[currentSrc.idx].setImageMemoryBarrier(commandBuffer, oldSrcLayout);
		}
		if (oldDstLayout != VK_IMAGE_LAYOUT_UNDEFINED)
		{
			m_textures[currentDst.idx].setImageMemoryBarrier(commandBuffer, oldDstLayout);
		}
		submitCommandAndWait(commandBuffer);
	}

	void RendererContextVK::submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter)
	{
		BX_UNUSED(_render, _clearQuad, _textVideoMemBlitter);

		m_commandBuffer = beginNewCommand();

		BGFX_VK_PROFILER_BEGIN_LITERAL("rendererSubmit", kColorView);

		submitCommandAndWait(m_commandBuffer);
		m_commandBuffer = VK_NULL_HANDLE;

		if (updateResolution(_render->m_resolution) )
		{
			return;
		}

		if (m_swapchain == VK_NULL_HANDLE)
			return;

		int64_t timeBegin = bx::getHPCounter();
		int64_t captureElapsed = 0;

		uint32_t frameQueryIdx = m_gpuTimer.begin(BGFX_CONFIG_MAX_VIEWS);

		if (0 < _render->m_iboffset)
		{
			BGFX_PROFILER_SCOPE("bgfx/Update transient index buffer", kColorResource);
			TransientIndexBuffer* ib = _render->m_transientIb;
			m_indexBuffers[ib->handle.idx].update(/*m_commandList*/NULL, 0, _render->m_iboffset, ib->data);
		}

		if (0 < _render->m_vboffset)
		{
			BGFX_PROFILER_SCOPE("bgfx/Update transient vertex buffer", kColorResource);
			TransientVertexBuffer* vb = _render->m_transientVb;
			m_vertexBuffers[vb->handle.idx].update(/*m_commandList*/NULL, 0, _render->m_vboffset, vb->data);
		}

		_render->sort();

		RenderDraw currentState;
		currentState.clear();
		currentState.m_stateFlags = BGFX_STATE_NONE;
		currentState.m_stencil    = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);

		static ViewState viewState;
		viewState.reset(_render);

// 		bool wireframe = !!(_render->m_debug&BGFX_DEBUG_WIREFRAME);
// 		setDebugWireframe(wireframe);

		uint16_t currentSamplerStateIdx = kInvalidHandle;
		ProgramHandle currentProgram    = BGFX_INVALID_HANDLE;
		uint32_t currentBindHash        = 0;
		uint32_t currentDslHash         = 0;
		bool     hasPredefined          = false;
		bool     commandListChanged     = false;
		VkPipeline currentPipeline = VK_NULL_HANDLE;
		SortKey key;
		uint16_t view = UINT16_MAX;
		FrameBufferHandle fbh = { BGFX_CONFIG_MAX_FRAME_BUFFERS };

		BlitState bs(_render);

		uint32_t blendFactor = 0;

		const uint64_t primType = _render->m_debug&BGFX_DEBUG_WIREFRAME ? BGFX_STATE_PT_LINES : 0;
		uint8_t primIndex = uint8_t(primType >> BGFX_STATE_PT_SHIFT);
		PrimInfo prim = s_primInfo[primIndex];

		bool wasCompute     = false;
		bool viewHasScissor = false;
		bool restoreScissor = false;
		Rect viewScissorRect;
		viewScissorRect.clear();

		const uint32_t maxComputeBindings = g_caps.limits.maxComputeBindings;
		BX_UNUSED(maxComputeBindings);

		uint32_t statsNumPrimsSubmitted[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumPrimsRendered[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumInstances[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumIndices = 0;
		uint32_t statsKeyType[2] = {};

		VkSemaphore renderWait = m_presentDone[m_backBufferColorIdx];

		{
			VkResult result = vkAcquireNextImageKHR(
				m_device
				, m_swapchain
				, UINT64_MAX
				, renderWait
				, VK_NULL_HANDLE
				, &m_backBufferColorIdx
				);

			if (VK_ERROR_OUT_OF_DATE_KHR       == result
			||  VK_ERROR_VALIDATION_FAILED_EXT == result)
			{
				m_needToRefreshSwapchain = true;
				return;
			}
		}

		const uint64_t f0 = BGFX_STATE_BLEND_FACTOR;
		const uint64_t f1 = BGFX_STATE_BLEND_INV_FACTOR;
		const uint64_t f2 = BGFX_STATE_BLEND_FACTOR<<4;
		const uint64_t f3 = BGFX_STATE_BLEND_INV_FACTOR<<4;

		ScratchBufferVK& scratchBuffer = m_scratchBuffer[m_backBufferColorIdx];
		scratchBuffer.reset();

		VkCommandBufferBeginInfo cbbi;
		cbbi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		cbbi.pNext = NULL;
		cbbi.flags = 0
			| VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
			;
		cbbi.pInheritanceInfo = NULL;
		m_commandBuffer = m_commandBuffers[m_backBufferColorIdx];
		VK_CHECK(vkBeginCommandBuffer(m_commandBuffer, &cbbi) );

		setImageMemoryBarrier(m_commandBuffer
			, m_backBufferColorImage[m_backBufferColorIdx]
			, VK_IMAGE_ASPECT_COLOR_BIT
			, m_backBufferColorImageLayout[m_backBufferColorIdx]
			, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
			, 1, 1);
		m_backBufferColorImageLayout[m_backBufferColorIdx] = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkRenderPassBeginInfo rpbi;
		rpbi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		rpbi.pNext = NULL;
		rpbi.renderPass  = m_renderPass;
		rpbi.framebuffer = m_backBufferColor[m_backBufferColorIdx];
		rpbi.renderArea.offset.x = 0;
		rpbi.renderArea.offset.y = 0;
		rpbi.renderArea.extent = m_sci.imageExtent;
		rpbi.clearValueCount = 0;
		rpbi.pClearValues    = NULL;

		bool beginRenderPass = false;

		Profiler<TimerQueryVK> profiler(
			  _render
			, m_gpuTimer
			, s_viewName
			);

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

				if (viewChanged || isCompute || wasCompute)
				{
					if (beginRenderPass)
					{
						vkCmdEndRenderPass(m_commandBuffer);
						beginRenderPass = false;
					}

					VK_CHECK(vkEndCommandBuffer(m_commandBuffer) );

					kick(renderWait);
					renderWait = VK_NULL_HANDLE;
					finishAll();

					view = key.m_view;
					currentPipeline = VK_NULL_HANDLE;
					currentSamplerStateIdx = kInvalidHandle;
					currentProgram         = BGFX_INVALID_HANDLE;
					hasPredefined          = false;
					BX_UNUSED(currentSamplerStateIdx);

					VK_CHECK(vkBeginCommandBuffer(m_commandBuffer, &cbbi) );
					fbh = _render->m_view[view].m_fbh;
					setFrameBuffer(fbh);

					viewState.m_rect = _render->m_view[view].m_rect;
					const Rect& rect        = _render->m_view[view].m_rect;
					const Rect& scissorRect = _render->m_view[view].m_scissor;
					viewHasScissor  = !scissorRect.isZero();
					viewScissorRect = viewHasScissor ? scissorRect : rect;

					rpbi.framebuffer = isValid(m_fbh)
						? m_frameBuffers[m_fbh.idx].m_framebuffer
						: m_backBufferColor[m_backBufferColorIdx]
						;
					rpbi.renderPass = isValid(m_fbh)
						? m_frameBuffers[m_fbh.idx].m_renderPass
						: m_renderPass
						;
					rpbi.renderArea.offset.x = rect.m_x;
					rpbi.renderArea.offset.y = rect.m_y;
					rpbi.renderArea.extent.width  = rect.m_width;
					rpbi.renderArea.extent.height = rect.m_height;

					if (item > 1)
					{
						profiler.end();
					}

					BGFX_VK_PROFILER_END();
					setViewType(view, " ");
					BGFX_VK_PROFILER_BEGIN(view, kColorView);

					profiler.begin(view);

					if (!isCompute && !beginRenderPass)
					{
						vkCmdBeginRenderPass(m_commandBuffer, &rpbi, VK_SUBPASS_CONTENTS_INLINE);
						beginRenderPass = true;

						VkViewport vp;
						vp.x        =  float(rect.m_x);
						vp.y        =  float(rect.m_y + rect.m_height);
						vp.width    =  float(rect.m_width);
						vp.height   = -float(rect.m_height);
						vp.minDepth = 0.0f;
						vp.maxDepth = 1.0f;
						vkCmdSetViewport(m_commandBuffer, 0, 1, &vp);

						VkRect2D rc;
						rc.offset.x      = viewScissorRect.m_x;
						rc.offset.y      = viewScissorRect.m_y;
						rc.extent.width  = viewScissorRect.m_width;
						rc.extent.height = viewScissorRect.m_height;
						vkCmdSetScissor(m_commandBuffer, 0, 1, &rc);

						restoreScissor = false;

						Clear& clr = _render->m_view[view].m_clear;
						if (BGFX_CLEAR_NONE != clr.m_flags)
						{
							Rect clearRect = rect;
							clearRect.setIntersect(rect, viewScissorRect);
							clearQuad(clearRect, clr, _render->m_colorPalette);
						}

						prim = s_primInfo[Topology::Count]; // Force primitive type update.

						submitBlit(bs, view);
					}
				}

				if (isCompute)
				{
					if (!wasCompute)
					{
						wasCompute = true;

						BGFX_VK_PROFILER_END();
						setViewType(view, "C");
						BGFX_VK_PROFILER_BEGIN(view, kColorCompute);
					}

					const RenderCompute& compute = renderItem.compute;

					VkPipeline pipeline = getPipeline(key.m_program);

					if (pipeline != currentPipeline)
					{
						currentPipeline = pipeline;
						vkCmdBindPipeline(m_commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);
						currentBindHash = 0;
						currentDslHash = 0;
					}

					bool constantsChanged = false;

					if (compute.m_uniformBegin < compute.m_uniformEnd
					||  currentProgram.idx != key.m_program.idx)
					{
						rendererUpdateUniforms(this, _render->m_uniformBuffer[compute.m_uniformIdx], compute.m_uniformBegin, compute.m_uniformEnd);

						currentProgram = key.m_program;
						ProgramVK& program = m_program[currentProgram.idx];

						UniformBuffer* vcb = program.m_vsh->m_constantBuffer;

						if (NULL != vcb)
						{
							commit(*vcb);
						}

						hasPredefined = 0 < program.m_numPredefined;
						constantsChanged = true;
					}

					const ProgramVK& program = m_program[currentProgram.idx];

					if (constantsChanged
					||  hasPredefined)
					{
						viewState.setPredefined<4>(this, view, program, _render, compute);
					}

					if (program.m_descriptorSetLayoutHash != 0)
					{
						uint32_t bindHash = bx::hash<bx::HashMurmur2A>(renderBind.m_bind, sizeof(renderBind.m_bind) );

						if (currentBindHash != bindHash
						||  currentDslHash  != program.m_descriptorSetLayoutHash)
						{
							currentBindHash = bindHash;
							currentDslHash  = program.m_descriptorSetLayoutHash;

							allocDescriptorSet(program, renderBind, scratchBuffer);
						}

						uint32_t offset = 0;

						if (constantsChanged
						||  hasPredefined)
						{
							const uint32_t align = uint32_t(m_deviceProperties.limits.minUniformBufferOffsetAlignment);
							const uint32_t vsize = bx::strideAlign(program.m_vsh->m_size, align);

							offset = scratchBuffer.m_pos;

							bx::memCopy(&scratchBuffer.m_data[scratchBuffer.m_pos], m_vsScratch, program.m_vsh->m_size);

							scratchBuffer.m_pos += vsize;
						}

						vkCmdBindDescriptorSets(
							m_commandBuffer
							, VK_PIPELINE_BIND_POINT_COMPUTE
							, program.m_pipelineLayout
							, 0
							, 1
							, &scratchBuffer.getCurrentDS()
							, constantsChanged || hasPredefined ? 1 : 0
							, &offset
							);
					}

					if (isValid(compute.m_indirectBuffer) )
					{
						const VertexBufferVK& vb = m_vertexBuffers[compute.m_indirectBuffer.idx];

						uint32_t numDrawIndirect = UINT16_MAX == compute.m_numIndirect
							? vb.m_size/BGFX_CONFIG_DRAW_INDIRECT_STRIDE
							: compute.m_numIndirect
							;

						uint32_t args = compute.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
						for (uint32_t ii = 0; ii < numDrawIndirect; ++ii)
						{
							vkCmdDispatchIndirect(m_commandBuffer, vb.m_buffer, args);
							args += BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
						}
					}
					else
					{
						vkCmdDispatch(m_commandBuffer, compute.m_numX, compute.m_numY, compute.m_numZ);
					}

					continue;
				}

				const RenderDraw& draw = renderItem.draw;

				const bool hasOcclusionQuery = false; //0 != (draw.m_stateFlags & BGFX_STATE_INTERNAL_OCCLUSION_QUERY);
				{
					const bool occluded = false //true
//						&& isValid(draw.m_occlusionQuery)
//						&& !hasOcclusionQuery
//						&& !isVisible(_render, draw.m_occlusionQuery, 0 != (draw.m_submitFlags&BGFX_SUBMIT_INTERNAL_OCCLUSION_VISIBLE) )
						;

					if (occluded
					||  _render->m_frameCache.isZeroArea(viewScissorRect, draw.m_scissor) )
					{
//						if (resetState)
//						{
//							currentState.clear();
//							currentState.m_scissor = !draw.m_scissor;
//							currentBind.clear();
//						}

						continue;
					}
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

					if (viewChanged)
					{
						BGFX_VK_PROFILER_END();
						setViewType(view, " ");
						BGFX_VK_PROFILER_BEGIN(view, kColorDraw);
					}

					commandListChanged = true;
				}

				if (commandListChanged)
				{
					commandListChanged = false;

//					m_commandList->SetGraphicsRootSignature(m_rootSignature);
//					ID3D12DescriptorHeap* heaps[] = {
//						m_samplerAllocator.getHeap(),
//						scratchBuffer.getHeap(),
//					};
//					m_commandList->SetDescriptorHeaps(BX_COUNTOF(heaps), heaps);

					currentPipeline        = VK_NULL_HANDLE;
					currentBindHash        = 0;
					currentDslHash         = 0;
					currentSamplerStateIdx = kInvalidHandle;
					currentProgram         = BGFX_INVALID_HANDLE;
					currentState.clear();
					currentState.m_scissor = !draw.m_scissor;
					changedFlags = BGFX_STATE_MASK;
					changedStencil = packStencil(BGFX_STENCIL_MASK, BGFX_STENCIL_MASK);
					currentState.m_stateFlags = newFlags;
					currentState.m_stencil    = newStencil;

					const uint64_t pt = newFlags&BGFX_STATE_PT_MASK;
					primIndex = uint8_t(pt>>BGFX_STATE_PT_SHIFT);
				}

				rendererUpdateUniforms(this, _render->m_uniformBuffer[draw.m_uniformIdx], draw.m_uniformBegin, draw.m_uniformEnd);

				if (0 != draw.m_streamMask)
				{
					currentState.m_streamMask = draw.m_streamMask;

					const uint64_t state = draw.m_stateFlags;
					bool hasFactor = 0
						|| f0 == (state & f0)
						|| f1 == (state & f1)
						|| f2 == (state & f2)
						|| f3 == (state & f3)
						;

					const VertexLayout* layouts[BGFX_CONFIG_MAX_VERTEX_STREAMS];
					uint8_t numStreams = 0;
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

							currentState.m_stream[idx].m_layoutHandle   = draw.m_stream[idx].m_layoutHandle;
							currentState.m_stream[idx].m_handle         = draw.m_stream[idx].m_handle;
							currentState.m_stream[idx].m_startVertex    = draw.m_stream[idx].m_startVertex;

							uint16_t handle = draw.m_stream[idx].m_handle.idx;
							const VertexBufferVK& vb = m_vertexBuffers[handle];
							const uint16_t decl = isValid(draw.m_stream[idx].m_layoutHandle)
								? draw.m_stream[idx].m_layoutHandle.idx
								: vb.m_layoutHandle.idx
								;
							const VertexLayout& layout = m_vertexLayouts[decl];

							layouts[numStreams] = &layout;
						}
					}

					VkPipeline pipeline =
						getPipeline(state
							, draw.m_stencil
							, numStreams
							, layouts
							, key.m_program
							, uint8_t(draw.m_instanceDataStride/16)
							);

					uint16_t scissor = draw.m_scissor;

					if (pipeline != currentPipeline
					||  0 != changedStencil)
					{
						const uint32_t fstencil = unpackStencil(0, draw.m_stencil);
						const uint32_t ref = (fstencil&BGFX_STENCIL_FUNC_REF_MASK)>>BGFX_STENCIL_FUNC_REF_SHIFT;
						vkCmdSetStencilReference(m_commandBuffer, VK_STENCIL_FRONT_AND_BACK, ref);
					}

					if (pipeline != currentPipeline
					|| (hasFactor && blendFactor != draw.m_rgba) )
					{
						blendFactor = draw.m_rgba;

						float bf[4];
						bf[0] = ( (draw.m_rgba>>24)     )/255.0f;
						bf[1] = ( (draw.m_rgba>>16)&0xff)/255.0f;
						bf[2] = ( (draw.m_rgba>> 8)&0xff)/255.0f;
						bf[3] = ( (draw.m_rgba    )&0xff)/255.0f;
						vkCmdSetBlendConstants(m_commandBuffer, bf);
					}

					if (0 != (BGFX_STATE_PT_MASK & changedFlags)
					||  prim.m_topology != s_primInfo[primIndex].m_topology)
					{
						const uint64_t pt = newFlags&BGFX_STATE_PT_MASK;
						primIndex = uint8_t(pt>>BGFX_STATE_PT_SHIFT);
						prim = s_primInfo[primIndex];
//						m_commandList->IASetPrimitiveTopology(prim.m_topology);
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
								VkRect2D rc;
								rc.offset.x      = viewScissorRect.m_x;
								rc.offset.y      = viewScissorRect.m_y;
								rc.extent.width  = viewScissorRect.m_width;
								rc.extent.height = viewScissorRect.m_height;
								vkCmdSetScissor(m_commandBuffer, 0, 1, &rc);
							}
						}
						else
						{
							restoreScissor = true;
							Rect scissorRect;
							scissorRect.setIntersect(viewScissorRect, _render->m_frameCache.m_rectCache.m_cache[scissor]);

							VkRect2D rc;
							rc.offset.x      = scissorRect.m_x;
							rc.offset.y      = scissorRect.m_y;
							rc.extent.width  = scissorRect.m_width;
							rc.extent.height = scissorRect.m_height;
							vkCmdSetScissor(m_commandBuffer, 0, 1, &rc);
						}
					}

					if (pipeline != currentPipeline)
					{
						currentPipeline = pipeline;
						vkCmdBindPipeline(m_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
					}

					bool constantsChanged = false;
					if (draw.m_uniformBegin < draw.m_uniformEnd
					||  currentProgram.idx != key.m_program.idx
					||  BGFX_STATE_ALPHA_REF_MASK & changedFlags)
					{
						currentProgram = key.m_program;
						ProgramVK& program = m_program[currentProgram.idx];

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

					const ProgramVK& program = m_program[currentProgram.idx];

					if (hasPredefined)
					{
						uint32_t ref = (newFlags & BGFX_STATE_ALPHA_REF_MASK) >> BGFX_STATE_ALPHA_REF_SHIFT;
						viewState.m_alphaRef = ref / 255.0f;
						viewState.setPredefined<4>(this, view, program, _render, draw);
					}

					if (program.m_descriptorSetLayoutHash != 0)
					{
						uint32_t bindHash = bx::hash<bx::HashMurmur2A>(renderBind.m_bind, sizeof(renderBind.m_bind) );
						if (currentBindHash != bindHash
						||  currentDslHash  != program.m_descriptorSetLayoutHash)
						{
							currentBindHash = bindHash;
							currentDslHash  = program.m_descriptorSetLayoutHash;

							allocDescriptorSet(program, renderBind, scratchBuffer);
						}

						uint32_t numOffset = 0;
						uint32_t offsets[2] = { 0, 0 };

						if (constantsChanged
						||  hasPredefined)
						{
							const uint32_t align = uint32_t(m_deviceProperties.limits.minUniformBufferOffsetAlignment);
							const uint32_t vsize = bx::strideAlign(program.m_vsh->m_size, align);
							const uint32_t fsize = bx::strideAlign(NULL != program.m_fsh ? program.m_fsh->m_size : 0, align);
							const uint32_t total = vsize + fsize;

							if (vsize > 0)
							{
								offsets[numOffset++] = scratchBuffer.m_pos;
								bx::memCopy(&scratchBuffer.m_data[scratchBuffer.m_pos], m_vsScratch, program.m_vsh->m_size);
							}

							if (fsize > 0)
							{
								offsets[numOffset++] = scratchBuffer.m_pos + vsize;
								bx::memCopy(&scratchBuffer.m_data[scratchBuffer.m_pos + vsize], m_fsScratch, program.m_fsh->m_size);
							}

							scratchBuffer.m_pos += total;
						}

						vkCmdBindDescriptorSets(
							m_commandBuffer
							, VK_PIPELINE_BIND_POINT_GRAPHICS
							, program.m_pipelineLayout
							, 0
							, 1
							, &scratchBuffer.getCurrentDS()
							, numOffset
							, offsets
							);
					}

					uint32_t numIndices = 0;
					for (uint32_t ii = 0; ii < numStreams; ++ii)
					{
						VkDeviceSize offset = 0;
						vkCmdBindVertexBuffers(m_commandBuffer
							, ii
							, 1
							, &m_vertexBuffers[draw.m_stream[ii].m_handle.idx].m_buffer
							, &offset
							);
					}

					if (isValid(draw.m_instanceDataBuffer) )
					{
						VkDeviceSize instanceOffset = draw.m_instanceDataOffset;
						VertexBufferVK& instanceBuffer = m_vertexBuffers[draw.m_instanceDataBuffer.idx];
						vkCmdBindVertexBuffers(m_commandBuffer
							, numStreams
							, 1
							, &instanceBuffer.m_buffer
							, &instanceOffset
							);
					}

					if (!isValid(draw.m_indexBuffer) )
					{
						const VertexBufferVK& vertexBuffer = m_vertexBuffers[draw.m_stream[0].m_handle.idx];
						const VertexLayout* layout = layouts[0];

						const uint32_t numVertices = UINT32_MAX == draw.m_numVertices
							? vertexBuffer.m_size / layout->m_stride
							: draw.m_numVertices
							;
						vkCmdDraw(m_commandBuffer
							, numVertices
							, draw.m_numInstances
							, draw.m_stream[0].m_startVertex
							, 0
							);
					}
					else
					{
						BufferVK& ib = m_indexBuffers[draw.m_indexBuffer.idx];

						const bool hasIndex16 = 0 == (ib.m_flags & BGFX_BUFFER_INDEX32);
						const uint32_t indexSize = hasIndex16 ? 2 : 4;

						numIndices = UINT32_MAX == draw.m_numIndices
							? ib.m_size / indexSize
							: draw.m_numIndices
							;

						vkCmdBindIndexBuffer(m_commandBuffer
							, ib.m_buffer
							, 0
							, hasIndex16
								? VK_INDEX_TYPE_UINT16
								: VK_INDEX_TYPE_UINT32
							);
						vkCmdDrawIndexed(m_commandBuffer
							, numIndices
							, draw.m_numInstances
							, draw.m_startIndex
							, draw.m_stream[0].m_startVertex
							, 0
							);
					}

					uint32_t numPrimsSubmitted = numIndices / prim.m_div - prim.m_sub;
					uint32_t numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

					statsNumPrimsSubmitted[primIndex] += numPrimsSubmitted;
					statsNumPrimsRendered[primIndex]  += numPrimsRendered;
					statsNumInstances[primIndex]      += draw.m_numInstances;
					statsNumIndices                   += numIndices;

					if (hasOcclusionQuery)
					{
//						m_occlusionQuery.begin(m_commandList, _render, draw.m_occlusionQuery);
//						m_occlusionQuery.end(m_commandList);
					}
				}
			}

			if (wasCompute)
			{
				setViewType(view, "C");
				BGFX_VK_PROFILER_END();
				BGFX_VK_PROFILER_BEGIN(view, kColorCompute);
			}

			submitBlit(bs, BGFX_CONFIG_MAX_VIEWS);

			if (0 < _render->m_numRenderItems)
			{
				captureElapsed = -bx::getHPCounter();
//				capture();
				captureElapsed += bx::getHPCounter();

				profiler.end();
			}
		}

		BGFX_VK_PROFILER_END();

		int64_t timeEnd = bx::getHPCounter();
		int64_t frameTime = timeEnd - timeBegin;

		static int64_t min = frameTime;
		static int64_t max = frameTime;
		min = bx::min<int64_t>(min, frameTime);
		max = bx::max<int64_t>(max, frameTime);

		static uint32_t maxGpuLatency = 0;
		static double   maxGpuElapsed = 0.0f;
		double elapsedGpuMs = 0.0;
BX_UNUSED(maxGpuLatency, maxGpuElapsed, elapsedGpuMs);

		static int64_t presentMin = 0; //m_presentElapsed;
		static int64_t presentMax = 0; //m_presentElapsed;
BX_UNUSED(presentMin, presentMax);
//		presentMin = bx::min<int64_t>(presentMin, m_presentElapsed);
//		presentMax = bx::max<int64_t>(presentMax, m_presentElapsed);

		if (UINT32_MAX != frameQueryIdx)
		{
			m_gpuTimer.end(frameQueryIdx);

			const TimerQueryVK::Result& result = m_gpuTimer.m_result[BGFX_CONFIG_MAX_VIEWS];
			double toGpuMs = 1000.0 / double(m_gpuTimer.m_frequency);
			elapsedGpuMs   = (result.m_end - result.m_begin) * toGpuMs;
			maxGpuElapsed  = elapsedGpuMs > maxGpuElapsed ? elapsedGpuMs : maxGpuElapsed;

			maxGpuLatency = bx::uint32_imax(maxGpuLatency, result.m_pending-1);
		}

		maxGpuLatency = bx::uint32_imax(maxGpuLatency, m_gpuTimer.m_control.available()-1);

		const int64_t timerFreq = bx::getHPFrequency();

		Stats& perfStats = _render->m_perfStats;
		perfStats.cpuTimeBegin  = timeBegin;
		perfStats.cpuTimeEnd    = timeEnd;
		perfStats.cpuTimerFreq  = timerFreq;
		const TimerQueryVK::Result& result = m_gpuTimer.m_result[BGFX_CONFIG_MAX_VIEWS];
		perfStats.gpuTimeBegin  = result.m_begin;
		perfStats.gpuTimeEnd    = result.m_end;
		perfStats.gpuTimerFreq  = m_gpuTimer.m_frequency;
		perfStats.numDraw       = statsKeyType[0];
		perfStats.numCompute    = statsKeyType[1];
		perfStats.numBlit       = _render->m_numBlitItems;
		perfStats.maxGpuLatency = maxGpuLatency;
		bx::memCopy(perfStats.numPrims, statsNumPrimsRendered, sizeof(perfStats.numPrims) );
		perfStats.gpuMemoryMax  = -INT64_MAX;
		perfStats.gpuMemoryUsed = -INT64_MAX;

		if (_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
			BGFX_VK_PROFILER_BEGIN_LITERAL("debugstats", kColorFrame);

//			m_needPresent = true;
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

				const VkPhysicalDeviceProperties& pdp = m_deviceProperties;
				tvm.printf(0, pos++, 0x8f, " Device: %s (%s)"
					, pdp.deviceName
					, getName(pdp.deviceType)
					);

				if (s_extension[Extension::EXT_memory_budget].m_supported)
				{
					VkPhysicalDeviceMemoryBudgetPropertiesEXT dmbp;
					dmbp.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_BUDGET_PROPERTIES_EXT;
					dmbp.pNext = NULL;

					VkPhysicalDeviceMemoryProperties2 pdmp2;
					pdmp2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2;
					pdmp2.pNext = &dmbp;

					vkGetPhysicalDeviceMemoryProperties2KHR(m_physicalDevice, &pdmp2);

					for (uint32_t ii = 0; ii < VK_MAX_MEMORY_HEAPS; ++ii)
					{
						if (dmbp.heapBudget[ii] == 0)
						{
							continue;
						}

						char budget[16];
						bx::prettify(budget, BX_COUNTOF(budget), dmbp.heapBudget[ii]);

						char usage[16];
						bx::prettify(usage, BX_COUNTOF(usage), dmbp.heapUsage[ii]);

						tvm.printf(0, pos++, 0x8f, " Memory %d - Budget: %12s, Usage: %12s"
							, ii
							, budget
							, usage
							);
					}
				}

				pos = 10;
				tvm.printf(10, pos++, 0x8b, "       Frame: % 7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] / % 6.2f FPS "
					, double(frameTime)*toMs
					, double(min)*toMs
					, double(max)*toMs
					, freq/frameTime
					);
//				tvm.printf(10, pos++, 0x8b, "     Present: % 7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] "
//					, double(m_presentElapsed)*toMs
//					, double(presentMin)*toMs
//					, double(presentMax)*toMs
//					);

				const uint32_t msaa = (m_resolution.reset&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT;
				tvm.printf(10, pos++, 0x8b, " Reset flags: [%c] vsync, [%c] MSAAx%d, [%c] MaxAnisotropy "
					, !!(m_resolution.reset&BGFX_RESET_VSYNC) ? '\xfe' : ' '
					, 0 != msaa ? '\xfe' : ' '
					, 1<<msaa
					, !!(m_resolution.reset&BGFX_RESET_MAXANISOTROPY) ? '\xfe' : ' '
					);

				double elapsedCpuMs = double(frameTime)*toMs;
				tvm.printf(10, pos++, 0x8b, "   Submitted: %5d (draw %5d, compute %4d) / CPU %7.4f [ms] "
					, _render->m_numRenderItems
					, statsKeyType[0]
					, statsKeyType[1]
					, elapsedCpuMs
					);

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
//				tvm.printf(10, pos++, 0x8b, " Uniform size: %7d, Max: %7d ", _render->m_uniformEnd, _render->m_uniformMax);
				tvm.printf(10, pos++, 0x8b, "     DVB size: %7d ", _render->m_vboffset);
				tvm.printf(10, pos++, 0x8b, "     DIB size: %7d ", _render->m_iboffset);

				pos++;
				tvm.printf(10, pos++, 0x8b, " State cache:             ");
				tvm.printf(10, pos++, 0x8b, " PSO    | DSL    |  DS    ");
				tvm.printf(10, pos++, 0x8b, " %6d | %6d | %6d "
					, m_pipelineStateCache.getCount()
					, m_descriptorSetLayoutCache.getCount()
					, scratchBuffer.m_currentDs
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
//				presentMin = m_presentElapsed;
//				presentMax = m_presentElapsed;
			}

			blit(this, _textVideoMemBlitter, tvm);

			BGFX_VK_PROFILER_END();
		}
		else if (_render->m_debug & BGFX_DEBUG_TEXT)
		{
			BGFX_VK_PROFILER_BEGIN_LITERAL("debugtext", kColorFrame);

			blit(this, _textVideoMemBlitter, _render->m_textVideoMem);

			BGFX_VK_PROFILER_END();
		}

		const uint32_t align = uint32_t(m_deviceProperties.limits.nonCoherentAtomSize);
		const uint32_t size = bx::min(bx::strideAlign(scratchBuffer.m_pos, align), scratchBuffer.m_size);
		VkMappedMemoryRange range;
		range.sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		range.pNext  = NULL;
		range.memory = scratchBuffer.m_deviceMem;
		range.offset = 0;
		range.size   = size;
		vkFlushMappedMemoryRanges(m_device, 1, &range);

		if (beginRenderPass)
		{
			vkCmdEndRenderPass(m_commandBuffer);
			beginRenderPass = false;
		}

		setImageMemoryBarrier(
			  m_commandBuffer
			, m_backBufferColorImage[m_backBufferColorIdx]
			, VK_IMAGE_ASPECT_COLOR_BIT
			, m_backBufferColorImageLayout[m_backBufferColorIdx]
			, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
			, 1
			, 1
			);
		m_backBufferColorImageLayout[m_backBufferColorIdx] = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VK_CHECK(vkEndCommandBuffer(m_commandBuffer) );

		kick(renderWait);
		finishAll();

		VK_CHECK(vkResetCommandPool(m_device, m_commandPool, 0) );
	}

} /* namespace vk */ } // namespace bgfx

#else

namespace bgfx { namespace vk
{
	RendererContextI* rendererCreate(const Init& _init)
	{
		BX_UNUSED(_init);
		return NULL;
	}

	void rendererDestroy()
	{
	}
} /* namespace vk */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_VULKAN

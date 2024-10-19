/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_VULKAN
#	include <bx/pixelformat.h>
#	include "renderer_vk.h"
#	include "shader_spirv.h"

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
#define $_ VK_COMPONENT_SWIZZLE_IDENTITY
#define $0 VK_COMPONENT_SWIZZLE_ZERO
#define $1 VK_COMPONENT_SWIZZLE_ONE
#define $R VK_COMPONENT_SWIZZLE_R
#define $G VK_COMPONENT_SWIZZLE_G
#define $B VK_COMPONENT_SWIZZLE_B
#define $A VK_COMPONENT_SWIZZLE_A
		{ VK_FORMAT_BC1_RGB_UNORM_BLOCK,       VK_FORMAT_BC1_RGB_UNORM_BLOCK,      VK_FORMAT_UNDEFINED,           VK_FORMAT_BC1_RGB_SRGB_BLOCK,       { $_, $_, $_, $_ } }, // BC1
		{ VK_FORMAT_BC2_UNORM_BLOCK,           VK_FORMAT_BC2_UNORM_BLOCK,          VK_FORMAT_UNDEFINED,           VK_FORMAT_BC2_SRGB_BLOCK,           { $_, $_, $_, $_ } }, // BC2
		{ VK_FORMAT_BC3_UNORM_BLOCK,           VK_FORMAT_BC3_UNORM_BLOCK,          VK_FORMAT_UNDEFINED,           VK_FORMAT_BC3_SRGB_BLOCK,           { $_, $_, $_, $_ } }, // BC3
		{ VK_FORMAT_BC4_UNORM_BLOCK,           VK_FORMAT_BC4_UNORM_BLOCK,          VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // BC4
		{ VK_FORMAT_BC5_UNORM_BLOCK,           VK_FORMAT_BC5_UNORM_BLOCK,          VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // BC5
		{ VK_FORMAT_BC6H_SFLOAT_BLOCK,         VK_FORMAT_BC6H_SFLOAT_BLOCK,        VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // BC6H
		{ VK_FORMAT_BC7_UNORM_BLOCK,           VK_FORMAT_BC7_UNORM_BLOCK,          VK_FORMAT_UNDEFINED,           VK_FORMAT_BC7_SRGB_BLOCK,           { $_, $_, $_, $_ } }, // BC7
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // ETC1
		{ VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK,   VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK,   { $_, $_, $_, $_ } }, // ETC2
		{ VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK, VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK, { $_, $_, $_, $_ } }, // ETC2A
		{ VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK, VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK, { $_, $_, $_, $_ } }, // ETC2A1
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // PTC12
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // PTC14
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // PTC12A
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // PTC14A
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // PTC22
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // PTC24
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // ATC
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // ATCE
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // ATCI
		{ VK_FORMAT_ASTC_4x4_UNORM_BLOCK,      VK_FORMAT_ASTC_4x4_UNORM_BLOCK,     VK_FORMAT_UNDEFINED,           VK_FORMAT_ASTC_4x4_SRGB_BLOCK,      { $_, $_, $_, $_ } }, // ASTC4x4
		{ VK_FORMAT_ASTC_5x4_UNORM_BLOCK,      VK_FORMAT_ASTC_5x4_UNORM_BLOCK,     VK_FORMAT_UNDEFINED,           VK_FORMAT_ASTC_5x4_SRGB_BLOCK,      { $_, $_, $_, $_ } }, // ASTC5x4
		{ VK_FORMAT_ASTC_5x5_UNORM_BLOCK,      VK_FORMAT_ASTC_5x5_UNORM_BLOCK,     VK_FORMAT_UNDEFINED,           VK_FORMAT_ASTC_5x5_SRGB_BLOCK,      { $_, $_, $_, $_ } }, // ASTC5x5
		{ VK_FORMAT_ASTC_6x5_UNORM_BLOCK,      VK_FORMAT_ASTC_6x5_UNORM_BLOCK,     VK_FORMAT_UNDEFINED,           VK_FORMAT_ASTC_6x5_SRGB_BLOCK,      { $_, $_, $_, $_ } }, // ASTC6x5
		{ VK_FORMAT_ASTC_6x6_UNORM_BLOCK,      VK_FORMAT_ASTC_6x6_UNORM_BLOCK,     VK_FORMAT_UNDEFINED,           VK_FORMAT_ASTC_6x6_SRGB_BLOCK,      { $_, $_, $_, $_ } }, // ASTC6x6
		{ VK_FORMAT_ASTC_8x5_UNORM_BLOCK,      VK_FORMAT_ASTC_8x5_UNORM_BLOCK,     VK_FORMAT_UNDEFINED,           VK_FORMAT_ASTC_8x5_SRGB_BLOCK,      { $_, $_, $_, $_ } }, // ASTC8x5
		{ VK_FORMAT_ASTC_8x6_UNORM_BLOCK,      VK_FORMAT_ASTC_8x6_UNORM_BLOCK,     VK_FORMAT_UNDEFINED,           VK_FORMAT_ASTC_8x6_SRGB_BLOCK,      { $_, $_, $_, $_ } }, // ASTC8x6
		{ VK_FORMAT_ASTC_8x8_UNORM_BLOCK,      VK_FORMAT_ASTC_8x8_UNORM_BLOCK,     VK_FORMAT_UNDEFINED,           VK_FORMAT_ASTC_8x8_SRGB_BLOCK,      { $_, $_, $_, $_ } }, // ASTC8x8
		{ VK_FORMAT_ASTC_10x5_UNORM_BLOCK,     VK_FORMAT_ASTC_10x5_UNORM_BLOCK,    VK_FORMAT_UNDEFINED,           VK_FORMAT_ASTC_10x5_SRGB_BLOCK,     { $_, $_, $_, $_ } }, // ASTC10x5
		{ VK_FORMAT_ASTC_10x6_UNORM_BLOCK,     VK_FORMAT_ASTC_10x6_UNORM_BLOCK,    VK_FORMAT_UNDEFINED,           VK_FORMAT_ASTC_10x6_SRGB_BLOCK,     { $_, $_, $_, $_ } }, // ASTC10x6
		{ VK_FORMAT_ASTC_10x8_UNORM_BLOCK,     VK_FORMAT_ASTC_10x8_UNORM_BLOCK,    VK_FORMAT_UNDEFINED,           VK_FORMAT_ASTC_10x8_SRGB_BLOCK,     { $_, $_, $_, $_ } }, // ASTC10x8
		{ VK_FORMAT_ASTC_10x10_UNORM_BLOCK,    VK_FORMAT_ASTC_10x10_UNORM_BLOCK,   VK_FORMAT_UNDEFINED,           VK_FORMAT_ASTC_10x10_SRGB_BLOCK,    { $_, $_, $_, $_ } }, // ASTC10x10
		{ VK_FORMAT_ASTC_12x10_UNORM_BLOCK,    VK_FORMAT_ASTC_12x10_UNORM_BLOCK,   VK_FORMAT_UNDEFINED,           VK_FORMAT_ASTC_12x10_SRGB_BLOCK,    { $_, $_, $_, $_ } }, // ASTC12x10
		{ VK_FORMAT_ASTC_12x12_UNORM_BLOCK,    VK_FORMAT_ASTC_12x12_UNORM_BLOCK,   VK_FORMAT_UNDEFINED,           VK_FORMAT_ASTC_12x12_SRGB_BLOCK,    { $_, $_, $_, $_ } }, // ASTC12x12
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // Unknown
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // R1
		{ VK_FORMAT_R8_UNORM,                  VK_FORMAT_R8_UNORM,                 VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $0, $0, $0, $R } }, // A8
		{ VK_FORMAT_R8_UNORM,                  VK_FORMAT_R8_UNORM,                 VK_FORMAT_UNDEFINED,           VK_FORMAT_R8_SRGB,                  { $_, $_, $_, $_ } }, // R8
		{ VK_FORMAT_R8_SINT,                   VK_FORMAT_R8_SINT,                  VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // R8I
		{ VK_FORMAT_R8_UINT,                   VK_FORMAT_R8_UINT,                  VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // R8U
		{ VK_FORMAT_R8_SNORM,                  VK_FORMAT_R8_SNORM,                 VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // R8S
		{ VK_FORMAT_R16_UNORM,                 VK_FORMAT_R16_UNORM,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // R16
		{ VK_FORMAT_R16_SINT,                  VK_FORMAT_R16_SINT,                 VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // R16I
		{ VK_FORMAT_R16_UINT,                  VK_FORMAT_R16_UINT,                 VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // R16U
		{ VK_FORMAT_R16_SFLOAT,                VK_FORMAT_R16_SFLOAT,               VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // R16F
		{ VK_FORMAT_R16_SNORM,                 VK_FORMAT_R16_SNORM,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // R16S
		{ VK_FORMAT_R32_SINT,                  VK_FORMAT_R32_SINT,                 VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // R32I
		{ VK_FORMAT_R32_UINT,                  VK_FORMAT_R32_UINT,                 VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // R32U
		{ VK_FORMAT_R32_SFLOAT,                VK_FORMAT_R32_SFLOAT,               VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // R32F
		{ VK_FORMAT_R8G8_UNORM,                VK_FORMAT_R8G8_UNORM,               VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8_SRGB,                { $_, $_, $_, $_ } }, // RG8
		{ VK_FORMAT_R8G8_SINT,                 VK_FORMAT_R8G8_SINT,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RG8I
		{ VK_FORMAT_R8G8_UINT,                 VK_FORMAT_R8G8_UINT,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RG8U
		{ VK_FORMAT_R8G8_SNORM,                VK_FORMAT_R8G8_SNORM,               VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RG8S
		{ VK_FORMAT_R16G16_UNORM,              VK_FORMAT_R16G16_UNORM,             VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RG16
		{ VK_FORMAT_R16G16_SINT,               VK_FORMAT_R16G16_SINT,              VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RG16I
		{ VK_FORMAT_R16G16_UINT,               VK_FORMAT_R16G16_UINT,              VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RG16U
		{ VK_FORMAT_R16G16_SFLOAT,             VK_FORMAT_R16G16_SFLOAT,            VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RG16F
		{ VK_FORMAT_R16G16_SNORM,              VK_FORMAT_R16G16_SNORM,             VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RG16S
		{ VK_FORMAT_R32G32_SINT,               VK_FORMAT_R32G32_SINT,              VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RG32I
		{ VK_FORMAT_R32G32_UINT,               VK_FORMAT_R32G32_UINT,              VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RG32U
		{ VK_FORMAT_R32G32_SFLOAT,             VK_FORMAT_R32G32_SFLOAT,            VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RG32F
		{ VK_FORMAT_R8G8B8_UNORM,              VK_FORMAT_R8G8B8_UNORM,             VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8B8_SRGB,              { $_, $_, $_, $_ } }, // RGB8
		{ VK_FORMAT_R8G8B8_SINT,               VK_FORMAT_R8G8B8_SINT,              VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8B8_SRGB,              { $_, $_, $_, $_ } }, // RGB8I
		{ VK_FORMAT_R8G8B8_UINT,               VK_FORMAT_R8G8B8_UINT,              VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8B8_SRGB,              { $_, $_, $_, $_ } }, // RGB8U
		{ VK_FORMAT_R8G8B8_SNORM,              VK_FORMAT_R8G8B8_SNORM,             VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RGB8S
		{ VK_FORMAT_E5B9G9R9_UFLOAT_PACK32,    VK_FORMAT_E5B9G9R9_UFLOAT_PACK32,   VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RGB9E5F
		{ VK_FORMAT_B8G8R8A8_UNORM,            VK_FORMAT_B8G8R8A8_UNORM,           VK_FORMAT_UNDEFINED,           VK_FORMAT_B8G8R8A8_SRGB,            { $_, $_, $_, $_ } }, // BGRA8
		{ VK_FORMAT_R8G8B8A8_UNORM,            VK_FORMAT_R8G8B8A8_UNORM,           VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8B8A8_SRGB,            { $_, $_, $_, $_ } }, // RGBA8
		{ VK_FORMAT_R8G8B8A8_SINT,             VK_FORMAT_R8G8B8A8_SINT,            VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8B8A8_SRGB,            { $_, $_, $_, $_ } }, // RGBA8I
		{ VK_FORMAT_R8G8B8A8_UINT,             VK_FORMAT_R8G8B8A8_UINT,            VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8B8A8_SRGB,            { $_, $_, $_, $_ } }, // RGBA8U
		{ VK_FORMAT_R8G8B8A8_SNORM,            VK_FORMAT_R8G8B8A8_SNORM,           VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RGBA8S
		{ VK_FORMAT_R16G16B16A16_UNORM,        VK_FORMAT_R16G16B16A16_UNORM,       VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RGBA16
		{ VK_FORMAT_R16G16B16A16_SINT,         VK_FORMAT_R16G16B16A16_SINT,        VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RGBA16I
		{ VK_FORMAT_R16G16B16A16_UINT,         VK_FORMAT_R16G16B16A16_UINT,        VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RGBA16U
		{ VK_FORMAT_R16G16B16A16_SFLOAT,       VK_FORMAT_R16G16B16A16_SFLOAT,      VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RGBA16F
		{ VK_FORMAT_R16G16B16A16_SNORM,        VK_FORMAT_R16G16B16A16_SNORM,       VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RGBA16S
		{ VK_FORMAT_R32G32B32A32_SINT,         VK_FORMAT_R32G32B32A32_SINT,        VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RGBA32I
		{ VK_FORMAT_R32G32B32A32_UINT,         VK_FORMAT_R32G32B32A32_UINT,        VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RGBA32U
		{ VK_FORMAT_R32G32B32A32_SFLOAT,       VK_FORMAT_R32G32B32A32_SFLOAT,      VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RGBA32F
		{ VK_FORMAT_R5G6B5_UNORM_PACK16,       VK_FORMAT_R5G6B5_UNORM_PACK16,      VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // B5G6R5
		{ VK_FORMAT_B5G6R5_UNORM_PACK16,       VK_FORMAT_B5G6R5_UNORM_PACK16,      VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // R5G6B5
		{ VK_FORMAT_B4G4R4A4_UNORM_PACK16,     VK_FORMAT_B4G4R4A4_UNORM_PACK16,    VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $G, $R, $A, $B } }, // BGRA4
		{ VK_FORMAT_R4G4B4A4_UNORM_PACK16,     VK_FORMAT_R4G4B4A4_UNORM_PACK16,    VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $A, $B, $G, $R } }, // RGBA4
		{ VK_FORMAT_A1R5G5B5_UNORM_PACK16,     VK_FORMAT_A1R5G5B5_UNORM_PACK16,    VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // BGR5A1
		{ VK_FORMAT_A1R5G5B5_UNORM_PACK16,     VK_FORMAT_A1R5G5B5_UNORM_PACK16,    VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $B, $G, $R, $A } }, // RGB5A1
		{ VK_FORMAT_A2R10G10B10_UNORM_PACK32,  VK_FORMAT_A2R10G10B10_UNORM_PACK32, VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $B, $G, $R, $A } }, // RGB10A2
		{ VK_FORMAT_B10G11R11_UFLOAT_PACK32,   VK_FORMAT_B10G11R11_UFLOAT_PACK32,  VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // RG11B10F
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // UnknownDepth
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_R16_UNORM,                VK_FORMAT_D16_UNORM,           VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // D16
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_R32_SFLOAT,               VK_FORMAT_D32_SFLOAT_S8_UINT,  VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // D24
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_R32_SFLOAT,               VK_FORMAT_D32_SFLOAT_S8_UINT,  VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // D24S8
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_R32_SFLOAT,               VK_FORMAT_D32_SFLOAT_S8_UINT,  VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // D32
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_R32_SFLOAT,               VK_FORMAT_D32_SFLOAT,          VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // D16F
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_R32_SFLOAT,               VK_FORMAT_D32_SFLOAT,          VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // D24F
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_R32_SFLOAT,               VK_FORMAT_D32_SFLOAT,          VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // D32F
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_R8_UINT,                  VK_FORMAT_S8_UINT,             VK_FORMAT_UNDEFINED,                { $_, $_, $_, $_ } }, // D0S8
#undef $_
#undef $0
#undef $1
#undef $R
#undef $G
#undef $B
#undef $A
	};
	BX_STATIC_ASSERT(TextureFormat::Count == BX_COUNTOF(s_textureFormat) );

	struct ImageTest
	{
		VkImageType        type;
		VkImageUsageFlags  usage;
		VkImageCreateFlags flags;
		uint32_t           formatCaps[2];
	};

	static const ImageTest s_imageTest[] =
	{
		{ VK_IMAGE_TYPE_2D, VK_IMAGE_USAGE_SAMPLED_BIT,                  0,                                   { BGFX_CAPS_FORMAT_TEXTURE_2D,          BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB   } },
		{ VK_IMAGE_TYPE_3D, VK_IMAGE_USAGE_SAMPLED_BIT,                  0,                                   { BGFX_CAPS_FORMAT_TEXTURE_3D,          BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB   } },
		{ VK_IMAGE_TYPE_2D, VK_IMAGE_USAGE_SAMPLED_BIT,                  VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT, { BGFX_CAPS_FORMAT_TEXTURE_CUBE,        BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB } },
		{ VK_IMAGE_TYPE_2D, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,         0,                                   { BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER, 0                                  } },
		{ VK_IMAGE_TYPE_2D, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, 0,                                   { BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER, 0                                  } },
		{ VK_IMAGE_TYPE_2D, VK_IMAGE_USAGE_STORAGE_BIT,                  0,                                   { BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ,  0                                  } },
		{ VK_IMAGE_TYPE_2D, VK_IMAGE_USAGE_STORAGE_BIT,                  0,                                   { BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE, 0                                  } },
	};

	struct LayerInfo
	{
		bool m_supported;
		bool m_initialize;
	};

	struct Layer
	{
		enum Enum
		{
			VK_LAYER_KHRONOS_validation,
			VK_LAYER_LUNARG_standard_validation,

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
		{ "VK_LAYER_KHRONOS_validation",         1, { false, false }, { false, false } },
		{ "VK_LAYER_LUNARG_standard_validation", 1, { false, false }, { false, false } },
		{ "",                                    0, { false, false }, { false, false } },
	};
	BX_STATIC_ASSERT(Layer::Count == BX_COUNTOF(s_layer)-1);

	void updateLayer(const char* _name, uint32_t _version, bool _instanceLayer)
	{
		bx::StringView layerName(_name);

		for (uint32_t ii = 0; ii < Layer::Count; ++ii)
		{
			Layer& layer = s_layer[ii];
			LayerInfo& layerInfo = _instanceLayer
				? layer.m_instance
				: layer.m_device
				;

			if (!layerInfo.m_supported && layerInfo.m_initialize)
			{
				if (       0 == bx::strCmp(layerName, layer.m_name)
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
			EXT_conservative_rasterization,
			EXT_custom_border_color,
			EXT_debug_report,
			EXT_debug_utils,
			EXT_line_rasterization,
			EXT_memory_budget,
			EXT_shader_viewport_index_layer,
			KHR_draw_indirect_count,
			KHR_get_physical_device_properties2,

#	if BX_PLATFORM_ANDROID
			KHR_android_surface,
#	elif BX_PLATFORM_LINUX
			KHR_wayland_surface,
			KHR_xlib_surface,
			KHR_xcb_surface,
#	elif BX_PLATFORM_WINDOWS
			KHR_win32_surface,
#	elif BX_PLATFORM_OSX
			MVK_macos_surface,
#	elif BX_PLATFORM_NX
			NN_vi_surface,
#	endif

			Count
		};

		const char* m_name;
		uint32_t    m_minVersion;
		bool        m_instanceExt;
		bool        m_supported;
		bool        m_initialize;
		Layer::Enum m_layer;
	};

	// Extension registry
	//
	static Extension s_extension[] =
	{
		{ "VK_EXT_conservative_rasterization",      1, false, false, true,                                                          Layer::Count },
		{ "VK_EXT_custom_border_color",             1, false, false, true,                                                          Layer::Count },
		{ "VK_EXT_debug_report",                    1, false, false, false,                                                         Layer::Count },
		{ "VK_EXT_debug_utils",                     1, false, false, BGFX_CONFIG_DEBUG_OBJECT_NAME || BGFX_CONFIG_DEBUG_ANNOTATION, Layer::Count },
		{ "VK_EXT_line_rasterization",              1, false, false, true,                                                          Layer::Count },
		{ "VK_EXT_memory_budget",                   1, false, false, true,                                                          Layer::Count },
		{ "VK_EXT_shader_viewport_index_layer",     1, false, false, true,                                                          Layer::Count },
		{ "VK_KHR_draw_indirect_count",             1, false, false, true,                                                          Layer::Count },
		{ "VK_KHR_get_physical_device_properties2", 1, false, false, true,                                                          Layer::Count },
#	if BX_PLATFORM_ANDROID
		{ VK_KHR_ANDROID_SURFACE_EXTENSION_NAME,    1, false, false, true,                                                          Layer::Count },
#	elif BX_PLATFORM_LINUX
		{ VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME,    1, false, false, true,                                                          Layer::Count },
		{ VK_KHR_XLIB_SURFACE_EXTENSION_NAME,       1, false, false, true,                                                          Layer::Count },
		{ VK_KHR_XCB_SURFACE_EXTENSION_NAME,        1, false, false, true,                                                          Layer::Count },
#	elif BX_PLATFORM_WINDOWS
		{ VK_KHR_WIN32_SURFACE_EXTENSION_NAME,      1, false, false, true,                                                          Layer::Count },
#	elif BX_PLATFORM_OSX
		{ VK_MVK_MACOS_SURFACE_EXTENSION_NAME,      1, false, false, true,                                                          Layer::Count },
#	elif BX_PLATFORM_NX
		{ VK_NN_VI_SURFACE_EXTENSION_NAME,          1, false, false, true,                                                          Layer::Count },
#	endif
	};
	BX_STATIC_ASSERT(Extension::Count == BX_COUNTOF(s_extension) );

	bool updateExtension(const char* _name, uint32_t _version, bool _instanceExt, Extension _extensions[Extension::Count])
	{
		bool supported = false;
		if (BX_ENABLED(BGFX_CONFIG_RENDERER_USE_EXTENSIONS) )
		{
			const bx::StringView ext(_name);
			for (uint32_t ii = 0; ii < Extension::Count; ++ii)
			{
				Extension& extension = _extensions[ii];
				const LayerInfo& layerInfo = _instanceExt
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
		return s_deviceTypeName[bx::min<int32_t>(_type, BX_COUNTOF(s_deviceTypeName)-1 )];
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

	constexpr size_t kMinAlignment = 16;

	static void* VKAPI_PTR allocationFunction(void* _userData, size_t _size, size_t _alignment, VkSystemAllocationScope _allocationScope)
	{
		bx::AllocatorI* allocator = (bx::AllocatorI*)_userData;
		return bx::alignedAlloc(allocator, _size, bx::max(kMinAlignment, _alignment), bx::Location(s_allocScopeName[_allocationScope], 0) );
	}

	static void* VKAPI_PTR reallocationFunction(void* _userData, void* _ptr, size_t _size, size_t _alignment, VkSystemAllocationScope _allocationScope)
	{
		bx::AllocatorI* allocator = (bx::AllocatorI*)_userData;

		BX_UNUSED(_userData);
		if (0 == _size)
		{
			bx::alignedFree(allocator, _ptr, 0);
			return NULL;
		}

		return bx::alignedRealloc(allocator, _ptr, _size, bx::max(kMinAlignment, _alignment), bx::Location(s_allocScopeName[_allocationScope], 0) );
	}

	static void VKAPI_PTR freeFunction(void* _userData, void* _ptr)
	{
		if (NULL == _ptr)
		{
			return;
		}

		bx::AllocatorI* allocator = (bx::AllocatorI*)_userData;
		bx::alignedFree(allocator, _ptr, kMinAlignment);
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
		  VkDebugReportFlagsEXT _flags
		, VkDebugReportObjectTypeEXT _objectType
		, uint64_t _object
		, size_t _location
		, int32_t _messageCode
		, const char* _layerPrefix
		, const char* _message
		, void* _userData
		)
	{
		BX_UNUSED(_flags, _objectType, _object, _location, _messageCode, _layerPrefix, _message, _userData, s_debugReportObjectType);

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

		return VK_FALSE;
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

	void dumpExtensions(VkPhysicalDevice _physicalDevice, Extension _extensions[Extension::Count])
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
				VkExtensionProperties* extensionProperties = (VkExtensionProperties*)bx::alloc(g_allocator, numExtensionProperties * sizeof(VkExtensionProperties) );
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
						, _extensions
						);

					BX_TRACE("\tv%-3d %s%s"
						, extensionProperties[extension].specVersion
						, extensionProperties[extension].extensionName
						, supported ? " (supported)" : "", extensionProperties[extension].extensionName
						);

					BX_UNUSED(supported);
				}

				bx::free(g_allocator, extensionProperties);
			}
		}

		// Layer extensions.
		uint32_t numLayerProperties;
		VkResult result = enumerateLayerProperties(_physicalDevice, &numLayerProperties, NULL);

		if (VK_SUCCESS == result
		&&  0 < numLayerProperties)
		{
			VkLayerProperties* layerProperties = (VkLayerProperties*)bx::alloc(g_allocator, numLayerProperties * sizeof(VkLayerProperties) );
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
					VkExtensionProperties* extensionProperties = (VkExtensionProperties*)bx::alloc(g_allocator, numExtensionProperties * sizeof(VkExtensionProperties) );
					result = enumerateExtensionProperties(_physicalDevice
						, layerProperties[layer].layerName
						, &numExtensionProperties
						, extensionProperties
						);

					for (uint32_t extension = 0; extension < numExtensionProperties; ++extension)
					{
						const bool supported = updateExtension(
							  extensionProperties[extension].extensionName
							, extensionProperties[extension].specVersion
							, VK_NULL_HANDLE == _physicalDevice
							, _extensions
							);

						BX_TRACE("%c\t\t%s (s: 0x%08x)"
							, indent
							, extensionProperties[extension].extensionName
							, extensionProperties[extension].specVersion
							, supported ? " (supported)" : "", extensionProperties[extension].extensionName
							);

						BX_UNUSED(supported);
					}

					bx::free(g_allocator, extensionProperties);
				}
			}

			bx::free(g_allocator, layerProperties);
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
			VKENUM(VK_ERROR_OUT_OF_POOL_MEMORY);
			VKENUM(VK_ERROR_FRAGMENTED_POOL);
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
	constexpr VkObjectType getType();

	template<> VkObjectType getType<VkBuffer             >() { return VK_OBJECT_TYPE_BUFFER;                }
	template<> VkObjectType getType<VkCommandPool        >() { return VK_OBJECT_TYPE_COMMAND_POOL;          }
	template<> VkObjectType getType<VkDescriptorPool     >() { return VK_OBJECT_TYPE_DESCRIPTOR_POOL;       }
	template<> VkObjectType getType<VkDescriptorSet      >() { return VK_OBJECT_TYPE_DESCRIPTOR_SET;        }
	template<> VkObjectType getType<VkDescriptorSetLayout>() { return VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT; }
	template<> VkObjectType getType<VkDeviceMemory       >() { return VK_OBJECT_TYPE_DEVICE_MEMORY;         }
	template<> VkObjectType getType<VkFence              >() { return VK_OBJECT_TYPE_FENCE;                 }
	template<> VkObjectType getType<VkFramebuffer        >() { return VK_OBJECT_TYPE_FRAMEBUFFER;           }
	template<> VkObjectType getType<VkImage              >() { return VK_OBJECT_TYPE_IMAGE;                 }
	template<> VkObjectType getType<VkImageView          >() { return VK_OBJECT_TYPE_IMAGE_VIEW;            }
	template<> VkObjectType getType<VkPipeline           >() { return VK_OBJECT_TYPE_PIPELINE;              }
	template<> VkObjectType getType<VkPipelineCache      >() { return VK_OBJECT_TYPE_PIPELINE_CACHE;        }
	template<> VkObjectType getType<VkPipelineLayout     >() { return VK_OBJECT_TYPE_PIPELINE_LAYOUT;       }
	template<> VkObjectType getType<VkQueryPool          >() { return VK_OBJECT_TYPE_QUERY_POOL;            }
	template<> VkObjectType getType<VkRenderPass         >() { return VK_OBJECT_TYPE_RENDER_PASS;           }
	template<> VkObjectType getType<VkSampler            >() { return VK_OBJECT_TYPE_SAMPLER;               }
	template<> VkObjectType getType<VkSemaphore          >() { return VK_OBJECT_TYPE_SEMAPHORE;             }
	template<> VkObjectType getType<VkShaderModule       >() { return VK_OBJECT_TYPE_SHADER_MODULE;         }
	template<> VkObjectType getType<VkSurfaceKHR         >() { return VK_OBJECT_TYPE_SURFACE_KHR;           }
	template<> VkObjectType getType<VkSwapchainKHR       >() { return VK_OBJECT_TYPE_SWAPCHAIN_KHR;         }


	template<typename Ty>
	static BX_NO_INLINE void setDebugObjectName(VkDevice _device, Ty _object, const char* _format, ...)
	{
		if (BX_ENABLED(BGFX_CONFIG_DEBUG_OBJECT_NAME)
		&&  s_extension[Extension::EXT_debug_utils].m_supported)
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

	void setMemoryBarrier(
		  VkCommandBuffer _commandBuffer
		, VkPipelineStageFlags _srcStages
		, VkPipelineStageFlags _dstStages
		)
	{
		VkMemoryBarrier mb;
		mb.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
		mb.pNext = NULL;
		mb.srcAccessMask = VK_ACCESS_MEMORY_WRITE_BIT;
		mb.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT;

		vkCmdPipelineBarrier(
			  _commandBuffer
			, _srcStages
			, _dstStages
			, 0
			, 1
			, &mb
			, 0
			, NULL
			, 0
			, NULL
			);
	}

	void setImageMemoryBarrier(
		  VkCommandBuffer _commandBuffer
		, VkImage _image
		, VkImageAspectFlags _aspectMask
		, VkImageLayout _oldLayout
		, VkImageLayout _newLayout
		, uint32_t _baseMipLevel = 0
		, uint32_t _levelCount = VK_REMAINING_MIP_LEVELS
		, uint32_t _baseArrayLayer = 0
		, uint32_t _layerCount = VK_REMAINING_ARRAY_LAYERS
		)
	{
		BX_ASSERT(true
			&& _newLayout != VK_IMAGE_LAYOUT_UNDEFINED
			&& _newLayout != VK_IMAGE_LAYOUT_PREINITIALIZED
			, "_newLayout cannot use VK_IMAGE_LAYOUT_UNDEFINED or VK_IMAGE_LAYOUT_PREINITIALIZED."
			);

		constexpr VkPipelineStageFlags depthStageMask = 0
			| VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT
			| VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT
			;

		constexpr VkPipelineStageFlags sampledStageMask = 0
			| VK_PIPELINE_STAGE_VERTEX_SHADER_BIT
			| VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT
			| VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT
			;

		VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;

		VkAccessFlags srcAccessMask = 0;
		VkAccessFlags dstAccessMask = 0;

		switch (_oldLayout)
		{
		case VK_IMAGE_LAYOUT_UNDEFINED:
			break;

		case VK_IMAGE_LAYOUT_GENERAL:
			srcStageMask  = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
			srcAccessMask = VK_ACCESS_MEMORY_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
			srcStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
			srcStageMask  = depthStageMask;
			srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL:
			srcStageMask = depthStageMask | sampledStageMask;
			break;

		case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
			srcStageMask = sampledStageMask;
			break;

		case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
			srcStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
			break;

		case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
			srcStageMask  = VK_PIPELINE_STAGE_TRANSFER_BIT;
			srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_PREINITIALIZED:
			srcStageMask  = VK_PIPELINE_STAGE_HOST_BIT;
			srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
			break;

		default:
			BX_ASSERT(false, "Unknown image layout.");
			break;
		}

		switch (_newLayout)
		{
		case VK_IMAGE_LAYOUT_GENERAL:
			dstStageMask  = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
			dstAccessMask = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
			dstStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
			dstStageMask  = depthStageMask;
			dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL:
			dstStageMask  = depthStageMask | sampledStageMask;
			dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
			dstStageMask  = sampledStageMask;
			dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
			dstStageMask  = VK_PIPELINE_STAGE_TRANSFER_BIT;
			dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
			break;

		case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
			dstStageMask  = VK_PIPELINE_STAGE_TRANSFER_BIT;
			dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			break;

		case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
			// vkQueuePresentKHR performs automatic visibility operations
			break;

		default:
			BX_ASSERT(false, "Unknown image layout.");
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
		imb.subresourceRange.baseMipLevel   = _baseMipLevel;
		imb.subresourceRange.levelCount     = _levelCount;
		imb.subresourceRange.baseArrayLayer = _baseArrayLayer;
		imb.subresourceRange.layerCount     = _layerCount;
		vkCmdPipelineBarrier(
			  _commandBuffer
			, srcStageMask
			, dstStageMask
			, 0
			, 0
			, NULL
			, 0
			, NULL
			, 1
			, &imb
			);
	}

#define MAX_DESCRIPTOR_SETS (1024 * BGFX_CONFIG_MAX_FRAME_LATENCY)

	struct RendererContextVK : public RendererContextI
	{
		RendererContextVK()
			: m_allocatorCb(NULL)
			, m_renderDocDll(NULL)
			, m_vulkan1Dll(NULL)
			, m_maxAnisotropy(1.0f)
			, m_depthClamp(false)
			, m_wireframe(false)
			, m_captureBuffer(VK_NULL_HANDLE)
			, m_captureMemory(VK_NULL_HANDLE)
			, m_captureSize(0)
		{
		}

		~RendererContextVK()
		{
		}

		bool init(const Init& _init)
		{
			struct ErrorState
			{
				enum Enum
				{
					Default,
					LoadedVulkan1,
					InstanceCreated,
					DeviceCreated,
					CommandQueueCreated,
					SwapChainCreated,
					DescriptorCreated,
					TimerQueryCreated,
				};
			};

			ErrorState::Enum errorState = ErrorState::Default;

			const bool headless = NULL == g_platformData.nwh;

			const void* nextFeatures = NULL;
			VkPhysicalDeviceLineRasterizationFeaturesEXT lineRasterizationFeatures;
			VkPhysicalDeviceCustomBorderColorFeaturesEXT customBorderColorFeatures;

			bx::memSet(&lineRasterizationFeatures, 0, sizeof(lineRasterizationFeatures) );
			bx::memSet(&customBorderColorFeatures, 0, sizeof(customBorderColorFeatures) );

			m_fbh.idx = kInvalidHandle;
			bx::memSet(m_uniforms, 0, sizeof(m_uniforms) );
			bx::memSet(&m_resolution, 0, sizeof(m_resolution) );

			bool imported = true;
			VkResult result;
			m_globalQueueFamily = UINT32_MAX;

			if (_init.debug
			||  _init.profile)
			{
				m_renderDocDll = loadRenderDoc();
			}

			setGraphicsDebuggerPresent(NULL != m_renderDocDll);

			m_vulkan1Dll = bx::dlopen(
#if BX_PLATFORM_WINDOWS
				"vulkan-1.dll"
#elif BX_PLATFORM_ANDROID
				"libvulkan.so"
#elif BX_PLATFORM_OSX
				"libMoltenVK.dylib"
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
				s_layer[Layer::VK_LAYER_LUNARG_standard_validation].m_device.m_initialize   = _init.debug;
				s_layer[Layer::VK_LAYER_LUNARG_standard_validation].m_instance.m_initialize = _init.debug;
				s_layer[Layer::VK_LAYER_KHRONOS_validation        ].m_device.m_initialize   = _init.debug;
				s_layer[Layer::VK_LAYER_KHRONOS_validation        ].m_instance.m_initialize = _init.debug;

				s_extension[Extension::EXT_debug_report].m_initialize = _init.debug;

				s_extension[Extension::EXT_shader_viewport_index_layer].m_initialize = !!(_init.capabilities & BGFX_CAPS_VIEWPORT_LAYER_ARRAY);
				s_extension[Extension::EXT_conservative_rasterization ].m_initialize = !!(_init.capabilities & BGFX_CAPS_CONSERVATIVE_RASTER );
				s_extension[Extension::KHR_draw_indirect_count        ].m_initialize = !!(_init.capabilities & BGFX_CAPS_DRAW_INDIRECT_COUNT );

				dumpExtensions(VK_NULL_HANDLE, s_extension);

				if (s_layer[Layer::VK_LAYER_KHRONOS_validation].m_device.m_supported
				||  s_layer[Layer::VK_LAYER_KHRONOS_validation].m_instance.m_supported)
				{
					s_layer[Layer::VK_LAYER_LUNARG_standard_validation].m_device.m_supported   = false;
					s_layer[Layer::VK_LAYER_LUNARG_standard_validation].m_instance.m_supported = false;
				}

				uint32_t numEnabledLayers = 0;
				const char* enabledLayer[Layer::Count];

				BX_TRACE("Enabled instance layers:");

				for (uint32_t ii = 0; ii < Layer::Count; ++ii)
				{
					const Layer& layer = s_layer[ii];

					if (layer.m_instance.m_supported
					&&  layer.m_instance.m_initialize)
					{
						enabledLayer[numEnabledLayers++] = layer.m_name;
						BX_TRACE("\t%s", layer.m_name);
					}
				}

				uint32_t numEnabledExtensions = 0;
				const char* enabledExtension[Extension::Count + 1];

				if (!headless)
				{
					enabledExtension[numEnabledExtensions++] = VK_KHR_SURFACE_EXTENSION_NAME;
				}

				for (uint32_t ii = 0; ii < Extension::Count; ++ii)
				{
					const Extension& extension = s_extension[ii];
					const LayerInfo& layerInfo = s_layer[extension.m_layer].m_instance;

					const bool layerEnabled = false
						|| extension.m_layer == Layer::Count  || (layerInfo.m_supported && layerInfo.m_initialize)
						;

					if (extension.m_supported
					&&  extension.m_initialize
					&&  extension.m_instanceExt
					&&  layerEnabled)
					{
						enabledExtension[numEnabledExtensions++] = extension.m_name;
					}
				}

				BX_TRACE("Enabled instance extensions:");

				for (uint32_t ii = 0; ii < numEnabledExtensions; ++ii)
				{
					BX_TRACE("\t%s", enabledExtension[ii]);
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
				ici.flags = 0
					| (BX_ENABLED(BX_PLATFORM_OSX) ? VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR : 0)
					;
				ici.pApplicationInfo        = &appInfo;
				ici.enabledLayerCount       = numEnabledLayers;
				ici.ppEnabledLayerNames     = enabledLayer;
				ici.enabledExtensionCount   = numEnabledExtensions;
				ici.ppEnabledExtensionNames = enabledExtension;

				if (BX_ENABLED(BGFX_CONFIG_DEBUG) )
				{
					// Validation layer is calling freeFunction with pointers that are not allocated
					// via callback mechanism. This is bug in validation layer, and work-around
					// would be to keep track of allocated pointers and ignore those that are not
					// allocated by it.
					//
					// Anyhow we just let VK take care of memory, until they fix the issue...
					//
					// s_allocationCb.pUserData = g_allocator;
					// m_allocatorCb = &s_allocationCb;
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

				BX_TRACE("Instance API version: %d.%d.%d"
					, VK_API_VERSION_MAJOR(m_instanceApiVersion)
					, VK_API_VERSION_MINOR(m_instanceApiVersion)
					, VK_API_VERSION_PATCH(m_instanceApiVersion)
					);
				BX_TRACE("Instance variant: %d", VK_API_VERSION_VARIANT(m_instanceApiVersion) );
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

				Extension physicalDeviceExtensions[4][Extension::Count];

				uint32_t physicalDeviceIdx         = UINT32_MAX;
				uint32_t fallbackPhysicalDeviceIdx = UINT32_MAX;

				for (uint32_t ii = 0; ii < numPhysicalDevices; ++ii)
				{
					VkPhysicalDeviceProperties pdp;
					vkGetPhysicalDeviceProperties(physicalDevices[ii], &pdp);

					BX_TRACE("Physical device %d:", ii);
					BX_TRACE("\t          Name: %s", pdp.deviceName);
					BX_TRACE("\t   API version: %d.%d.%d"
						, VK_API_VERSION_MAJOR(pdp.apiVersion)
						, VK_API_VERSION_MINOR(pdp.apiVersion)
						, VK_API_VERSION_PATCH(pdp.apiVersion)
						);
					BX_TRACE("\t   API variant: %d", VK_API_VERSION_VARIANT(pdp.apiVersion) );
					BX_TRACE("\tDriver version: %x", pdp.driverVersion);
					BX_TRACE("\t      VendorId: %x", pdp.vendorID);
					BX_TRACE("\t      DeviceId: %x", pdp.deviceID);
					BX_TRACE("\t          Type: %d", pdp.deviceType);

					if (VK_PHYSICAL_DEVICE_TYPE_CPU == pdp.deviceType)
					{
						pdp.vendorID = BGFX_PCI_ID_SOFTWARE_RASTERIZER;
					}

					g_caps.gpu[ii].vendorId = uint16_t(pdp.vendorID);
					g_caps.gpu[ii].deviceId = uint16_t(pdp.deviceID);
					++g_caps.numGPUs;

					if ( (BGFX_PCI_ID_NONE != g_caps.vendorId ||            0 != g_caps.deviceId)
					&&   (BGFX_PCI_ID_NONE == g_caps.vendorId || pdp.vendorID == g_caps.vendorId)
					&&   (               0 == g_caps.deviceId || pdp.deviceID == g_caps.deviceId) )
					{
						if (pdp.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
						||  pdp.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
						{
							fallbackPhysicalDeviceIdx = ii;
						}

						physicalDeviceIdx = ii;
					}
					else if (UINT32_MAX == physicalDeviceIdx)
					{
						if (pdp.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
						{
							fallbackPhysicalDeviceIdx = ii;
						}
						else if (pdp.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
						{
							physicalDeviceIdx = ii;
						}
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

					bx::memCopy(&physicalDeviceExtensions[ii][0], &s_extension[0], sizeof(s_extension) );
					dumpExtensions(physicalDevices[ii], physicalDeviceExtensions[ii]);
				}

				if (UINT32_MAX == physicalDeviceIdx)
				{
					physicalDeviceIdx = UINT32_MAX == fallbackPhysicalDeviceIdx
						? 0
						: fallbackPhysicalDeviceIdx
						;
				}

				m_physicalDevice = physicalDevices[physicalDeviceIdx];

				bx::memCopy(&s_extension[0], &physicalDeviceExtensions[physicalDeviceIdx][0], sizeof(s_extension) );

				vkGetPhysicalDeviceProperties(m_physicalDevice, &m_deviceProperties);
				g_caps.vendorId = uint16_t(m_deviceProperties.vendorID);
				g_caps.deviceId = uint16_t(m_deviceProperties.deviceID);

				BX_TRACE("Using physical device %d: %s", physicalDeviceIdx, m_deviceProperties.deviceName);

				VkPhysicalDeviceFeatures supportedFeatures;

				if (s_extension[Extension::KHR_get_physical_device_properties2].m_supported)
				{
					VkPhysicalDeviceFeatures2KHR deviceFeatures2;
					deviceFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2_KHR;
					deviceFeatures2.pNext = NULL;

					VkBaseOutStructure* next = (VkBaseOutStructure*)&deviceFeatures2;

					if (s_extension[Extension::EXT_line_rasterization].m_supported)
					{
						next->pNext = (VkBaseOutStructure*)&lineRasterizationFeatures;
						next = (VkBaseOutStructure*)&lineRasterizationFeatures;
						lineRasterizationFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINE_RASTERIZATION_FEATURES_EXT;
						lineRasterizationFeatures.pNext = NULL;
					}

					if (s_extension[Extension::EXT_custom_border_color].m_supported)
					{
						next->pNext = (VkBaseOutStructure*)&customBorderColorFeatures;
						next = (VkBaseOutStructure*)&customBorderColorFeatures;
						customBorderColorFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_FEATURES_EXT;
						customBorderColorFeatures.pNext = NULL;
					}

					nextFeatures = deviceFeatures2.pNext;

					vkGetPhysicalDeviceFeatures2KHR(m_physicalDevice, &deviceFeatures2);
					supportedFeatures = deviceFeatures2.features;
				}
				else
				{
					vkGetPhysicalDeviceFeatures(m_physicalDevice, &supportedFeatures);
				}

				bx::memSet(&m_deviceFeatures, 0, sizeof(m_deviceFeatures) );

				m_deviceFeatures.fullDrawIndexUint32               = supportedFeatures.fullDrawIndexUint32;
				m_deviceFeatures.imageCubeArray                    = supportedFeatures.imageCubeArray            && (_init.capabilities & BGFX_CAPS_TEXTURE_CUBE_ARRAY);
				m_deviceFeatures.independentBlend                  = supportedFeatures.independentBlend          && (_init.capabilities & BGFX_CAPS_BLEND_INDEPENDENT);
				m_deviceFeatures.multiDrawIndirect                 = supportedFeatures.multiDrawIndirect         && (_init.capabilities & BGFX_CAPS_DRAW_INDIRECT);
				m_deviceFeatures.drawIndirectFirstInstance         = supportedFeatures.drawIndirectFirstInstance && (_init.capabilities & BGFX_CAPS_DRAW_INDIRECT);
				m_deviceFeatures.depthClamp                        = supportedFeatures.depthClamp;
				m_deviceFeatures.fillModeNonSolid                  = supportedFeatures.fillModeNonSolid;
				m_deviceFeatures.largePoints                       = supportedFeatures.largePoints;
				m_deviceFeatures.samplerAnisotropy                 = supportedFeatures.samplerAnisotropy;
				m_deviceFeatures.textureCompressionETC2            = supportedFeatures.textureCompressionETC2;
				m_deviceFeatures.textureCompressionBC              = supportedFeatures.textureCompressionBC;
				m_deviceFeatures.vertexPipelineStoresAndAtomics    = supportedFeatures.vertexPipelineStoresAndAtomics;
				m_deviceFeatures.fragmentStoresAndAtomics          = supportedFeatures.fragmentStoresAndAtomics;
				m_deviceFeatures.shaderImageGatherExtended         = supportedFeatures.shaderImageGatherExtended;
				m_deviceFeatures.shaderStorageImageExtendedFormats = supportedFeatures.shaderStorageImageExtendedFormats;
				m_deviceFeatures.shaderClipDistance                = supportedFeatures.shaderClipDistance;
				m_deviceFeatures.shaderCullDistance                = supportedFeatures.shaderCullDistance;
				m_deviceFeatures.shaderResourceMinLod              = supportedFeatures.shaderResourceMinLod;
				m_deviceFeatures.geometryShader                    = supportedFeatures.geometryShader;

				m_lineAASupport = true
					&& s_extension[Extension::EXT_line_rasterization].m_supported
					&& lineRasterizationFeatures.smoothLines
					;

				m_borderColorSupport = true
					&& s_extension[Extension::EXT_custom_border_color].m_supported
					&& customBorderColorFeatures.customBorderColors
					;

				m_timerQuerySupport = m_deviceProperties.limits.timestampComputeAndGraphics;

				const bool indirectDrawSupport = true
					&& m_deviceFeatures.multiDrawIndirect
					&& m_deviceFeatures.drawIndirectFirstInstance
					;

				g_caps.supported |= ( 0
					| BGFX_CAPS_ALPHA_TO_COVERAGE
					| (m_deviceFeatures.independentBlend ? BGFX_CAPS_BLEND_INDEPENDENT : 0)
					| BGFX_CAPS_COMPUTE
					| (indirectDrawSupport ? BGFX_CAPS_DRAW_INDIRECT : 0)
					| BGFX_CAPS_FRAGMENT_DEPTH
					| BGFX_CAPS_IMAGE_RW
					| (m_deviceFeatures.fullDrawIndexUint32 ? BGFX_CAPS_INDEX32 : 0)
					| BGFX_CAPS_INSTANCING
					| BGFX_CAPS_OCCLUSION_QUERY
					| (!headless ? BGFX_CAPS_SWAP_CHAIN : 0)
					| BGFX_CAPS_TEXTURE_2D_ARRAY
					| BGFX_CAPS_TEXTURE_3D
					| BGFX_CAPS_TEXTURE_BLIT
					| BGFX_CAPS_TEXTURE_COMPARE_ALL
					| (m_deviceFeatures.imageCubeArray ? BGFX_CAPS_TEXTURE_CUBE_ARRAY : 0)
					| BGFX_CAPS_TEXTURE_READ_BACK
					| BGFX_CAPS_VERTEX_ATTRIB_HALF
					| BGFX_CAPS_VERTEX_ATTRIB_UINT10
					| BGFX_CAPS_VERTEX_ID
					| (m_deviceFeatures.geometryShader ? BGFX_CAPS_PRIMITIVE_ID : 0)
					);

				g_caps.supported |= 0
					| (s_extension[Extension::EXT_conservative_rasterization ].m_supported ? BGFX_CAPS_CONSERVATIVE_RASTER  : 0)
					| (s_extension[Extension::EXT_shader_viewport_index_layer].m_supported ? BGFX_CAPS_VIEWPORT_LAYER_ARRAY : 0)
					| (s_extension[Extension::KHR_draw_indirect_count        ].m_supported && indirectDrawSupport ? BGFX_CAPS_DRAW_INDIRECT_COUNT : 0)
					;

				const uint32_t maxAttachments = bx::min<uint32_t>(m_deviceProperties.limits.maxFragmentOutputAttachments, m_deviceProperties.limits.maxColorAttachments);

				g_caps.limits.maxTextureSize     = m_deviceProperties.limits.maxImageDimension2D;
				g_caps.limits.maxTextureLayers   = m_deviceProperties.limits.maxImageArrayLayers;
				g_caps.limits.maxFBAttachments   = bx::min<uint32_t>(maxAttachments, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS);
				g_caps.limits.maxTextureSamplers = bx::min<uint32_t>(m_deviceProperties.limits.maxPerStageResources, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS);
				g_caps.limits.maxComputeBindings = bx::min<uint32_t>(m_deviceProperties.limits.maxPerStageResources, BGFX_MAX_COMPUTE_BINDINGS);
				g_caps.limits.maxVertexStreams   = bx::min<uint32_t>(m_deviceProperties.limits.maxVertexInputBindings, BGFX_CONFIG_MAX_VERTEX_STREAMS);

				{
					const VkSampleCountFlags sampleMask = ~0
						& m_deviceProperties.limits.framebufferColorSampleCounts
						& m_deviceProperties.limits.framebufferDepthSampleCounts
						;

					for (uint16_t ii = 0, last = 0; ii < BX_COUNTOF(s_msaa); ii++)
					{
						const VkSampleCountFlags sampleBit = s_msaa[ii].Sample;

						if (sampleBit & sampleMask)
						{
							last = ii;
						}
						else
						{
							s_msaa[ii] = s_msaa[last];
						}
					}
				}

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
							for (uint32_t test = 0; test < BX_COUNTOF(s_imageTest); ++test)
							{
								const ImageTest& it = s_imageTest[test];

								VkImageFormatProperties ifp;
								result = vkGetPhysicalDeviceImageFormatProperties(
									  m_physicalDevice
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

									const bool multisample = VK_SAMPLE_COUNT_1_BIT < ifp.sampleCounts;
									if (it.usage & VK_IMAGE_USAGE_SAMPLED_BIT)
									{
										support |= 0
											| BGFX_CAPS_FORMAT_TEXTURE_VERTEX
											| (multisample ? BGFX_CAPS_FORMAT_TEXTURE_MSAA : 0)
											;
									}

									if (it.usage & (VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT) )
									{
										support |= 0
											| BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN
											| (multisample ? BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA : 0)
											;
									}
								}
							}
						}

						fmt = s_textureFormat[ii].m_fmtSrgb;
					}

					g_caps.formats[ii] = support;
				}

				vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &m_memoryProperties);
			}

			{
				BX_TRACE("---");

				uint32_t queueFamilyPropertyCount = 0;
				vkGetPhysicalDeviceQueueFamilyProperties(
					  m_physicalDevice
					, &queueFamilyPropertyCount
					, NULL
					);

				VkQueueFamilyProperties* queueFamilyPropertices = (VkQueueFamilyProperties*)bx::alloc(g_allocator, queueFamilyPropertyCount * sizeof(VkQueueFamilyProperties) );
				vkGetPhysicalDeviceQueueFamilyProperties(
					  m_physicalDevice
					, &queueFamilyPropertyCount
					, queueFamilyPropertices
					);

				for (uint32_t ii = 0; ii < queueFamilyPropertyCount; ++ii)
				{
					const VkQueueFamilyProperties& qfp = queueFamilyPropertices[ii];

					BX_TRACE("Queue family property %d:", ii);
					BX_TRACE("\t  Queue flags: 0x%08x", qfp.queueFlags);
					BX_TRACE("\t  Queue count: %d", qfp.queueCount);
					BX_TRACE("\tTS valid bits: 0x%08x", qfp.timestampValidBits);
					BX_TRACE("\t    Min image: %d x %d x %d"
						, qfp.minImageTransferGranularity.width
						, qfp.minImageTransferGranularity.height
						, qfp.minImageTransferGranularity.depth
						);

					constexpr VkQueueFlags requiredFlags = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT;

					if (UINT32_MAX == m_globalQueueFamily
					&&  requiredFlags == (requiredFlags & qfp.queueFlags) )
					{
						m_globalQueueFamily = ii;
					}
				}

				bx::free(g_allocator, queueFamilyPropertices);

				if (UINT32_MAX == m_globalQueueFamily)
				{
					BX_TRACE("Init error: Unable to find combined graphics and compute queue.");
					goto error;
				}
			}

			{
				uint32_t numEnabledLayers = 0;
				const char* enabledLayer[Layer::Count];

				BX_TRACE("Enabled device layers:");

				for (uint32_t ii = 0; ii < Layer::Count; ++ii)
				{
					const Layer& layer = s_layer[ii];

					if (layer.m_device.m_supported
					&&  layer.m_device.m_initialize)
					{
						enabledLayer[numEnabledLayers++] = layer.m_name;
						BX_TRACE("\t%s", layer.m_name);
					}
				}

				uint32_t numEnabledExtensions = 0;
				const char* enabledExtension[Extension::Count + 3];

				enabledExtension[numEnabledExtensions++] = VK_KHR_MAINTENANCE1_EXTENSION_NAME;

				if (!headless)
				{
					enabledExtension[numEnabledExtensions++] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
				}

				if (BX_ENABLED(BX_PLATFORM_OSX) )
				{
					enabledExtension[numEnabledExtensions++] = VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME;
				}

				for (uint32_t ii = 0; ii < Extension::Count; ++ii)
				{
					const Extension& extension = s_extension[ii];

					bool layerEnabled = extension.m_layer == Layer::Count
						|| (s_layer[extension.m_layer].m_device.m_supported	&& s_layer[extension.m_layer].m_device.m_initialize)
						;

					if (extension.m_supported
					&&  extension.m_initialize
					&& !extension.m_instanceExt
					&&  layerEnabled)
					{
						enabledExtension[numEnabledExtensions++] = extension.m_name;
					}
				}

				BX_TRACE("Enabled device extensions:");

				for (uint32_t ii = 0; ii < numEnabledExtensions; ++ii)
				{
					BX_TRACE("\t%s", enabledExtension[ii]);
				}

				float queuePriorities[1] = { 0.0f };
				VkDeviceQueueCreateInfo dcqi;
				dcqi.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				dcqi.pNext = NULL;
				dcqi.flags = 0;
				dcqi.queueFamilyIndex = m_globalQueueFamily;
				dcqi.queueCount       = 1;
				dcqi.pQueuePriorities = queuePriorities;

				VkDeviceCreateInfo dci;
				dci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
				dci.pNext = nextFeatures;
				dci.flags = 0;
				dci.queueCreateInfoCount = 1;
				dci.pQueueCreateInfos    = &dcqi;
				dci.enabledLayerCount    = numEnabledLayers;
				dci.ppEnabledLayerNames  = enabledLayer;
				dci.enabledExtensionCount   = numEnabledExtensions;
				dci.ppEnabledExtensionNames = enabledExtension;
				dci.pEnabledFeatures        = &m_deviceFeatures;

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

			vkGetDeviceQueue(m_device, m_globalQueueFamily, 0, &m_globalQueue);

			{
				m_numFramesInFlight = _init.resolution.maxFrameLatency == 0
					? BGFX_CONFIG_MAX_FRAME_LATENCY
					: _init.resolution.maxFrameLatency
					;

				result = m_cmd.init(m_globalQueueFamily, m_globalQueue, m_numFramesInFlight);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: creating command queue failed %d: %s.", result, getName(result) );
					goto error;
				}

				result = m_cmd.alloc(&m_commandBuffer);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: allocating command buffer failed %d: %s.", result, getName(result) );
					goto error;
				}
			}

			errorState = ErrorState::CommandQueueCreated;

			m_presentElapsed = 0;

			{
				m_resolution = _init.resolution;
				m_resolution.reset &= ~BGFX_RESET_INTERNAL_FORCE;

				m_numWindows = 0;

				if (!headless)
				{
					m_textVideoMem.resize(false, _init.resolution.width, _init.resolution.height);
					m_textVideoMem.clear();

					for (uint8_t ii = 0; ii < BX_COUNTOF(m_swapChainFormats); ++ii)
					{
						m_swapChainFormats[ii] = TextureFormat::Enum(ii);
					}

					result = m_backBuffer.create(UINT16_MAX, g_platformData.nwh, m_resolution.width, m_resolution.height, m_resolution.format);

					if (VK_SUCCESS != result)
					{
						BX_TRACE("Init error: creating swap chain failed %d: %s.", result, getName(result) );
						goto error;
					}

					m_windows[0] = BGFX_INVALID_HANDLE;
					m_numWindows++;

					postReset();
				}
			}

			errorState = ErrorState::SwapChainCreated;

			{
				VkDescriptorPoolSize dps[] =
				{
					{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,          MAX_DESCRIPTOR_SETS * BGFX_CONFIG_MAX_TEXTURE_SAMPLERS },
					{ VK_DESCRIPTOR_TYPE_SAMPLER,                MAX_DESCRIPTOR_SETS * BGFX_CONFIG_MAX_TEXTURE_SAMPLERS },
					{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, MAX_DESCRIPTOR_SETS * 2                                },
					{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,         MAX_DESCRIPTOR_SETS * BGFX_CONFIG_MAX_TEXTURE_SAMPLERS },
					{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,          MAX_DESCRIPTOR_SETS * BGFX_CONFIG_MAX_TEXTURE_SAMPLERS },
				};

				VkDescriptorPoolCreateInfo dpci;
				dpci.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
				dpci.pNext = NULL;
				dpci.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
				dpci.maxSets       = MAX_DESCRIPTOR_SETS;
				dpci.poolSizeCount = BX_COUNTOF(dps);
				dpci.pPoolSizes    = dps;

				result = vkCreateDescriptorPool(m_device, &dpci, m_allocatorCb, &m_descriptorPool);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkCreateDescriptorPool failed %d: %s.", result, getName(result) );
					goto error;
				}

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
				const uint32_t size = 128;
				const uint32_t count = BGFX_CONFIG_MAX_DRAW_CALLS;

				for (uint32_t ii = 0; ii < m_numFramesInFlight; ++ii)
				{
					BX_TRACE("Create scratch buffer %d", ii);
					m_scratchBuffer[ii].createUniform(size, count);
				}

				for (uint32_t ii = 0; ii < m_numFramesInFlight; ++ii)
				{
					BX_TRACE("Create scratch staging buffer %d", ii);
					m_scratchStagingBuffer[ii].createStaging(BGFX_CONFIG_PER_FRAME_SCRATCH_STAGING_BUFFER_SIZE);
				}
			}

			errorState = ErrorState::DescriptorCreated;

			if (NULL == vkSetDebugUtilsObjectNameEXT)
			{
				vkSetDebugUtilsObjectNameEXT = stubSetDebugUtilsObjectNameEXT;
			}

			if (NULL == vkCmdBeginDebugUtilsLabelEXT
			||  NULL == vkCmdEndDebugUtilsLabelEXT)
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

			if (m_timerQuerySupport)
			{
				result = m_gpuTimer.init();

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: creating GPU timer failed %d: %s.", result, getName(result) );
					goto error;
				}
			}

			errorState = ErrorState::TimerQueryCreated;

			result = m_occlusionQuery.init();

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Init error: creating occlusion query failed %d: %s.", result, getName(result) );
				goto error;
			}

			g_internalData.context = m_device;
			return true;

		error:
			BX_TRACE("errorState %d", errorState);
			switch (errorState)
			{
			case ErrorState::TimerQueryCreated:
				if (m_timerQuerySupport)
				{
					m_gpuTimer.shutdown();
				}
				[[fallthrough]];

			case ErrorState::DescriptorCreated:
				for (uint32_t ii = 0; ii < m_numFramesInFlight; ++ii)
				{
					m_scratchBuffer[ii].destroy();
					m_scratchStagingBuffer[ii].destroy();
				}
				vkDestroy(m_pipelineCache);
				vkDestroy(m_descriptorPool);
				[[fallthrough]];

			case ErrorState::SwapChainCreated:
				m_backBuffer.destroy();
				[[fallthrough]];

			case ErrorState::CommandQueueCreated:
				m_cmd.shutdown();
				[[fallthrough]];

			case ErrorState::DeviceCreated:
				vkDestroyDevice(m_device, m_allocatorCb);
				[[fallthrough]];

			case ErrorState::InstanceCreated:
				if (VK_NULL_HANDLE != m_debugReportCallback)
				{
					vkDestroyDebugReportCallbackEXT(m_instance, m_debugReportCallback, m_allocatorCb);
				}

				vkDestroyInstance(m_instance, m_allocatorCb);
				[[fallthrough]];

			case ErrorState::LoadedVulkan1:
				bx::dlclose(m_vulkan1Dll);
				m_vulkan1Dll  = NULL;
				m_allocatorCb = NULL;
				unloadRenderDoc(m_renderDocDll);
				[[fallthrough]];

			case ErrorState::Default:
				break;
			};

			return false;
		}

		void shutdown()
		{
			VK_CHECK(vkDeviceWaitIdle(m_device) );

			if (m_timerQuerySupport)
			{
				m_gpuTimer.shutdown();
			}
			m_occlusionQuery.shutdown();

			preReset();

			m_pipelineStateCache.invalidate();
			m_descriptorSetLayoutCache.invalidate();
			m_renderPassCache.invalidate();
			m_samplerCache.invalidate();
			m_samplerBorderColorCache.invalidate();
			m_imageViewCache.invalidate();

			for (uint32_t ii = 0; ii < m_numFramesInFlight; ++ii)
			{
				m_scratchBuffer[ii].destroy();
			}

			for (uint32_t ii = 0; ii < m_numFramesInFlight; ++ii)
			{
				m_scratchStagingBuffer[ii].destroy();
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

			m_backBuffer.destroy();

			m_cmd.shutdown();

			vkDestroy(m_pipelineCache);
			vkDestroy(m_descriptorPool);

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
			int64_t start = bx::getHPCounter();

			for (uint16_t ii = 0; ii < m_numWindows; ++ii)
			{
				FrameBufferVK& fb = isValid(m_windows[ii])
					? m_frameBuffers[m_windows[ii].idx]
					: m_backBuffer
					;

				fb.present();
			}

			int64_t now = bx::getHPCounter();

			m_presentElapsed += now - start;
		}

		void createIndexBuffer(IndexBufferHandle _handle, const Memory* _mem, uint16_t _flags) override
		{
			m_indexBuffers[_handle.idx].create(m_commandBuffer, _mem->size, _mem->data, _flags, false);
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
			m_vertexBuffers[_handle.idx].create(m_commandBuffer, _mem->size, _mem->data, _layoutHandle, _flags);
		}

		void destroyVertexBuffer(VertexBufferHandle _handle) override
		{
			m_vertexBuffers[_handle.idx].destroy();
		}

		void createDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size, uint16_t _flags) override
		{
			m_indexBuffers[_handle.idx].create(m_commandBuffer, _size, NULL, _flags, false);
		}

		void updateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) override
		{
			m_indexBuffers[_handle.idx].update(m_commandBuffer, _offset, bx::min<uint32_t>(_size, _mem->size), _mem->data);
		}

		void destroyDynamicIndexBuffer(IndexBufferHandle _handle) override
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void createDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size, uint16_t _flags) override
		{
			VertexLayoutHandle layoutHandle = BGFX_INVALID_HANDLE;
			m_vertexBuffers[_handle.idx].create(m_commandBuffer, _size, NULL, layoutHandle, _flags);
		}

		void updateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) override
		{
			m_vertexBuffers[_handle.idx].update(m_commandBuffer, _offset, bx::min<uint32_t>(_size, _mem->size), _mem->data);
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
			return m_textures[_handle.idx].create(m_commandBuffer, _mem, _flags, _skip);
		}

		void updateTextureBegin(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/) override
		{
		}

		void updateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem) override
		{
			m_textures[_handle.idx].update(m_commandBuffer, _side, _mip, _rect, _z, _depth, _pitch, _mem);
		}

		void updateTextureEnd() override
		{
		}

		void readTexture(TextureHandle _handle, void* _data, uint8_t _mip) override
		{
			TextureVK& texture = m_textures[_handle.idx];

			uint32_t height = bx::uint32_max(1, texture.m_height >> _mip);
			uint32_t pitch  = texture.m_readback.pitch(_mip);
			uint32_t size = height * pitch;

			VkDeviceMemory stagingMemory;
			VkBuffer stagingBuffer;
			VK_CHECK(createReadbackBuffer(size, &stagingBuffer, &stagingMemory) );

			texture.m_readback.copyImageToBuffer(
				  m_commandBuffer
				, stagingBuffer
				, texture.m_currentImageLayout
				, texture.m_aspectMask
				, _mip
				);

			kick(true);

			texture.m_readback.readback(stagingMemory, 0, _data, _mip);

			vkDestroy(stagingBuffer);
			vkDestroy(stagingMemory);
		}

		void resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, uint16_t _numLayers) override
		{
			const TextureVK& texture = m_textures[_handle.idx];

			const TextureFormat::Enum format = TextureFormat::Enum(texture.m_requestedFormat);
			const uint64_t flags = texture.m_flags;

			const uint32_t size = sizeof(uint32_t) + sizeof(TextureCreate);
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
			tc.m_format    = format;
			tc.m_cubeMap   = false;
			tc.m_mem       = NULL;
			bx::write(&writer, tc, bx::ErrorAssert{});

			destroyTexture(_handle);
			createTexture(_handle, mem, flags, 0);

			bgfx::release(mem);
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
			m_imageViewCache.invalidateWithParent(_handle.idx);
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
			VK_CHECK(m_frameBuffers[_handle.idx].create(denseIdx, _nwh, _width, _height, _format, _depthFormat) );
		}

		void destroyFrameBuffer(FrameBufferHandle _handle) override
		{
			FrameBufferVK& frameBuffer = m_frameBuffers[_handle.idx];

			if (_handle.idx == m_fbh.idx)
			{
				setFrameBuffer(BGFX_INVALID_HANDLE, false);
			}

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

			const uint32_t size = bx::alignUp(g_uniformTypeSize[_type] * _num, 16);
			void* data = bx::alloc(g_allocator, size);
			bx::memSet(data, 0, size);
			m_uniforms[_handle.idx] = data;
			m_uniformReg.add(_handle, _name);
		}

		void destroyUniform(UniformHandle _handle) override
		{
			bx::free(g_allocator, m_uniforms[_handle.idx]);
			m_uniforms[_handle.idx] = NULL;
		}

		void requestScreenShot(FrameBufferHandle _fbh, const char* _filePath) override
		{
			const FrameBufferVK& frameBuffer = isValid(_fbh)
				? m_frameBuffers[_fbh.idx]
				: m_backBuffer
				;
			const SwapChainVK& swapChain = frameBuffer.m_swapChain;

			if (!isSwapChainReadable(swapChain) )
			{
				BX_TRACE("Unable to capture screenshot %s.", _filePath);
				return;
			}

			auto callback = [](void* _src, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _userData)
			{
				const char* filePath = (const char*)_userData;
				g_callback->screenShot(
					  filePath
					, _width
					, _height
					, _pitch
					, _src
					, _height * _pitch
					, false
					);
			};

			const uint8_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(swapChain.m_colorFormat) );
			const uint32_t size = frameBuffer.m_width * frameBuffer.m_height * bpp / 8;

			VkDeviceMemory stagingMemory;
			VkBuffer stagingBuffer;
			VK_CHECK(createReadbackBuffer(size, &stagingBuffer, &stagingMemory) );

			readSwapChain(swapChain, stagingBuffer, stagingMemory, callback, _filePath);

			vkDestroy(stagingBuffer);
			vkDestroy(stagingMemory);
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
			m_occlusionQuery.invalidate(_handle);
		}

		void setMarker(const char* _marker, uint16_t _len) override
		{
			if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
			{
				BX_UNUSED(_len);

				const uint32_t abgr = kColorMarker;

				VkDebugUtilsLabelEXT dul;
				dul.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
				dul.pNext = NULL;
				dul.pLabelName = _marker;
				dul.color[0] = ((abgr >> 24) & 0xff) / 255.0f;
				dul.color[1] = ((abgr >> 16) & 0xff) / 255.0f;
				dul.color[2] = ((abgr >> 8)  & 0xff) / 255.0f;
				dul.color[3] = ((abgr >> 0)  & 0xff) / 255.0f;

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
				setDebugObjectName(m_device, m_textures[_handle.idx].m_textureImage, "%.*s", _len, _name);

				if (VK_NULL_HANDLE != m_textures[_handle.idx].m_singleMsaaImage)
				{
					setDebugObjectName(m_device, m_textures[_handle.idx].m_singleMsaaImage, "%.*s", _len, _name);
				}
				break;

			case Handle::VertexBuffer:
				setDebugObjectName(m_device, m_vertexBuffers[_handle.idx].m_buffer, "%.*s", _len, _name);
				break;

			default:
				BX_ASSERT(false, "Invalid handle type?! %d", _handle.type);
				break;
			}
		}

		template<typename Ty>
		void release(Ty& _object)
		{
			if (VK_NULL_HANDLE != _object)
			{
				m_cmd.release(uint64_t(_object.vk), getType<Ty>() );
				_object = VK_NULL_HANDLE;
			}
		}

		void submitBlit(BlitState& _bs, uint16_t _view);

		void submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) override;

		void blitSetup(TextVideoMemBlitter& _blitter) override
		{
			const uint32_t width  = m_backBuffer.m_width;
			const uint32_t height = m_backBuffer.m_height;

			setFrameBuffer(BGFX_INVALID_HANDLE);

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
				| BGFX_STATE_MSAA
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

			ScratchBufferVK& scratchBuffer = m_scratchBuffer[m_cmd.m_currentFrameInFlight];
			const uint32_t bufferOffset = scratchBuffer.write(m_vsScratch, program.m_vsh->m_size);

			const TextureVK& texture = m_textures[_blitter.m_texture.idx];

			RenderBind bind;
			bind.clear();
			bind.m_bind[0].m_type = Binding::Texture;
			bind.m_bind[0].m_idx = _blitter.m_texture.idx;
			bind.m_bind[0].m_samplerFlags = (uint32_t)(texture.m_flags & BGFX_SAMPLER_BITS_MASK);

			const VkDescriptorSet descriptorSet = getDescriptorSet(program, bind, scratchBuffer, NULL);

			vkCmdBindDescriptorSets(
				  m_commandBuffer
				, VK_PIPELINE_BIND_POINT_GRAPHICS
				, program.m_pipelineLayout
				, 0
				, 1
				, &descriptorSet
				, 1
				, &bufferOffset
				);

			const VertexBufferVK& vb  = m_vertexBuffers[_blitter.m_vb->handle.idx];
			const VkDeviceSize offset = 0;
			vkCmdBindVertexBuffers(m_commandBuffer, 0, 1, &vb.m_buffer, &offset);

			const BufferVK& ib = m_indexBuffers[_blitter.m_ib->handle.idx];
			vkCmdBindIndexBuffer(
				  m_commandBuffer
				, ib.m_buffer
				, 0
				, VK_INDEX_TYPE_UINT16
				);
		}

		void blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices) override
		{
			const uint32_t numVertices = _numIndices*4/6;
			if (0 < numVertices && m_backBuffer.isRenderable() )
			{
				m_indexBuffers[_blitter.m_ib->handle.idx].update(m_commandBuffer, 0, _numIndices*2, _blitter.m_ib->data);
				m_vertexBuffers[_blitter.m_vb->handle.idx].update(m_commandBuffer, 0, numVertices*_blitter.m_layout.m_stride, _blitter.m_vb->data, true);

				VkRenderPassBeginInfo rpbi;
				rpbi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
				rpbi.pNext = NULL;
				rpbi.renderPass  = m_backBuffer.m_renderPass;
				rpbi.framebuffer = m_backBuffer.m_currentFramebuffer;
				rpbi.renderArea.offset.x = 0;
				rpbi.renderArea.offset.y = 0;
				rpbi.renderArea.extent.width  = m_backBuffer.m_width;
				rpbi.renderArea.extent.height = m_backBuffer.m_height;
				rpbi.clearValueCount = 0;
				rpbi.pClearValues    = NULL;

				vkCmdBeginRenderPass(m_commandBuffer, &rpbi, VK_SUBPASS_CONTENTS_INLINE);
				vkCmdDrawIndexed(m_commandBuffer, _numIndices, 1, 0, 0, 0);

				vkCmdEndRenderPass(m_commandBuffer);
			}
		}

		void preReset()
		{
			for (uint32_t ii = 0; ii < BX_COUNTOF(m_frameBuffers); ++ii)
			{
				m_frameBuffers[ii].preReset();
			}

			if (m_captureSize > 0)
			{
				g_callback->captureEnd();

				release(m_captureBuffer);
				release(m_captureMemory);
				m_captureSize = 0;
			}
		}

		void postReset()
		{
			for (uint32_t ii = 0; ii < BX_COUNTOF(m_frameBuffers); ++ii)
			{
				m_frameBuffers[ii].postReset();
			}

			if (m_resolution.reset & BGFX_RESET_CAPTURE)
			{
				const uint8_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_backBuffer.m_swapChain.m_colorFormat) );
				const uint32_t captureSize = m_backBuffer.m_width * m_backBuffer.m_height * bpp / 8;

				const uint8_t dstBpp = bimg::getBitsPerPixel(bimg::TextureFormat::BGRA8);
				const uint32_t dstPitch = m_backBuffer.m_width * dstBpp / 8;

				if (captureSize > m_captureSize)
				{
					release(m_captureBuffer);
					release(m_captureMemory);

					m_captureSize = captureSize;
					VK_CHECK(createReadbackBuffer(m_captureSize, &m_captureBuffer, &m_captureMemory) );
				}

				g_callback->captureBegin(m_resolution.width, m_resolution.height, dstPitch, TextureFormat::BGRA8, false);
			}
		}

		bool updateResolution(const Resolution& _resolution)
		{
			const bool suspended = !!(_resolution.reset & BGFX_RESET_SUSPEND);

			float maxAnisotropy = 1.0f;
			if (!!(_resolution.reset & BGFX_RESET_MAXANISOTROPY) )
			{
				maxAnisotropy = m_deviceProperties.limits.maxSamplerAnisotropy;
			}

			if (m_maxAnisotropy != maxAnisotropy)
			{
				m_maxAnisotropy = maxAnisotropy;
				m_samplerCache.invalidate();
				m_samplerBorderColorCache.invalidate();
			}

			bool depthClamp = m_deviceFeatures.depthClamp && !!(_resolution.reset & BGFX_RESET_DEPTH_CLAMP);

			if (m_depthClamp != depthClamp)
			{
				m_depthClamp = depthClamp;
				m_pipelineStateCache.invalidate();
			}

			if (NULL == m_backBuffer.m_nwh)
			{
				return suspended;
			}

			uint32_t flags = _resolution.reset & ~(0
				| BGFX_RESET_SUSPEND
				| BGFX_RESET_MAXANISOTROPY
				| BGFX_RESET_DEPTH_CLAMP
				);

			// Note: m_needToRefreshSwapchain is deliberately ignored when deciding whether to
			// recreate the swapchain because it can happen several frames before submit is called
			// with the new resolution.
			//
			// Instead, vkAcquireNextImageKHR and all draws to the backbuffer are skipped until
			// the window size is updated. That also fixes a related issue where VK_ERROR_OUT_OF_DATE_KHR
			// is returned from vkQueuePresentKHR when the window doesn't exist anymore, and
			// vkGetPhysicalDeviceSurfaceCapabilitiesKHR fails with VK_ERROR_SURFACE_LOST_KHR.

			if (false
			||  m_resolution.format != _resolution.format
			||  m_resolution.width  != _resolution.width
			||  m_resolution.height != _resolution.height
			||  m_resolution.reset  != flags
			||  m_backBuffer.m_swapChain.m_needToRecreateSurface)
			{
				flags &= ~BGFX_RESET_INTERNAL_FORCE;

				if (m_backBuffer.m_nwh != g_platformData.nwh)
				{
					m_backBuffer.m_nwh = g_platformData.nwh;
				}

				m_resolution = _resolution;
				m_resolution.reset = flags;

				m_textVideoMem.resize(false, _resolution.width, _resolution.height);
				m_textVideoMem.clear();

				preReset();

				m_backBuffer.update(m_commandBuffer, m_resolution);

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

		void setFrameBuffer(FrameBufferHandle _fbh, bool _acquire = true)
		{
			BGFX_PROFILER_SCOPE("Vk::setFrameBuffer()", kColorFrame);
			BX_ASSERT(false
				  ||  isValid(_fbh)
				  ||  NULL != m_backBuffer.m_nwh
				, "Rendering to backbuffer in headless mode."
				);

			FrameBufferVK& newFrameBuffer = isValid(_fbh)
				? m_frameBuffers[_fbh.idx]
				: m_backBuffer
				;

			FrameBufferVK& oldFrameBuffer = isValid(m_fbh)
				? m_frameBuffers[m_fbh.idx]
				: m_backBuffer
				;

			if (NULL == oldFrameBuffer.m_nwh
			&&  m_fbh.idx != _fbh.idx)
			{
				oldFrameBuffer.resolve();

				for (uint8_t ii = 0, num = oldFrameBuffer.m_num; ii < num; ++ii)
				{
					TextureVK& texture = m_textures[oldFrameBuffer.m_texture[ii].idx];
					texture.setImageMemoryBarrier(m_commandBuffer, texture.m_sampledLayout);
					if (VK_NULL_HANDLE != texture.m_singleMsaaImage)
					{
						texture.setImageMemoryBarrier(m_commandBuffer, texture.m_sampledLayout, true);
					}
				}

				if (isValid(oldFrameBuffer.m_depth) )
				{
					TextureVK& texture = m_textures[oldFrameBuffer.m_depth.idx];
					const bool writeOnly  = 0 != (texture.m_flags&BGFX_TEXTURE_RT_WRITE_ONLY);

					if (!writeOnly)
					{
						texture.setImageMemoryBarrier(m_commandBuffer, texture.m_sampledLayout);
					}
				}
			}

			if (NULL == newFrameBuffer.m_nwh)
			{
				for (uint8_t ii = 0, num = newFrameBuffer.m_num; ii < num; ++ii)
				{
					TextureVK& texture = m_textures[newFrameBuffer.m_texture[ii].idx];
					texture.setImageMemoryBarrier(
						  m_commandBuffer
						, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
						);
				}

				if (isValid(newFrameBuffer.m_depth) )
				{
					TextureVK& texture = m_textures[newFrameBuffer.m_depth.idx];
					texture.setImageMemoryBarrier(
						  m_commandBuffer
						, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
						);
				}

				newFrameBuffer.acquire(m_commandBuffer);
			}

			if (_acquire)
			{
				int64_t start = bx::getHPCounter();

				newFrameBuffer.acquire(m_commandBuffer);

				int64_t now = bx::getHPCounter();

				if (NULL != newFrameBuffer.m_nwh)
				{
					m_presentElapsed += now - start;
				}
			}

			m_fbh = _fbh;
		}

		void setDebugWireframe(bool _wireframe)
		{
			const bool wireframe = m_deviceFeatures.fillModeNonSolid && _wireframe;
			if (m_wireframe != wireframe)
			{
				m_wireframe = wireframe;
				m_pipelineStateCache.invalidate();
			}
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

			const FrameBufferVK& frameBuffer = isValid(m_fbh)
				? m_frameBuffers[m_fbh.idx]
				: m_backBuffer
				;

			const uint32_t numAttachments = NULL == frameBuffer.m_nwh
				? frameBuffer.m_num
				: 1
				;

			if (!!(BGFX_STATE_BLEND_INDEPENDENT & _state)
			&&  m_deviceFeatures.independentBlend )
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
			_desc.depthClampEnable = m_deviceFeatures.depthClamp && m_depthClamp;
			_desc.rasterizerDiscardEnable = VK_FALSE;
			_desc.polygonMode = m_deviceFeatures.fillModeNonSolid && _wireframe
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

		void setConservativeRasterizerState(VkPipelineRasterizationConservativeStateCreateInfoEXT& _desc, uint64_t _state)
		{
			_desc.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_CONSERVATIVE_STATE_CREATE_INFO_EXT;
			_desc.pNext = NULL;
			_desc.flags = 0;
			_desc.conservativeRasterizationMode = (_state&BGFX_STATE_CONSERVATIVE_RASTER)
				? VK_CONSERVATIVE_RASTERIZATION_MODE_OVERESTIMATE_EXT
				: VK_CONSERVATIVE_RASTERIZATION_MODE_DISABLED_EXT
				;
			_desc.extraPrimitiveOverestimationSize = 0.0f;
		}

		void setLineRasterizerState(VkPipelineRasterizationLineStateCreateInfoEXT& _desc, uint64_t _state)
		{
			_desc.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_LINE_STATE_CREATE_INFO_EXT;
			_desc.pNext = NULL;
			_desc.lineRasterizationMode = (_state & BGFX_STATE_LINEAA)
				? VK_LINE_RASTERIZATION_MODE_RECTANGULAR_SMOOTH_EXT
				: VK_LINE_RASTERIZATION_MODE_DEFAULT_EXT
				;
			_desc.stippledLineEnable = VK_FALSE;
			_desc.lineStippleFactor = 0;
			_desc.lineStipplePattern = 0;
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

		VkResult getRenderPass(uint8_t _num, const VkFormat* _formats, const VkImageAspectFlags* _aspects, const bool* _resolve, VkSampleCountFlagBits _samples, ::VkRenderPass* _renderPass)
		{
			VkResult result = VK_SUCCESS;

			if (VK_SAMPLE_COUNT_1_BIT == _samples)
			{
				_resolve = NULL;
			}

			bx::HashMurmur2A hash;
			hash.begin();
			hash.add(_samples);
			hash.add(_formats, sizeof(VkFormat) * _num);
			if (NULL != _resolve)
			{
				hash.add(_resolve, sizeof(bool) * _num);
			}
			uint32_t hashKey = hash.end();

			VkRenderPass renderPass = m_renderPassCache.find(hashKey);

			if (VK_NULL_HANDLE != renderPass)
			{
				*_renderPass = renderPass;
				return result;
			}

			VkAttachmentDescription ad[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS * 2];

			for (uint8_t ii = 0; ii < (_num * 2); ++ii)
			{
				ad[ii].flags          = 0;
				ad[ii].format         = VK_FORMAT_UNDEFINED;
				ad[ii].samples        = _samples;
				ad[ii].loadOp         = VK_ATTACHMENT_LOAD_OP_LOAD;
				ad[ii].storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
				ad[ii].stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
				ad[ii].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
				ad[ii].initialLayout  = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
				ad[ii].finalLayout    = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			}

			VkAttachmentReference colorAr[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
			VkAttachmentReference resolveAr[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
			VkAttachmentReference depthAr;
			uint32_t numColorAr = 0;
			uint32_t numResolveAr = 0;

			colorAr[0].attachment   = VK_ATTACHMENT_UNUSED;
			colorAr[0].layout       = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			resolveAr[0].attachment = VK_ATTACHMENT_UNUSED;
			resolveAr[0].layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			depthAr.attachment      = VK_ATTACHMENT_UNUSED;
			depthAr.layout          = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

			for (uint8_t ii = 0; ii < _num; ++ii)
			{
				ad[ii].format = _formats[ii];

				if (_aspects[ii] & VK_IMAGE_ASPECT_COLOR_BIT)
				{
					colorAr[numColorAr].layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
					colorAr[numColorAr].attachment = ii;

					resolveAr[numColorAr].layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
					resolveAr[numColorAr].attachment = VK_ATTACHMENT_UNUSED;
					if (NULL != _resolve
					&&  _resolve[ii])
					{
						const uint32_t resolve = _num + numResolveAr;

						ad[resolve].format  = _formats[ii];
						ad[resolve].samples = VK_SAMPLE_COUNT_1_BIT;
						ad[resolve].loadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;

						resolveAr[numColorAr].attachment = resolve;
						numResolveAr++;
					}

					numColorAr++;
				}
				else if (_aspects[ii] & (VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT) )
				{
					ad[ii].stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_LOAD;
					ad[ii].stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE;
					ad[ii].initialLayout  = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
					ad[ii].finalLayout    = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

					depthAr.layout     = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
					depthAr.attachment = ii;
				}
			}

			VkSubpassDescription sd[1];
			sd[0].flags                   = 0;
			sd[0].pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS;
			sd[0].inputAttachmentCount    = 0;
			sd[0].pInputAttachments       = NULL;
			sd[0].colorAttachmentCount    = bx::max<uint32_t>(numColorAr, 1);
			sd[0].pColorAttachments       = colorAr;
			sd[0].pResolveAttachments     = resolveAr;
			sd[0].pDepthStencilAttachment = &depthAr;
			sd[0].preserveAttachmentCount = 0;
			sd[0].pPreserveAttachments    = NULL;

			const VkPipelineStageFlags graphicsStages = 0
				| VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT
				| VK_PIPELINE_STAGE_VERTEX_INPUT_BIT
				| VK_PIPELINE_STAGE_VERTEX_SHADER_BIT
				| VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT
				| VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT
				| VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT
				| VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
				;
			const VkPipelineStageFlags outsideStages = 0
				| graphicsStages
				| VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT
				| VK_PIPELINE_STAGE_TRANSFER_BIT
				;

			VkSubpassDependency dep[2];

			dep[0].srcSubpass      = VK_SUBPASS_EXTERNAL;
			dep[0].dstSubpass      = 0;
			dep[0].srcStageMask    = outsideStages;
			dep[0].dstStageMask    = graphicsStages;
			dep[0].srcAccessMask   = VK_ACCESS_MEMORY_WRITE_BIT;
			dep[0].dstAccessMask   = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT;
			dep[0].dependencyFlags = 0;

			dep[1].srcSubpass      = BX_COUNTOF(sd)-1;
			dep[1].dstSubpass      = VK_SUBPASS_EXTERNAL;
			dep[1].srcStageMask    = graphicsStages;
			dep[1].dstStageMask    = outsideStages;
			dep[1].srcAccessMask   = VK_ACCESS_MEMORY_WRITE_BIT;
			dep[1].dstAccessMask   = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT;
			dep[1].dependencyFlags = 0;

			VkRenderPassCreateInfo rpi;
			rpi.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			rpi.pNext           = NULL;
			rpi.flags           = 0;
			rpi.attachmentCount = _num + numResolveAr;
			rpi.pAttachments    = ad;
			rpi.subpassCount    = BX_COUNTOF(sd);
			rpi.pSubpasses      = sd;
			rpi.dependencyCount = BX_COUNTOF(dep);
			rpi.pDependencies   = dep;

			result = vkCreateRenderPass(m_device, &rpi, m_allocatorCb, &renderPass);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create render pass error: vkCreateRenderPass failed %d: %s.", result, getName(result) );
				return result;
			}

			m_renderPassCache.add(hashKey, renderPass);

			*_renderPass = renderPass;

			return result;
		}

		VkResult getRenderPass(uint8_t _num, const Attachment* _attachments, ::VkRenderPass* _renderPass)
		{
			VkFormat formats[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
			VkImageAspectFlags aspects[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
			VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT;

			for (uint8_t ii = 0; ii < _num; ++ii)
			{
				const TextureVK& texture = m_textures[_attachments[ii].handle.idx];
				formats[ii] = texture.m_format;
				aspects[ii] = texture.m_aspectMask;
				samples = texture.m_sampler.Sample;
			}

			return getRenderPass(_num, formats, aspects, NULL, samples, _renderPass);
		}

		VkResult getRenderPass(const SwapChainVK& swapChain, ::VkRenderPass* _renderPass)
		{
			const VkFormat formats[2] =
			{
				swapChain.m_sci.imageFormat,
				swapChain.m_backBufferDepthStencil.m_format
			};
			const VkImageAspectFlags aspects[2] =
			{
				VK_IMAGE_ASPECT_COLOR_BIT,
				swapChain.m_backBufferDepthStencil.m_aspectMask
			};
			const bool resolve[2] =
			{
				swapChain.m_supportsManualResolve ? false : true,
				false
			};
			const VkSampleCountFlagBits samples = swapChain.m_sampler.Sample;

			return getRenderPass(BX_COUNTOF(formats), formats, aspects, resolve, samples, _renderPass);
		}

		VkSampler getSampler(uint32_t _flags, VkFormat _format, const float _palette[][4])
		{
			uint32_t index = ((_flags & BGFX_SAMPLER_BORDER_COLOR_MASK) >> BGFX_SAMPLER_BORDER_COLOR_SHIFT);
			index = bx::min<uint32_t>(BGFX_CONFIG_MAX_COLOR_PALETTE - 1, index);

			_flags &= BGFX_SAMPLER_BITS_MASK;
			_flags &= ~(m_deviceFeatures.samplerAnisotropy ? 0 : (BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC) );

			// Force both min+max anisotropic, can't be set individually.
			_flags |= 0 != (_flags & (BGFX_SAMPLER_MIN_ANISOTROPIC|BGFX_SAMPLER_MAG_ANISOTROPIC) )
					? BGFX_SAMPLER_MIN_ANISOTROPIC|BGFX_SAMPLER_MAG_ANISOTROPIC
					: 0
					;

			const float* rgba = NULL == _palette
				? NULL
				: _palette[index]
				;

			const bool needColor = true
				&& needBorderColor(_flags)
				&& NULL != rgba
				&& m_borderColorSupport
				;

			uint32_t hashKey;
			VkSampler sampler = VK_NULL_HANDLE;
			if (!needColor)
			{
				bx::HashMurmur2A hash;
				hash.begin();
				hash.add(_flags);
				hash.add(-1);
				hash.add(VK_FORMAT_UNDEFINED);
				hashKey = hash.end();

				sampler = m_samplerCache.find(hashKey);
			}
			else
			{
				bx::HashMurmur2A hash;
				hash.begin();
				hash.add(_flags);
				hash.add(index);
				hash.add(_format);
				hashKey = hash.end();

				const uint32_t colorHashKey = m_samplerBorderColorCache.find(hashKey);
				const uint32_t newColorHashKey = bx::hash<bx::HashMurmur2A>(rgba, sizeof(float) * 4);
				if (newColorHashKey == colorHashKey)
				{
					sampler = m_samplerCache.find(hashKey);
				}
				else
				{
					m_samplerBorderColorCache.add(hashKey, newColorHashKey);
				}
			}

			if (VK_NULL_HANDLE != sampler)
			{
				return sampler;
			}

			const uint32_t cmpFunc = (_flags&BGFX_SAMPLER_COMPARE_MASK)>>BGFX_SAMPLER_COMPARE_SHIFT;

			const float maxLodBias = m_deviceProperties.limits.maxSamplerLodBias;
			const float lodBias = bx::clamp(float(BGFX_CONFIG_MIP_LOD_BIAS), -maxLodBias, maxLodBias);

			VkSamplerCreateInfo sci;
			sci.sType            = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			sci.pNext            = NULL;
			sci.flags            = 0;
			sci.magFilter        = _flags & BGFX_SAMPLER_MAG_POINT ? VK_FILTER_NEAREST              : VK_FILTER_LINEAR;
			sci.minFilter        = _flags & BGFX_SAMPLER_MIN_POINT ? VK_FILTER_NEAREST              : VK_FILTER_LINEAR;
			sci.mipmapMode       = _flags & BGFX_SAMPLER_MIP_POINT ? VK_SAMPLER_MIPMAP_MODE_NEAREST : VK_SAMPLER_MIPMAP_MODE_LINEAR;
			sci.addressModeU     = s_textureAddress[(_flags&BGFX_SAMPLER_U_MASK)>>BGFX_SAMPLER_U_SHIFT];
			sci.addressModeV     = s_textureAddress[(_flags&BGFX_SAMPLER_V_MASK)>>BGFX_SAMPLER_V_SHIFT];
			sci.addressModeW     = s_textureAddress[(_flags&BGFX_SAMPLER_W_MASK)>>BGFX_SAMPLER_W_SHIFT];
			sci.mipLodBias       = lodBias;
			sci.anisotropyEnable = !!(_flags & (BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC) );
			sci.maxAnisotropy    = m_maxAnisotropy;
			sci.compareEnable    = 0 != cmpFunc;
			sci.compareOp        = s_cmpFunc[cmpFunc];
			sci.minLod           = 0.0f;
			sci.maxLod           = VK_LOD_CLAMP_NONE;
			sci.borderColor      = VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK;
			sci.unnormalizedCoordinates = VK_FALSE;

			VkSamplerCustomBorderColorCreateInfoEXT cbcci;
			if (needColor)
			{
				cbcci.sType = VK_STRUCTURE_TYPE_SAMPLER_CUSTOM_BORDER_COLOR_CREATE_INFO_EXT;
				cbcci.pNext = NULL;
				cbcci.format = _format;
				bx::memCopy(cbcci.customBorderColor.float32, rgba, sizeof(cbcci.customBorderColor.float32) );

				sci.pNext = &cbcci;
				sci.borderColor = VK_BORDER_COLOR_FLOAT_CUSTOM_EXT;
			}

			VK_CHECK(vkCreateSampler(m_device, &sci, m_allocatorCb, &sampler) );

			m_samplerCache.add(hashKey, sampler);
			return sampler;
		}

		VkImageView getCachedImageView(TextureHandle _handle, uint32_t _mip, uint32_t _numMips, VkImageViewType _type, bool _stencil = false)
		{
			const TextureVK& texture = m_textures[_handle.idx];

			_stencil = _stencil && !!(texture.m_aspectMask & VK_IMAGE_ASPECT_STENCIL_BIT);

			bx::HashMurmur2A hash;
			hash.begin();
			hash.add(_handle.idx);
			hash.add(_mip);
			hash.add(_numMips);
			hash.add(_type);
			hash.add(_stencil);
			uint32_t hashKey = hash.end();

			VkImageView* viewCached = m_imageViewCache.find(hashKey);

			if (NULL != viewCached)
			{
				return *viewCached;
			}

			const VkImageAspectFlags aspectMask = 0
				| VK_IMAGE_ASPECT_COLOR_BIT
				| ( _stencil ? VK_IMAGE_ASPECT_STENCIL_BIT : VK_IMAGE_ASPECT_DEPTH_BIT)
				;

			VkImageView view;
			VK_CHECK(texture.createView(0, texture.m_numSides, _mip, _numMips, _type, aspectMask, false, &view) );
			m_imageViewCache.add(hashKey, view, _handle.idx);

			return view;
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

			VK_CHECK(vkCreateComputePipelines(m_device, m_pipelineCache, 1, &cpci, m_allocatorCb, &pipeline) );

			m_pipelineStateCache.add(hash, pipeline);

			return pipeline;
		}

		VkPipeline getPipeline(uint64_t _state, uint64_t _stencil, uint8_t _numStreams, const VertexLayout** _layouts, ProgramHandle _program, uint8_t _numInstanceData)
		{
			ProgramVK& program = m_program[_program.idx];

			_state &= 0
				| BGFX_STATE_WRITE_MASK
				| BGFX_STATE_DEPTH_TEST_MASK
				| BGFX_STATE_BLEND_MASK
				| BGFX_STATE_BLEND_EQUATION_MASK
				| (g_caps.supported & BGFX_CAPS_BLEND_INDEPENDENT ? BGFX_STATE_BLEND_INDEPENDENT : 0)
				| BGFX_STATE_BLEND_ALPHA_TO_COVERAGE
				| BGFX_STATE_CULL_MASK
				| BGFX_STATE_FRONT_CCW
				| BGFX_STATE_MSAA
				| (m_lineAASupport ? BGFX_STATE_LINEAA : 0)
				| (g_caps.supported & BGFX_CAPS_CONSERVATIVE_RASTER ? BGFX_STATE_CONSERVATIVE_RASTER : 0)
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

			const FrameBufferVK& frameBuffer = isValid(m_fbh)
				? m_frameBuffers[m_fbh.idx]
				: m_backBuffer
				;

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
			murmur.add(_numInstanceData);
			murmur.add(frameBuffer.m_renderPass);
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
			setRasterizerState(rasterizationState, _state, m_wireframe);

			VkBaseInStructure* nextRasterizationState = (VkBaseInStructure*)&rasterizationState;

			VkPipelineRasterizationConservativeStateCreateInfoEXT conservativeRasterizationState;
			if (s_extension[Extension::EXT_conservative_rasterization].m_supported)
			{
				nextRasterizationState->pNext = (VkBaseInStructure*)&conservativeRasterizationState;
				nextRasterizationState = (VkBaseInStructure*)&conservativeRasterizationState;
				setConservativeRasterizerState(conservativeRasterizationState, _state);
			}

			VkPipelineRasterizationLineStateCreateInfoEXT lineRasterizationState;
			if (m_lineAASupport)
			{
				nextRasterizationState->pNext = (VkBaseInStructure*)&lineRasterizationState;
				nextRasterizationState = (VkBaseInStructure*)&lineRasterizationState;
				setLineRasterizerState(lineRasterizationState, _state);
			}

			VkPipelineDepthStencilStateCreateInfo depthStencilState;
			setDepthStencilState(depthStencilState, _state, _stencil);

			VkVertexInputBindingDescription  inputBinding[BGFX_CONFIG_MAX_VERTEX_STREAMS + 1];
			VkVertexInputAttributeDescription inputAttrib[Attrib::Count + BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT];

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

			VkPipelineMultisampleStateCreateInfo multisampleState;
			multisampleState.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
			multisampleState.pNext = NULL;
			multisampleState.flags = 0;
			multisampleState.rasterizationSamples  = frameBuffer.m_sampler.Sample;
			multisampleState.sampleShadingEnable   = VK_FALSE;
			multisampleState.minSampleShading      = 0.0f;
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
			graphicsPipeline.layout     = program.m_pipelineLayout;
			graphicsPipeline.renderPass = frameBuffer.m_renderPass;
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
				cachedData = bx::alloc(g_allocator, length);
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

			VK_CHECK(vkCreateGraphicsPipelines(
				  m_device
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
					cachedData = bx::realloc(g_allocator, cachedData, dataSize);
				}

				VK_CHECK(vkGetPipelineCacheData(m_device, cache, &dataSize, cachedData) );
				g_callback->cacheWrite(hash, cachedData, (uint32_t)dataSize);
			}

			VK_CHECK(vkMergePipelineCaches(m_device, m_pipelineCache, 1, &cache) );
			vkDestroy(cache);

			if (NULL != cachedData)
			{
				bx::free(g_allocator, cachedData);
			}

			return pipeline;
		}

		VkDescriptorSet getDescriptorSet(const ProgramVK& program, const RenderBind& renderBind, const ScratchBufferVK& scratchBuffer, const float _palette[][4])
		{
			VkDescriptorSet descriptorSet;

			VkDescriptorSetAllocateInfo dsai;
			dsai.sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			dsai.pNext              = NULL;
			dsai.descriptorPool     = m_descriptorPool;
			dsai.descriptorSetCount = 1;
			dsai.pSetLayouts        = &program.m_descriptorSetLayout;

			VK_CHECK(vkAllocateDescriptorSets(m_device, &dsai, &descriptorSet) );

			VkDescriptorImageInfo  imageInfo[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
			VkDescriptorBufferInfo bufferInfo[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];

			constexpr uint32_t kMaxDescriptorSets = 2 * BGFX_CONFIG_MAX_TEXTURE_SAMPLERS + 2;
			VkWriteDescriptorSet wds[kMaxDescriptorSets] = {};

			uint32_t wdsCount    = 0;
			uint32_t bufferCount = 0;
			uint32_t imageCount  = 0;

			for (uint32_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
			{
				const Binding& bind = renderBind.m_bind[stage];
				const BindInfo& bindInfo = program.m_bindInfo[stage];

				if (kInvalidHandle != bind.m_idx
				&&  isValid(bindInfo.uniformHandle) )
				{
					switch (bind.m_type)
					{
					case Binding::Image:
						{
							const bool isImageDescriptor = BindType::Image == bindInfo.type;

							wds[wdsCount].sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
							wds[wdsCount].pNext            = NULL;
							wds[wdsCount].dstSet           = descriptorSet;
							wds[wdsCount].dstBinding       = bindInfo.binding;
							wds[wdsCount].dstArrayElement  = 0;
							wds[wdsCount].descriptorCount  = 1;
							wds[wdsCount].descriptorType   = isImageDescriptor
								? VK_DESCRIPTOR_TYPE_STORAGE_IMAGE
								: VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE
								;
							wds[wdsCount].pImageInfo       = NULL;
							wds[wdsCount].pBufferInfo      = NULL;
							wds[wdsCount].pTexelBufferView = NULL;

							const TextureVK& texture = m_textures[bind.m_idx];

							VkImageViewType type = texture.m_type;
							if (UINT32_MAX != bindInfo.index)
							{
								type = program.m_textures[bindInfo.index].type;
							}
							else if (type == VK_IMAGE_VIEW_TYPE_CUBE
							     ||  type == VK_IMAGE_VIEW_TYPE_CUBE_ARRAY)
							{
								type = VK_IMAGE_VIEW_TYPE_2D_ARRAY;
							}

							BX_ASSERT(
								  texture.m_currentImageLayout == texture.m_sampledLayout
								, "Mismatching image layout. Texture currently used as a framebuffer attachment?"
								);

							imageInfo[imageCount].imageLayout = texture.m_sampledLayout;
							imageInfo[imageCount].sampler     = VK_NULL_HANDLE;
							imageInfo[imageCount].imageView   = getCachedImageView(
								  { bind.m_idx }
								, bind.m_mip
								, 1
								, type
								);
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

							const BufferVK& sb = bind.m_type == Binding::VertexBuffer
								? m_vertexBuffers[bind.m_idx]
								: m_indexBuffers[bind.m_idx]
								;

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
							const uint32_t samplerFlags = 0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & bind.m_samplerFlags)
								? bind.m_samplerFlags
								: (uint32_t)texture.m_flags
								;
							const bool sampleStencil = !!(samplerFlags & BGFX_SAMPLER_SAMPLE_STENCIL);
							VkSampler sampler = getSampler(samplerFlags, texture.m_format, _palette);

							const VkImageViewType type = UINT32_MAX == bindInfo.index
								? texture.m_type
								: program.m_textures[bindInfo.index].type
								;

							BX_ASSERT(
								  texture.m_currentImageLayout == texture.m_sampledLayout
								, "Mismatching image layout. Texture currently used as a framebuffer attachment?"
								);

							imageInfo[imageCount].imageLayout = texture.m_sampledLayout;
							imageInfo[imageCount].sampler     = sampler;
							imageInfo[imageCount].imageView   = getCachedImageView(
								  { bind.m_idx }
								, 0
								, texture.m_numMips
								, type
								, sampleStencil
								);

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

			const uint32_t vsize = program.m_vsh->m_size;
			const uint32_t fsize = NULL != program.m_fsh ? program.m_fsh->m_size : 0;

			if (vsize > 0)
			{
				bufferInfo[bufferCount].buffer = scratchBuffer.m_buffer;
				bufferInfo[bufferCount].offset = 0;
				bufferInfo[bufferCount].range  = vsize;

				wds[wdsCount].sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
				wds[wdsCount].pNext            = NULL;
				wds[wdsCount].dstSet           = descriptorSet;
				wds[wdsCount].dstBinding       = program.m_vsh->m_uniformBinding;
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
				wds[wdsCount].dstBinding       = program.m_fsh->m_uniformBinding;
				wds[wdsCount].dstArrayElement  = 0;
				wds[wdsCount].descriptorCount  = 1;
				wds[wdsCount].descriptorType   = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
				wds[wdsCount].pImageInfo       = NULL;
				wds[wdsCount].pBufferInfo      = &bufferInfo[bufferCount];
				wds[wdsCount].pTexelBufferView = NULL;
				++wdsCount;
				++bufferCount;
			}

			vkUpdateDescriptorSets(m_device, wdsCount, wds, 0, NULL);

			VkDescriptorSet temp = descriptorSet;
			release(temp);

			return descriptorSet;
		}

		bool isSwapChainReadable(const SwapChainVK& _swapChain)
		{
			return true
				&& NULL != _swapChain.m_nwh
				&& _swapChain.m_needPresent
				&& _swapChain.m_supportsReadback
				&& bimg::imageConvert(bimg::TextureFormat::BGRA8, bimg::TextureFormat::Enum(_swapChain.m_colorFormat) )
				;
		}

		typedef void (*SwapChainReadFunc)(void* /*src*/, uint32_t /*width*/, uint32_t /*height*/, uint32_t /*pitch*/, const void* /*userData*/);

		bool readSwapChain(const SwapChainVK& _swapChain, VkBuffer _buffer, VkDeviceMemory _memory, SwapChainReadFunc _func, const void* _userData = NULL)
		{
			if (isSwapChainReadable(_swapChain) )
			{
				// source for the copy is the last rendered swapchain image
				const VkImage image = _swapChain.m_backBufferColorImage[_swapChain.m_backBufferColorIdx];
				const VkImageLayout layout = _swapChain.m_backBufferColorImageLayout[_swapChain.m_backBufferColorIdx];

				const uint32_t width  = _swapChain.m_sci.imageExtent.width;
				const uint32_t height = _swapChain.m_sci.imageExtent.height;

				ReadbackVK readback;
				readback.create(image, width, height, _swapChain.m_colorFormat);
				const uint32_t pitch = readback.pitch();

				readback.copyImageToBuffer(m_commandBuffer, _buffer, layout, VK_IMAGE_ASPECT_COLOR_BIT);

				// stall for commandbuffer to finish
				kick(true);

				uint8_t* src;
				VK_CHECK(vkMapMemory(m_device, _memory, 0, VK_WHOLE_SIZE, 0, (void**)&src) );

				if (_swapChain.m_colorFormat == TextureFormat::RGBA8)
				{
					bimg::imageSwizzleBgra8(src, pitch, width, height, src, pitch);
					_func(src, width, height, pitch, _userData);
				}
				else if (_swapChain.m_colorFormat == TextureFormat::BGRA8)
				{
					_func(src, width, height, pitch, _userData);
				}
				else
				{
					const uint8_t dstBpp = bimg::getBitsPerPixel(bimg::TextureFormat::BGRA8);
					const uint32_t dstPitch = width * dstBpp / 8;
					const uint32_t dstSize = height * dstPitch;

					void* dst = bx::alloc(g_allocator, dstSize);

					bimg::imageConvert(g_allocator, dst, bimg::TextureFormat::BGRA8, src, bimg::TextureFormat::Enum(_swapChain.m_colorFormat), width, height, 1);

					_func(dst, width, height, dstPitch, _userData);

					bx::free(g_allocator, dst);
				}

				vkUnmapMemory(m_device, _memory);

				readback.destroy();

				return true;
			}

			return false;
		}

		void capture()
		{
			if (m_captureSize > 0)
			{
				m_backBuffer.resolve();

				auto callback = [](void* _src, uint32_t /*_width*/, uint32_t _height, uint32_t _pitch, const void* /*_userData*/)
				{
					const uint32_t size = _height * _pitch;
					g_callback->captureFrame(_src, size);
				};

				readSwapChain(m_backBuffer.m_swapChain, m_captureBuffer, m_captureMemory, callback);
			}
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
				case UniformType::Sampler|kUniformFragmentBit:
					// do nothing, but VkDescriptorSetImageInfo would be set before drawing
					break;

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

		void clearQuad(const Rect& _rect, const Clear& _clear, const float _palette[][4])
		{
			VkClearRect rect[1];
			rect[0].rect.offset.x      = _rect.m_x;
			rect[0].rect.offset.y      = _rect.m_y;
			rect[0].rect.extent.width  = _rect.m_width;
			rect[0].rect.extent.height = _rect.m_height;
			rect[0].baseArrayLayer = 0;
			rect[0].layerCount     = 1;

			uint32_t numMrt;
			bgfx::TextureFormat::Enum mrtFormat[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
			VkImageAspectFlags depthAspectMask;

			const FrameBufferVK& fb = isValid(m_fbh)
				? m_frameBuffers[m_fbh.idx]
				: m_backBuffer
				;

			if (NULL == fb.m_nwh)
			{
				numMrt = fb.m_num;
				for (uint8_t ii = 0; ii < fb.m_num; ++ii)
				{
					mrtFormat[ii] = bgfx::TextureFormat::Enum(m_textures[fb.m_texture[ii].idx].m_requestedFormat);
				}
				depthAspectMask = isValid(fb.m_depth) ? m_textures[fb.m_depth.idx].m_aspectMask : 0;
				rect[0].layerCount = fb.m_attachment[0].numLayers;
			}
			else
			{
				numMrt = 1;
				mrtFormat[0] = fb.m_swapChain.m_colorFormat;
				depthAspectMask = fb.m_swapChain.m_backBufferDepthStencil.m_aspectMask;
			}

			VkClearAttachment attachments[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS + 1];
			uint32_t mrt = 0;

			if (BGFX_CLEAR_COLOR & _clear.m_flags)
			{
				for (uint32_t ii = 0; ii < numMrt; ++ii)
				{
					attachments[mrt].colorAttachment = mrt;
					attachments[mrt].aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

					VkClearColorValue& clearValue = attachments[mrt].clearValue.color;

					const bimg::ImageBlockInfo& blockInfo = bimg::getBlockInfo(bimg::TextureFormat::Enum(mrtFormat[ii]) );
					const bx::EncodingType::Enum type = bx::EncodingType::Enum(blockInfo.encoding);

					if (BGFX_CLEAR_COLOR_USE_PALETTE & _clear.m_flags)
					{
						const uint8_t index = bx::min<uint8_t>(BGFX_CONFIG_MAX_COLOR_PALETTE-1, _clear.m_index[ii]);

						switch (type)
						{
						case bx::EncodingType::Int:
						case bx::EncodingType::Uint:
							clearValue.int32[0] = int32_t(_palette[index][0]);
							clearValue.int32[1] = int32_t(_palette[index][1]);
							clearValue.int32[2] = int32_t(_palette[index][2]);
							clearValue.int32[3] = int32_t(_palette[index][3]);
							break;
						default:
							bx::memCopy(&clearValue.float32, _palette[index], sizeof(clearValue.float32) );
							break;
						}
					}
					else
					{
						switch (type)
						{
						case bx::EncodingType::Int:
						case bx::EncodingType::Uint:
							clearValue.uint32[0] = _clear.m_index[0];
							clearValue.uint32[1] = _clear.m_index[1];
							clearValue.uint32[2] = _clear.m_index[2];
							clearValue.uint32[3] = _clear.m_index[3];
							break;
						default:
							bx::unpackRgba8(clearValue.float32, _clear.m_index);
							break;
						}
					}

					++mrt;
				}
			}

			depthAspectMask &= 0
				| (_clear.m_flags & BGFX_CLEAR_DEPTH   ? VK_IMAGE_ASPECT_DEPTH_BIT   : 0)
				| (_clear.m_flags & BGFX_CLEAR_STENCIL ? VK_IMAGE_ASPECT_STENCIL_BIT : 0)
				;

			if (0 != depthAspectMask)
			{
				attachments[mrt].colorAttachment = VK_ATTACHMENT_UNUSED;
				// The above is meaningless and not required by the spec, but Khronos
				// Validation Layer has a conditional jump depending on this, even
				// without VK_IMAGE_ASPECT_COLOR_BIT set. Valgrind found this.
				attachments[mrt].aspectMask = depthAspectMask;
				attachments[mrt].clearValue.depthStencil.stencil = _clear.m_stencil;
				attachments[mrt].clearValue.depthStencil.depth   = _clear.m_depth;
				++mrt;
			}

			if (mrt > 0)
			{
				vkCmdClearAttachments(m_commandBuffer, mrt, attachments, BX_COUNTOF(rect), rect);
			}
		}

		void kick(bool _finishAll = false)
		{
			m_cmd.kick(_finishAll);
			VK_CHECK(m_cmd.alloc(&m_commandBuffer) );
			m_cmd.finish(_finishAll);
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

		VkResult allocateMemory(const VkMemoryRequirements* requirements, VkMemoryPropertyFlags propertyFlags, ::VkDeviceMemory* memory) const
		{
			BGFX_PROFILER_SCOPE("RendererContextVK::allocateMemory", kColorResource);
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
					result = vkAllocateMemory(m_device, &ma, m_allocatorCb, memory);
				}
			}
			while (result != VK_SUCCESS
			   &&  searchIndex >= 0);

			return result;
		}

		VkResult createHostBuffer(uint32_t _size, VkMemoryPropertyFlags _flags, ::VkBuffer* _buffer, ::VkDeviceMemory* _memory, const void* _data = NULL)
		{
			BGFX_PROFILER_SCOPE("createHostBuffer", kColorResource);
			VkResult result = VK_SUCCESS;

			VkBufferCreateInfo bci;
			bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bci.pNext = NULL;
			bci.flags = 0;
			bci.size = _size;
			bci.queueFamilyIndexCount = 0;
			bci.pQueueFamilyIndices = NULL;
			bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			bci.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;

			result = vkCreateBuffer(m_device, &bci, m_allocatorCb, _buffer);
			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create host buffer error: vkCreateBuffer failed %d: %s.", result, getName(result) );
				return result;
			}

			VkMemoryRequirements mr;
			vkGetBufferMemoryRequirements(m_device, *_buffer, &mr);

			result = allocateMemory(&mr, _flags, _memory);

			if (VK_SUCCESS != result
			&&  (_flags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT) )
			{
				result = allocateMemory(&mr, _flags & ~VK_MEMORY_PROPERTY_HOST_CACHED_BIT, _memory);
			}

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create host buffer error: vkAllocateMemory failed %d: %s.", result, getName(result) );
				return result;
			}

			result = vkBindBufferMemory(m_device, *_buffer, *_memory, 0);
			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create host buffer error: vkBindBufferMemory failed %d: %s.", result, getName(result) );
				return result;
			}

			if (_data != NULL)
			{
				BGFX_PROFILER_SCOPE("map and copy data", kColorResource);
				void* dst;
				result = vkMapMemory(m_device, *_memory, 0, _size, 0, &dst);
				if (VK_SUCCESS != result)
				{
					BX_TRACE("Create host buffer error: vkMapMemory failed %d: %s.", result, getName(result) );
					return result;
				}

				bx::memCopy(dst, _data, _size);
				vkUnmapMemory(m_device, *_memory);
			}

			return result;
		}

		VkResult createStagingBuffer(uint32_t _size, ::VkBuffer* _buffer, ::VkDeviceMemory* _memory, const void* _data = NULL)
		{
			const VkMemoryPropertyFlags flags = 0
				| VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
				| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
				;
			return createHostBuffer(_size, flags, _buffer, _memory, _data);
		}

		StagingBufferVK allocFromScratchStagingBuffer(uint32_t _size, uint32_t _align, const void *_data = NULL)
		{
			BGFX_PROFILER_SCOPE("allocFromScratchStagingBuffer", kColorResource);

			StagingBufferVK result;
			ScratchBufferVK &scratch = m_scratchStagingBuffer[m_cmd.m_currentFrameInFlight];

			if (_size <= BGFX_CONFIG_MAX_STAGING_SIZE_FOR_SCRATCH_BUFFER)
			{
				const uint32_t scratchOffset = scratch.alloc(_size, _align);

				if (scratchOffset != UINT32_MAX)
				{
					result.m_isFromScratch = true;
					result.m_size = _size;
					result.m_offset = scratchOffset;
					result.m_buffer = scratch.m_buffer;
					result.m_deviceMem = scratch.m_deviceMem;
					result.m_data = scratch.m_data + result.m_offset;

					if (_data != NULL)
					{
						BGFX_PROFILER_SCOPE("copy to scratch", kColorResource);
						bx::memCopy(result.m_data, _data, _size);
					}

					return result;
				}
			}

			// Not enough space or too big, we will create a new staging buffer on the spot.
			result.m_isFromScratch = false;

			VK_CHECK(createStagingBuffer(_size, &result.m_buffer, &result.m_deviceMem, _data));

			result.m_size = _size;
			result.m_offset = 0;
			result.m_data = NULL;

			return result;
		}

		VkResult createReadbackBuffer(uint32_t _size, ::VkBuffer* _buffer, ::VkDeviceMemory* _memory)
		{
			const VkMemoryPropertyFlags flags = 0
				| VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
				| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
				| VK_MEMORY_PROPERTY_HOST_CACHED_BIT
				;

			return createHostBuffer(_size, flags, _buffer, _memory, NULL);
		}

		VkAllocationCallbacks*   m_allocatorCb;
		VkDebugReportCallbackEXT m_debugReportCallback;
		VkInstance       m_instance;
		VkPhysicalDevice m_physicalDevice;
		uint32_t         m_instanceApiVersion;

		VkPhysicalDeviceProperties       m_deviceProperties;
		VkPhysicalDeviceMemoryProperties m_memoryProperties;
		VkPhysicalDeviceFeatures         m_deviceFeatures;

		bool m_lineAASupport;
		bool m_borderColorSupport;
		bool m_timerQuerySupport;

		FrameBufferVK m_backBuffer;
		TextureFormat::Enum m_swapChainFormats[TextureFormat::Count];

		uint16_t m_numWindows;
		FrameBufferHandle m_windows[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		int64_t m_presentElapsed;

		ScratchBufferVK m_scratchBuffer[BGFX_CONFIG_MAX_FRAME_LATENCY];
		ScratchBufferVK m_scratchStagingBuffer[BGFX_CONFIG_MAX_FRAME_LATENCY];

		uint32_t        m_numFramesInFlight;
		CommandQueueVK  m_cmd;
		VkCommandBuffer m_commandBuffer;

		VkDevice m_device;
		uint32_t m_globalQueueFamily;
		VkQueue  m_globalQueue;
		VkDescriptorPool m_descriptorPool;
		VkPipelineCache  m_pipelineCache;

		TimerQueryVK m_gpuTimer;
		OcclusionQueryVK m_occlusionQuery;

		void* m_renderDocDll;
		void* m_vulkan1Dll;

		IndexBufferVK  m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBufferVK m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		ShaderVK       m_shaders[BGFX_CONFIG_MAX_SHADERS];
		ProgramVK      m_program[BGFX_CONFIG_MAX_PROGRAMS];
		TextureVK      m_textures[BGFX_CONFIG_MAX_TEXTURES];
		VertexLayout   m_vertexLayouts[BGFX_CONFIG_MAX_VERTEX_LAYOUTS];
		FrameBufferVK  m_frameBuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS];

		void* m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];
		Matrix4 m_predefinedUniforms[PredefinedUniform::Count];
		UniformRegistry m_uniformReg;

		StateCacheT<VkPipeline> m_pipelineStateCache;
		StateCacheT<VkDescriptorSetLayout> m_descriptorSetLayoutCache;
		StateCacheT<VkRenderPass> m_renderPassCache;
		StateCacheT<VkSampler> m_samplerCache;
		StateCacheT<uint32_t> m_samplerBorderColorCache;
		StateCacheLru<VkImageView, 1024> m_imageViewCache;

		Resolution m_resolution;
		float m_maxAnisotropy;
		bool m_depthClamp;
		bool m_wireframe;

		VkBuffer m_captureBuffer;
		VkDeviceMemory m_captureMemory;
		uint32_t m_captureSize;

		TextVideoMem m_textVideoMem;

		uint8_t m_fsScratch[64<<10];
		uint8_t m_vsScratch[64<<10];

		FrameBufferHandle m_fbh;
	};

	static RendererContextVK* s_renderVK;

	RendererContextI* rendererCreate(const Init& _init)
	{
		s_renderVK = BX_NEW(g_allocator, RendererContextVK);
		if (!s_renderVK->init(_init) )
		{
			bx::deleteObject(g_allocator, s_renderVK);
			s_renderVK = NULL;
		}
		return s_renderVK;
	}

	void rendererDestroy()
	{
		s_renderVK->shutdown();
		bx::deleteObject(g_allocator, s_renderVK);
		s_renderVK = NULL;
	}

#define VK_DESTROY_FUNC(_name)                                                          \
	void vkDestroy(Vk##_name& _obj)                                                     \
	{                                                                                   \
		if (VK_NULL_HANDLE != _obj)                                                     \
		{                                                                               \
			BGFX_PROFILER_SCOPE("vkDestroy" #_name, kColorResource);                    \
			vkDestroy##_name(s_renderVK->m_device, _obj.vk, s_renderVK->m_allocatorCb); \
			_obj = VK_NULL_HANDLE;                                                      \
		}                                                                               \
	}                                                                                   \
	void release(Vk##_name& _obj)                                                       \
	{                                                                                   \
		s_renderVK->release(_obj);                                                      \
	}
VK_DESTROY
#undef VK_DESTROY_FUNC

	void vkDestroy(VkDeviceMemory& _obj)
	{
		if (VK_NULL_HANDLE != _obj)
		{
			BGFX_PROFILER_SCOPE("vkFreeMemory", kColorResource);
			vkFreeMemory(s_renderVK->m_device, _obj.vk, s_renderVK->m_allocatorCb);
			_obj = VK_NULL_HANDLE;
		}
	}

	void vkDestroy(VkSurfaceKHR& _obj)
	{
		if (VK_NULL_HANDLE != _obj)
		{
			BGFX_PROFILER_SCOPE("vkDestroySurfaceKHR", kColorResource);
			vkDestroySurfaceKHR(s_renderVK->m_instance, _obj.vk, s_renderVK->m_allocatorCb);
			_obj = VK_NULL_HANDLE;
		}
	}

	void vkDestroy(VkDescriptorSet& _obj)
	{
		if (VK_NULL_HANDLE != _obj)
		{
			BGFX_PROFILER_SCOPE("vkFreeDescriptorSets", kColorResource);
			vkFreeDescriptorSets(s_renderVK->m_device, s_renderVK->m_descriptorPool, 1, &_obj);
			_obj = VK_NULL_HANDLE;
		}
	}

	void release(VkDeviceMemory& _obj)
	{
		s_renderVK->release(_obj);
	}

	void release(VkSurfaceKHR& _obj)
	{
		s_renderVK->release(_obj);
	}

	void release(VkDescriptorSet& _obj)
	{
		s_renderVK->release(_obj);
	}

	void ScratchBufferVK::create(uint32_t _size, uint32_t _count, VkBufferUsageFlags usage, uint32_t _align)
	{
		const VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;
		const VkDevice device = s_renderVK->m_device;

		const uint32_t entrySize = bx::strideAlign(_size, _align);
		const uint32_t totalSize = entrySize * _count;

		VkBufferCreateInfo bci;
		bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bci.pNext = NULL;
		bci.flags = 0;
		bci.size  = totalSize;
		bci.usage = usage;
		bci.sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
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

		VkMemoryPropertyFlags flags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
		VkResult result = s_renderVK->allocateMemory(&mr, flags, &m_deviceMem);

		if (VK_SUCCESS != result)
		{
			flags &= ~VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
			VK_CHECK(s_renderVK->allocateMemory(&mr, flags, &m_deviceMem) );
		}

		m_size = (uint32_t)mr.size;
		m_pos  = 0;
		m_align = _align;

		VK_CHECK(vkBindBufferMemory(device, m_buffer, m_deviceMem, 0) );

		VK_CHECK(vkMapMemory(device, m_deviceMem, 0, m_size, 0, (void**)&m_data) );
	}

	void ScratchBufferVK::createUniform(uint32_t _size, uint32_t _count)
	{
		const VkPhysicalDeviceLimits& deviceLimits = s_renderVK->m_deviceProperties.limits;
		const uint32_t align = uint32_t(deviceLimits.minUniformBufferOffsetAlignment);

		create(_size, _count, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, align);
	}

	void ScratchBufferVK::createStaging(uint32_t _size)
	{
		const VkPhysicalDeviceLimits& deviceLimits = s_renderVK->m_deviceProperties.limits;
		const uint32_t align = uint32_t(deviceLimits.optimalBufferCopyOffsetAlignment);

		create(_size, 1, VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, align);
	}

	void ScratchBufferVK::destroy()
	{
		reset();

		vkUnmapMemory(s_renderVK->m_device, m_deviceMem);

		s_renderVK->release(m_buffer);
		s_renderVK->release(m_deviceMem);
	}

	void ScratchBufferVK::reset()
	{
		m_pos = 0;
	}

	uint32_t ScratchBufferVK::alloc(uint32_t _size, uint32_t _minAlign)
	{
		const uint32_t align = bx::uint32_lcm(m_align, _minAlign);
		const uint32_t dstOffset = bx::strideAlign(m_pos, align);

		if (dstOffset + _size <= m_size)
		{
			m_pos = dstOffset + _size;
			return dstOffset;
		}

		return UINT32_MAX;
	}

	uint32_t ScratchBufferVK::write(const void* _data, uint32_t _size, uint32_t _minAlign)
	{
		uint32_t dstOffset = alloc(_size, _minAlign);
		BX_ASSERT(dstOffset != UINT32_MAX, "Not enough space on ScratchBuffer left to allocate %u bytes with alignment %u.", _size, _minAlign);

		if (_size > 0)
		{
			bx::memCopy(&m_data[dstOffset], _data, _size);
		}

		return dstOffset;
	}


	void ScratchBufferVK::flush()
	{
		const VkPhysicalDeviceLimits& deviceLimits = s_renderVK->m_deviceProperties.limits;
		VkDevice device = s_renderVK->m_device;

		const uint32_t align = uint32_t(deviceLimits.nonCoherentAtomSize);
		const uint32_t size  = bx::min(bx::strideAlign(m_pos, align), m_size);

		VkMappedMemoryRange range;
		range.sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		range.pNext  = NULL;
		range.memory = m_deviceMem;
		range.offset = 0;
		range.size   = size;
		VK_CHECK(vkFlushMappedMemoryRanges(device, 1, &range) );
	}

	void BufferVK::create(VkCommandBuffer _commandBuffer, uint32_t _size, void* _data, uint16_t _flags, bool _vertex, uint32_t _stride)
	{
		BX_UNUSED(_stride);

		m_size    = _size;
		m_flags   = _flags;
		m_dynamic = NULL == _data;

		const bool storage  = m_flags & BGFX_BUFFER_COMPUTE_READ_WRITE;
		const bool indirect = m_flags & BGFX_BUFFER_DRAW_INDIRECT;

		VkBufferCreateInfo bci;
		bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bci.pNext = NULL;
		bci.flags = 0;
		bci.size  = _size;
		bci.usage = 0
			| (_vertex              ? VK_BUFFER_USAGE_VERTEX_BUFFER_BIT   : VK_BUFFER_USAGE_INDEX_BUFFER_BIT)
			| (storage || indirect  ? VK_BUFFER_USAGE_STORAGE_BUFFER_BIT  : 0)
			| (indirect             ? VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT : 0)
			| VK_BUFFER_USAGE_TRANSFER_DST_BIT
			;
		bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		bci.queueFamilyIndexCount = 0;
		bci.pQueueFamilyIndices   = NULL;

		const VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;
		const VkDevice device = s_renderVK->m_device;
		VK_CHECK(vkCreateBuffer(device, &bci, allocatorCb, &m_buffer) );

		VkMemoryRequirements mr;
		vkGetBufferMemoryRequirements(device, m_buffer, &mr);

		VK_CHECK(s_renderVK->allocateMemory(&mr, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &m_deviceMem) );

		VK_CHECK(vkBindBufferMemory(device, m_buffer, m_deviceMem, 0) );

		if (!m_dynamic)
		{
			update(_commandBuffer, 0, _size, _data);
		}
	}

	void BufferVK::update(VkCommandBuffer _commandBuffer, uint32_t _offset, uint32_t _size, void* _data, bool _discard)
	{
		BGFX_PROFILER_SCOPE("BufferVK::update", kColorFrame);
		BX_UNUSED(_discard);

		StagingBufferVK stagingBuffer = s_renderVK->allocFromScratchStagingBuffer(_size, 8, _data);

		VkBufferCopy region;
		region.srcOffset = stagingBuffer.m_offset;
		region.dstOffset = _offset;
		region.size      = _size;
		vkCmdCopyBuffer(_commandBuffer, stagingBuffer.m_buffer, m_buffer, 1, &region);

		setMemoryBarrier(
			  _commandBuffer
			, VK_PIPELINE_STAGE_TRANSFER_BIT
			, VK_PIPELINE_STAGE_TRANSFER_BIT
			);

		if (!stagingBuffer.m_isFromScratch)
		{
			s_renderVK->release(stagingBuffer.m_buffer);
			s_renderVK->release(stagingBuffer.m_deviceMem);
		}
	}

	void BufferVK::destroy()
	{
		if (VK_NULL_HANDLE != m_buffer)
		{
			s_renderVK->release(m_buffer);
			s_renderVK->release(m_deviceMem);

			m_dynamic = false;
		}
	}

	void VertexBufferVK::create(VkCommandBuffer _commandBuffer, uint32_t _size, void* _data, VertexLayoutHandle _layoutHandle, uint16_t _flags)
	{
		BufferVK::create(_commandBuffer, _size, _data, _flags, true);
		m_layoutHandle = _layoutHandle;
	}

	void ShaderVK::create(const Memory* _mem)
	{
		bx::MemoryReader reader(_mem->data, _mem->size);

		bx::ErrorAssert err;

		uint32_t magic;
		bx::read(&reader, magic, &err);

		VkShaderStageFlagBits shaderStage = VK_SHADER_STAGE_ALL;

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

		m_oldBindingModel = isShaderVerLess(magic, 11);

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
			m_bindInfo[ii].index          = UINT32_MAX;
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

				auto textureDimensionToViewType = [](TextureDimension::Enum dimension)
				{
					switch (dimension)
					{
					case TextureDimension::Dimension1D:        return VK_IMAGE_VIEW_TYPE_1D;
					case TextureDimension::Dimension2D:        return VK_IMAGE_VIEW_TYPE_2D;
					case TextureDimension::Dimension2DArray:   return VK_IMAGE_VIEW_TYPE_2D_ARRAY;
					case TextureDimension::DimensionCube:      return VK_IMAGE_VIEW_TYPE_CUBE;
					case TextureDimension::DimensionCubeArray: return VK_IMAGE_VIEW_TYPE_CUBE_ARRAY;
					case TextureDimension::Dimension3D:        return VK_IMAGE_VIEW_TYPE_3D;
					default:                                   return VK_IMAGE_VIEW_TYPE_MAX_ENUM;
					}
				};

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
						// regCount is used for descriptor type
						const bool isBuffer = idToDescriptorType(regCount) == DescriptorType::StorageBuffer;
						if (0 == regIndex)
						{
							continue;
						}

						const uint8_t reverseShift = m_oldBindingModel
							? (fragment ? kSpirvOldFragmentShift : 0) + (isBuffer ? kSpirvOldBufferShift : kSpirvOldImageShift)
							: kSpirvBindShift;

						const uint16_t stage = regIndex - reverseShift; // regIndex is used for buffer binding index

						m_bindInfo[stage].type = isBuffer ? BindType::Buffer : BindType::Image;
						m_bindInfo[stage].uniformHandle  = { 0 };
						m_bindInfo[stage].binding        = regIndex;

						if (!isBuffer)
						{
							const VkImageViewType viewType = hasTexData
								? textureDimensionToViewType(idToTextureDimension(texDimension) )
								: VK_IMAGE_VIEW_TYPE_MAX_ENUM
								;

							if (VK_IMAGE_VIEW_TYPE_MAX_ENUM != viewType)
							{
								m_bindInfo[stage].index = m_numTextures;
								m_textures[m_numTextures].type = viewType;
								m_numTextures++;
							}
						}

						kind = "storage";
					}
					else if (UniformType::Sampler == (~kUniformMask & type) )
					{
						const uint8_t reverseShift = m_oldBindingModel
							? (fragment ? kSpirvOldFragmentShift : 0) + kSpirvOldTextureShift
							: kSpirvBindShift;

						const uint16_t stage = regIndex - reverseShift; // regIndex is used for image/sampler binding index

						const UniformRegInfo* info = s_renderVK->m_uniformReg.find(name);
						BX_ASSERT(NULL != info, "User defined uniform '%s' is not found, it won't be set.", name);

						m_bindInfo[stage].uniformHandle    = info->m_handle;
						m_bindInfo[stage].type             = BindType::Sampler;
						m_bindInfo[stage].binding          = regIndex;
						m_bindInfo[stage].samplerBinding   = regIndex + kSpirvSamplerShift;

						const VkImageViewType viewType = hasTexData
							? textureDimensionToViewType(idToTextureDimension(texDimension) )
							: VK_IMAGE_VIEW_TYPE_MAX_ENUM
							;

						if (VK_IMAGE_VIEW_TYPE_MAX_ENUM != viewType)
						{
							m_bindInfo[stage].index = m_numTextures;
							m_textures[m_numTextures].type = viewType;
							m_numTextures++;
						}

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

		VkShaderModuleCreateInfo smci;
		smci.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		smci.pNext    = NULL;
		smci.flags    = 0;
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

		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(hashIn);
		murmur.add(hashOut);
		murmur.add(m_code->data, m_code->size);
		murmur.add(m_numAttrs);
		murmur.add(m_attrMask,  m_numAttrs);
		murmur.add(m_attrRemap, m_numAttrs);
		m_hash = murmur.end();

		bx::read(&reader, m_size, &err);

		// fill binding description with uniform information
		uint16_t bidx = 0;
		if (m_size > 0)
		{
			m_uniformBinding = fragment ? (m_oldBindingModel ? kSpirvOldFragmentBinding : kSpirvFragmentBinding) : 0;

			VkDescriptorSetLayoutBinding& binding = m_bindings[bidx];
			binding.stageFlags = shaderStage;
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
					binding.stageFlags = shaderStage;
					binding.descriptorType = BindType::Buffer == m_bindInfo[ii].type
						? VK_DESCRIPTOR_TYPE_STORAGE_BUFFER
						: VK_DESCRIPTOR_TYPE_STORAGE_IMAGE
						;
					binding.binding = m_bindInfo[ii].binding;
					binding.pImmutableSamplers = NULL;
					binding.descriptorCount = 1;
					bidx++;
				}
				break;

				case BindType::Sampler:
				{
					VkDescriptorSetLayoutBinding& textureBinding = m_bindings[bidx];
					textureBinding.stageFlags = shaderStage;
					textureBinding.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
					textureBinding.binding = m_bindInfo[ii].binding;
					textureBinding.pImmutableSamplers = NULL;
					textureBinding.descriptorCount = 1;
					bidx++;

					VkDescriptorSetLayoutBinding& samplerBinding = m_bindings[bidx];
					samplerBinding.stageFlags = shaderStage;
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

		m_numTextures = 0;

		for (uint8_t stage = 0; stage < BX_COUNTOF(m_bindInfo); ++stage)
		{
			const ShaderVK* shader = NULL;
			if (isValid(m_vsh->m_bindInfo[stage].uniformHandle) )
			{
				shader = _vsh;

				BX_ASSERT(false
					  || NULL == m_fsh
					  || !isValid(m_fsh->m_bindInfo[stage].uniformHandle)
					  || !(m_vsh->m_oldBindingModel || m_fsh->m_oldBindingModel)
					, "Shared vertex/fragment bindings require shader binary version >= 11."
					);
			}
			else if (NULL != m_fsh
				 &&  isValid(m_fsh->m_bindInfo[stage].uniformHandle) )
			{
				shader = _fsh;
			}

			if (NULL != shader)
			{
				m_bindInfo[stage] = shader->m_bindInfo[stage];
				uint32_t& index = m_bindInfo[stage].index;
				if (UINT32_MAX != index)
				{
					m_textures[m_numTextures] = shader->m_textures[index];
					index = m_numTextures;
					m_numTextures++;
				}
			}
		}

		// create exact pipeline layout
		m_descriptorSetLayout = VK_NULL_HANDLE;

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

			uint32_t descriptorSetLayoutHash = murmur.end();

			m_descriptorSetLayout = s_renderVK->m_descriptorSetLayoutCache.find(descriptorSetLayoutHash);

			if (VK_NULL_HANDLE == m_descriptorSetLayout)
			{
				VkDescriptorSetLayoutBinding bindings[2 * BX_COUNTOF(ShaderVK::m_bindings)];

				bx::memCopy(
					  bindings
					, m_vsh->m_bindings
					, sizeof(VkDescriptorSetLayoutBinding) * m_vsh->m_numBindings
					);

				numBindings = m_vsh->m_numBindings;

				if (NULL != m_fsh)
				{
					for (uint16_t ii = 0; ii < m_fsh->m_numBindings; ii++)
					{
						const VkDescriptorSetLayoutBinding& fsBinding = m_fsh->m_bindings[ii];
						uint16_t vsBindingIdx = UINT16_MAX;
						for (uint16_t jj = 0; jj < m_vsh->m_numBindings; jj++)
						{
							if (fsBinding.binding == bindings[jj].binding)
							{
								vsBindingIdx = jj;
								break;
							}
						}
						if (UINT16_MAX != vsBindingIdx)
						{
							BX_ASSERT(
								  bindings[vsBindingIdx].descriptorType == fsBinding.descriptorType
								, "Mismatching descriptor types. Shaders compiled with different versions of shaderc?"
								);
							bindings[vsBindingIdx].stageFlags |= fsBinding.stageFlags;
						}
						else
						{
							bindings[numBindings] = fsBinding;
							numBindings++;
						}
					}
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
					, &m_descriptorSetLayout
					) );

				s_renderVK->m_descriptorSetLayoutCache.add(descriptorSetLayoutHash, m_descriptorSetLayout);
			}
		}

		VkPipelineLayoutCreateInfo plci;
		plci.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		plci.pNext = NULL;
		plci.flags = 0;
		plci.pushConstantRangeCount = 0;
		plci.pPushConstantRanges = NULL;
		plci.setLayoutCount = (m_descriptorSetLayout == VK_NULL_HANDLE ? 0 : 1);
		plci.pSetLayouts = &m_descriptorSetLayout;

		VK_CHECK(vkCreatePipelineLayout(
			  s_renderVK->m_device
			, &plci
			, s_renderVK->m_allocatorCb
			, &m_pipelineLayout
			) );
	}

	void ProgramVK::destroy()
	{
		s_renderVK->release(m_pipelineLayout);
		m_numPredefined = 0;
		m_vsh = NULL;
		m_fsh = NULL;
	}

	VkResult TimerQueryVK::init()
	{
		BGFX_PROFILER_SCOPE("TimerQueryVK::init", kColorFrame);
		VkResult result = VK_SUCCESS;

		const VkDevice device = s_renderVK->m_device;
		const VkCommandBuffer commandBuffer = s_renderVK->m_commandBuffer;

		const uint32_t count = m_control.m_size * 2;

		VkQueryPoolCreateInfo qpci;
		qpci.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
		qpci.pNext = NULL;
		qpci.flags = 0;
		qpci.queryType = VK_QUERY_TYPE_TIMESTAMP;
		qpci.queryCount = count;
		qpci.pipelineStatistics = 0;

		result = vkCreateQueryPool(device, &qpci, s_renderVK->m_allocatorCb, &m_queryPool);

		if (VK_SUCCESS != result)
		{
			BX_TRACE("Create timer query error: vkCreateQueryPool failed %d: %s.", result, getName(result) );
			return result;
		}

		vkCmdResetQueryPool(commandBuffer, m_queryPool, 0, count);

		const uint32_t size = count * sizeof(uint64_t);
		result = s_renderVK->createReadbackBuffer(size, &m_readback, &m_readbackMemory);

		if (VK_SUCCESS != result)
		{
			return result;
		}

		result = vkMapMemory(device, m_readbackMemory, 0, VK_WHOLE_SIZE, 0, (void**)&m_queryResult);

		if (VK_SUCCESS != result)
		{
			BX_TRACE("Create timer query error: vkMapMemory failed %d: %s.", result, getName(result) );
			return result;
		}

		m_frequency = uint64_t(1000000000.0 / double(s_renderVK->m_deviceProperties.limits.timestampPeriod) );

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_result); ++ii)
		{
			m_result[ii].reset();
		}

		m_control.reset();

		return result;
	}

	void TimerQueryVK::shutdown()
	{
		vkDestroy(m_queryPool);
		vkDestroy(m_readback);
		vkUnmapMemory(s_renderVK->m_device, m_readbackMemory);
		vkDestroy(m_readbackMemory);
	}

	uint32_t TimerQueryVK::begin(uint32_t _resultIdx, uint32_t _frameNum)
	{
		BGFX_PROFILER_SCOPE("TimerQueryVK::begin", kColorFrame);
		while (0 == m_control.reserve(1) )
		{
			m_control.consume(1);
		}

		Result& result = m_result[_resultIdx];
		++result.m_pending;

		const uint32_t idx = m_control.m_current;
		Query& query = m_query[idx];
		query.m_resultIdx = _resultIdx;
		query.m_ready     = false;
		query.m_frameNum  = _frameNum;

		const VkCommandBuffer commandBuffer = s_renderVK->m_commandBuffer;
		const uint32_t offset = idx * 2 + 0;

		vkCmdResetQueryPool(commandBuffer, m_queryPool, offset, 2);
		vkCmdWriteTimestamp(commandBuffer, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, m_queryPool, offset + 0);

		m_control.commit(1);

		return idx;
	}

	void TimerQueryVK::end(uint32_t _idx)
	{
		BGFX_PROFILER_SCOPE("TimerQueryVK::end", kColorFrame);
		Query& query = m_query[_idx];
		query.m_ready = true;
		query.m_completed = s_renderVK->m_cmd.m_submitted + s_renderVK->m_cmd.m_numFramesInFlight;

		const VkCommandBuffer commandBuffer = s_renderVK->m_commandBuffer;
		const uint32_t offset = _idx * 2 + 0;

		vkCmdWriteTimestamp(commandBuffer, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, m_queryPool, offset + 1);

		vkCmdCopyQueryPoolResults(
			  commandBuffer
			, m_queryPool
			, offset
			, 2
			, m_readback
			, offset * sizeof(uint64_t)
			, sizeof(uint64_t)
			, VK_QUERY_RESULT_WAIT_BIT | VK_QUERY_RESULT_64_BIT
			);

		setMemoryBarrier(commandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_HOST_BIT);

		while (update() )
		{
		}
	}

	bool TimerQueryVK::update()
	{
		if (0 != m_control.available() )
		{
			uint32_t idx = m_control.m_read;
			Query& query = m_query[idx];

			if (!query.m_ready)
			{
				return false;
			}

			if (query.m_completed > s_renderVK->m_cmd.m_submitted)
			{
				return false;
			}

			m_control.consume(1);

			Result& result = m_result[query.m_resultIdx];
			--result.m_pending;
			result.m_frameNum = query.m_frameNum;

			uint32_t offset = idx * 2;
			result.m_begin  = m_queryResult[offset+0];
			result.m_end    = m_queryResult[offset+1];

			return true;
		}

		return false;
	}

	VkResult OcclusionQueryVK::init()
	{
		BGFX_PROFILER_SCOPE("OcclusionQueryVK::init", kColorFrame);
		VkResult result = VK_SUCCESS;

		const VkDevice device = s_renderVK->m_device;
		const VkCommandBuffer commandBuffer = s_renderVK->m_commandBuffer;

		const uint32_t count = BX_COUNTOF(m_handle);

		VkQueryPoolCreateInfo qpci;
		qpci.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
		qpci.pNext = NULL;
		qpci.flags = 0;
		qpci.queryType = VK_QUERY_TYPE_OCCLUSION;
		qpci.queryCount = count;
		qpci.pipelineStatistics = 0;

		result = vkCreateQueryPool(device, &qpci, s_renderVK->m_allocatorCb, &m_queryPool);

		if (VK_SUCCESS != result)
		{
			BX_TRACE("Create occlusion query error: vkCreateQueryPool failed %d: %s.", result, getName(result) );
			return result;
		}

		vkCmdResetQueryPool(commandBuffer, m_queryPool, 0, count);

		const uint32_t size = count * sizeof(uint32_t);
		result = s_renderVK->createReadbackBuffer(size, &m_readback, &m_readbackMemory);

		if (VK_SUCCESS != result)
		{
			return result;
		}

		result = vkMapMemory(device, m_readbackMemory, 0, VK_WHOLE_SIZE, 0, (void**)&m_queryResult);

		if (VK_SUCCESS != result)
		{
			BX_TRACE("Create occlusion query error: vkMapMemory failed %d: %s.", result, getName(result) );
			return result;
		}

		m_control.reset();

		return result;
	}

	void OcclusionQueryVK::shutdown()
	{
		vkDestroy(m_queryPool);
		vkDestroy(m_readback);
		vkUnmapMemory(s_renderVK->m_device, m_readbackMemory);
		vkDestroy(m_readbackMemory);
	}

	void OcclusionQueryVK::begin(OcclusionQueryHandle _handle)
	{
		BGFX_PROFILER_SCOPE("OcclusionQueryVK::shutdown", kColorFrame);
		m_control.reserve(1);

		const VkCommandBuffer commandBuffer = s_renderVK->m_commandBuffer;

		m_handle[m_control.m_current] = _handle;
		vkCmdBeginQuery(commandBuffer, m_queryPool, _handle.idx, 0);
	}

	void OcclusionQueryVK::end()
	{
		BGFX_PROFILER_SCOPE("OcclusionQueryVK::end", kColorFrame);
		const VkCommandBuffer commandBuffer = s_renderVK->m_commandBuffer;

		const OcclusionQueryHandle handle = m_handle[m_control.m_current];
		vkCmdEndQuery(commandBuffer, m_queryPool, handle.idx);

		m_control.commit(1);
	}

	void OcclusionQueryVK::flush(Frame* _render)
	{
		BGFX_PROFILER_SCOPE("OcclusionQueryVK::flush", kColorFrame);
		if (0 < m_control.available() )
		{
			VkCommandBuffer commandBuffer = s_renderVK->m_commandBuffer;

			const uint32_t size = m_control.m_size;

			// need to copy each result individually because VK_QUERY_RESULT_WAIT_BIT causes
			// vkWaitForFences to hang indefinitely if we copy all results (including unavailable ones)
			for (uint32_t ii = 0, num = m_control.available(); ii < num; ++ii)
			{
				const OcclusionQueryHandle& handle = m_handle[(m_control.m_read + ii) % size];
				if (isValid(handle) )
				{
					vkCmdCopyQueryPoolResults(
						  commandBuffer
						, m_queryPool
						, handle.idx
						, 1
						, m_readback
						, handle.idx * sizeof(uint32_t)
						, sizeof(uint32_t)
						, VK_QUERY_RESULT_WAIT_BIT
						);
				}
			}

			setMemoryBarrier(commandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_HOST_BIT);
			s_renderVK->kick(true);

			commandBuffer = s_renderVK->m_commandBuffer;

			// resetting in the new command buffer prevents a false positive validation layer error
			const uint32_t count = BX_COUNTOF(m_handle);
			vkCmdResetQueryPool(commandBuffer, m_queryPool, 0, count);

			resolve(_render);
		}
	}

	void OcclusionQueryVK::resolve(Frame* _render)
	{
		while (0 != m_control.available() )
		{
			OcclusionQueryHandle handle = m_handle[m_control.m_read];
			if (isValid(handle) )
			{
				_render->m_occlusion[handle.idx] = m_queryResult[handle.idx];
			}
			m_control.consume(1);
		}
	}

	void OcclusionQueryVK::invalidate(OcclusionQueryHandle _handle)
	{
		const uint32_t size = m_control.m_size;

		for (uint32_t ii = 0, num = m_control.available(); ii < num; ++ii)
		{
			OcclusionQueryHandle& handle = m_handle[(m_control.m_read + ii) % size];
			if (handle.idx == _handle.idx)
			{
				handle.idx = bgfx::kInvalidHandle;
			}
		}
	}

	void ReadbackVK::create(VkImage _image, uint32_t _width, uint32_t _height, TextureFormat::Enum _format)
	{
		m_image  = _image;
		m_width  = _width;
		m_height = _height;
		m_format = _format;
	}

	void ReadbackVK::destroy()
	{
		m_image = VK_NULL_HANDLE;
	}

	uint32_t ReadbackVK::pitch(uint8_t _mip) const
	{
		uint32_t mipWidth = bx::uint32_max(1, m_width >> _mip);
		uint8_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_format) );
		return mipWidth * bpp / 8;
	}

	void ReadbackVK::copyImageToBuffer(VkCommandBuffer _commandBuffer, VkBuffer _buffer, VkImageLayout _layout, VkImageAspectFlags _aspect, uint8_t _mip) const
	{
		BGFX_PROFILER_SCOPE("ReadbackVK::copyImageToBuffer", kColorFrame);
		uint32_t mipWidth  = bx::uint32_max(1, m_width  >> _mip);
		uint32_t mipHeight = bx::uint32_max(1, m_height >> _mip);

		setImageMemoryBarrier(
			  _commandBuffer
			, m_image
			, _aspect
			, _layout
			, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
			, _mip
			, 1
			, 0
			, 1
			);

		VkBufferImageCopy bic;
		bic.bufferOffset = 0;
		bic.bufferRowLength   = mipWidth;
		bic.bufferImageHeight = mipHeight;
		bic.imageSubresource.aspectMask     = _aspect;
		bic.imageSubresource.mipLevel       = _mip;
		bic.imageSubresource.baseArrayLayer = 0;
		bic.imageSubresource.layerCount     = 1;
		bic.imageOffset = { 0, 0, 0 };
		bic.imageExtent = { mipWidth, mipHeight, 1 };

		vkCmdCopyImageToBuffer(
			  _commandBuffer
			, m_image
			, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
			, _buffer
			, 1
			, &bic
			);

		// Make changes to the buffer visible to the host
		setMemoryBarrier(
			_commandBuffer
			, VK_PIPELINE_STAGE_TRANSFER_BIT
			, VK_PIPELINE_STAGE_HOST_BIT
			);

		setImageMemoryBarrier(
			  _commandBuffer
			, m_image
			, _aspect
			, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
			, _layout
			, _mip
			, 1
			, 0
			, 1
			);
	}

	void ReadbackVK::readback(VkDeviceMemory _memory, VkDeviceSize _offset, void* _data, uint8_t _mip) const
	{
		BGFX_PROFILER_SCOPE("ReadbackVK::readback", kColorResource);
		if (m_image == VK_NULL_HANDLE)
		{
			return;
		}

		uint32_t mipHeight = bx::uint32_max(1, m_height >> _mip);
		uint32_t rowPitch = pitch(_mip);

		uint8_t* src;
		VK_CHECK(vkMapMemory(s_renderVK->m_device, _memory, 0, VK_WHOLE_SIZE, 0, (void**)&src) );
		src += _offset;
		uint8_t* dst = (uint8_t*)_data;

		for (uint32_t yy = 0; yy < mipHeight; ++yy)
		{
			bx::memCopy(dst, src, rowPitch);
			src += rowPitch;
			dst += rowPitch;
		}

		vkUnmapMemory(s_renderVK->m_device, _memory);
	}

	VkResult TextureVK::create(VkCommandBuffer _commandBuffer, uint32_t _width, uint32_t _height, uint64_t _flags, VkFormat _format)
	{
		BGFX_PROFILER_SCOPE("TextureVK::create", kColorResource);
		BX_ASSERT(0 != (_flags & BGFX_TEXTURE_RT_MASK), "");
		_flags |= BGFX_TEXTURE_RT_WRITE_ONLY;

		m_flags     = _flags;
		m_width     = _width;
		m_height    = _height;
		m_depth     = 1;
		m_numLayers = 1;
		m_requestedFormat = uint8_t(bimg::TextureFormat::Count);
		m_textureFormat   = uint8_t(bimg::TextureFormat::Count);
		m_format = _format;
		m_components = { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY };
		m_aspectMask = getAspectMask(m_format);
		m_sampler = s_msaa[bx::uint32_satsub( (m_flags & BGFX_TEXTURE_RT_MSAA_MASK) >> BGFX_TEXTURE_RT_MSAA_SHIFT, 1)];
		m_type = VK_IMAGE_VIEW_TYPE_2D;
		m_numMips = 1;
		m_numSides = 1;

		VkResult result = createImages(_commandBuffer);

		if (VK_SUCCESS == result)
		{
			const VkImageLayout layout = 0 != (m_aspectMask & (VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT) )
				? VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
				: VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
				;
			setImageMemoryBarrier(_commandBuffer, layout);
		}

		return result;
	}

	VkResult TextureVK::createImages(VkCommandBuffer _commandBuffer)
	{
		BGFX_PROFILER_SCOPE("TextureVK::createImages", kColorResource);
		VkResult result = VK_SUCCESS;

		const VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;
		const VkDevice device = s_renderVK->m_device;

		if (m_sampler.Count > 1)
		{
			BX_ASSERT(VK_IMAGE_VIEW_TYPE_3D != m_type, "Can't create multisample 3D image.");
			BX_ASSERT(m_numMips <= 1, "Can't create multisample image with mip chain.");
		}

		// create texture and allocate its device memory
		VkImageCreateInfo ici;
		ici.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		ici.pNext = NULL;
		ici.flags = 0
			| (VK_IMAGE_VIEW_TYPE_CUBE == m_type
				? VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT
				: 0
				)
			| (VK_IMAGE_VIEW_TYPE_3D == m_type
				? VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT_KHR
				: 0
				)
			;
		ici.pQueueFamilyIndices   = NULL;
		ici.queueFamilyIndexCount = 0;
		ici.initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED;
		ici.sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
		ici.usage                 = 0
			| VK_IMAGE_USAGE_TRANSFER_SRC_BIT
			| VK_IMAGE_USAGE_TRANSFER_DST_BIT
			| VK_IMAGE_USAGE_SAMPLED_BIT
			| (m_flags & BGFX_TEXTURE_RT_MASK
				? (m_aspectMask & (VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT)
					? VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
					: VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
				: 0
				)
			| (m_flags & BGFX_TEXTURE_COMPUTE_WRITE ? VK_IMAGE_USAGE_STORAGE_BIT : 0)
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

		result = vkCreateImage(device, &ici, allocatorCb, &m_textureImage);
		if (VK_SUCCESS != result)
		{
			BX_TRACE("Create texture image error: vkCreateImage failed %d: %s.", result, getName(result) );
			return result;
		}

		VkMemoryRequirements imageMemReq;
		vkGetImageMemoryRequirements(device, m_textureImage, &imageMemReq);

		result = s_renderVK->allocateMemory(&imageMemReq, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &m_textureDeviceMem);
		if (VK_SUCCESS != result)
		{
			BX_TRACE("Create texture image error: allocateMemory failed %d: %s.", result, getName(result) );
			return result;
		}

		result = vkBindImageMemory(device, m_textureImage, m_textureDeviceMem, 0);
		if (VK_SUCCESS != result)
		{
			BX_TRACE("Create texture image error: vkBindImageMemory failed %d: %s.", result, getName(result) );
			return result;
		}

		m_sampledLayout = m_flags & BGFX_TEXTURE_COMPUTE_WRITE
			? VK_IMAGE_LAYOUT_GENERAL
			: VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
			;

		const bool needResolve = true
			&& 1 < m_sampler.Count
			&& 0 != (ici.usage & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
			&& 0 == (m_flags & BGFX_TEXTURE_MSAA_SAMPLE)
			&& 0 == (m_flags & BGFX_TEXTURE_RT_WRITE_ONLY)
			;

		if (needResolve)
		{
			VkImageCreateInfo ici_resolve = ici;
			ici_resolve.samples = s_msaa[0].Sample;
			ici_resolve.usage &= ~VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
			ici_resolve.flags &= ~VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;

			result = vkCreateImage(device, &ici_resolve, allocatorCb, &m_singleMsaaImage);
			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create texture image error: vkCreateImage failed %d: %s.", result, getName(result) );
				return result;
			}

			VkMemoryRequirements imageMemReq_resolve;
			vkGetImageMemoryRequirements(device, m_singleMsaaImage, &imageMemReq_resolve);

			result = s_renderVK->allocateMemory(&imageMemReq_resolve, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &m_singleMsaaDeviceMem);
			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create texture image error: allocateMemory failed %d: %s.", result, getName(result) );
				return result;
			}

			result = vkBindImageMemory(device, m_singleMsaaImage, m_singleMsaaDeviceMem, 0);
			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create texture image error: vkBindImageMemory failed %d: %s.", result, getName(result) );
				return result;
			}

			setImageMemoryBarrier(_commandBuffer, m_sampledLayout, true);
		}

		return result;
	}

	void* TextureVK::create(VkCommandBuffer _commandBuffer, const Memory* _mem, uint64_t _flags, uint8_t _skip)
	{
		BGFX_PROFILER_SCOPE("TextureVK::create", kColorResource);
		bimg::ImageContainer imageContainer;

		if (bimg::imageParse(imageContainer, _mem->data, _mem->size) )
		{
			const bimg::ImageBlockInfo& blockInfo = bimg::getBlockInfo(imageContainer.m_format);
			const uint8_t startLod = bx::min<uint8_t>(_skip, imageContainer.m_numMips - 1);

			bimg::TextureInfo ti;
			bimg::imageGetSize(
				  &ti
				, uint16_t(imageContainer.m_width  >> startLod)
				, uint16_t(imageContainer.m_height >> startLod)
				, uint16_t(imageContainer.m_depth  >> startLod)
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

			m_aspectMask = getAspectMask(m_format);
			m_sampler = s_msaa[bx::uint32_satsub( (m_flags & BGFX_TEXTURE_RT_MSAA_MASK) >> BGFX_TEXTURE_RT_MSAA_SHIFT, 1)];

			if (imageContainer.m_cubeMap)
			{
				m_type = imageContainer.m_numLayers > 1
					? VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
					: VK_IMAGE_VIEW_TYPE_CUBE
					;
			}
			else if (imageContainer.m_depth > 1)
			{
				m_type = VK_IMAGE_VIEW_TYPE_3D;
			}
			else if (imageContainer.m_numLayers > 1)
			{
				m_type = VK_IMAGE_VIEW_TYPE_2D_ARRAY;
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

			VK_CHECK(createImages(_commandBuffer) );

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
				uint32_t mipLevel;
				uint32_t layer;
			};

			ImageInfo* imageInfos = (ImageInfo*)bx::alloc(g_allocator, sizeof(ImageInfo) * numSrd);
			bx::memSet(imageInfos, 0, sizeof(ImageInfo) * numSrd);
			uint32_t alignment = 1; // tightly aligned buffer

			for (uint16_t side = 0; side < numSides; ++side)
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
							const uint32_t size  = slice * mip.m_depth;

							uint8_t* temp = (uint8_t*)bx::alloc(g_allocator, size);
							bimg::imageDecodeToBgra8(
								  g_allocator
								, temp
								, mip.m_data
								, mip.m_width
								, mip.m_height
								, pitch
								, mip.m_format
								);

							imageInfos[kk].data     = temp;
							imageInfos[kk].width    = mip.m_width;
							imageInfos[kk].height   = mip.m_height;
							imageInfos[kk].depth    = mip.m_depth;
							imageInfos[kk].pitch    = pitch;
							imageInfos[kk].slice    = slice;
							imageInfos[kk].size     = size;
							imageInfos[kk].mipLevel = lod;
							imageInfos[kk].layer    = side;
						}
						else if (compressed)
						{
							const uint32_t pitch = bx::strideAlign( (mip.m_width / blockInfo.blockWidth) * mip.m_blockSize, alignment);
							const uint32_t slice = bx::strideAlign( (mip.m_height / blockInfo.blockHeight) * pitch, alignment);
							const uint32_t size  = slice * mip.m_depth;

							uint8_t* temp = (uint8_t*)bx::alloc(g_allocator, size);
							bimg::imageCopy(
								  temp
								, mip.m_height / blockInfo.blockHeight
								, (mip.m_width / blockInfo.blockWidth) * mip.m_blockSize
								, mip.m_depth
								, mip.m_data
								, pitch
								);

							imageInfos[kk].data     = temp;
							imageInfos[kk].width    = mip.m_width;
							imageInfos[kk].height   = mip.m_height;
							imageInfos[kk].depth    = mip.m_depth;
							imageInfos[kk].pitch    = pitch;
							imageInfos[kk].slice    = slice;
							imageInfos[kk].size     = size;
							imageInfos[kk].mipLevel = lod;
							imageInfos[kk].layer    = side;
						}
						else
						{
							const uint32_t pitch = bx::strideAlign(mip.m_width * mip.m_bpp / 8, alignment);
							const uint32_t slice = bx::strideAlign(mip.m_height * pitch, alignment);
							const uint32_t size  = slice * mip.m_depth;

							uint8_t* temp = (uint8_t*)bx::alloc(g_allocator, size);
							bimg::imageCopy(
								  temp
								, mip.m_height
								, mip.m_width * mip.m_bpp / 8
								, mip.m_depth
								, mip.m_data
								, pitch
								);

							imageInfos[kk].data     = temp;
							imageInfos[kk].width    = mip.m_width;
							imageInfos[kk].height   = mip.m_height;
							imageInfos[kk].depth    = mip.m_depth;
							imageInfos[kk].pitch    = pitch;
							imageInfos[kk].slice    = slice;
							imageInfos[kk].size     = size;
							imageInfos[kk].mipLevel = lod;
							imageInfos[kk].layer    = side;
						}
					}
					++kk;
				}
			}

			uint32_t totalMemSize = 0;
			VkBufferImageCopy* bufferCopyInfo = (VkBufferImageCopy*)bx::alloc(g_allocator, sizeof(VkBufferImageCopy) * numSrd);

			for (uint32_t ii = 0; ii < numSrd; ++ii)
			{
				const uint32_t idealWidth  = bx::max<uint32_t>(1, m_width  >> imageInfos[ii].mipLevel);
				const uint32_t idealHeight = bx::max<uint32_t>(1, m_height >> imageInfos[ii].mipLevel);
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

			if (totalMemSize > 0)
			{
				const VkDevice device = s_renderVK->m_device;
				const bimg::ImageBlockInfo &dstBlockInfo = bimg::getBlockInfo(bimg::TextureFormat::Enum(m_textureFormat));

				StagingBufferVK stagingBuffer = s_renderVK->allocFromScratchStagingBuffer(totalMemSize, dstBlockInfo.blockSize);

				uint8_t* mappedMemory;

				if (!stagingBuffer.m_isFromScratch)
				{
					VK_CHECK(vkMapMemory(
						  device
						, stagingBuffer.m_deviceMem
						, 0
						, totalMemSize
						, 0
						, (void**)&mappedMemory
						) );
				}
				else
				{
					mappedMemory = stagingBuffer.m_data;
				}

				// copy image to staging buffer
				for (uint32_t ii = 0; ii < numSrd; ++ii)
				{
					bx::memCopy(mappedMemory, imageInfos[ii].data, imageInfos[ii].size);
					mappedMemory += imageInfos[ii].size;
					bufferCopyInfo[ii].bufferOffset += stagingBuffer.m_offset;
					BX_ASSERT(
						  bx::uint32_mod(bufferCopyInfo[ii].bufferOffset, dstBlockInfo.blockSize) == 0
						, "Alignment for subimage %u is not aligned correctly (%u)."
						, ii, bufferCopyInfo[ii].bufferOffset, dstBlockInfo.blockSize
						);
				}

				if (!stagingBuffer.m_isFromScratch)
				{
					vkUnmapMemory(device, stagingBuffer.m_deviceMem);
				}

				copyBufferToTexture(_commandBuffer, stagingBuffer.m_buffer, numSrd, bufferCopyInfo);

				if (!stagingBuffer.m_isFromScratch)
				{
					s_renderVK->release(stagingBuffer.m_buffer);
					s_renderVK->release(stagingBuffer.m_deviceMem);
				}
			}
			else
			{
				setImageMemoryBarrier(_commandBuffer, m_sampledLayout);
			}

			bx::free(g_allocator, bufferCopyInfo);

			for (uint32_t ii = 0; ii < numSrd; ++ii)
			{
				bx::free(g_allocator, imageInfos[ii].data);
			}

			bx::free(g_allocator, imageInfos);

			m_readback.create(m_textureImage, m_width, m_height, TextureFormat::Enum(m_textureFormat) );
		}

		return m_directAccessPtr;
	}

	void TextureVK::destroy()
	{
		BGFX_PROFILER_SCOPE("TextureVK::destroy", kColorResource);
		m_readback.destroy();

		if (VK_NULL_HANDLE != m_textureImage)
		{
			s_renderVK->release(m_textureImage);
			s_renderVK->release(m_textureDeviceMem);
		}

		if (VK_NULL_HANDLE != m_singleMsaaImage)
		{
			s_renderVK->release(m_singleMsaaImage);
			s_renderVK->release(m_singleMsaaDeviceMem);
		}

		m_currentImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		m_currentSingleMsaaImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	}

	void TextureVK::update(VkCommandBuffer _commandBuffer, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem)
	{
		BGFX_PROFILER_SCOPE("TextureVK::update", kColorResource);
		const uint32_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat) );
		const bimg::ImageBlockInfo& blockInfo = bimg::getBlockInfo(bimg::TextureFormat::Enum(m_textureFormat) );
		uint32_t rectpitch = _rect.m_width * bpp / 8;
		uint32_t slicepitch = rectpitch * _rect.m_height;
		uint32_t align = blockInfo.blockSize;
		if (bimg::isCompressed(bimg::TextureFormat::Enum(m_textureFormat) ) )
		{
			rectpitch  = (_rect.m_width  / blockInfo.blockWidth ) * blockInfo.blockSize;
			slicepitch = (_rect.m_height / blockInfo.blockHeight) * rectpitch;
		}
		const uint32_t srcpitch = UINT16_MAX == _pitch ? rectpitch : _pitch;
		const uint32_t size     = UINT16_MAX == _pitch ? slicepitch  * _depth: _rect.m_height * _pitch * _depth;
		const bool convert = m_textureFormat != m_requestedFormat;

		VkBufferImageCopy region;
		region.bufferOffset      = 0;
		region.bufferRowLength   = (_pitch == UINT16_MAX ? 0 : _pitch * 8 / bpp);
		region.bufferImageHeight = 0;
		region.imageSubresource.aspectMask     = m_aspectMask;
		region.imageSubresource.mipLevel       = _mip;
		region.imageSubresource.baseArrayLayer = 0;
		region.imageSubresource.layerCount     = 1;
		region.imageOffset = { _rect.m_x,     _rect.m_y,      0      };
		region.imageExtent = { _rect.m_width, _rect.m_height, _depth };

		uint8_t* data = _mem->data;
		uint8_t* temp = NULL;

		if (convert)
		{
			temp = (uint8_t*)bx::alloc(g_allocator, slicepitch);
			bimg::imageDecodeToBgra8(g_allocator, temp, data, _rect.m_width, _rect.m_height, srcpitch, bimg::TextureFormat::Enum(m_requestedFormat));
			data = temp;

			region.imageExtent =
			{
				bx::max(1u, m_width  >> _mip),
				bx::max(1u, m_height >> _mip),
				_depth,
			};
		}

		StagingBufferVK stagingBuffer = s_renderVK->allocFromScratchStagingBuffer(size, align, data);
		region.bufferOffset += stagingBuffer.m_offset;
		BX_ASSERT(region.bufferOffset % align == 0,
				"Alignment for image (mip %u, z %s) is not aligned correctly (%u).",
				_mip, _z, region.bufferOffset, align);

		if (VK_IMAGE_VIEW_TYPE_3D == m_type)
		{
			region.imageOffset.z = _z;
		}
		else if (VK_IMAGE_VIEW_TYPE_CUBE == m_type
		||       VK_IMAGE_VIEW_TYPE_CUBE_ARRAY == m_type)
		{
			region.imageSubresource.baseArrayLayer = _z * 6 + _side;
		}
		else
		{
			region.imageSubresource.baseArrayLayer = _z;
		}

		copyBufferToTexture(_commandBuffer, stagingBuffer.m_buffer, 1, &region);

		if (!stagingBuffer.m_isFromScratch)
		{
			s_renderVK->release(stagingBuffer.m_buffer);
			s_renderVK->release(stagingBuffer.m_deviceMem);
		}

		if (NULL != temp)
		{
			bx::free(g_allocator, temp);
		}
	}

	void TextureVK::resolve(VkCommandBuffer _commandBuffer, uint8_t _resolve, uint32_t _layer, uint32_t _numLayers, uint32_t _mip)
	{
		BGFX_PROFILER_SCOPE("TextureVK::resolve", kColorResource);
		const bool needResolve = VK_NULL_HANDLE != m_singleMsaaImage;

		const bool needMipGen = true
			&& !needResolve
			&& 0 != (m_flags & BGFX_TEXTURE_RT_MASK)
			&& 0 == (m_flags & BGFX_TEXTURE_RT_WRITE_ONLY)
			&& (_mip + 1) < m_numMips
			&& 0 != (_resolve & BGFX_RESOLVE_AUTO_GEN_MIPS)
			;

		const VkImageLayout oldLayout = m_currentImageLayout;
		const VkImageLayout oldSingleMsaaLayout = m_currentSingleMsaaImageLayout;

		const uint32_t numLayers = false
			|| m_type == VK_IMAGE_VIEW_TYPE_CUBE
			|| m_type == VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
			? m_numSides
			: _numLayers
			;

		if (needResolve)
		{
			setImageMemoryBarrier(_commandBuffer, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
			setImageMemoryBarrier(_commandBuffer, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, true);

			VkImageResolve resolve;
			resolve.srcOffset.x = 0;
			resolve.srcOffset.y = 0;
			resolve.srcOffset.z = 0;
			resolve.dstOffset.x = 0;
			resolve.dstOffset.y = 0;
			resolve.dstOffset.z = 0;
			resolve.srcSubresource.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
			resolve.srcSubresource.mipLevel       = _mip;
			resolve.srcSubresource.baseArrayLayer = _layer;
			resolve.srcSubresource.layerCount     = numLayers;
			resolve.dstSubresource.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
			resolve.dstSubresource.mipLevel       = _mip;
			resolve.dstSubresource.baseArrayLayer = _layer;
			resolve.dstSubresource.layerCount     = numLayers;
			resolve.extent.width  = m_width;
			resolve.extent.height = m_height;
			resolve.extent.depth  = 1;

			vkCmdResolveImage(
				  _commandBuffer
				, m_textureImage
				, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
				, m_singleMsaaImage
				, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
				, 1
				, &resolve
				);
		}

		if (needMipGen)
		{
			BGFX_PROFILER_SCOPE("TextureVK::resolve genMipmaps", kColorResource);
			setImageMemoryBarrier(_commandBuffer, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

			int32_t mipWidth  = bx::max<int32_t>(int32_t(m_width)  >> _mip, 1);
			int32_t mipHeight = bx::max<int32_t>(int32_t(m_height) >> _mip, 1);

			const VkFilter filter = bimg::isDepth(bimg::TextureFormat::Enum(m_textureFormat) )
				? VK_FILTER_NEAREST
				: VK_FILTER_LINEAR
				;

			VkImageBlit blit;
			blit.srcOffsets[0] = { 0, 0, 0 };
			blit.srcOffsets[1] = { mipWidth, mipHeight, 1 };
			blit.srcSubresource.aspectMask     = m_aspectMask;
			blit.srcSubresource.mipLevel       = 0;
			blit.srcSubresource.baseArrayLayer = _layer;
			blit.srcSubresource.layerCount     = numLayers;
			blit.dstOffsets[0] = { 0, 0, 0 };
			blit.dstOffsets[1] = { mipWidth, mipHeight, 1 };
			blit.dstSubresource.aspectMask     = m_aspectMask;
			blit.dstSubresource.mipLevel       = 0;
			blit.dstSubresource.baseArrayLayer = _layer;
			blit.dstSubresource.layerCount     = numLayers;

			for (uint32_t i = _mip + 1; i < m_numMips; i++)
			{
				BGFX_PROFILER_SCOPE("mipmap", kColorResource);
				blit.srcOffsets[1] = { mipWidth, mipHeight, 1 };
				blit.srcSubresource.mipLevel = i - 1;

				mipWidth  = bx::uint32_max(mipWidth  >> 1, 1);
				mipHeight = bx::uint32_max(mipHeight >> 1, 1);

				blit.dstOffsets[1] = { mipWidth, mipHeight, 1 };
				blit.dstSubresource.mipLevel = i;

				vk::setImageMemoryBarrier(
					  _commandBuffer
					, m_textureImage
					, m_aspectMask
					, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
					, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
					, blit.srcSubresource.mipLevel
					, 1
					, _layer
					, numLayers
					);

				vkCmdBlitImage(
					  _commandBuffer
					, m_textureImage
					, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
					, m_textureImage
					, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
					, 1
					, &blit
					, filter
					);
			}

			vk::setImageMemoryBarrier(
				  _commandBuffer
				, m_textureImage
				, m_aspectMask
				, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
				, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
				, _mip
				, m_numMips - _mip - 1
				, _layer
				, numLayers
				);
		}

		setImageMemoryBarrier(_commandBuffer, oldLayout);
		setImageMemoryBarrier(_commandBuffer, oldSingleMsaaLayout, true);
	}

	void TextureVK::copyBufferToTexture(VkCommandBuffer _commandBuffer, VkBuffer _stagingBuffer, uint32_t _bufferImageCopyCount, VkBufferImageCopy* _bufferImageCopy)
	{
		BGFX_PROFILER_SCOPE("TextureVK::copyBufferToTexture", kColorResource);
		const VkImageLayout oldLayout = m_currentImageLayout == VK_IMAGE_LAYOUT_UNDEFINED
			? m_sampledLayout
			: m_currentImageLayout
			;

		setImageMemoryBarrier(_commandBuffer, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

		bimg::TextureFormat::Enum format = bimg::TextureFormat::Enum(m_textureFormat);
		const bimg::ImageBlockInfo& blockInfo = bimg::getBlockInfo(format);
		for (uint32_t ii = 0; ii < _bufferImageCopyCount; ++ii)
		{
			BX_ASSERT(
				  bx::uint32_mod(_bufferImageCopy[ii].bufferOffset, blockInfo.blockSize) == 0
				, "Misaligned texture of type %s to offset %u, which is not a multiple of %u."
				, bimg::getName(format), _bufferImageCopy[ii].bufferOffset, blockInfo.blockSize
				);
		}
		BX_UNUSED(blockInfo);

		vkCmdCopyBufferToImage(
			  _commandBuffer
			, _stagingBuffer
			, m_textureImage
			, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
			, _bufferImageCopyCount
			, _bufferImageCopy
			);

		setImageMemoryBarrier(_commandBuffer, oldLayout);
	}

	VkImageLayout TextureVK::setImageMemoryBarrier(VkCommandBuffer _commandBuffer, VkImageLayout _newImageLayout, bool _singleMsaaImage)
	{
		if (_singleMsaaImage && VK_NULL_HANDLE == m_singleMsaaImage)
		{
			return VK_IMAGE_LAYOUT_UNDEFINED;
		}

		VkImageLayout& currentLayout = _singleMsaaImage
			? m_currentSingleMsaaImageLayout
			: m_currentImageLayout
			;

		const VkImageLayout oldLayout = currentLayout;

		if (currentLayout == _newImageLayout)
		{
			return oldLayout;
		}

		const VkImage image = _singleMsaaImage
			? m_singleMsaaImage
			: m_textureImage
			;

		vk::setImageMemoryBarrier(
			  _commandBuffer
			, image
			, m_aspectMask
			, currentLayout
			, _newImageLayout
			);

		currentLayout = _newImageLayout;
		return oldLayout;
	}

	VkResult TextureVK::createView(uint32_t _layer, uint32_t _numLayers, uint32_t _mip, uint32_t _numMips, VkImageViewType _type, VkImageAspectFlags _aspectMask, bool _renderTarget, ::VkImageView* _view) const
	{
		VkResult result = VK_SUCCESS;

		if (VK_IMAGE_VIEW_TYPE_3D == m_type)
		{
			BX_ASSERT(false
				  || !_renderTarget
				  || !(m_aspectMask & (VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT) )
				, "3D image can't be a depth attachment"
			);
		}

		if (VK_IMAGE_VIEW_TYPE_CUBE       == _type
		||  VK_IMAGE_VIEW_TYPE_CUBE_ARRAY == _type)
		{
			BX_ASSERT(_numLayers % 6 == 0, "");
			BX_ASSERT(
				  VK_IMAGE_VIEW_TYPE_3D != m_type
				, "3D image can't be aliased as a cube texture"
				);
		}

		VkImageViewCreateInfo viewInfo;
		viewInfo.sType      = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewInfo.pNext      = NULL;
		viewInfo.flags      = 0;
		viewInfo.image      = ((VK_NULL_HANDLE != m_singleMsaaImage) && !_renderTarget)
			? m_singleMsaaImage
			: m_textureImage
			;
		viewInfo.viewType   = _type;
		viewInfo.format     = m_format;
		viewInfo.components = m_components;
		viewInfo.subresourceRange.aspectMask     = m_aspectMask & _aspectMask;
		viewInfo.subresourceRange.baseMipLevel   = _mip;
		viewInfo.subresourceRange.levelCount     = _numMips;
		viewInfo.subresourceRange.baseArrayLayer = _layer;
		viewInfo.subresourceRange.layerCount     = 1;

		if (VK_IMAGE_VIEW_TYPE_2D != _type
		&&  VK_IMAGE_VIEW_TYPE_3D != _type)
		{
			viewInfo.subresourceRange.layerCount = VK_IMAGE_VIEW_TYPE_CUBE == _type
				? 6
				: _numLayers
				;
		}

		VkImageView view = VK_NULL_HANDLE;

		result = vkCreateImageView(
			  s_renderVK->m_device
			, &viewInfo
			, s_renderVK->m_allocatorCb
			, &view
			);

		if (VK_SUCCESS != result)
		{
			BX_TRACE("Create texture view error: vkCreateImageView failed %d: %s.", result, getName(result) );
			return result;
		}

		*_view = view;

		return result;
	}

	VkImageAspectFlags TextureVK::getAspectMask(VkFormat _format)
	{
		switch (_format)
		{
		case VK_FORMAT_S8_UINT:
			return VK_IMAGE_ASPECT_STENCIL_BIT;
			break;
		case VK_FORMAT_D16_UNORM:
		case VK_FORMAT_X8_D24_UNORM_PACK32:
		case VK_FORMAT_D32_SFLOAT:
			return VK_IMAGE_ASPECT_DEPTH_BIT;
		case VK_FORMAT_D16_UNORM_S8_UINT:
		case VK_FORMAT_D24_UNORM_S8_UINT:
		case VK_FORMAT_D32_SFLOAT_S8_UINT:
			return VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
		default:
			return VK_IMAGE_ASPECT_COLOR_BIT;
		}
	}

	VkResult SwapChainVK::create(VkCommandBuffer _commandBuffer, void* _nwh, const Resolution& _resolution, TextureFormat::Enum _depthFormat)
	{
		struct ErrorState
		{
			enum Enum
			{
				Default,
				SurfaceCreated,
				SwapChainCreated,
				AttachmentsCreated
			};
		};

		ErrorState::Enum errorState = ErrorState::Default;

		VkResult result = VK_SUCCESS;

		if (NULL == _nwh)
		{
			return result;
		}

		m_nwh = _nwh;
		m_resolution = _resolution;
		m_depthFormat = TextureFormat::Count == _depthFormat ? TextureFormat::D24S8 : _depthFormat;

		m_queue = s_renderVK->m_globalQueue;

		result = createSurface();

		if (VK_SUCCESS != result)
		{
			BX_TRACE("Create swap chain error: creating surface failed %d: %s.", result, getName(result) );
			goto error;
		}

		errorState = ErrorState::SurfaceCreated;

		{
			m_sci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			m_sci.pNext = NULL;
			m_sci.flags = 0;
			m_sci.imageArrayLayers      = 1;
			m_sci.imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE;
			m_sci.queueFamilyIndexCount = 0;
			m_sci.pQueueFamilyIndices   = NULL;
			m_sci.preTransform          = BX_ENABLED(BX_PLATFORM_NX)
				? VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR
				: VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR
				;
			m_sci.oldSwapchain          = VK_NULL_HANDLE;

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_backBufferColorImageView); ++ii)
			{
				m_backBufferColorImage[ii]     = VK_NULL_HANDLE;
				m_backBufferColorImageView[ii] = VK_NULL_HANDLE;
				m_backBufferFrameBuffer[ii]    = VK_NULL_HANDLE;
				m_backBufferFence[ii]          = VK_NULL_HANDLE;
				m_presentDoneSemaphore[ii]     = VK_NULL_HANDLE;
				m_renderDoneSemaphore[ii]      = VK_NULL_HANDLE;
			}

			m_lastImageRenderedSemaphore = VK_NULL_HANDLE;
			m_lastImageAcquiredSemaphore = VK_NULL_HANDLE;

			result = createSwapChain();

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create swap chain error: creating swapchain and image views failed %d: %s", result, getName(result) );
				goto error;
			}
		}

		errorState = ErrorState::SwapChainCreated;

		{
			result = createAttachments(_commandBuffer);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create swap chain error: creating MSAA/depth attachments failed %d: %s.", result, getName(result) );
				goto error;
			}
		}

		errorState = ErrorState::AttachmentsCreated;

		{
			result = createFrameBuffer();

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create swap chain error: creating frame buffers failed %d: %s.", result, getName(result) );
				goto error;
			}
		}

		return VK_SUCCESS;

	error:
		BX_TRACE("errorState %d", errorState);
		switch (errorState)
		{
		case ErrorState::AttachmentsCreated:
			releaseAttachments();
			[[fallthrough]];

		case ErrorState::SwapChainCreated:
			releaseSwapChain();
			[[fallthrough]];

		case ErrorState::SurfaceCreated:
			releaseSurface();
			[[fallthrough]];

		case ErrorState::Default:
			break;
		};

		return VK_SUCCESS != result
			? result
			: VK_ERROR_INITIALIZATION_FAILED
			;
	}

	void SwapChainVK::destroy()
	{
		if (VK_NULL_HANDLE != m_swapChain)
		{
			releaseFrameBuffer();
			releaseAttachments();
			releaseSwapChain();
			releaseSurface();

			// can't delay-delete the surface, since there can only be one swapchain per surface
			// new framebuffer with the same window would get an error at swapchain creation
			s_renderVK->kick(true);
		}

		m_nwh = NULL;
	}

	void SwapChainVK::update(VkCommandBuffer _commandBuffer, void* _nwh, const Resolution& _resolution)
	{
		BGFX_PROFILER_SCOPE("SwapChainVK::update", kColorFrame);
		const VkPhysicalDevice physicalDevice = s_renderVK->m_physicalDevice;

		m_lastImageRenderedSemaphore = VK_NULL_HANDLE;
		m_lastImageAcquiredSemaphore = VK_NULL_HANDLE;

		const uint64_t recreateSurfaceMask     = BGFX_RESET_HIDPI;
		const uint64_t recreateSwapchainMask   = BGFX_RESET_VSYNC | BGFX_RESET_SRGB_BACKBUFFER;
		const uint64_t recreateAttachmentsMask = BGFX_RESET_MSAA_MASK;

		const bool recreateSurface = false
			|| m_needToRecreateSurface
			|| m_nwh != _nwh
			|| (m_resolution.reset & recreateSurfaceMask) != (_resolution.reset & recreateSurfaceMask)
			;

		const bool recreateSwapchain = false
			|| m_resolution.format != _resolution.format
			|| m_resolution.width  != _resolution.width
			|| m_resolution.height != _resolution.height
			|| (m_resolution.reset & recreateSwapchainMask) != (_resolution.reset & recreateSwapchainMask)
			|| recreateSurface
			;

		const bool recreateAttachments = false
			|| (m_resolution.reset & recreateAttachmentsMask) != (_resolution.reset & recreateAttachmentsMask)
			|| recreateSwapchain
			;

		m_nwh = _nwh;
		m_resolution = _resolution;

		if (recreateAttachments)
		{
			releaseFrameBuffer();
			releaseAttachments();

			if (recreateSwapchain)
			{
				releaseSwapChain();

				if (recreateSurface)
				{
					m_sci.oldSwapchain = VK_NULL_HANDLE;
					releaseSurface();
					s_renderVK->kick(true);
					_commandBuffer = s_renderVK->m_commandBuffer;

					VkResult result = createSurface();
					if (VK_SUCCESS != result)
					{
						BX_TRACE("Surface lost.");
						return;
					}
				}

				VkSurfaceCapabilitiesKHR surfaceCapabilities;
				VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, m_surface, &surfaceCapabilities) );

				const uint32_t width = bx::clamp<uint32_t>(
					  m_resolution.width
					, surfaceCapabilities.minImageExtent.width
					, surfaceCapabilities.maxImageExtent.width
					);
				const uint32_t height = bx::clamp<uint32_t>(
					  m_resolution.height
					, surfaceCapabilities.minImageExtent.height
					, surfaceCapabilities.maxImageExtent.height
					);

				// swapchain can't have size 0
				// on some platforms this happens when minimized
				if (width  == 0
				||  height == 0)
				{
					m_sci.oldSwapchain = VK_NULL_HANDLE;
					s_renderVK->kick(true);
					return;
				}

				VK_CHECK(createSwapChain() );
			}

			VK_CHECK(createAttachments(_commandBuffer) );
			VK_CHECK(createFrameBuffer() );
		}
	}

	VkResult SwapChainVK::createSurface()
	{
		BGFX_PROFILER_SCOPE("SwapChainVK::createSurface", kColorFrame);
		VkResult result = VK_ERROR_INITIALIZATION_FAILED;

		const VkInstance instance = s_renderVK->m_instance;
		const VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;

#if BX_PLATFORM_WINDOWS
		{
			if (NULL != vkCreateWin32SurfaceKHR)
			{
				VkWin32SurfaceCreateInfoKHR sci;
				sci.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
				sci.pNext = NULL;
				sci.flags     = 0;
				sci.hinstance = (HINSTANCE)GetModuleHandle(NULL);
				sci.hwnd      = (HWND)m_nwh;
				result = vkCreateWin32SurfaceKHR(instance, &sci, allocatorCb, &m_surface);
			}
		}
#elif BX_PLATFORM_ANDROID
		{
			if (NULL != vkCreateAndroidSurfaceKHR)
			{
				VkAndroidSurfaceCreateInfoKHR sci;
				sci.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
				sci.pNext = NULL;
				sci.flags = 0;
				sci.window = (ANativeWindow*)m_nwh;
				result = vkCreateAndroidSurfaceKHR(instance, &sci, allocatorCb, &m_surface);
			}
		}
#elif BX_PLATFORM_LINUX
		{
			if (g_platformData.type == bgfx::NativeWindowHandleType::Wayland)
			{
				BGFX_FATAL(s_extension[Extension::KHR_wayland_surface].m_supported, Fatal::UnableToInitialize, VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME " not supported");
				BGFX_FATAL(NULL != vkCreateWaylandSurfaceKHR, Fatal::UnableToInitialize, "vkCreateWaylandSurfaceKHR == 0");
				VkWaylandSurfaceCreateInfoKHR sci;
				sci.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
				sci.pNext = NULL;
				sci.flags = 0;
				sci.display = (wl_display*)g_platformData.ndt;
				sci.surface = (wl_surface*)m_nwh;
				result = vkCreateWaylandSurfaceKHR(instance, &sci, allocatorCb, &m_surface);
			}
			else
			{
				if (s_extension[Extension::KHR_xlib_surface].m_supported)
				{
					BGFX_FATAL(NULL != vkCreateXlibSurfaceKHR, Fatal::UnableToInitialize, "vkCreateXlibSurfaceKHR == 0")
					VkXlibSurfaceCreateInfoKHR sci;
					sci.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
					sci.pNext = NULL;
					sci.flags  = 0;
					sci.dpy    = (Display*)g_platformData.ndt;
					sci.window = (Window)m_nwh;
					result = vkCreateXlibSurfaceKHR(instance, &sci, allocatorCb, &m_surface);
				}

				if (VK_SUCCESS != result && s_extension[Extension::KHR_xcb_surface].m_supported)
				{
					void* xcbdll = bx::dlopen("libX11-xcb.so.1");

					if (NULL != xcbdll
					&&  NULL != vkCreateXcbSurfaceKHR)
					{
						typedef xcb_connection_t* (*PFN_XGETXCBCONNECTION)(Display*);
						PFN_XGETXCBCONNECTION XGetXCBConnection = (PFN_XGETXCBCONNECTION)bx::dlsym(xcbdll, "XGetXCBConnection");

						union { void* ptr; xcb_window_t window; } cast = { m_nwh };

						BGFX_FATAL(NULL != vkCreateXcbSurfaceKHR, Fatal::UnableToInitialize, "vkCreateXcbSurfaceKHR == 0")

						VkXcbSurfaceCreateInfoKHR sci;
						sci.sType      = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
						sci.pNext      = NULL;
						sci.flags      = 0;
						sci.connection = XGetXCBConnection( (Display*)g_platformData.ndt);
						sci.window     = cast.window;
						result = vkCreateXcbSurfaceKHR(instance, &sci, allocatorCb, &m_surface);

						bx::dlclose(xcbdll);
					}
				}
			}
		}

#elif BX_PLATFORM_OSX
		{
			if (NULL != vkCreateMacOSSurfaceMVK)
			{
				NSWindow* window    = (NSWindow*)(m_nwh);
				CAMetalLayer* layer = (CAMetalLayer*)(m_nwh);

				if ([window isKindOfClass:[NSWindow class]])
				{
					NSView *contentView = (NSView *)window.contentView;
					layer               = [CAMetalLayer layer];

					[contentView setWantsLayer : YES];
					[contentView setLayer : layer];
				}
				else if ([layer isKindOfClass:[CAMetalLayer class]])
				{
					NSView *contentView = (NSView *)layer.delegate;
					window              = contentView.window;
				}
				else
				{
					BX_WARN(0, "Unable to create MoltenVk surface. Please set platform data window to an NSWindow or CAMetalLayer");
					return result;
				}

				if (m_resolution.reset & BGFX_RESET_HIDPI)
				{
					layer.contentsScale = [window backingScaleFactor];
				}

				VkMacOSSurfaceCreateInfoMVK sci;
				sci.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
				sci.pNext = NULL;
				sci.flags = 0;
				sci.pView = (__bridge void*)layer;
				result = vkCreateMacOSSurfaceMVK(instance, &sci, allocatorCb, &m_surface);
			}
		}
#elif BX_PLATFORM_NX
		if (NULL != vkCreateViSurfaceNN)
		{
			VkViSurfaceCreateInfoNN sci;
			sci.sType  = VK_STRUCTURE_TYPE_VI_SURFACE_CREATE_INFO_NN;
			sci.pNext  = NULL;
			sci.flags  = 0;
			sci.window = m_nwh;
			result = vkCreateViSurfaceNN(instance, &sci, allocatorCb, &m_surface);
		}
#else
#	error "Figure out KHR surface..."
#endif // BX_PLATFORM_

		m_needToRecreateSurface = false;

		if (VK_SUCCESS != result)
		{
			BX_TRACE("Create surface error: vkCreate[Platform]SurfaceKHR failed %d: %s.", result, getName(result) );
			return result;
		}

		const VkPhysicalDevice physicalDevice = s_renderVK->m_physicalDevice;
		const uint32_t queueFamily = s_renderVK->m_globalQueueFamily;

		VkBool32 surfaceSupported;
		result = vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamily, m_surface, &surfaceSupported);

		if (VK_SUCCESS != result
		||  !surfaceSupported)
		{
			BX_TRACE("Create surface error: Presentation to the given surface not supported.");
			return VK_ERROR_INITIALIZATION_FAILED;
		}

		return result;
	}

	void SwapChainVK::releaseSurface()
	{
		release(m_surface);
	}

	VkResult SwapChainVK::createSwapChain()
	{
		BGFX_PROFILER_SCOPE("SwapChainVK::createSwapchain", kColorFrame);
		VkResult result = VK_SUCCESS;

		const VkPhysicalDevice physicalDevice = s_renderVK->m_physicalDevice;
		const VkDevice device = s_renderVK->m_device;
		const VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;

		// Waiting for the device to be idle seems to get rid of VK_DEVICE_LOST
		// upon resizing the window quickly. (See https://github.com/mpv-player/mpv/issues/8360
		// and https://github.com/bkaradzic/bgfx/issues/3227).
		result = vkDeviceWaitIdle(device);
		BX_WARN(VK_SUCCESS == result, "Create swapchain error: vkDeviceWaitIdle() failed: %d: %s", result, getName(result));

		VkSurfaceCapabilitiesKHR surfaceCapabilities;
		result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, m_surface, &surfaceCapabilities);

		if (VK_SUCCESS != result)
		{
			BX_TRACE("Create swapchain error: vkGetPhysicalDeviceSurfaceCapabilitiesKHR failed %d: %s.", result, getName(result) );
			return result;
		}

		const uint32_t minSwapBufferCount = bx::max<uint32_t>(surfaceCapabilities.minImageCount, 2);
		const uint32_t maxSwapBufferCount = surfaceCapabilities.maxImageCount == 0
			? kMaxBackBuffers
			: bx::min<uint32_t>(surfaceCapabilities.maxImageCount, kMaxBackBuffers)
			;

		if (minSwapBufferCount > maxSwapBufferCount)
		{
			BX_TRACE("Create swapchain error: Incompatible swapchain image count (min: %d, max: %d, MaxBackBuffers: %d)."
				, minSwapBufferCount
				, maxSwapBufferCount
				, kMaxBackBuffers
				);
			return VK_ERROR_INITIALIZATION_FAILED;
		}

		const uint32_t swapBufferCount = bx::clamp<uint32_t>(m_resolution.numBackBuffers, minSwapBufferCount, maxSwapBufferCount);

		const VkColorSpaceKHR surfaceColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;

		const bool srgb = !!(m_resolution.reset & BGFX_RESET_SRGB_BACKBUFFER);
		m_colorFormat = findSurfaceFormat(m_resolution.format, surfaceColorSpace, srgb);

		if (TextureFormat::Count == m_colorFormat)
		{
			BX_TRACE("Create swapchain error: Unable to find surface format (srgb: %d).", srgb);
			return VK_ERROR_INITIALIZATION_FAILED;
		}

		const VkFormat surfaceFormat = srgb
			? s_textureFormat[m_colorFormat].m_fmtSrgb
			: s_textureFormat[m_colorFormat].m_fmt
			;

		const uint32_t width = bx::clamp<uint32_t>(
			  m_resolution.width
			, surfaceCapabilities.minImageExtent.width
			, surfaceCapabilities.maxImageExtent.width
			);
		const uint32_t height = bx::clamp<uint32_t>(
			  m_resolution.height
			, surfaceCapabilities.minImageExtent.height
			, surfaceCapabilities.maxImageExtent.height
			);

		VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

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

		const VkImageUsageFlags imageUsageMask = 0
			| VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
			| VK_IMAGE_USAGE_TRANSFER_SRC_BIT
			| VK_IMAGE_USAGE_TRANSFER_DST_BIT
			;
		const VkImageUsageFlags imageUsage = surfaceCapabilities.supportedUsageFlags & imageUsageMask;

		m_supportsReadback      = 0 != (imageUsage & VK_IMAGE_USAGE_TRANSFER_SRC_BIT);
		m_supportsManualResolve = 0 != (imageUsage & VK_IMAGE_USAGE_TRANSFER_DST_BIT);

		const bool vsync = !!(m_resolution.reset & BGFX_RESET_VSYNC);
		uint32_t presentModeIdx = findPresentMode(vsync);
		if (UINT32_MAX == presentModeIdx)
		{
			BX_TRACE("Create swapchain error: Unable to find present mode (vsync: %d).", vsync);
			return VK_ERROR_INITIALIZATION_FAILED;
		}

		m_sci.surface            = m_surface;
		m_sci.minImageCount      = swapBufferCount;
		m_sci.imageFormat        = surfaceFormat;
		m_sci.imageColorSpace    = surfaceColorSpace;
		m_sci.imageExtent.width  = width;
		m_sci.imageExtent.height = height;
		m_sci.imageUsage         = imageUsage;
		m_sci.compositeAlpha     = compositeAlpha;
		m_sci.presentMode        = s_presentMode[presentModeIdx].mode;
		m_sci.clipped            = VK_FALSE;

		result = vkCreateSwapchainKHR(device, &m_sci, allocatorCb, &m_swapChain);
		if (VK_SUCCESS != result)
		{
			BX_TRACE("Create swapchain error: vkCreateSwapchainKHR failed %d: %s.", result, getName(result) );
			return result;
		}

		m_sci.oldSwapchain = m_swapChain;

		result = vkGetSwapchainImagesKHR(device, m_swapChain, &m_numSwapChainImages, NULL);
		if (VK_SUCCESS != result)
		{
			BX_TRACE("Create swapchain error: vkGetSwapchainImagesKHR failed %d: %s.", result, getName(result) );
			return result;
		}

		BX_TRACE("Create swapchain numSwapChainImages %d, minImageCount %d, BX_COUNTOF(m_backBufferColorImage) %d"
			, m_numSwapChainImages
			, m_sci.minImageCount
			, BX_COUNTOF(m_backBufferColorImage)
			);

		if (m_numSwapChainImages < m_sci.minImageCount)
		{
			BX_TRACE("Create swapchain error: vkGetSwapchainImagesKHR: numSwapchainImages %d < minImageCount %d."
				, m_numSwapChainImages
				, m_sci.minImageCount
				);
			return VK_ERROR_INITIALIZATION_FAILED;
		}

		if (m_numSwapChainImages > BX_COUNTOF(m_backBufferColorImage) )
		{
			BX_TRACE("Create swapchain error: vkGetSwapchainImagesKHR: numSwapchainImages %d > countof(m_backBufferColorImage) %d."
				, m_numSwapChainImages
				, BX_COUNTOF(m_backBufferColorImage)
				);
			return VK_ERROR_INITIALIZATION_FAILED;
		}

		result = vkGetSwapchainImagesKHR(device, m_swapChain, &m_numSwapChainImages, &m_backBufferColorImage[0]);
		if (VK_SUCCESS != result && VK_INCOMPLETE != result)
		{
			BX_TRACE("Create swapchain error: vkGetSwapchainImagesKHR failed %d: %s."
				, result
				, getName(result)
				);
			return result;
		}

		VkImageViewCreateInfo ivci;
		ivci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		ivci.pNext = NULL;
		ivci.flags = 0;
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

		for (uint32_t ii = 0; ii < m_numSwapChainImages; ++ii)
		{
			ivci.image = m_backBufferColorImage[ii];

			result = vkCreateImageView(device, &ivci, allocatorCb, &m_backBufferColorImageView[ii]);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create swapchain error: vkCreateImageView failed %d: %s.", result, getName(result) );
				return result;
			}

			m_backBufferColorImageLayout[ii] = VK_IMAGE_LAYOUT_UNDEFINED;
		}

		VkSemaphoreCreateInfo sci;
		sci.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		sci.pNext = NULL;
		sci.flags = 0;

		// We will make a fully filled pool of semaphores and cycle through those.
		// This is to make sure we have enough, even in the case where there are
		// more frames in flight than images on the swapchain.
		for (uint32_t ii = 0; ii < kMaxBackBuffers; ++ii)
		{
			if (VK_SUCCESS != vkCreateSemaphore(device, &sci, allocatorCb, &m_presentDoneSemaphore[ii])
			||  VK_SUCCESS != vkCreateSemaphore(device, &sci, allocatorCb, &m_renderDoneSemaphore[ii]) )
			{
				BX_TRACE("Create swapchain error: vkCreateSemaphore failed %d: %s.", result, getName(result) );
				return result;
			}
		}

		m_backBufferColorIdx = 0;
		m_currentSemaphore = 0;

		m_needPresent = false;
		m_needToRefreshSwapchain = false;

		return result;
	}

	void SwapChainVK::releaseSwapChain()
	{
		BGFX_PROFILER_SCOPE("SwapChainVK::releaseSwapChain", kColorFrame);
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_backBufferColorImageView); ++ii)
		{
			release(m_backBufferColorImageView[ii]);

			m_backBufferFence[ii] = VK_NULL_HANDLE;
		}

		for (uint32_t ii = 0; ii < kMaxBackBuffers; ++ii)
		{
			release(m_presentDoneSemaphore[ii]);
			release(m_renderDoneSemaphore[ii]);
		}

		release(m_swapChain);
	}

	VkResult SwapChainVK::createAttachments(VkCommandBuffer _commandBuffer)
	{
		BGFX_PROFILER_SCOPE("SwapChainVK::createAttachments", kColorFrame);
		VkResult result = VK_SUCCESS;

		const uint32_t samplerIndex = (m_resolution.reset & BGFX_RESET_MSAA_MASK) >> BGFX_RESET_MSAA_SHIFT;
		const uint64_t textureFlags = (uint64_t(samplerIndex + 1) << BGFX_TEXTURE_RT_MSAA_SHIFT) | BGFX_TEXTURE_RT | BGFX_TEXTURE_RT_WRITE_ONLY;
		m_sampler = s_msaa[samplerIndex];

		const uint16_t requiredCaps = m_sampler.Count > 1
			? BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
			: BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
			;

		// the spec guarantees that at least one of D24S8 and D32FS8 is supported
		VkFormat depthFormat = VK_FORMAT_D32_SFLOAT_S8_UINT;

		if (g_caps.formats[m_depthFormat] & requiredCaps)
		{
			depthFormat = s_textureFormat[m_depthFormat].m_fmtDsv;
		}
		else if (g_caps.formats[TextureFormat::D24S8] & requiredCaps)
		{
			depthFormat = s_textureFormat[TextureFormat::D24S8].m_fmtDsv;
		}

		result = m_backBufferDepthStencil.create(
			  _commandBuffer
			, m_sci.imageExtent.width
			, m_sci.imageExtent.height
			, textureFlags
			, depthFormat
			);

		if (VK_SUCCESS != result)
		{
			BX_TRACE("Create swapchain error: creating depth stencil image failed %d: %s.", result, getName(result) );
			return result;
		}

		result = m_backBufferDepthStencil.createView(0, 1, 0, 1, VK_IMAGE_VIEW_TYPE_2D, m_backBufferDepthStencil.m_aspectMask, true, &m_backBufferDepthStencilImageView);

		if (VK_SUCCESS != result)
		{
			BX_TRACE("Create swapchain error: creating depth stencil image view failed %d: %s.", result, getName(result) );
			return result;
		}

		if (m_sampler.Count > 1)
		{
			result = m_backBufferColorMsaa.create(
				  _commandBuffer
				, m_sci.imageExtent.width
				, m_sci.imageExtent.height
				, textureFlags
				, m_sci.imageFormat
				);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create swapchain error: creating MSAA color image failed %d: %s.", result, getName(result) );
				return result;
			}

			result = m_backBufferColorMsaa.createView(0, 1, 0, 1, VK_IMAGE_VIEW_TYPE_2D, m_backBufferColorMsaa.m_aspectMask, true, &m_backBufferColorMsaaImageView);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create swapchain error: creating MSAA color image view failed %d: %s.", result, getName(result) );
				return result;
			}
		}

		return result;
	}

	void SwapChainVK::releaseAttachments()
	{
		BGFX_PROFILER_SCOPE("SwapChainVK::releaseAttachments", kColorFrame);
		release(m_backBufferDepthStencilImageView);
		release(m_backBufferColorMsaaImageView);

		m_backBufferDepthStencil.destroy();
		m_backBufferColorMsaa.destroy();
	}

	VkResult SwapChainVK::createFrameBuffer()
	{
		BGFX_PROFILER_SCOPE("SwapChainVK::createFrameBuffer", kColorFrame);
		VkResult result = VK_SUCCESS;

		const VkDevice device = s_renderVK->m_device;
		const VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;

		VkRenderPass renderPass;
		result = s_renderVK->getRenderPass(*this, &renderPass);

		if (VK_SUCCESS != result)
		{
			return result;
		}

		for (uint32_t ii = 0; ii < m_numSwapChainImages; ++ii)
		{
			uint32_t numAttachments = 2;
			::VkImageView attachments[3] =
			{
				m_sampler.Count > 1
					? m_backBufferColorMsaaImageView
					: m_backBufferColorImageView[ii],
				m_backBufferDepthStencilImageView,
			};

			if (m_sampler.Count > 1 && !m_supportsManualResolve)
			{
				attachments[numAttachments++] = m_backBufferColorImageView[ii];
			}

			VkFramebufferCreateInfo fci;
			fci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			fci.pNext = NULL;
			fci.flags = 0;
			fci.renderPass = renderPass;
			fci.attachmentCount = numAttachments;
			fci.pAttachments = attachments;
			fci.width = m_sci.imageExtent.width;
			fci.height = m_sci.imageExtent.height;
			fci.layers = 1;

			result = vkCreateFramebuffer(device, &fci, allocatorCb, &m_backBufferFrameBuffer[ii]);

			if (VK_SUCCESS != result)
			{
				return result;
			}
		}

		return result;
	}

	void SwapChainVK::releaseFrameBuffer()
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_backBufferColorImageView); ++ii)
		{
			release(m_backBufferFrameBuffer[ii]);
		}
	}

	uint32_t SwapChainVK::findPresentMode(bool _vsync)
	{
		BGFX_PROFILER_SCOPE("SwapChainVK::findPresentMode", kColorFrame);
		VkResult result = VK_SUCCESS;

		const VkPhysicalDevice physicalDevice = s_renderVK->m_physicalDevice;

		uint32_t numPresentModes;
		result = vkGetPhysicalDeviceSurfacePresentModesKHR(
			  physicalDevice
			, m_surface
			, &numPresentModes
			, NULL
			);

		if (VK_SUCCESS != result)
		{
			BX_TRACE("findPresentMode error: vkGetPhysicalDeviceSurfacePresentModesKHR failed %d: %s.", result, getName(result) );
			return UINT32_MAX;
		}

		VkPresentModeKHR presentModes[16];
		numPresentModes = bx::min<uint32_t>(numPresentModes, BX_COUNTOF(presentModes) );
		result = vkGetPhysicalDeviceSurfacePresentModesKHR(
			  physicalDevice
			, m_surface
			, &numPresentModes
			, presentModes
			);

		if (VK_SUCCESS != result)
		{
			BX_TRACE("findPresentMode error: vkGetPhysicalDeviceSurfacePresentModesKHR failed %d: %s.", result, getName(result) );
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

	TextureFormat::Enum SwapChainVK::findSurfaceFormat(TextureFormat::Enum _format, VkColorSpaceKHR _colorSpace, bool _srgb)
	{
		BGFX_PROFILER_SCOPE("SwapChainVK::findSurfaceFormat", kColorFrame);
		VkResult result = VK_SUCCESS;

		TextureFormat::Enum selectedFormat = TextureFormat::Count;

		const VkPhysicalDevice physicalDevice = s_renderVK->m_physicalDevice;

		uint32_t numSurfaceFormats;
		result = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, m_surface, &numSurfaceFormats, NULL);

		if (VK_SUCCESS != result)
		{
			BX_TRACE("findSurfaceFormat error: vkGetPhysicalDeviceSurfaceFormatsKHR failed %d: %s.", result, getName(result) );
			return selectedFormat;
		}

		VkSurfaceFormatKHR* surfaceFormats = (VkSurfaceFormatKHR*)bx::alloc(g_allocator, numSurfaceFormats * sizeof(VkSurfaceFormatKHR) );
		result = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, m_surface, &numSurfaceFormats, surfaceFormats);

		if (VK_SUCCESS != result)
		{
			BX_TRACE("findSurfaceFormat error: vkGetPhysicalDeviceSurfaceFormatsKHR failed %d: %s.", result, getName(result) );
			bx::free(g_allocator, surfaceFormats);
			return selectedFormat;
		}

		const TextureFormat::Enum requestedFormats[] =
		{
			_format,
			TextureFormat::BGRA8,
			TextureFormat::RGBA8,
		};

		for (uint32_t ii = 0; ii < BX_COUNTOF(requestedFormats) && TextureFormat::Count == selectedFormat; ii++)
		{
			const TextureFormat::Enum requested = requestedFormats[ii];
			const VkFormat requestedVkFormat = _srgb
				? s_textureFormat[requested].m_fmtSrgb
				: s_textureFormat[requested].m_fmt
				;

			for (uint32_t jj = 0; jj < numSurfaceFormats; jj++)
			{
				if (_colorSpace == surfaceFormats[jj].colorSpace
				&&  requestedVkFormat == surfaceFormats[jj].format)
				{
					selectedFormat = requested;
					if (0 != ii
					&&  s_renderVK->m_swapChainFormats[_format] != selectedFormat)
					{
						s_renderVK->m_swapChainFormats[_format] = selectedFormat;
						BX_TRACE(
							"findSurfaceFormat: Surface format %s not found! Defaulting to %s."
							, bimg::getName(bimg::TextureFormat::Enum(_format) )
							, bimg::getName(bimg::TextureFormat::Enum(selectedFormat) )
							);
					}
					break;
				}
			}
		}

		bx::free(g_allocator, surfaceFormats);

		if (TextureFormat::Count == selectedFormat)
		{
			BX_TRACE("findSurfaceFormat error: No supported surface format found.");
		}

		return selectedFormat;
	}

	bool SwapChainVK::acquire(VkCommandBuffer _commandBuffer)
	{
		BGFX_PROFILER_SCOPE("SwapChainVK::acquire", kColorFrame);
		if (VK_NULL_HANDLE == m_swapChain
		||  m_needToRefreshSwapchain)
		{
			return false;
		}

		if (!m_needPresent)
		{
			const VkDevice device = s_renderVK->m_device;

			m_lastImageAcquiredSemaphore = m_presentDoneSemaphore[m_currentSemaphore];
			m_lastImageRenderedSemaphore = m_renderDoneSemaphore[m_currentSemaphore];
			m_currentSemaphore = (m_currentSemaphore + 1) % kMaxBackBuffers;

			VkResult result;
			{
				BGFX_PROFILER_SCOPE("vkAcquireNextImageKHR", kColorFrame);
				result = vkAcquireNextImageKHR(
					  device
					, m_swapChain
					, UINT64_MAX
					, m_lastImageAcquiredSemaphore
					, VK_NULL_HANDLE
					, &m_backBufferColorIdx
					);
			}

			switch (result)
			{
			case VK_SUCCESS:
				break;

			case VK_ERROR_SURFACE_LOST_KHR:
				m_needToRecreateSurface = true;
				[[fallthrough]];

			case VK_ERROR_OUT_OF_DATE_KHR:
			case VK_SUBOPTIMAL_KHR:
				m_needToRefreshSwapchain = true;
				return false;

			default:
				BX_ASSERT(VK_SUCCESS == result, "vkAcquireNextImageKHR(...); VK error 0x%x: %s", result, getName(result) );
				return false;
			}

			if (VK_NULL_HANDLE != m_backBufferFence[m_backBufferColorIdx])
			{
				BGFX_PROFILER_SCOPE("vkWaitForFences", kColorFrame);
				VK_CHECK(vkWaitForFences(
					  device
					, 1
					, &m_backBufferFence[m_backBufferColorIdx]
					, VK_TRUE
					, UINT64_MAX
					) );
			}

			transitionImage(_commandBuffer);

			m_needPresent = true;
		}

		return true;
	}

	void SwapChainVK::present()
	{
		BGFX_PROFILER_SCOPE("SwapChainVk::present", kColorFrame);
		if (VK_NULL_HANDLE != m_swapChain
		&&  m_needPresent)
		{
			VkPresentInfoKHR pi;
			pi.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			pi.pNext = NULL;
			pi.waitSemaphoreCount = 1;
			pi.pWaitSemaphores    = &m_lastImageRenderedSemaphore;
			pi.swapchainCount     = 1;
			pi.pSwapchains        = &m_swapChain;
			pi.pImageIndices      = &m_backBufferColorIdx;
			pi.pResults           = NULL;
			VkResult result;
			{
				BGFX_PROFILER_SCOPE("vkQueuePresentHKR", kColorFrame);
				result = vkQueuePresentKHR(m_queue, &pi);
			}

			switch (result)
			{
			case VK_ERROR_SURFACE_LOST_KHR:
				m_needToRecreateSurface = true;
				[[fallthrough]];

			case VK_ERROR_OUT_OF_DATE_KHR:
			case VK_SUBOPTIMAL_KHR:
				m_needToRefreshSwapchain = true;
				break;

			default:
				BX_ASSERT(VK_SUCCESS == result, "vkQueuePresentKHR(...); VK error 0x%x: %s", result, getName(result) );
				break;
			}

			m_needPresent = false;
			m_lastImageRenderedSemaphore = VK_NULL_HANDLE;
		}
	}

	void SwapChainVK::transitionImage(VkCommandBuffer _commandBuffer)
	{
		VkImageLayout& layout = m_backBufferColorImageLayout[m_backBufferColorIdx];

		const bool toPresent = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL == layout;

		const VkImageLayout newLayout = toPresent
			? VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
			: VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
			;

		layout = toPresent ? layout : VK_IMAGE_LAYOUT_UNDEFINED;

		setImageMemoryBarrier(
			  _commandBuffer
			, m_backBufferColorImage[m_backBufferColorIdx]
			, VK_IMAGE_ASPECT_COLOR_BIT
			, layout
			, newLayout
		);

		layout = newLayout;
	}

	void FrameBufferVK::create(uint8_t _num, const Attachment* _attachment)
	{
		BGFX_PROFILER_SCOPE("FrameBufferVK::create", kColorFrame);
		m_numTh = _num;
		bx::memCopy(m_attachment, _attachment, sizeof(Attachment) * _num);

		postReset();
	}

	VkResult FrameBufferVK::create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat)
	{
		BGFX_PROFILER_SCOPE("FrameBufferVK::create", kColorFrame);
		VkResult result = VK_SUCCESS;

		Resolution resolution = s_renderVK->m_resolution;
		resolution.format = TextureFormat::Count == _format ? resolution.format : _format;
		resolution.width  = _width;
		resolution.height = _height;
		if (_denseIdx != UINT16_MAX)
		{
			resolution.reset &= ~BGFX_RESET_MSAA_MASK;
		}

		result = m_swapChain.create(s_renderVK->m_commandBuffer, _nwh, resolution, _depthFormat);

		if (VK_SUCCESS != result)
		{
			return result;
		}

		result = s_renderVK->getRenderPass(m_swapChain, &m_renderPass);

		if (VK_SUCCESS != result)
		{
			return result;
		}

		m_denseIdx = _denseIdx;
		m_nwh = _nwh;
		m_width = _width;
		m_height = _height;
		m_sampler = m_swapChain.m_sampler;

		return result;
	}

	void FrameBufferVK::preReset()
	{
		BGFX_PROFILER_SCOPE("FrameBufferVK::preReset", kColorFrame);
		if (VK_NULL_HANDLE != m_framebuffer)
		{
			s_renderVK->release(m_framebuffer);

			for (uint8_t ii = 0; ii < m_numTh; ++ii)
			{
				s_renderVK->release(m_textureImageViews[ii]);
			}
		}
	}

	void FrameBufferVK::postReset()
	{
		BGFX_PROFILER_SCOPE("FrameBufferVK::postReset", kColorFrame);
		if (m_numTh > 0)
		{
			const VkDevice device = s_renderVK->m_device;
			const VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;

			VK_CHECK(s_renderVK->getRenderPass(m_numTh, m_attachment, &m_renderPass) );

			m_depth = BGFX_INVALID_HANDLE;
			m_num = 0;

			for (uint8_t ii = 0; ii < m_numTh; ++ii)
			{
				const Attachment& at = m_attachment[ii];
				const TextureVK& texture = s_renderVK->m_textures[at.handle.idx];
				VK_CHECK(texture.createView(
					  at.layer
					, at.numLayers
					, at.mip
					, 1
					, at.numLayers > 1 ? VK_IMAGE_VIEW_TYPE_2D_ARRAY : VK_IMAGE_VIEW_TYPE_2D
					, texture.m_aspectMask
					, true
					, &m_textureImageViews[ii]
					) );

				if (texture.m_aspectMask & VK_IMAGE_ASPECT_COLOR_BIT)
				{
					m_texture[m_num] = at.handle;
					m_num++;
				}
				else if (texture.m_aspectMask & (VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT) )
				{
					m_depth = at.handle;
				}
			}

			const TextureVK& firstTexture = s_renderVK->m_textures[m_attachment[0].handle.idx];
			m_width  = bx::uint32_max(firstTexture.m_width  >> m_attachment[0].mip, 1);
			m_height = bx::uint32_max(firstTexture.m_height >> m_attachment[0].mip, 1);
			m_sampler = firstTexture.m_sampler;

			VkFramebufferCreateInfo fci;
			fci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			fci.pNext = NULL;
			fci.flags = 0;
			fci.renderPass      = m_renderPass;
			fci.attachmentCount = m_numTh;
			fci.pAttachments    = &m_textureImageViews[0];
			fci.width  = m_width;
			fci.height = m_height;
			fci.layers = m_attachment[0].numLayers;

			VK_CHECK(vkCreateFramebuffer(device, &fci, allocatorCb, &m_framebuffer) );

			m_currentFramebuffer = m_framebuffer;
		}
	}

	void FrameBufferVK::update(VkCommandBuffer _commandBuffer, const Resolution& _resolution)
	{
		BGFX_PROFILER_SCOPE("FrameBufferVK::update", kColorResource);
		m_swapChain.update(_commandBuffer, m_nwh, _resolution);
		VK_CHECK(s_renderVK->getRenderPass(m_swapChain, &m_renderPass) );
		m_width   = _resolution.width;
		m_height  = _resolution.height;
		m_sampler = m_swapChain.m_sampler;
	}

	void FrameBufferVK::resolve()
	{
		if (!m_needResolve)
		{
			return;
		}

		BGFX_PROFILER_SCOPE("FrameBufferVK::resolve", kColorFrame);
		if (NULL == m_nwh)
		{
			for (uint32_t ii = 0; ii < m_numTh; ++ii)
			{
				const Attachment& at = m_attachment[ii];

				if (isValid(at.handle) )
				{
					TextureVK& texture = s_renderVK->m_textures[at.handle.idx];
					texture.resolve(s_renderVK->m_commandBuffer, at.resolve, at.layer, at.numLayers, at.mip);
				}
			}
		}
		else if (isRenderable()
		&&       m_sampler.Count > 1
		&&       m_swapChain.m_supportsManualResolve)
		{
			m_swapChain.m_backBufferColorMsaa.m_singleMsaaImage = m_swapChain.m_backBufferColorImage[m_swapChain.m_backBufferColorIdx];
			m_swapChain.m_backBufferColorMsaa.m_currentSingleMsaaImageLayout = m_swapChain.m_backBufferColorImageLayout[m_swapChain.m_backBufferColorIdx];

			m_swapChain.m_backBufferColorMsaa.resolve(s_renderVK->m_commandBuffer, 0, 0, 1, 0);

			m_swapChain.m_backBufferColorMsaa.m_singleMsaaImage = VK_NULL_HANDLE;
			m_swapChain.m_backBufferColorMsaa.m_currentSingleMsaaImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		}

		m_needResolve = false;
	}

	uint16_t FrameBufferVK::destroy()
	{
		BGFX_PROFILER_SCOPE("FrameBufferVK::destroy", kColorFrame);
		preReset();

		if (NULL != m_nwh)
		{
			m_swapChain.destroy();
			m_nwh = NULL;
			m_needPresent = false;
		}

		m_numTh = 0;
		m_num = 0;
		m_depth = BGFX_INVALID_HANDLE;

		m_needResolve = false;

		uint16_t denseIdx = m_denseIdx;
		m_denseIdx = UINT16_MAX;
		return denseIdx;
	}

	bool FrameBufferVK::acquire(VkCommandBuffer _commandBuffer)
	{
		BGFX_PROFILER_SCOPE("FrameBufferVK::acquire", kColorFrame);
		bool acquired = true;

		if (NULL != m_nwh)
		{
			acquired = m_swapChain.acquire(_commandBuffer);
			m_needPresent = m_swapChain.m_needPresent;
			m_currentFramebuffer = m_swapChain.m_backBufferFrameBuffer[m_swapChain.m_backBufferColorIdx];
		}

		m_needResolve = true;

		return acquired;
	}

	void FrameBufferVK::present()
	{
		BGFX_PROFILER_SCOPE("FrameBufferVK::present", kColorFrame);
		m_swapChain.present();
		m_needPresent = false;
	}

	bool FrameBufferVK::isRenderable() const
	{
		return false
			|| (NULL == m_nwh)
			|| m_swapChain.m_needPresent
			;
	}

	VkResult CommandQueueVK::init(uint32_t _queueFamily, VkQueue _queue, uint32_t _numFramesInFlight)
	{
		m_queueFamily = _queueFamily;
		m_queue = _queue;
		m_numFramesInFlight = bx::clamp<uint32_t>(_numFramesInFlight, 1, BGFX_CONFIG_MAX_FRAME_LATENCY);
		m_activeCommandBuffer = VK_NULL_HANDLE;
		m_consumeIndex = 0;

		return reset();
	}

	VkResult CommandQueueVK::reset()
	{
		shutdown();

		m_currentFrameInFlight = 0;
		m_consumeIndex         = 0;

		m_numSignalSemaphores = 0;
		m_numWaitSemaphores   = 0;

		m_activeCommandBuffer = VK_NULL_HANDLE;
		m_currentFence        = VK_NULL_HANDLE;
		m_completedFence      = VK_NULL_HANDLE;

		m_submitted = 0;

		VkCommandPoolCreateInfo cpci;
		cpci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		cpci.pNext = NULL;
		cpci.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
		cpci.queueFamilyIndex = m_queueFamily;

		VkCommandBufferAllocateInfo cbai;
		cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		cbai.pNext = NULL;
		cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		cbai.commandBufferCount = 1;

		VkFenceCreateInfo fci;
		fci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fci.pNext = NULL;
		fci.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		VkResult result = VK_SUCCESS;

		for (uint32_t ii = 0; ii < m_numFramesInFlight; ++ii)
		{
			result = vkCreateCommandPool(
				  s_renderVK->m_device
				, &cpci
				, s_renderVK->m_allocatorCb
				, &m_commandList[ii].m_commandPool
				);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create command queue error: vkCreateCommandPool failed %d: %s.", result, getName(result) );
				return result;
			}

			cbai.commandPool = m_commandList[ii].m_commandPool;

			result = vkAllocateCommandBuffers(
				  s_renderVK->m_device
				, &cbai
				, &m_commandList[ii].m_commandBuffer
				);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create command queue error: vkAllocateCommandBuffers failed %d: %s.", result, getName(result) );
				return result;
			}

			result = vkCreateFence(
				  s_renderVK->m_device
				, &fci
				, s_renderVK->m_allocatorCb
				, &m_commandList[ii].m_fence
				);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Create command queue error: vkCreateFence failed %d: %s.", result, getName(result) );
				return result;
			}
		}

		return result;
	}

	void CommandQueueVK::shutdown()
	{
		kick(true);
		finish(true);

		for (uint32_t ii = 0; ii < m_numFramesInFlight; ++ii)
		{
			vkDestroy(m_commandList[ii].m_fence);
			m_commandList[ii].m_commandBuffer = VK_NULL_HANDLE;
			vkDestroy(m_commandList[ii].m_commandPool);
		}
	}

	VkResult CommandQueueVK::alloc(VkCommandBuffer* _commandBuffer)
	{
		BGFX_PROFILER_SCOPE("CommandQueueVK::alloc", kColorResource);
		VkResult result = VK_SUCCESS;

		if (m_activeCommandBuffer == VK_NULL_HANDLE)
		{
			const VkDevice device = s_renderVK->m_device;
			CommandList& commandList = m_commandList[m_currentFrameInFlight];

			{
				BGFX_PROFILER_SCOPE("vkWaitForFences", kColorFrame);
				result = vkWaitForFences(device, 1, &commandList.m_fence, VK_TRUE, UINT64_MAX);
			}

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Allocate command buffer error: vkWaitForFences failed %d: %s.", result, getName(result) );
				return result;
			}

			result = vkResetCommandPool(device, commandList.m_commandPool, 0);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Allocate command buffer error: vkResetCommandPool failed %d: %s.", result, getName(result) );
				return result;
			}

			VkCommandBufferBeginInfo cbi;
			cbi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			cbi.pNext = NULL;
			cbi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
			cbi.pInheritanceInfo = NULL;

			result = vkBeginCommandBuffer(commandList.m_commandBuffer, &cbi);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Allocate command buffer error: vkBeginCommandBuffer failed %d: %s.", result, getName(result) );
				return result;
			}

			m_activeCommandBuffer = commandList.m_commandBuffer;
			m_currentFence = commandList.m_fence;
		}

		if (NULL != _commandBuffer)
		{
			*_commandBuffer = m_activeCommandBuffer;
		}

		return result;
	}

	void CommandQueueVK::addWaitSemaphore(VkSemaphore _semaphore, VkPipelineStageFlags _waitFlags)
	{
		BX_ASSERT(m_numWaitSemaphores < BX_COUNTOF(m_waitSemaphores), "Too many wait semaphores.");

		m_waitSemaphores[m_numWaitSemaphores]      = _semaphore;
		m_waitSemaphoreStages[m_numWaitSemaphores] = _waitFlags;
		m_numWaitSemaphores++;
	}

	void CommandQueueVK::addSignalSemaphore(VkSemaphore _semaphore)
	{
		BX_ASSERT(m_numSignalSemaphores < BX_COUNTOF(m_signalSemaphores), "Too many signal semaphores.");

		m_signalSemaphores[m_numSignalSemaphores] = _semaphore;
		m_numSignalSemaphores++;
	}

	void CommandQueueVK::kick(bool _wait)
	{
		BGFX_PROFILER_SCOPE("CommandQueueVK::kick", kColorDraw);
		if (VK_NULL_HANDLE != m_activeCommandBuffer)
		{
			const VkDevice device = s_renderVK->m_device;

			setMemoryBarrier(
				  m_activeCommandBuffer
				, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
				, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
				);

			VK_CHECK(vkEndCommandBuffer(m_activeCommandBuffer) );

			m_completedFence = m_currentFence;
			m_currentFence = VK_NULL_HANDLE;

			VK_CHECK(vkResetFences(device, 1, &m_completedFence) );

			VkSubmitInfo si;
			si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			si.pNext = NULL;
			si.waitSemaphoreCount    = m_numWaitSemaphores;
			si.pWaitSemaphores       = &m_waitSemaphores[0];
			si.pWaitDstStageMask     = m_waitSemaphoreStages;
			si.commandBufferCount    = 1;
			si.pCommandBuffers       = &m_activeCommandBuffer;
			si.signalSemaphoreCount  = m_numSignalSemaphores;
			si.pSignalSemaphores     = &m_signalSemaphores[0];

			m_numWaitSemaphores   = 0;
			m_numSignalSemaphores = 0;

			{
				BGFX_PROFILER_SCOPE("CommandQueueVK::kick vkQueueSubmit", kColorDraw);
				VK_CHECK(vkQueueSubmit(m_queue, 1, &si, m_completedFence) );
			}

			if (_wait)
			{
				BGFX_PROFILER_SCOPE("CommandQueue::kick vkWaitForFences", kColorDraw);
				VK_CHECK(vkWaitForFences(device, 1, &m_completedFence, VK_TRUE, UINT64_MAX) );
			}

			m_activeCommandBuffer = VK_NULL_HANDLE;

			m_currentFrameInFlight = (m_currentFrameInFlight + 1) % m_numFramesInFlight;
			m_submitted++;
		}
	}

	void CommandQueueVK::finish(bool _finishAll)
	{
		BGFX_PROFILER_SCOPE("CommandQueueVK::finish", kColorDraw);
		if (_finishAll)
		{
			for (uint32_t ii = 0; ii < m_numFramesInFlight; ++ii)
			{
				consume();
			}

			m_consumeIndex = m_currentFrameInFlight;
		}
		else
		{
			consume();
		}
	}

	void CommandQueueVK::release(uint64_t _handle, VkObjectType _type)
	{
		Resource resource;
		resource.m_type = _type;
		resource.m_handle = _handle;
		m_release[m_currentFrameInFlight].push_back(resource);
	}

	void CommandQueueVK::consume()
	{
		BGFX_PROFILER_SCOPE("CommandQueueVK::consume", kColorResource);
		m_consumeIndex = (m_consumeIndex + 1) % m_numFramesInFlight;

		for (const Resource& resource : m_release[m_consumeIndex])
		{
			switch (resource.m_type)
			{
			case VK_OBJECT_TYPE_BUFFER:                destroy<VkBuffer             >(resource.m_handle); break;
			case VK_OBJECT_TYPE_IMAGE_VIEW:            destroy<VkImageView          >(resource.m_handle); break;
			case VK_OBJECT_TYPE_IMAGE:                 destroy<VkImage              >(resource.m_handle); break;
			case VK_OBJECT_TYPE_FRAMEBUFFER:           destroy<VkFramebuffer        >(resource.m_handle); break;
			case VK_OBJECT_TYPE_PIPELINE_LAYOUT:       destroy<VkPipelineLayout     >(resource.m_handle); break;
			case VK_OBJECT_TYPE_PIPELINE:              destroy<VkPipeline           >(resource.m_handle); break;
			case VK_OBJECT_TYPE_DESCRIPTOR_SET:        destroy<VkDescriptorSet      >(resource.m_handle); break;
			case VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT: destroy<VkDescriptorSetLayout>(resource.m_handle); break;
			case VK_OBJECT_TYPE_RENDER_PASS:           destroy<VkRenderPass         >(resource.m_handle); break;
			case VK_OBJECT_TYPE_SAMPLER:               destroy<VkSampler            >(resource.m_handle); break;
			case VK_OBJECT_TYPE_SEMAPHORE:             destroy<VkSemaphore          >(resource.m_handle); break;
			case VK_OBJECT_TYPE_SURFACE_KHR:           destroy<VkSurfaceKHR         >(resource.m_handle); break;
			case VK_OBJECT_TYPE_SWAPCHAIN_KHR:         destroy<VkSwapchainKHR       >(resource.m_handle); break;
			case VK_OBJECT_TYPE_DEVICE_MEMORY:         destroy<VkDeviceMemory       >(resource.m_handle); break;
			default:
				BX_ASSERT(false, "Invalid resource type: %d", resource.m_type);
				break;
			}
		}

		m_release[m_consumeIndex].clear();
	}

	void RendererContextVK::submitBlit(BlitState& _bs, uint16_t _view)
	{
		BGFX_PROFILER_SCOPE("RendererContextVK::submitBlit", kColorFrame);
		VkImageLayout srcLayouts[BGFX_CONFIG_MAX_BLIT_ITEMS];
		VkImageLayout dstLayouts[BGFX_CONFIG_MAX_BLIT_ITEMS];

		BlitState bs0 = _bs;

		while (bs0.hasItem(_view) )
		{
			uint16_t item = bs0.m_item;

			const BlitItem& blit = bs0.advance();

			TextureVK& src = m_textures[blit.m_src.idx];
			TextureVK& dst = m_textures[blit.m_dst.idx];

			srcLayouts[item] = VK_NULL_HANDLE != src.m_singleMsaaImage ? src.m_currentSingleMsaaImageLayout : src.m_currentImageLayout;
			dstLayouts[item] = dst.m_currentImageLayout;
		}

		bs0 = _bs;

		while (bs0.hasItem(_view) )
		{
			const BlitItem& blit = bs0.advance();

			TextureVK& src = m_textures[blit.m_src.idx];
			TextureVK& dst = m_textures[blit.m_dst.idx];

			src.setImageMemoryBarrier(
				  m_commandBuffer
				, blit.m_src.idx == blit.m_dst.idx ? VK_IMAGE_LAYOUT_GENERAL : VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL
				, VK_NULL_HANDLE != src.m_singleMsaaImage
				);

			if (blit.m_src.idx != blit.m_dst.idx)
			{
				dst.setImageMemoryBarrier(m_commandBuffer, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
			}

			const uint16_t srcSamples = VK_NULL_HANDLE != src.m_singleMsaaImage ? 1 : src.m_sampler.Count;
			const uint16_t dstSamples = dst.m_sampler.Count;
			BX_UNUSED(srcSamples, dstSamples);

			BX_ASSERT(
				  srcSamples == dstSamples
				, "Mismatching texture sample count (%d != %d)."
				, srcSamples
				, dstSamples
				);

			VkImageCopy copyInfo;
			copyInfo.srcSubresource.aspectMask     = src.m_aspectMask;
			copyInfo.srcSubresource.mipLevel       = blit.m_srcMip;
			copyInfo.srcSubresource.baseArrayLayer = 0;
			copyInfo.srcSubresource.layerCount     = 1;
			copyInfo.srcOffset.x = blit.m_srcX;
			copyInfo.srcOffset.y = blit.m_srcY;
			copyInfo.srcOffset.z = 0;
			copyInfo.dstSubresource.aspectMask     = dst.m_aspectMask;
			copyInfo.dstSubresource.mipLevel       = blit.m_dstMip;
			copyInfo.dstSubresource.baseArrayLayer = 0;
			copyInfo.dstSubresource.layerCount     = 1;
			copyInfo.dstOffset.x = blit.m_dstX;
			copyInfo.dstOffset.y = blit.m_dstY;
			copyInfo.dstOffset.z = 0;
			copyInfo.extent.width  = blit.m_width;
			copyInfo.extent.height = blit.m_height;
			copyInfo.extent.depth  = 1;

			const uint32_t depth = bx::max<uint32_t>(1, blit.m_depth);

			if (VK_IMAGE_VIEW_TYPE_3D == src.m_type)
			{
				BX_ASSERT(VK_IMAGE_VIEW_TYPE_3D == dst.m_type, "Can't blit between 2D and 3D image.");

				copyInfo.srcOffset.z  = blit.m_srcZ;
				copyInfo.dstOffset.z  = blit.m_dstZ;
				copyInfo.extent.depth = depth;
			}
			else
			{
				copyInfo.srcSubresource.baseArrayLayer = blit.m_srcZ;
				copyInfo.dstSubresource.baseArrayLayer = blit.m_dstZ;
				copyInfo.srcSubresource.layerCount = depth;
				copyInfo.dstSubresource.layerCount = depth;
			}

			vkCmdCopyImage(
				  m_commandBuffer
				, VK_NULL_HANDLE != src.m_singleMsaaImage ? src.m_singleMsaaImage : src.m_textureImage
				, VK_NULL_HANDLE != src.m_singleMsaaImage ? src.m_currentSingleMsaaImageLayout : src.m_currentImageLayout
				, dst.m_textureImage
				, dst.m_currentImageLayout
				, 1
				, &copyInfo
				);

			setMemoryBarrier(
				  m_commandBuffer
				, VK_PIPELINE_STAGE_TRANSFER_BIT
				, VK_PIPELINE_STAGE_TRANSFER_BIT
				);
		}

		while (_bs.hasItem(_view) )
		{
			uint16_t item = _bs.m_item;

			const BlitItem& blit = _bs.advance();

			TextureVK& src = m_textures[blit.m_src.idx];
			TextureVK& dst = m_textures[blit.m_dst.idx];

			src.setImageMemoryBarrier(m_commandBuffer, srcLayouts[item], VK_NULL_HANDLE != src.m_singleMsaaImage);
			dst.setImageMemoryBarrier(m_commandBuffer, dstLayouts[item]);
		}
	}

	void RendererContextVK::submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter)
	{
		BX_UNUSED(_clearQuad);

		if (updateResolution(_render->m_resolution) )
		{
			return;
		}

		if (_render->m_capture)
		{
			renderDocTriggerCapture();
		}

		BGFX_VK_PROFILER_BEGIN_LITERAL("rendererSubmit", kColorView);

		int64_t timeBegin = bx::getHPCounter();
		int64_t captureElapsed = 0;

		uint32_t frameQueryIdx = UINT32_MAX;

		if (m_timerQuerySupport)
		{
			frameQueryIdx = m_gpuTimer.begin(BGFX_CONFIG_MAX_VIEWS, _render->m_frameNum);
		}

		if (0 < _render->m_iboffset)
		{
			BGFX_PROFILER_SCOPE("bgfx/Update transient index buffer", kColorResource);
			TransientIndexBuffer* ib = _render->m_transientIb;
			m_indexBuffers[ib->handle.idx].update(m_commandBuffer, 0, _render->m_iboffset, ib->data);
		}

		if (0 < _render->m_vboffset)
		{
			BGFX_PROFILER_SCOPE("bgfx/Update transient vertex buffer", kColorResource);
			TransientVertexBuffer* vb = _render->m_transientVb;
			m_vertexBuffers[vb->handle.idx].update(m_commandBuffer, 0, _render->m_vboffset, vb->data);
		}

		_render->sort();

		RenderDraw currentState;
		currentState.clear();
		currentState.m_stateFlags = BGFX_STATE_NONE;
		currentState.m_stencil    = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);

		static ViewState viewState;
		viewState.reset(_render);

		bool wireframe = !!(_render->m_debug&BGFX_DEBUG_WIREFRAME);
		setDebugWireframe(wireframe);

		ProgramHandle currentProgram = BGFX_INVALID_HANDLE;
		bool hasPredefined = false;
		VkPipeline currentPipeline = VK_NULL_HANDLE;
		VkDescriptorSet currentDescriptorSet = VK_NULL_HANDLE;
		uint32_t currentBindHash = 0;
		uint32_t descriptorSetCount = 0;
		VkIndexType currentIndexFormat = VK_INDEX_TYPE_MAX_ENUM;
		SortKey key;
		uint16_t view = UINT16_MAX;
		FrameBufferHandle fbh = { BGFX_CONFIG_MAX_FRAME_BUFFERS };

		BlitState bs(_render);

		uint64_t blendFactor = UINT64_MAX;

		bool wasCompute     = false;
		bool viewHasScissor = false;
		bool restoreScissor = false;
		Rect viewScissorRect;
		viewScissorRect.clear();

		bool isFrameBufferValid = false;

		uint32_t statsNumPrimsSubmitted[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumPrimsRendered[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumInstances[BX_COUNTOF(s_primInfo)] = {};
		uint32_t statsNumIndices = 0;
		uint32_t statsKeyType[2] = {};

		const uint64_t f0 = BGFX_STATE_BLEND_FACTOR;
		const uint64_t f1 = BGFX_STATE_BLEND_INV_FACTOR;
		const uint64_t f2 = BGFX_STATE_BLEND_FACTOR<<4;
		const uint64_t f3 = BGFX_STATE_BLEND_INV_FACTOR<<4;

		ScratchBufferVK& scratchBuffer = m_scratchBuffer[m_cmd.m_currentFrameInFlight];
		scratchBuffer.reset();

		ScratchBufferVK& scratchStagingBuffer = m_scratchStagingBuffer[m_cmd.m_currentFrameInFlight];
		scratchStagingBuffer.reset();

		setMemoryBarrier(
			  m_commandBuffer
			, VK_PIPELINE_STAGE_TRANSFER_BIT
			, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT | VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT
			);

		VkRenderPassBeginInfo rpbi;
		rpbi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		rpbi.pNext = NULL;
		rpbi.clearValueCount = 0;
		rpbi.pClearValues    = NULL;

		bool beginRenderPass = false;

		Profiler<TimerQueryVK> profiler(
			  _render
			, m_gpuTimer
			, s_viewName
			, m_timerQuerySupport
			);

		m_occlusionQuery.flush(_render);

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

				if (viewChanged)
				{
					if (beginRenderPass)
					{
						vkCmdEndRenderPass(m_commandBuffer);
						beginRenderPass = false;
					}

					view = key.m_view;
					currentProgram = BGFX_INVALID_HANDLE;
					hasPredefined  = false;

					if (item > 1)
					{
						profiler.end();
					}

					BGFX_VK_PROFILER_END();
					setViewType(view, " ");
					BGFX_VK_PROFILER_BEGIN(view, kColorView);

					profiler.begin(view);

					if (_render->m_view[view].m_fbh.idx != fbh.idx)
					{
						fbh = _render->m_view[view].m_fbh;
						setFrameBuffer(fbh);
					}

					const FrameBufferVK& fb = isValid(m_fbh)
						? m_frameBuffers[m_fbh.idx]
						: m_backBuffer
						;

					isFrameBufferValid = fb.isRenderable();

					if (isFrameBufferValid)
					{
						viewState.m_rect = _render->m_view[view].m_rect;
						const Rect& rect        = _render->m_view[view].m_rect;
						const Rect& scissorRect = _render->m_view[view].m_scissor;
						viewHasScissor  = !scissorRect.isZero();
						viewScissorRect = viewHasScissor ? scissorRect : rect;
						restoreScissor = false;

						rpbi.framebuffer = fb.m_currentFramebuffer;
						rpbi.renderPass  = fb.m_renderPass;
						rpbi.renderArea.offset.x = rect.m_x;
						rpbi.renderArea.offset.y = rect.m_y;
						rpbi.renderArea.extent.width  = rect.m_width;
						rpbi.renderArea.extent.height = rect.m_height;

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

						const Clear& clr = _render->m_view[view].m_clear;
						if (BGFX_CLEAR_NONE != clr.m_flags)
						{
							vkCmdBeginRenderPass(m_commandBuffer, &rpbi, VK_SUBPASS_CONTENTS_INLINE);

							Rect clearRect = rect;
							clearRect.setIntersect(rect, viewScissorRect);
							clearQuad(clearRect, clr, _render->m_colorPalette);

							vkCmdEndRenderPass(m_commandBuffer);
						}

						submitBlit(bs, view);
					}
				}

				if (isCompute)
				{
					if (!wasCompute)
					{
						wasCompute = true;
						currentBindHash = 0;

						BGFX_VK_PROFILER_END();
						setViewType(view, "C");
						BGFX_VK_PROFILER_BEGIN(view, kColorCompute);
					}

					// renderpass external subpass dependencies handle graphics -> compute and compute -> graphics
					// but not compute -> compute (possibly also across views if they contain no draw calls)
					setMemoryBarrier(
						  m_commandBuffer
						, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT
						, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT | VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT
					);

					const RenderCompute& compute = renderItem.compute;

					const VkPipeline pipeline = getPipeline(key.m_program);

					if (currentPipeline != pipeline)
					{
						currentPipeline = pipeline;
						vkCmdBindPipeline(m_commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);
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

					if (VK_NULL_HANDLE != program.m_descriptorSetLayout)
					{
						const uint32_t vsize = program.m_vsh->m_size;
						uint32_t numOffset = 0;
						uint32_t offset = 0;

						if (constantsChanged
						||  hasPredefined)
						{
							if (vsize > 0)
							{
								offset = scratchBuffer.write(m_vsScratch, vsize);
								++numOffset;
							}
						}

						bx::HashMurmur2A hash;
						hash.begin();
						hash.add(program.m_descriptorSetLayout);
						hash.add(renderBind.m_bind, sizeof(renderBind.m_bind) );
						hash.add(vsize);
						hash.add(0);
						const uint32_t bindHash = hash.end();

						if (currentBindHash != bindHash)
						{
							currentBindHash = bindHash;

							currentDescriptorSet = getDescriptorSet(
								  program
								, renderBind
								, scratchBuffer
								, _render->m_colorPalette
							);

							descriptorSetCount++;
						}

						vkCmdBindDescriptorSets(
							  m_commandBuffer
							, VK_PIPELINE_BIND_POINT_COMPUTE
							, program.m_pipelineLayout
							, 0
							, 1
							, &currentDescriptorSet
							, numOffset
							, &offset
							);
					}

					if (isValid(compute.m_indirectBuffer) )
					{
						const VertexBufferVK& vb = m_vertexBuffers[compute.m_indirectBuffer.idx];

						uint32_t numDrawIndirect = UINT32_MAX == compute.m_numIndirect
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

				rendererUpdateUniforms(this, _render->m_uniformBuffer[draw.m_uniformIdx], draw.m_uniformBegin, draw.m_uniformEnd);

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

				const uint64_t changedFlags = currentState.m_stateFlags ^ draw.m_stateFlags;
				currentState.m_stateFlags = draw.m_stateFlags;

				if (!beginRenderPass)
				{
					if (wasCompute)
					{
						wasCompute = false;
						currentBindHash = 0;
					}

					BGFX_VK_PROFILER_END();
					setViewType(view, " ");
					BGFX_VK_PROFILER_BEGIN(view, kColorDraw);

					vkCmdBeginRenderPass(m_commandBuffer, &rpbi, VK_SUBPASS_CONTENTS_INLINE);
					beginRenderPass = true;

					currentProgram = BGFX_INVALID_HANDLE;
					currentState.m_scissor = !draw.m_scissor;
				}

				if (0 != draw.m_streamMask)
				{
					const bool bindAttribs = hasVertexStreamChanged(currentState, draw);

					currentState.m_streamMask         = draw.m_streamMask;
					currentState.m_instanceDataBuffer = draw.m_instanceDataBuffer;
					currentState.m_instanceDataOffset = draw.m_instanceDataOffset;
					currentState.m_instanceDataStride = draw.m_instanceDataStride;

					const VertexLayout* layouts[BGFX_CONFIG_MAX_VERTEX_STREAMS];
					VkBuffer streamBuffers[BGFX_CONFIG_MAX_VERTEX_STREAMS + 1];
					VkDeviceSize streamOffsets[BGFX_CONFIG_MAX_VERTEX_STREAMS + 1];
					uint8_t numStreams = 0;
					uint32_t numVertices = draw.m_numVertices;
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

							currentState.m_stream[idx] = draw.m_stream[idx];

							const VertexBufferHandle handle = draw.m_stream[idx].m_handle;
							const VertexBufferVK& vb = m_vertexBuffers[handle.idx];
							const uint16_t decl = isValid(draw.m_stream[idx].m_layoutHandle)
								? draw.m_stream[idx].m_layoutHandle.idx
								: vb.m_layoutHandle.idx
								;
							const VertexLayout& layout = m_vertexLayouts[decl];
							const uint32_t stride = layout.m_stride;

							streamBuffers[numStreams] = m_vertexBuffers[handle.idx].m_buffer;
							streamOffsets[numStreams] = draw.m_stream[idx].m_startVertex * stride;
							layouts[numStreams]       = &layout;

							numVertices = bx::uint32_min(UINT32_MAX == draw.m_numVertices
								? vb.m_size/stride
								: draw.m_numVertices
								, numVertices
								);
						}
					}

					if (bindAttribs)
					{
						uint32_t numVertexBuffers = numStreams;

						if (isValid(draw.m_instanceDataBuffer) )
						{
							streamOffsets[numVertexBuffers] = draw.m_instanceDataOffset;
							streamBuffers[numVertexBuffers] = m_vertexBuffers[draw.m_instanceDataBuffer.idx].m_buffer;
							numVertexBuffers++;
						}

						if (0 < numVertexBuffers)
						{
							vkCmdBindVertexBuffers(
								  m_commandBuffer
								, 0
								, numVertexBuffers
								, &streamBuffers[0]
								, streamOffsets
								);
						}
					}

					const VkPipeline pipeline =
						getPipeline(draw.m_stateFlags
							, draw.m_stencil
							, numStreams
							, layouts
							, key.m_program
							, uint8_t(draw.m_instanceDataStride/16)
							);

					if (currentPipeline != pipeline)
					{
						currentPipeline = pipeline;
						vkCmdBindPipeline(m_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
					}

					const bool hasStencil = 0 != draw.m_stencil;

					if (hasStencil
					&&  currentState.m_stencil != draw.m_stencil)
					{
						currentState.m_stencil = draw.m_stencil;

						const uint32_t fstencil = unpackStencil(0, draw.m_stencil);
						const uint32_t ref = (fstencil&BGFX_STENCIL_FUNC_REF_MASK)>>BGFX_STENCIL_FUNC_REF_SHIFT;
						vkCmdSetStencilReference(m_commandBuffer, VK_STENCIL_FRONT_AND_BACK, ref);
					}

					const bool hasFactor = 0
						|| f0 == (draw.m_stateFlags & f0)
						|| f1 == (draw.m_stateFlags & f1)
						|| f2 == (draw.m_stateFlags & f2)
						|| f3 == (draw.m_stateFlags & f3)
						;

					if (hasFactor
					&&  blendFactor != draw.m_rgba)
					{
						blendFactor = draw.m_rgba;

						float bf[4];
						bf[0] = ( (draw.m_rgba>>24)     )/255.0f;
						bf[1] = ( (draw.m_rgba>>16)&0xff)/255.0f;
						bf[2] = ( (draw.m_rgba>> 8)&0xff)/255.0f;
						bf[3] = ( (draw.m_rgba    )&0xff)/255.0f;
						vkCmdSetBlendConstants(m_commandBuffer, bf);
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

					const ProgramVK& program = m_program[currentProgram.idx];

					if (hasPredefined)
					{
						uint32_t ref = (draw.m_stateFlags & BGFX_STATE_ALPHA_REF_MASK) >> BGFX_STATE_ALPHA_REF_SHIFT;
						viewState.m_alphaRef = ref / 255.0f;
						viewState.setPredefined<4>(this, view, program, _render, draw);
					}

					if (VK_NULL_HANDLE != program.m_descriptorSetLayout)
					{
						const uint32_t vsize = program.m_vsh->m_size;
						const uint32_t fsize = NULL != program.m_fsh ? program.m_fsh->m_size : 0;
						uint32_t numOffset = 0;
						uint32_t offsets[2] = { 0, 0 };

						if (constantsChanged
						||  hasPredefined)
						{
							if (vsize > 0)
							{
								offsets[numOffset++] = scratchBuffer.write(m_vsScratch, vsize);
							}

							if (fsize > 0)
							{
								offsets[numOffset++] = scratchBuffer.write(m_fsScratch, fsize);
							}
						}

						bx::HashMurmur2A hash;
						hash.begin();
						hash.add(program.m_descriptorSetLayout);
						hash.add(renderBind.m_bind, sizeof(renderBind.m_bind) );
						hash.add(vsize);
						hash.add(fsize);
						const uint32_t bindHash = hash.end();

						if (currentBindHash != bindHash)
						{
							currentBindHash = bindHash;

							currentDescriptorSet = getDescriptorSet(
								  program
								, renderBind
								, scratchBuffer
								, _render->m_colorPalette
							);

							descriptorSetCount++;
						}

						vkCmdBindDescriptorSets(
							  m_commandBuffer
							, VK_PIPELINE_BIND_POINT_GRAPHICS
							, program.m_pipelineLayout
							, 0
							, 1
							, &currentDescriptorSet
							, numOffset
							, offsets
							);
					}

					VkBuffer bufferIndirect = VK_NULL_HANDLE;
					VkBuffer bufferNumIndirect = VK_NULL_HANDLE;
					uint32_t numDrawIndirect = 0;
					uint32_t bufferOffsetIndirect = 0;
					uint32_t bufferNumOffsetIndirect = 0;
					if (isValid(draw.m_indirectBuffer) )
					{
						const VertexBufferVK& vb = m_vertexBuffers[draw.m_indirectBuffer.idx];
						bufferIndirect = vb.m_buffer;
						numDrawIndirect = UINT32_MAX == draw.m_numIndirect
							? vb.m_size / BGFX_CONFIG_DRAW_INDIRECT_STRIDE
							: draw.m_numIndirect
							;
						bufferOffsetIndirect = draw.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE;

						if (isValid(draw.m_numIndirectBuffer) )
						{
							bufferNumIndirect = m_indexBuffers[draw.m_numIndirectBuffer.idx].m_buffer;
							bufferNumOffsetIndirect = draw.m_numIndirectIndex * sizeof(uint32_t);
						}
					}

					if (hasOcclusionQuery)
					{
						m_occlusionQuery.begin(draw.m_occlusionQuery);
					}

					const uint8_t primIndex = uint8_t((draw.m_stateFlags & BGFX_STATE_PT_MASK) >> BGFX_STATE_PT_SHIFT);
					const PrimInfo& prim = s_primInfo[primIndex];

					uint32_t numPrimsSubmitted = 0;
					uint32_t numIndices = 0;

					if (!isValid(draw.m_indexBuffer) )
					{
						numPrimsSubmitted = numVertices / prim.m_div - prim.m_sub;

						if (isValid(draw.m_indirectBuffer) )
						{
							if (isValid(draw.m_numIndirectBuffer) )
							{
								vkCmdDrawIndirectCountKHR(
									  m_commandBuffer
									, bufferIndirect
									, bufferOffsetIndirect
									, bufferNumIndirect
									, bufferNumOffsetIndirect
									, numDrawIndirect
									, BGFX_CONFIG_DRAW_INDIRECT_STRIDE
									);
							}
							else
							{
								vkCmdDrawIndirect(
									  m_commandBuffer
									, bufferIndirect
									, bufferOffsetIndirect
									, numDrawIndirect
									, BGFX_CONFIG_DRAW_INDIRECT_STRIDE
									);
							}
						}
						else
						{
							vkCmdDraw(
								  m_commandBuffer
								, numVertices
								, draw.m_numInstances
								, 0
								, 0
								);
						}
					}
					else
					{
						const bool isIndex16          = draw.isIndex16();
						const uint32_t indexSize      = isIndex16 ? 2 : 4;
						const VkIndexType indexFormat = isIndex16 ? VK_INDEX_TYPE_UINT16 : VK_INDEX_TYPE_UINT32;
						const BufferVK& ib            = m_indexBuffers[draw.m_indexBuffer.idx];

						numIndices = UINT32_MAX == draw.m_numIndices
							? ib.m_size / indexSize
							: draw.m_numIndices
							;

						numPrimsSubmitted = numIndices / prim.m_div - prim.m_sub;

						if (currentState.m_indexBuffer.idx != draw.m_indexBuffer.idx
						||  currentIndexFormat != indexFormat)
						{
							currentState.m_indexBuffer = draw.m_indexBuffer;
							currentIndexFormat = indexFormat;

							vkCmdBindIndexBuffer(
								  m_commandBuffer
								, m_indexBuffers[draw.m_indexBuffer.idx].m_buffer
								, 0
								, indexFormat
								);
						}

						if (isValid(draw.m_indirectBuffer) )
						{
							if (isValid(draw.m_numIndirectBuffer) )
							{
								vkCmdDrawIndexedIndirectCountKHR(
									  m_commandBuffer
									, bufferIndirect
									, bufferOffsetIndirect
									, bufferNumIndirect
									, bufferNumOffsetIndirect
									, numDrawIndirect
									, BGFX_CONFIG_DRAW_INDIRECT_STRIDE
									);
							}
							else
							{
								vkCmdDrawIndexedIndirect(
									  m_commandBuffer
									, bufferIndirect
									, bufferOffsetIndirect
									, numDrawIndirect
									, BGFX_CONFIG_DRAW_INDIRECT_STRIDE
									);
							}
						}
						else
						{
							vkCmdDrawIndexed(
								  m_commandBuffer
								, numIndices
								, draw.m_numInstances
								, draw.m_startIndex
								, 0
								, 0
								);
						}
					}

					uint32_t numPrimsRendered  = numPrimsSubmitted*draw.m_numInstances;

					statsNumPrimsSubmitted[primIndex] += numPrimsSubmitted;
					statsNumPrimsRendered[primIndex]  += numPrimsRendered;
					statsNumInstances[primIndex]      += draw.m_numInstances;
					statsNumIndices                   += numIndices;

					if (hasOcclusionQuery)
					{
						m_occlusionQuery.end();
					}
				}
			}

			if (beginRenderPass)
			{
				vkCmdEndRenderPass(m_commandBuffer);
				beginRenderPass = false;
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
				capture();
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

		static int64_t presentMin = m_presentElapsed;
		static int64_t presentMax = m_presentElapsed;
		presentMin = bx::min<int64_t>(presentMin, m_presentElapsed);
		presentMax = bx::max<int64_t>(presentMax, m_presentElapsed);

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

		VkPhysicalDeviceMemoryBudgetPropertiesEXT dmbp;
		dmbp.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_BUDGET_PROPERTIES_EXT;
		dmbp.pNext = NULL;

		int64_t gpuMemoryAvailable = -INT64_MAX;
		int64_t gpuMemoryUsed      = -INT64_MAX;

		if (s_extension[Extension::EXT_memory_budget].m_supported)
		{
			VkPhysicalDeviceMemoryProperties2 pdmp2;
			pdmp2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2;
			pdmp2.pNext = &dmbp;

			vkGetPhysicalDeviceMemoryProperties2KHR(m_physicalDevice, &pdmp2);

			gpuMemoryAvailable = 0;
			gpuMemoryUsed      = 0;

			for (uint32_t ii = 0; ii < m_memoryProperties.memoryHeapCount; ++ii)
			{
				if (!!(m_memoryProperties.memoryHeaps[ii].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) )
				{
					gpuMemoryAvailable += dmbp.heapBudget[ii];
					gpuMemoryUsed += dmbp.heapUsage[ii];
				}
			}
		}

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
		perfStats.gpuFrameNum   = result.m_frameNum;
		bx::memCopy(perfStats.numPrims, statsNumPrimsRendered, sizeof(perfStats.numPrims) );
		perfStats.gpuMemoryMax  = gpuMemoryAvailable;
		perfStats.gpuMemoryUsed = gpuMemoryUsed;

		if (_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
			BGFX_VK_PROFILER_BEGIN_LITERAL("debugstats", kColorFrame);

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

				if (0 <= gpuMemoryAvailable && 0 <= gpuMemoryUsed)
				{
					for (uint32_t ii = 0; ii < m_memoryProperties.memoryHeapCount; ++ii)
					{
						char budget[16];
						bx::prettify(budget, BX_COUNTOF(budget), dmbp.heapBudget[ii]);

						char usage[16];
						bx::prettify(usage, BX_COUNTOF(usage), dmbp.heapUsage[ii]);

						const bool local = (!!(m_memoryProperties.memoryHeaps[ii].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) );

						tvm.printf(0, pos++, 0x8f, " Memory %d %s - Budget: %12s, Usage: %12s"
							, ii
							, local ? "(local)    " : "(non-local)"
							, budget
							, usage
							);
					}
				}

				pos = 10;
				tvm.printf(10, pos++, 0x8b, "       Frame: % 7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] / % 6.2f FPS"
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
				tvm.printf(10, pos++, 0x8b, " Occlusion queries: %3d ", m_occlusionQuery.m_control.available() );

				pos++;
				tvm.printf(10, pos++, 0x8b, " State cache:             ");
				tvm.printf(10, pos++, 0x8b, " PSO    | DSL    |  DS    ");
				tvm.printf(10, pos++, 0x8b, " %6d | %6d | %6d "
					, m_pipelineStateCache.getCount()
					, m_descriptorSetLayoutCache.getCount()
					, descriptorSetCount
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
				presentMin = m_presentElapsed;
				presentMax = m_presentElapsed;
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

		m_presentElapsed = 0;

		{
			BGFX_PROFILER_SCOPE("scratchBuffer::flush", kColorResource);
			scratchBuffer.flush();
		}

		{
			BGFX_PROFILER_SCOPE("scratchStagingBuffer::flush", kColorResource);
			scratchStagingBuffer.flush();
		}

		for (uint16_t ii = 0; ii < m_numWindows; ++ii)
		{
			FrameBufferVK& fb = isValid(m_windows[ii])
				? m_frameBuffers[m_windows[ii].idx]
				: m_backBuffer
				;

			if (fb.m_needPresent)
			{
				fb.resolve();

				fb.m_swapChain.transitionImage(m_commandBuffer);

				m_cmd.addWaitSemaphore(fb.m_swapChain.m_lastImageAcquiredSemaphore, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
				m_cmd.addSignalSemaphore(fb.m_swapChain.m_lastImageRenderedSemaphore);
				fb.m_swapChain.m_lastImageAcquiredSemaphore = VK_NULL_HANDLE;

				fb.m_swapChain.m_backBufferFence[fb.m_swapChain.m_backBufferColorIdx] = m_cmd.m_currentFence;
			}
		}

		kick();
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

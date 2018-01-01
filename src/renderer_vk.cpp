/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_VULKAN
#	include "renderer_vk.h"

namespace bgfx { namespace vk
{
	static char s_viewName[BGFX_CONFIG_MAX_VIEWS][256];

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
		{ VK_PRIMITIVE_TOPOLOGY_POINT_LIST,     1, 1, 0 },
		{ VK_PRIMITIVE_TOPOLOGY_MAX_ENUM,       0, 0, 0 },
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

//	static DXGI_SAMPLE_DESC s_msaa[] =
//	{
//		{  1, 0 },
//		{  2, 0 },
//		{  4, 0 },
//		{  8, 0 },
//		{ 16, 0 },
//	};

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
	};

	static const TextureFormatInfo s_textureFormat[] =
	{
		{ VK_FORMAT_BC1_RGB_UNORM_BLOCK,       VK_FORMAT_BC1_RGB_UNORM_BLOCK,      VK_FORMAT_UNDEFINED,           VK_FORMAT_BC1_RGB_SRGB_BLOCK       }, // BC1
		{ VK_FORMAT_BC2_UNORM_BLOCK,           VK_FORMAT_BC2_UNORM_BLOCK,          VK_FORMAT_UNDEFINED,           VK_FORMAT_BC2_SRGB_BLOCK           }, // BC2
		{ VK_FORMAT_BC3_UNORM_BLOCK,           VK_FORMAT_BC3_UNORM_BLOCK,          VK_FORMAT_UNDEFINED,           VK_FORMAT_BC3_SRGB_BLOCK           }, // BC3
		{ VK_FORMAT_BC4_UNORM_BLOCK,           VK_FORMAT_BC4_UNORM_BLOCK,          VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // BC4
		{ VK_FORMAT_BC5_UNORM_BLOCK,           VK_FORMAT_BC5_UNORM_BLOCK,          VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // BC5
		{ VK_FORMAT_BC6H_SFLOAT_BLOCK,         VK_FORMAT_BC6H_SFLOAT_BLOCK,        VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // BC6H
		{ VK_FORMAT_BC7_UNORM_BLOCK,           VK_FORMAT_BC7_UNORM_BLOCK,          VK_FORMAT_UNDEFINED,           VK_FORMAT_BC7_SRGB_BLOCK           }, // BC7
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // ETC1
		{ VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK,   VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK   }, // ETC2
		{ VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK, VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK }, // ETC2A
		{ VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK, VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK }, // ETC2A1
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // PTC12
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // PTC14
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // PTC12A
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // PTC14A
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // PTC22
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // PTC24
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // Unknown
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // R1
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // A8
		{ VK_FORMAT_R8_UNORM,                  VK_FORMAT_R8_UNORM,                 VK_FORMAT_UNDEFINED,           VK_FORMAT_R8_SRGB                  }, // R8
		{ VK_FORMAT_R8_SINT,                   VK_FORMAT_R8_SINT,                  VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // R8I
		{ VK_FORMAT_R8_UINT,                   VK_FORMAT_R8_UINT,                  VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // R8U
		{ VK_FORMAT_R8_SNORM,                  VK_FORMAT_R8_SNORM,                 VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // R8S
		{ VK_FORMAT_R16_UNORM,                 VK_FORMAT_R16_UNORM,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // R16
		{ VK_FORMAT_R16_SINT,                  VK_FORMAT_R16_SINT,                 VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // R16I
		{ VK_FORMAT_R16_UNORM,                 VK_FORMAT_R16_UNORM,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // R16U
		{ VK_FORMAT_R16_SFLOAT,                VK_FORMAT_R16_SFLOAT,               VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // R16F
		{ VK_FORMAT_R16_SNORM,                 VK_FORMAT_R16_SNORM,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // R16S
		{ VK_FORMAT_R32_SINT,                  VK_FORMAT_R32_SINT,                 VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // R32I
		{ VK_FORMAT_R32_UINT,                  VK_FORMAT_R32_UINT,                 VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // R32U
		{ VK_FORMAT_R32_SFLOAT,                VK_FORMAT_R32_SFLOAT,               VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // R32F
		{ VK_FORMAT_R8G8_UNORM,                VK_FORMAT_R8G8_UNORM,               VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8_SRGB                }, // RG8
		{ VK_FORMAT_R8G8_SINT,                 VK_FORMAT_R8G8_SINT,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RG8I
		{ VK_FORMAT_R8G8_UINT,                 VK_FORMAT_R8G8_UINT,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RG8U
		{ VK_FORMAT_R8G8_SNORM,                VK_FORMAT_R8G8_SNORM,               VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RG8S
		{ VK_FORMAT_R16G16_UNORM,              VK_FORMAT_R16G16_UNORM,             VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RG16
		{ VK_FORMAT_R16G16_SINT,               VK_FORMAT_R16G16_SINT,              VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RG16I
		{ VK_FORMAT_R16G16_UINT,               VK_FORMAT_R16G16_UINT,              VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RG16U
		{ VK_FORMAT_R16G16_SFLOAT,             VK_FORMAT_R16G16_SFLOAT,            VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RG16F
		{ VK_FORMAT_R16G16_SNORM,              VK_FORMAT_R16G16_SNORM,             VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RG16S
		{ VK_FORMAT_R32G32_SINT,               VK_FORMAT_R32G32_SINT,              VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RG32I
		{ VK_FORMAT_R32G32_UINT,               VK_FORMAT_R32G32_UINT,              VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RG32U
		{ VK_FORMAT_R32G32_SFLOAT,             VK_FORMAT_R32G32_SFLOAT,            VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RG32F
		{ VK_FORMAT_R8G8B8_UNORM,              VK_FORMAT_R8G8B8_UNORM,             VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8B8_SRGB              }, // RGB8
		{ VK_FORMAT_R8G8B8_SINT,               VK_FORMAT_R8G8B8_SINT,              VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8B8_SRGB              }, // RGB8I
		{ VK_FORMAT_R8G8B8_UINT,               VK_FORMAT_R8G8B8_UINT,              VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8B8_SRGB              }, // RGB8U
		{ VK_FORMAT_R8G8B8_SNORM,              VK_FORMAT_R8G8B8_SNORM,             VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RGB8S
		{ VK_FORMAT_E5B9G9R9_UFLOAT_PACK32,    VK_FORMAT_E5B9G9R9_UFLOAT_PACK32,   VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RGB9E5F
		{ VK_FORMAT_B8G8R8A8_UNORM,            VK_FORMAT_B8G8R8A8_UNORM,           VK_FORMAT_UNDEFINED,           VK_FORMAT_B8G8R8A8_SRGB            }, // BGRA8
		{ VK_FORMAT_R8G8B8A8_UNORM,            VK_FORMAT_R8G8B8A8_UNORM,           VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8B8A8_SRGB            }, // RGBA8
		{ VK_FORMAT_R8G8B8A8_SINT,             VK_FORMAT_R8G8B8A8_SINT,            VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8B8A8_SRGB            }, // RGBA8I
		{ VK_FORMAT_R8G8B8A8_UINT,             VK_FORMAT_R8G8B8A8_UINT,            VK_FORMAT_UNDEFINED,           VK_FORMAT_R8G8B8A8_SRGB            }, // RGBA8U
		{ VK_FORMAT_R8G8B8A8_SNORM,            VK_FORMAT_R8G8B8A8_SNORM,           VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RGBA8S
		{ VK_FORMAT_R16G16B16A16_UNORM,        VK_FORMAT_R16G16B16A16_UNORM,       VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RGBA16
		{ VK_FORMAT_R16G16B16A16_SINT,         VK_FORMAT_R16G16B16A16_SINT,        VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RGBA16I
		{ VK_FORMAT_R16G16B16A16_UINT,         VK_FORMAT_R16G16B16A16_UINT,        VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RGBA16U
		{ VK_FORMAT_R16G16B16A16_SFLOAT,       VK_FORMAT_R16G16B16A16_SFLOAT,      VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RGBA16F
		{ VK_FORMAT_R16G16B16A16_SNORM,        VK_FORMAT_R16G16B16A16_SNORM,       VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RGBA16S
		{ VK_FORMAT_R32G32B32A32_SINT,         VK_FORMAT_R32G32B32A32_SINT,        VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RGBA32I
		{ VK_FORMAT_R32G32B32A32_UINT,         VK_FORMAT_R32G32B32A32_UINT,        VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RGBA32U
		{ VK_FORMAT_R32G32B32A32_SFLOAT,       VK_FORMAT_R32G32B32A32_SFLOAT,      VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RGBA32F
		{ VK_FORMAT_B5G6R5_UNORM_PACK16,       VK_FORMAT_B5G6R5_UNORM_PACK16,      VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // R5G6B5
		{ VK_FORMAT_B4G4R4A4_UNORM_PACK16,     VK_FORMAT_B4G4R4A4_UNORM_PACK16,    VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RGBA4
		{ VK_FORMAT_B5G5R5A1_UNORM_PACK16,     VK_FORMAT_B5G5R5A1_UNORM_PACK16,    VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RGB5A1
		{ VK_FORMAT_A2R10G10B10_UNORM_PACK32,  VK_FORMAT_A2R10G10B10_UNORM_PACK32, VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RGB10A2
		{ VK_FORMAT_B10G11R11_UFLOAT_PACK32,   VK_FORMAT_B10G11R11_UFLOAT_PACK32,  VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // RG11B10F
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED,                VK_FORMAT_UNDEFINED,           VK_FORMAT_UNDEFINED                }, // UnknownDepth
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_R16_UNORM,                VK_FORMAT_D16_UNORM,           VK_FORMAT_UNDEFINED                }, // D16
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_X8_D24_UNORM_PACK32,      VK_FORMAT_D24_UNORM_S8_UINT,   VK_FORMAT_UNDEFINED                }, // D24
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_X8_D24_UNORM_PACK32,      VK_FORMAT_D24_UNORM_S8_UINT,   VK_FORMAT_UNDEFINED                }, // D24S8
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_X8_D24_UNORM_PACK32,      VK_FORMAT_D24_UNORM_S8_UINT,   VK_FORMAT_UNDEFINED                }, // D32
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_R32_SFLOAT,               VK_FORMAT_D32_SFLOAT,          VK_FORMAT_UNDEFINED                }, // D16F
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_R32_SFLOAT,               VK_FORMAT_D32_SFLOAT,          VK_FORMAT_UNDEFINED                }, // D24F
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_R32_SFLOAT,               VK_FORMAT_D32_SFLOAT,          VK_FORMAT_UNDEFINED                }, // D32F
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_X8_D24_UNORM_PACK32,      VK_FORMAT_D24_UNORM_S8_UINT,   VK_FORMAT_UNDEFINED                }, // D0S8
	};
	BX_STATIC_ASSERT(TextureFormat::Count == BX_COUNTOF(s_textureFormat) );

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

	uint32_t fillVertexDecl(VkPipelineVertexInputStateCreateInfo& _vertexInputState, const VertexDecl& _decl)
	{
		VkVertexInputBindingDescription*   inputBinding = const_cast<VkVertexInputBindingDescription*>(_vertexInputState.pVertexBindingDescriptions);
		VkVertexInputAttributeDescription* inputAttrib  = const_cast<VkVertexInputAttributeDescription*>(_vertexInputState.pVertexAttributeDescriptions);

		inputBinding->binding   = 0;
		inputBinding->stride    = _decl.m_stride;
		inputBinding->inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		_vertexInputState.vertexBindingDescriptionCount = 1;

		uint32_t numAttribs = 0;
		for (uint32_t attr = 0; attr < Attrib::Count; ++attr)
		{
			if (UINT16_MAX != _decl.m_attributes[attr])
			{
				inputAttrib->location   = numAttribs;
				inputAttrib->binding    = 0;

				if (0 == _decl.m_attributes[attr])
				{
					inputAttrib->format = VK_FORMAT_R32G32B32_SFLOAT;
					inputAttrib->offset = 0;
				}
				else
				{
					uint8_t num;
					AttribType::Enum type;
					bool normalized;
					bool asInt;
					_decl.decode(Attrib::Enum(attr), num, type, normalized, asInt);
					inputAttrib->format = s_attribType[type][num-1][normalized];
					inputAttrib->offset = _decl.m_offset[attr];
				}

				++inputAttrib;
				++numAttribs;
			}
		}

		_vertexInputState.vertexAttributeDescriptionCount = numAttribs;

		return numAttribs;
	}

	static const char* s_allocScopeName[] =
	{
		"vkCommand",
		"vkObject",
		"vkCache",
		"vkDevice",
		"vkInstance",
	};
	BX_STATIC_ASSERT(VK_SYSTEM_ALLOCATION_SCOPE_RANGE_SIZE == BX_COUNTOF(s_allocScopeName) );

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
				numExtensionProperties = bx::uint32_min(numExtensionProperties, BX_COUNTOF(extensionProperties) );
				result = enumerateExtensionProperties(_physicalDevice
					, NULL
					, &numExtensionProperties
					, extensionProperties
					);

				BX_TRACE("\tGlobal extensions (%d):"
					, numExtensionProperties
					);

				for (uint32_t extension = 0; extension < numExtensionProperties; ++extension)
				{
					BX_TRACE("\t\t%s (s: 0x%08x)"
						, extensionProperties[extension].extensionName
						, extensionProperties[extension].specVersion
						);
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
			numLayerProperties = bx::uint32_min(numLayerProperties, BX_COUNTOF(layerProperties) );
			result = enumerateLayerProperties(_physicalDevice, &numLayerProperties, layerProperties);

			char indent = VK_NULL_HANDLE == _physicalDevice ? ' ' : '\t';
			BX_UNUSED(indent);

			BX_TRACE("%cLayer extensions (%d):"
				, indent
				, numLayerProperties
				);
			for (uint32_t layer = 0; layer < numLayerProperties; ++layer)
			{
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
					numExtensionProperties = bx::uint32_min(numExtensionProperties, BX_COUNTOF(extensionProperties) );
					result = enumerateExtensionProperties(_physicalDevice
						, layerProperties[layer].layerName
						, &numExtensionProperties
						, extensionProperties
						);

					for (uint32_t extension = 0; extension < numExtensionProperties; ++extension)
					{
						BX_TRACE("%c\t\t%s (s: 0x%08x)"
							, indent
							, extensionProperties[extension].extensionName
							, extensionProperties[extension].specVersion
							);
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

	void setImageMemoryBarrier(VkCommandBuffer _commandBuffer, VkImage _image, VkImageLayout _oldLayout, VkImageLayout _newLayout)
	{
		VkAccessFlags srcAccessMask = 0;
		VkAccessFlags dstAccessMask = 0;
		VkImageAspectFlags aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

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
			aspectMask     = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
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
		imb.subresourceRange.aspectMask     = aspectMask;
		imb.subresourceRange.baseMipLevel   = 0;
		imb.subresourceRange.levelCount     = 1;
		imb.subresourceRange.baseArrayLayer = 0;
		imb.subresourceRange.layerCount     = 1;
		vkCmdPipelineBarrier(_commandBuffer
			, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
			, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT
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
			, m_renderdocdll(NULL)
			, m_vulkan1dll(NULL)
			, m_maxAnisotropy(1)
			, m_depthClamp(false)
			, m_wireframe(false)
		{
		}

		~RendererContextVK()
		{
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
					RenderPassCreated,
					SurfaceCreated,
					SwapchainCreated,
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

			m_renderdocdll = loadRenderDoc();
			m_vulkan1dll = bx::dlopen(
#if BX_PLATFORM_WINDOWS
					"vulkan-1.dll"
#elif BX_PLATFORM_ANDROID
					"libvulkan.so"
#else
					"libvulkan.so.1"
#endif // BX_PLATFORM_*
					);

			if (NULL == m_vulkan1dll)
			{
				BX_TRACE("Init error: Failed to load vulkan dynamic library.");
				goto error;
			}

			errorState = ErrorState::LoadedVulkan1;

			BX_TRACE("Shared library functions:");
#define VK_IMPORT_FUNC(_optional, _func) \
			_func = (PFN_##_func)bx::dlsym(m_vulkan1dll, #_func); \
			BX_TRACE("\t%p " #_func, _func); \
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

				VkApplicationInfo appInfo;
				appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
				appInfo.pNext = NULL;
				appInfo.pApplicationName   = "bgfx";
				appInfo.applicationVersion = BGFX_API_VERSION;
				appInfo.pEngineName   = "bgfx";
				appInfo.engineVersion = BGFX_API_VERSION;
				appInfo.apiVersion    = VK_MAKE_VERSION(1, 0, 0); //VK_HEADER_VERSION);

				const char* enabledLayerNames[] =
				{
#if BGFX_CONFIG_DEBUG
//					"VK_LAYER_GOOGLE_threading",
//					"VK_LAYER_GOOGLE_unique_objects",
//					"VK_LAYER_LUNARG_device_limits",
//					"VK_LAYER_LUNARG_standard_validation",
//					"VK_LAYER_LUNARG_image",
//					"VK_LAYER_LUNARG_mem_tracker",
//					"VK_LAYER_LUNARG_object_tracker",
//					"VK_LAYER_LUNARG_parameter_validation",
//					"VK_LAYER_LUNARG_swapchain",
//					"VK_LAYER_LUNARG_vktrace",
//					"VK_LAYER_RENDERDOC_Capture",
#endif // BGFX_CONFIG_DEBUG
					/*not used*/ ""
				};

				const char* enabledExtension[] =
				{
					VK_KHR_SURFACE_EXTENSION_NAME,
					KHR_SURFACE_EXTENSION_NAME,
#if BGFX_CONFIG_DEBUG
					VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
#endif // BGFX_CONFIG_DEBUG
					/*not used*/ ""
				};

				VkInstanceCreateInfo ici;
				ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
				ici.pNext = NULL;
				ici.flags = 0;
				ici.pApplicationInfo = &appInfo;
				ici.enabledLayerCount   = BX_COUNTOF(enabledLayerNames) - 1;
				ici.ppEnabledLayerNames = enabledLayerNames;
				ici.enabledExtensionCount   = BX_COUNTOF(enabledExtension) - 1;
				ici.ppEnabledExtensionNames = enabledExtension;

				if (BX_ENABLED(BGFX_CONFIG_DEBUG) )
				{
					m_allocatorCb = &s_allocationCb;
					BX_UNUSED(s_allocationCb);
				}

				result = vkCreateInstance(&ici
						, m_allocatorCb
						, &m_instance
						);
			}

			if (VK_SUCCESS != result)
			{
				BX_TRACE("Init error: vkCreateInstance failed %d: %s.", result, getName(result) );
				goto error;
			}

			errorState = ErrorState::InstanceCreated;

			BX_TRACE("Instance functions:");
#define VK_IMPORT_INSTANCE_FUNC(_optional, _func) \
			_func = (PFN_##_func)vkGetInstanceProcAddr(m_instance, #_func); \
			BX_TRACE("\t%p " #_func, _func); \
			imported &= _optional || NULL != _func
VK_IMPORT_INSTANCE
#undef VK_IMPORT_INSTANCE_FUNC

			if (!imported)
			{
				BX_TRACE("Init error: Failed to load instance functions.");
				goto error;
			}

			m_debugReportCallback = VK_NULL_HANDLE;
			if (BX_ENABLED(BGFX_CONFIG_DEBUG) )
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
				numPhysicalDevices = bx::uint32_min(numPhysicalDevices, BX_COUNTOF(physicalDevices) );
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
					BX_TRACE("\t   API version: %x", pdp.apiVersion);
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

				g_caps.limits.maxTextureSize   = m_deviceProperties.limits.maxImageDimension2D;
				g_caps.limits.maxFBAttachments = uint8_t(bx::uint32_min(m_deviceProperties.limits.maxFragmentOutputAttachments, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS) );

				{
//					VkFormatProperties fp;
//					vkGetPhysicalDeviceFormatProperties(m_physicalDevice, fmt, &fp);

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
					};

					for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
					{
						uint8_t support = BGFX_CAPS_FORMAT_TEXTURE_NONE;

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

				VkQueueFamilyProperties queueFamilyPropertices[10] = {};
				queueFamilyPropertyCount = bx::uint32_min(queueFamilyPropertyCount, BX_COUNTOF(queueFamilyPropertices) );
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

			{
				const char* enabledLayerNames[] =
				{
#if BGFX_CONFIG_DEBUG
					"VK_LAYER_GOOGLE_threading",
//					"VK_LAYER_GOOGLE_unique_objects",
					"VK_LAYER_LUNARG_device_limits",
//					"VK_LAYER_LUNARG_standard_validation",
					"VK_LAYER_LUNARG_image",
					"VK_LAYER_LUNARG_object_tracker",
					"VK_LAYER_LUNARG_parameter_validation",
					"VK_LAYER_LUNARG_swapchain",
//					"VK_LAYER_LUNARG_vktrace",
//					"VK_LAYER_RENDERDOC_Capture",
#endif // BGFX_CONFIG_DEBUG
					/*not used*/ ""
				};

				const char* enabledExtension[] =
				{
					VK_KHR_SWAPCHAIN_EXTENSION_NAME,
//					"VK_LUNARG_DEBUG_MARKER",
					/*not used*/ ""
				};

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
				dci.enabledLayerCount    = BX_COUNTOF(enabledLayerNames) - 1;
				dci.ppEnabledLayerNames  = enabledLayerNames;
				dci.enabledExtensionCount   = BX_COUNTOF(enabledExtension) - 1;
				dci.ppEnabledExtensionNames = enabledExtension;
				dci.pEnabledFeatures = NULL;

				result = vkCreateDevice(m_physicalDevice
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
#define VK_IMPORT_DEVICE_FUNC(_optional, _func) \
			_func = (PFN_##_func)vkGetDeviceProcAddr(m_device, #_func); \
			BX_TRACE("\t%p " #_func, _func); \
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

			m_backBufferDepthStencilFormat =
				VK_FORMAT_D32_SFLOAT_S8_UINT
//				VK_FORMAT_D24_UNORM_S8_UINT
				;

			{
				m_sci.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;

				VkAttachmentDescription ad[2];
				ad[0].flags   = 0;
				ad[0].format  = m_sci.imageFormat;
				ad[0].samples = VK_SAMPLE_COUNT_1_BIT;
				ad[0].loadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
				ad[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
				ad[0].stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
				ad[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
				ad[0].initialLayout  = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
				ad[0].finalLayout    = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
				ad[1].flags   = 0;
				ad[1].format  = m_backBufferDepthStencilFormat;
				ad[1].samples = VK_SAMPLE_COUNT_1_BIT;
				ad[1].loadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
				ad[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
				ad[1].stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
				ad[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
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
				depthAr[0].layout     = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

				VkSubpassDescription sd[1];
				sd[0].flags = 0;
				sd[0].pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS;
				sd[0].inputAttachmentCount = 0;
				sd[0].pInputAttachments    = NULL;
				sd[0].colorAttachmentCount = BX_COUNTOF(colorAr);
				sd[0].pColorAttachments    = colorAr;
				sd[0].pResolveAttachments  = resolveAr;
				sd[0].pDepthStencilAttachment = depthAr;
				sd[0].preserveAttachmentCount = 0;
				sd[0].pPreserveAttachments    = NULL;

				VkRenderPassCreateInfo rpi;
				rpi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
				rpi.pNext = NULL;
				rpi.flags = 0;
				rpi.attachmentCount = BX_COUNTOF(ad);
				rpi.pAttachments    = ad;
				rpi.subpassCount    = BX_COUNTOF(sd);
				rpi.pSubpasses      = sd;
				rpi.dependencyCount = 0;
				rpi.pDependencies   = NULL;

				result = vkCreateRenderPass(m_device, &rpi, m_allocatorCb, &m_renderPass);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkCreateRenderPass failed %d: %s.", result, getName(result) );
					goto error;
				}
			}

			errorState = ErrorState::RenderPassCreated;

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
				result = vkCreateAndroidSurfaceKHR(m_instance, &sci, m_allocatorCb, &m_surface);
			}
#elif BX_PLATFORM_LINUX
			{
				if (NULL != vkCreateXlibSurfaceKHR)
				{
					VkXlibSurfaceCreateInfoKHR sci;
					sci.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
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
					VkXcbSurfaceCreateInfoKHR sci;
					sci.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
					sci.pNext = NULL;
					sci.flags      = 0;
					sci.connection = (xcb_connection_t*)g_platformData.ndt;
					union { void* ptr; xcb_window_t window; } cast = { g_platformData.nwh };
					sci.window = cast.window;
					result = vkCreateXcbSurfaceKHR(m_instance, &sci, m_allocatorCb, &m_surface);
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

				uint32_t numSurfaceFormats;
				result = vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, m_surface, &numSurfaceFormats, NULL);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkGetPhysicalDeviceSurfaceFormatsKHR failed %d: %s.", result, getName(result) );
					goto error;
				}

				VkSurfaceFormatKHR surfaceFormats[10];
				numSurfaceFormats = bx::uint32_min(numSurfaceFormats, BX_COUNTOF(surfaceFormats) );
				vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, m_surface, &numSurfaceFormats, surfaceFormats);

				// find the best match...
				uint32_t surfaceFormatIdx = 0;

				uint32_t numPresentModes;
				result = vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, m_surface, &numPresentModes, NULL);
				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkGetPhysicalDeviceSurfacePresentModesKHR failed %d: %s.", result, getName(result) );
					goto error;
				}

				VkPresentModeKHR presentModes[10];
				numPresentModes = bx::uint32_min(numPresentModes, BX_COUNTOF(presentModes) );
				vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, m_surface, &numPresentModes, presentModes);

				// find the best match...
				uint32_t presentModeIdx = 0;

				m_sci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
				m_sci.pNext = NULL;
				m_sci.flags = 0;
				m_sci.surface = m_surface;
				m_sci.minImageCount   = BX_COUNTOF(m_backBufferColorImage);
				m_sci.imageFormat     = surfaceFormats[surfaceFormatIdx].format;
				m_sci.imageColorSpace = surfaceFormats[surfaceFormatIdx].colorSpace;
				m_sci.imageExtent.width  = _init.resolution.m_width;
				m_sci.imageExtent.height = _init.resolution.m_height;
				m_sci.imageArrayLayers = 1;
				m_sci.imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
				m_sci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
				m_sci.queueFamilyIndexCount = 0;
				m_sci.pQueueFamilyIndices   = NULL;
				m_sci.preTransform   = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
				m_sci.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
				m_sci.presentMode    = presentModes[presentModeIdx];
				m_sci.clipped        = VK_TRUE;
				m_sci.oldSwapchain   = VK_NULL_HANDLE;
				result = vkCreateSwapchainKHR(m_device, &m_sci, m_allocatorCb, &m_swapchain);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkCreateSwapchainKHR failed %d: %s.", result, getName(result) );
					goto error;
				}

				uint32_t numSwapchainImages;
				result = vkGetSwapchainImagesKHR(m_device, m_swapchain, &numSwapchainImages, NULL);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkGetSwapchainImagesKHR failed %d: %s.", result, getName(result) );
					goto error;
				}

				if (numSwapchainImages < m_sci.minImageCount)
				{
					BX_TRACE("Init error: vkGetSwapchainImagesKHR: numSwapchainImages %d, minImageCount %d."
						, numSwapchainImages
						, m_sci.minImageCount
						);
					goto error;
				}

				numSwapchainImages = m_sci.minImageCount;
				result = vkGetSwapchainImagesKHR(m_device, m_swapchain, &numSwapchainImages, &m_backBufferColorImage[0]);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkGetSwapchainImagesKHR failed %d: %s.", result, getName(result) );
					goto error;
				}

				for (uint32_t ii = 0; ii < BX_COUNTOF(m_backBufferColorImageView); ++ii)
				{
					m_backBufferColorImageView[ii] = VK_NULL_HANDLE;
					m_backBufferColor[ii]          = VK_NULL_HANDLE;
				}

				VkImageCreateInfo ici;
				ici.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
				ici.pNext = NULL;
				ici.flags = 0;
				ici.imageType = VK_IMAGE_TYPE_2D;
				ici.format    = m_backBufferDepthStencilFormat;
				ici.extent.width  = m_sci.imageExtent.width;
				ici.extent.height = m_sci.imageExtent.height;
				ici.extent.depth  = 1;
				ici.mipLevels   = 1;
				ici.arrayLayers = 1;
				ici.samples = VK_SAMPLE_COUNT_1_BIT;
				ici.tiling  = VK_IMAGE_TILING_OPTIMAL;
				ici.usage   = 0
					| VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
					| VK_IMAGE_USAGE_TRANSFER_SRC_BIT
					;
				ici.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
				ici.queueFamilyIndexCount = 0; //m_sci.queueFamilyIndexCount;
				ici.pQueueFamilyIndices   = NULL; //m_sci.pQueueFamilyIndices;
				ici.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;
				result = vkCreateImage(m_device, &ici, m_allocatorCb, &m_backBufferDepthStencilImage);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkCreateImage failed %d: %s.", result, getName(result) );
					goto error;
				}

				VkMemoryRequirements mr;
				vkGetImageMemoryRequirements(m_device, m_backBufferDepthStencilImage, &mr);

				VkMemoryAllocateInfo ma;
				ma.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				ma.pNext = NULL;
				ma.allocationSize  = mr.size;
				ma.memoryTypeIndex = selectMemoryType(mr.memoryTypeBits
					, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
					);
				result = vkAllocateMemory(m_device
					, &ma
					, m_allocatorCb
					, &m_backBufferDepthStencilMemory
					);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkAllocateMemory failed %d: %s.", result, getName(result) );
					goto error;
				}

				result = vkBindImageMemory(m_device, m_backBufferDepthStencilImage, m_backBufferDepthStencilMemory, 0);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkBindImageMemory failed %d: %s.", result, getName(result) );
					goto error;
				}

				VkImageViewCreateInfo ivci;
				ivci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				ivci.pNext = NULL;
				ivci.flags = 0;
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
					BX_TRACE("Init error: vkCreateImageView failed %d: %s.", result, getName(result) );
					goto error;
				}

				::VkImageView attachments[] =
				{
					VK_NULL_HANDLE,
					m_backBufferDepthStencilImageView,
				};

				VkFramebufferCreateInfo fci;
				fci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
				fci.pNext = NULL;
				fci.flags = 0;
				fci.renderPass = m_renderPass;
				fci.attachmentCount = BX_COUNTOF(attachments);
				fci.pAttachments    = attachments;
				fci.width  = m_sci.imageExtent.width;
				fci.height = m_sci.imageExtent.height;
				fci.layers = 1;

				VkSemaphoreCreateInfo sci;
				sci.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
				sci.pNext = NULL;
				sci.flags = 0;

				for (uint32_t ii = 0; ii < numSwapchainImages; ++ii)
				{
					ivci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
					ivci.pNext = NULL;
					ivci.flags = 0;
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
						BX_TRACE("Init error: vkCreateImageView failed %d: %s.", result, getName(result) );
						goto error;
					}

					attachments[0] = m_backBufferColorImageView[ii];
					result = vkCreateFramebuffer(m_device, &fci, m_allocatorCb, &m_backBufferColor[ii]);

					if (VK_SUCCESS != result)
					{
						BX_TRACE("Init error: vkCreateFramebuffer failed %d: %s.", result, getName(result) );
						goto error;
					}

					result = vkCreateSemaphore(m_device, &sci, m_allocatorCb, &m_presentDone[ii]);

					if (VK_SUCCESS != result)
					{
						BX_TRACE("Init error: vkCreateSemaphore failed %d: %s.", result, getName(result) );
						goto error;
					}

					sci.flags = 0;
				}
			}

			errorState = ErrorState::SwapchainCreated;

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

				VkCommandBufferBeginInfo cbbi;
				cbbi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
				cbbi.pNext = NULL;
				cbbi.flags = 0;
				cbbi.pInheritanceInfo = NULL;

				VkCommandBuffer commandBuffer = m_commandBuffers[0];
				VK_CHECK(vkBeginCommandBuffer(commandBuffer, &cbbi) );

				VkRenderPassBeginInfo rpbi;
				rpbi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
				rpbi.pNext = NULL;
				rpbi.renderPass  = m_renderPass;
				rpbi.renderArea.offset.x = 0;
				rpbi.renderArea.offset.y = 0;
				rpbi.renderArea.extent = m_sci.imageExtent;
				rpbi.clearValueCount = 0;
				rpbi.pClearValues = NULL;

				setImageMemoryBarrier(commandBuffer
					, m_backBufferDepthStencilImage
					, VK_IMAGE_LAYOUT_UNDEFINED
					, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
					);

				for (uint32_t ii = 0; ii < BX_COUNTOF(m_backBufferColorImage); ++ii)
				{
					setImageMemoryBarrier(commandBuffer
						, m_backBufferColorImage[ii]
						, VK_IMAGE_LAYOUT_UNDEFINED
						, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
						);

					rpbi.framebuffer = m_backBufferColor[ii];
					vkCmdBeginRenderPass(commandBuffer, &rpbi, VK_SUBPASS_CONTENTS_INLINE);
					vkCmdEndRenderPass(commandBuffer);

					setImageMemoryBarrier(commandBuffer
						, m_backBufferColorImage[ii]
						, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
						, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
						);
				}

				VK_CHECK(vkEndCommandBuffer(commandBuffer) );
				m_backBufferColorIdx = 0;

				kick();
				finishAll();

				VK_CHECK(vkResetCommandPool(m_device, m_commandPool, 0) );
			}

			errorState = ErrorState::CommandBuffersCreated;

			{
				VkDescriptorPoolSize dps[] =
				{
//					{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS },
					{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,         10<<10                           },
//					{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,         BGFX_CONFIG_MAX_TEXTURE_SAMPLERS },
				};

				VkDescriptorSetLayoutBinding dslb[] =
				{
//					{ DslBinding::CombinedImageSampler, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, VK_SHADER_STAGE_ALL, NULL },
					{ DslBinding::UniformBuffer,        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,         1,                                VK_SHADER_STAGE_ALL, NULL },
//					{ DslBinding::StorageBuffer,        VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,         BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, VK_SHADER_STAGE_ALL, NULL },
				};

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

				VkDescriptorSetLayoutCreateInfo dsl;
				dsl.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				dsl.pNext = NULL;
				dsl.flags = 0;
				dsl.bindingCount = BX_COUNTOF(dslb);
				dsl.pBindings    = dslb;
				result = vkCreateDescriptorSetLayout(m_device, &dsl, m_allocatorCb, &m_descriptorSetLayout);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkCreateDescriptorSetLayout failed %d: %s.", result, getName(result) );
					goto error;
				}

				VkPipelineLayoutCreateInfo pl;
				pl.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
				pl.pNext = NULL;
				pl.flags = 0;
				pl.setLayoutCount = 1;
				pl.pSetLayouts    = &m_descriptorSetLayout;
				pl.pushConstantRangeCount = 0;
				pl.pPushConstantRanges    = NULL;
				result = vkCreatePipelineLayout(m_device, &pl, m_allocatorCb, &m_pipelineLayout);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("Init error: vkCreatePipelineLayout failed %d: %s.", result, getName(result) );
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

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_scratchBuffer); ++ii)
			{
				m_scratchBuffer[ii].create(BGFX_CONFIG_MAX_DRAW_CALLS*1024
					, 1024 //BGFX_CONFIG_MAX_TEXTURES + BGFX_CONFIG_MAX_SHADERS + BGFX_CONFIG_MAX_DRAW_CALLS
					);
			}

			errorState = ErrorState::DescriptorCreated;

			return true;

		error:
			BX_TRACE("errorState %d", errorState);
			switch (errorState)
			{
			case ErrorState::DescriptorCreated:
				vkDestroy(m_pipelineCache);
				vkDestroy(m_pipelineLayout);
				vkDestroy(m_descriptorSetLayout);
				vkDestroy(m_descriptorPool);

			case ErrorState::CommandBuffersCreated:
				vkFreeCommandBuffers(m_device, m_commandPool, BX_COUNTOF(m_commandBuffers), m_commandBuffers);
				vkDestroy(m_commandPool);
				vkDestroy(m_fence);

			case ErrorState::SwapchainCreated:
				for (uint32_t ii = 0; ii < BX_COUNTOF(m_backBufferColorImageView); ++ii)
				{
					if (VK_NULL_HANDLE != m_backBufferColorImageView[ii])
					{
						vkDestroy(m_backBufferColorImageView[ii]);
					}

					if (VK_NULL_HANDLE != m_backBufferColor[ii])
					{
						vkDestroy(m_backBufferColor[ii]);
					}

					if (VK_NULL_HANDLE != m_presentDone[ii])
					{
						vkDestroy(m_presentDone[ii]);
					}
				}
				vkDestroy(m_swapchain);

			case ErrorState::SurfaceCreated:
				vkDestroySurfaceKHR(m_instance, m_surface, m_allocatorCb);

			case ErrorState::RenderPassCreated:
				vkDestroy(m_renderPass);

			case ErrorState::DeviceCreated:
				vkDestroyDevice(m_device, m_allocatorCb);

			case ErrorState::InstanceCreated:
				if (VK_NULL_HANDLE != m_debugReportCallback)
				{
					vkDestroyDebugReportCallbackEXT(m_instance, m_debugReportCallback, m_allocatorCb);
				}

				vkDestroyInstance(m_instance, m_allocatorCb);

			case ErrorState::LoadedVulkan1:
				bx::dlclose(m_vulkan1dll);
				m_vulkan1dll  = NULL;
				m_allocatorCb = NULL;
				unloadRenderDoc(m_renderdocdll);

			case ErrorState::Default:
				break;
			};

			BX_CHECK(false, "Failed to initialize Vulkan.");
			return false;
		}

		void shutdown()
		{
			VK_CHECK(vkQueueWaitIdle(m_queueGraphics) );
			VK_CHECK(vkDeviceWaitIdle(m_device) );

			m_pipelineStateCache.invalidate();

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
			vkDestroy(m_pipelineLayout);
			vkDestroy(m_descriptorSetLayout);
			vkDestroy(m_descriptorPool);

			vkFreeCommandBuffers(m_device, m_commandPool, BX_COUNTOF(m_commandBuffers), m_commandBuffers);
			vkDestroy(m_commandPool);
			vkDestroy(m_fence);

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_backBufferColorImageView); ++ii)
			{
				if (VK_NULL_HANDLE != m_backBufferColorImageView[ii])
				{
					vkDestroy(m_backBufferColorImageView[ii]);
				}

				if (VK_NULL_HANDLE != m_backBufferColor[ii])
				{
					vkDestroy(m_backBufferColor[ii]);
				}

				if (VK_NULL_HANDLE != m_presentDone[ii])
				{
					vkDestroy(m_presentDone[ii]);
				}
			}
			vkDestroy(m_swapchain);

			vkDestroy(m_backBufferDepthStencilImageView);
			vkFreeMemory(m_device, m_backBufferDepthStencilMemory, m_allocatorCb);
			vkDestroy(m_backBufferDepthStencilImage);

			vkDestroySurfaceKHR(m_instance, m_surface, m_allocatorCb);

			vkDestroy(m_renderPass);

			vkDestroyDevice(m_device, m_allocatorCb);

			if (VK_NULL_HANDLE != m_debugReportCallback)
			{
				vkDestroyDebugReportCallbackEXT(m_instance, m_debugReportCallback, m_allocatorCb);
			}

			vkDestroyInstance(m_instance, m_allocatorCb);

			bx::dlclose(m_vulkan1dll);
			m_vulkan1dll  = NULL;
			m_allocatorCb = NULL;
			unloadRenderDoc(m_renderdocdll);
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

		void flip(HMD& /*_hmd*/) override
		{
			if (VK_NULL_HANDLE != m_swapchain)
			{
				VkPresentInfoKHR pi;
				pi.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
				pi.pNext = NULL;
				pi.waitSemaphoreCount = 0;
				pi.pWaitSemaphores    = NULL; //&m_presentDone[0];
				pi.swapchainCount = 1;
				pi.pSwapchains    = &m_swapchain;
				pi.pImageIndices  = &m_backBufferColorIdx;
				pi.pResults       = NULL;
				VK_CHECK(vkQueuePresentKHR(m_queueGraphics, &pi) );
			}
		}

		void createIndexBuffer(IndexBufferHandle _handle, Memory* _mem, uint16_t _flags) override
		{
			m_indexBuffers[_handle.idx].create(_mem->size, _mem->data, _flags, false);
		}

		void destroyIndexBuffer(IndexBufferHandle _handle) override
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void createVertexDecl(VertexDeclHandle _handle, const VertexDecl& _decl) override
		{
			VertexDecl& decl = m_vertexDecls[_handle.idx];
			bx::memCopy(&decl, &_decl, sizeof(VertexDecl) );
			dump(decl);
		}

		void destroyVertexDecl(VertexDeclHandle /*_handle*/) override
		{
		}

		void createVertexBuffer(VertexBufferHandle _handle, Memory* _mem, VertexDeclHandle _declHandle, uint16_t _flags) override
		{
			m_vertexBuffers[_handle.idx].create(_mem->size, _mem->data, _declHandle, _flags);
		}

		void destroyVertexBuffer(VertexBufferHandle _handle) override
		{
			m_vertexBuffers[_handle.idx].destroy();
		}

		void createDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size, uint16_t _flags) override
		{
			m_indexBuffers[_handle.idx].create(_size, NULL, _flags, false);
		}

		void updateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem) override
		{
			BX_UNUSED(_handle, _offset, _size, _mem);
//			m_indexBuffers[_handle.idx].update(m_commandBuffer, _offset, bx::uint32_min(_size, _mem->size), _mem->data);
		}

		void destroyDynamicIndexBuffer(IndexBufferHandle _handle) override
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void createDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size, uint16_t _flags) override
		{
			VertexDeclHandle decl = BGFX_INVALID_HANDLE;
			m_vertexBuffers[_handle.idx].create(_size, NULL, decl, _flags);
		}

		void updateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem) override
		{
			BX_UNUSED(_handle, _offset, _size, _mem);
//			m_vertexBuffers[_handle.idx].update(m_commandBuffer, _offset, bx::uint32_min(_size, _mem->size), _mem->data);
		}

		void destroyDynamicVertexBuffer(VertexBufferHandle _handle) override
		{
			m_vertexBuffers[_handle.idx].destroy();
		}

		void createShader(ShaderHandle _handle, Memory* _mem) override
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

		void* createTexture(TextureHandle /*_handle*/, Memory* /*_mem*/, uint32_t /*_flags*/, uint8_t /*_skip*/) override
		{
			return NULL;
		}

		void updateTextureBegin(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/) override
		{
		}

		void updateTexture(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/, const Rect& /*_rect*/, uint16_t /*_z*/, uint16_t /*_depth*/, uint16_t /*_pitch*/, const Memory* /*_mem*/) override
		{
		}

		void updateTextureEnd() override
		{
		}

		void readTexture(TextureHandle /*_handle*/, void* /*_data*/, uint8_t /*_mip*/) override
		{
		}

		void resizeTexture(TextureHandle /*_handle*/, uint16_t /*_width*/, uint16_t /*_height*/, uint8_t /*_numMips*/) override
		{
		}

		void overrideInternal(TextureHandle /*_handle*/, uintptr_t /*_ptr*/) override
		{
		}

		uintptr_t getInternal(TextureHandle /*_handle*/) override
		{
			return 0;
		}

		void destroyTexture(TextureHandle /*_handle*/) override
		{
		}

		void createFrameBuffer(FrameBufferHandle /*_handle*/, uint8_t /*_num*/, const Attachment* /*_attachment*/) override
		{
		}

		void createFrameBuffer(FrameBufferHandle /*_handle*/, void* /*_nwh*/, uint32_t /*_width*/, uint32_t /*_height*/, TextureFormat::Enum /*_depthFormat*/) override
		{
		}

		void destroyFrameBuffer(FrameBufferHandle /*_handle*/) override
		{
		}

		void createUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name) override
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

		void destroyUniform(UniformHandle _handle) override
		{
			BX_FREE(g_allocator, m_uniforms[_handle.idx]);
			m_uniforms[_handle.idx] = NULL;
		}

		void requestScreenShot(FrameBufferHandle /*_handle*/, const char* /*_filePath*/) override
		{
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

		void setMarker(const char* /*_marker*/, uint32_t /*_size*/) override
		{
		}

		void invalidateOcclusionQuery(OcclusionQueryHandle _handle) override
		{
			BX_UNUSED(_handle);
		}

		virtual void setName(Handle _handle, const char* _name) override
		{
			BX_UNUSED(_handle, _name)
		}

		void submitBlit(BlitState& _bs, uint16_t _view);

		void submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) override;

		void blitSetup(TextVideoMemBlitter& /*_blitter*/) override
		{
		}

		void blitRender(TextVideoMemBlitter& /*_blitter*/, uint32_t /*_numIndices*/) override
		{
		}

		void updateResolution(const Resolution& _resolution)
		{
			if (!!(_resolution.m_flags & BGFX_RESET_MAXANISOTROPY) )
			{
				m_maxAnisotropy = UINT32_MAX;
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

			uint32_t flags = _resolution.m_flags & ~(BGFX_RESET_HMD_RECENTER | BGFX_RESET_MAXANISOTROPY | BGFX_RESET_DEPTH_CLAMP);

			if (m_resolution.m_width  != _resolution.m_width
			||  m_resolution.m_height != _resolution.m_height
			||  m_resolution.m_flags  != flags)
			{
				flags &= ~BGFX_RESET_INTERNAL_FORCE;

				bool resize = (m_resolution.m_flags&BGFX_RESET_MSAA_MASK) == (_resolution.m_flags&BGFX_RESET_MSAA_MASK);

				m_resolution = _resolution;
				m_resolution.m_flags = flags;

				m_textVideoMem.resize(false, _resolution.m_width, _resolution.m_height);
				m_textVideoMem.clear();

#if 1
				BX_UNUSED(resize);
#else
				m_scd.BufferDesc.Width  = _resolution.m_width;
				m_scd.BufferDesc.Height = _resolution.m_height;

				preReset();

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
				{
					updateMsaa();
					m_scd.SampleDesc = s_msaa[(m_resolution.m_flags&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT];

					DX_RELEASE(m_swapChain, 0);

					HRESULT hr;
					hr = m_factory->CreateSwapChain(m_cmd.m_commandQueue
							, &m_scd
							, reinterpret_cast<IDXGISwapChain**>(&m_swapChain)
							);
					BGFX_FATAL(SUCCEEDED(hr), bgfx::Fatal::UnableToInitialize, "Failed to create swap chain.");
				}

				postReset();
#endif // 0
			}
		}

		void setShaderUniform(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			BX_UNUSED(_flags, _regIndex, _val, _numRegs);
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

		void commitShaderUniforms(VkCommandBuffer _commandBuffer, uint16_t _programIdx)
		{
			const ProgramVK& program = m_program[_programIdx];
			VkDescriptorBufferInfo descriptorBufferInfo;
			uint32_t total = 0
				+ program.m_vsh->m_size
				+ (NULL != program.m_fsh ? program.m_fsh->m_size : 0)
				;
			if (0 < total)
			{
				uint8_t* data = (uint8_t*)m_scratchBuffer[m_backBufferColorIdx].allocUbv(descriptorBufferInfo, total);

				uint32_t size = program.m_vsh->m_size;
				bx::memCopy(data, m_vsScratch, size);
				data += size;

				if (NULL != program.m_fsh)
				{
					bx::memCopy(data, m_fsScratch, program.m_fsh->m_size);
				}

				vkCmdBindDescriptorSets(_commandBuffer
					, VK_PIPELINE_BIND_POINT_GRAPHICS
					, m_pipelineLayout
					, 0
					, 1
					, &m_scratchBuffer[m_backBufferColorIdx].m_descriptorSet
						[m_scratchBuffer[m_backBufferColorIdx].m_currentDs - 1]
					, 0
					, NULL
					);
			}

			m_vsChanges = 0;
			m_fsChanges = 0;
		}

		void setFrameBuffer(FrameBufferHandle _fbh, bool _msaa = true)
		{
			BX_UNUSED(_msaa);

			if (isValid(m_fbh)
			&&  m_fbh.idx != _fbh.idx)
			{
				const FrameBufferVK& frameBuffer = m_frameBuffers[m_fbh.idx];
				BX_UNUSED(frameBuffer);

//				for (uint8_t ii = 0, num = frameBuffer.m_num; ii < num; ++ii)
//				{
//					TextureVK& texture = m_textures[frameBuffer.m_texture[ii].idx];
//					texture.setState(m_commandList, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
//				}
//
//				if (isValid(frameBuffer.m_depth) )
//				{
//					TextureVK& texture = m_textures[frameBuffer.m_depth.idx];
//					const bool writeOnly  = 0 != (texture.m_flags&BGFX_TEXTURE_RT_WRITE_ONLY);
//					if (!writeOnly)
//					{
//						texture.setState(m_commandList, D3D12_RESOURCE_STATE_DEPTH_READ);
//					}
//				}
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
					BX_UNUSED(texture);
//					texture.setState(m_commandList, D3D12_RESOURCE_STATE_RENDER_TARGET);
				}

				if (isValid(frameBuffer.m_depth) )
				{
					TextureVK& texture = m_textures[frameBuffer.m_depth.idx];
					BX_UNUSED(texture);
//					texture.setState(m_commandList, D3D12_RESOURCE_STATE_DEPTH_WRITE);
				}

//				m_commandList->OMSetRenderTargets(frameBuffer.m_num
//												, m_currentColor
//												, true
//												, m_currentDepthStencil
//												);
			}

			m_fbh = _fbh;
//			m_rtMsaa = _msaa;
		}

		void setBlendState(VkPipelineColorBlendStateCreateInfo& _desc, uint64_t _state, uint32_t _rgba = 0)
		{
			VkPipelineColorBlendAttachmentState* bas = const_cast<VkPipelineColorBlendAttachmentState*>(_desc.pAttachments);

			uint8_t writeMask = (_state & BGFX_STATE_ALPHA_WRITE)
					? VK_COLOR_COMPONENT_A_BIT
					: 0
					;
			writeMask |= (_state & BGFX_STATE_RGB_WRITE)
					? VK_COLOR_COMPONENT_R_BIT
					| VK_COLOR_COMPONENT_G_BIT
					| VK_COLOR_COMPONENT_B_BIT
					: 0
					;

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

			if (!!(BGFX_STATE_BLEND_INDEPENDENT & _state) )
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
			_desc.frontFace = VK_FRONT_FACE_CLOCKWISE;
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
			_desc.depthWriteEnable = !!(BGFX_STATE_DEPTH_WRITE & _state);
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

		uint32_t setInputLayout(VkPipelineVertexInputStateCreateInfo& _vertexInputState, const VertexDecl& _vertexDecl, const ProgramVK& _program, uint8_t _numInstanceData)
		{
			_vertexInputState.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
			_vertexInputState.pNext = NULL;
			_vertexInputState.flags = 0;

			VertexDecl decl;
			bx::memCopy(&decl, &_vertexDecl, sizeof(VertexDecl) );
			const uint16_t* attrMask = _program.m_vsh->m_attrMask;

			for (uint32_t ii = 0; ii < Attrib::Count; ++ii)
			{
				uint16_t mask = attrMask[ii];
				uint16_t attr = (decl.m_attributes[ii] & mask);
				decl.m_attributes[ii] = attr == 0 ? UINT16_MAX : attr == UINT16_MAX ? 0 : attr;
			}

			uint32_t num = fillVertexDecl(_vertexInputState, decl);

//			const D3D12_INPUT_ELEMENT_DESC inst = { "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 };

			// VK_VERTEX_INPUT_RATE_INSTANCE

			for (uint32_t ii = 0; ii < _numInstanceData; ++ii)
			{
				uint32_t index = 7 - ii; // TEXCOORD7 = i_data0, TEXCOORD6 = i_data1, etc.

				BX_UNUSED(index);
//				bx::memCopy(curr, &inst, sizeof(D3D12_INPUT_ELEMENT_DESC) );
//				curr->InputSlot = 1;
//				curr->SemanticIndex = index;
//				curr->AlignedByteOffset = ii*16;
			}

			_vertexInputState.vertexAttributeDescriptionCount = num;
			return num;
		}

		VkPipeline getPipeline(uint16_t _programIdx)
		{
			BX_UNUSED(_programIdx);
			// vkCreateComputePipelines
			return VK_NULL_HANDLE;
		}

		VkPipeline getPipeline(uint64_t _state, uint64_t _stencil, uint16_t _declIdx, uint16_t _programIdx, uint8_t _numInstanceData)
		{
			ProgramVK& program = m_program[_programIdx];

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
			setInputLayout(vertexInputState, m_vertexDecls[_declIdx], program, _numInstanceData);

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
			shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			shaderStages[1].pNext = NULL;
			shaderStages[1].flags = 0;
			shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
			shaderStages[1].module = program.m_fsh->m_module;
			shaderStages[1].pName  = "main";
			shaderStages[1].pSpecializationInfo = NULL;

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
			multisampleState.rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
			multisampleState.sampleShadingEnable   = VK_FALSE;
			multisampleState.minSampleShading      = !!(BGFX_STATE_CONSERVATIVE_RASTER & _state) ? 1.0f : 0.0f;
			multisampleState.pSampleMask           = NULL;
			multisampleState.alphaToCoverageEnable = !!(BGFX_STATE_BLEND_ALPHA_TO_COVERAGE & _state);
			multisampleState.alphaToOneEnable      = VK_FALSE;

			VkGraphicsPipelineCreateInfo graphicsPipeline;
			graphicsPipeline.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
			graphicsPipeline.pNext = NULL;
			graphicsPipeline.flags = 0;
			graphicsPipeline.stageCount = BX_COUNTOF(shaderStages);
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
			graphicsPipeline.layout     = m_pipelineLayout;
			graphicsPipeline.renderPass = m_renderPass;
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
//			FrameBufferHandle fbh = m_fbh;
//			if (isValid(fbh) )
//			{
//				const FrameBufferVK& fb = m_frameBuffers[fbh.idx];
//				numMrt = bx::uint32_max(1, fb.m_num);
//			}

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
						uint8_t index = (uint8_t)bx::uint32_min(BGFX_CONFIG_MAX_COLOR_PALETTE-1, _clear.m_index[ii]);
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

 			vkCmdClearAttachments(m_commandBuffer
				, mrt
				, attachments
				, BX_COUNTOF(rect)
				, rect
				);
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

		uint32_t selectMemoryType(uint32_t memoryTypeBits, uint32_t propertyFlags)
		{
			for (uint32_t ii = 0; ii < m_memoryProperties.memoryTypeCount; ++ii)
			{
				if ( ( ((1<<ii) & memoryTypeBits) != 0)
				&& ( (m_memoryProperties.memoryTypes[ii].propertyFlags & propertyFlags) == propertyFlags) )
				{
					return ii;
				}
			}

			BX_TRACE("failed to find memory that supports flags 0x%08x", propertyFlags);
			return 0;
		}

		VkAllocationCallbacks* m_allocatorCb;
		VkDebugReportCallbackEXT m_debugReportCallback;
		VkInstance       m_instance;
		VkPhysicalDevice m_physicalDevice;

		VkPhysicalDeviceProperties m_deviceProperties;
		VkPhysicalDeviceMemoryProperties m_memoryProperties;

		VkSwapchainCreateInfoKHR m_sci;
		VkSurfaceKHR     m_surface;
		VkSwapchainKHR   m_swapchain;
		VkImage          m_backBufferColorImage[4];
		VkImageView      m_backBufferColorImageView[4];
		VkFramebuffer    m_backBufferColor[4];
		VkCommandBuffer  m_commandBuffers[4];
		VkCommandBuffer  m_commandBuffer;

		VkFormat         m_backBufferDepthStencilFormat;
		VkDeviceMemory   m_backBufferDepthStencilMemory;
		VkImage          m_backBufferDepthStencilImage;
		VkImageView      m_backBufferDepthStencilImageView;

		ScratchBufferVK  m_scratchBuffer[4];
		VkSemaphore      m_presentDone[4];

		uint32_t m_qfiGraphics;
		uint32_t m_qfiCompute;

		VkDevice m_device;
		VkQueue  m_queueGraphics;
		VkQueue  m_queueCompute;
		VkFence  m_fence;
		VkRenderPass m_renderPass;
		VkDescriptorPool m_descriptorPool;
		VkDescriptorSetLayout m_descriptorSetLayout;
		VkPipelineLayout m_pipelineLayout;
		VkPipelineCache m_pipelineCache;
		VkCommandPool m_commandPool;

		void* m_renderdocdll;
		void* m_vulkan1dll;

		IndexBufferVK m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBufferVK m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		ShaderVK m_shaders[BGFX_CONFIG_MAX_SHADERS];
		ProgramVK m_program[BGFX_CONFIG_MAX_PROGRAMS];
		TextureVK m_textures[BGFX_CONFIG_MAX_TEXTURES];
		VertexDecl m_vertexDecls[BGFX_CONFIG_MAX_VERTEX_DECLS];
		FrameBufferVK m_frameBuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		void* m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];
		Matrix4 m_predefinedUniforms[PredefinedUniform::Count];
		UniformRegistry m_uniformReg;

		StateCacheT<VkPipeline> m_pipelineStateCache;

		Resolution m_resolution;
		uint32_t m_maxAnisotropy;
		bool m_depthClamp;
		bool m_wireframe;

		TextVideoMem m_textVideoMem;

		uint8_t m_fsScratch[64<<10];
		uint8_t m_vsScratch[64<<10];
		uint32_t m_fsChanges;
		uint32_t m_vsChanges;

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

#define VK_DESTROY_FUNC(_name) \
			void vkDestroy(Vk##_name& _obj) \
			{ \
				if (VK_NULL_HANDLE != _obj) \
				{ \
					vkDestroy##_name(s_renderVK->m_device, _obj, s_renderVK->m_allocatorCb); \
					_obj = VK_NULL_HANDLE; \
				} \
			}
VK_DESTROY
#undef VK_DESTROY_FUNC

	void ScratchBufferVK::create(uint32_t _size, uint32_t _maxDescriptors)
	{
		m_maxDescriptors = _maxDescriptors;
		m_descriptorSet  = (VkDescriptorSet*)BX_ALLOC(g_allocator, _maxDescriptors * sizeof(VkDescriptorSet) );

		VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;
		VkDevice device = s_renderVK->m_device;

		VkDescriptorSetAllocateInfo dsai;
		dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		dsai.pNext = NULL;
		dsai.descriptorPool = s_renderVK->m_descriptorPool;
		dsai.descriptorSetCount = 1;
		dsai.pSetLayouts        = &s_renderVK->m_descriptorSetLayout;
		for (uint32_t ii = 0, num = m_maxDescriptors; ii < num; ++ii)
		{
			VK_CHECK(vkAllocateDescriptorSets(device, &dsai, &m_descriptorSet[ii]) );
		}

		VkBufferCreateInfo bci;
		bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bci.pNext = NULL;
		bci.flags = 0;
		bci.size  = _size;
		bci.usage = 0
			| VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT
//			| VK_BUFFER_USAGE_TRANSFER_DST_BIT
			;
		bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		bci.queueFamilyIndexCount = 0;
		bci.pQueueFamilyIndices   = NULL;

		VK_CHECK(vkCreateBuffer(device
			, &bci
			, allocatorCb
			, &m_buffer
			) );

		VkMemoryRequirements mr;
		vkGetBufferMemoryRequirements(device
			, m_buffer
			, &mr
			);

		VkMemoryAllocateInfo ma;
		ma.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		ma.pNext = NULL;
		ma.allocationSize  = mr.size;
		ma.memoryTypeIndex = s_renderVK->selectMemoryType(mr.memoryTypeBits
			, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
			);
		VK_CHECK(vkAllocateMemory(device
			, &ma
			, allocatorCb
			, &m_deviceMem
			) );

		m_size = (uint32_t)mr.size;
		m_pos  = 0;

		VK_CHECK(vkBindBufferMemory(device, m_buffer, m_deviceMem, 0) );

		VK_CHECK(vkMapMemory(device, m_deviceMem, 0, ma.allocationSize, 0, (void**)&m_data) );
	}

	void ScratchBufferVK::destroy()
	{
		VkAllocationCallbacks* allocatorCb = s_renderVK->m_allocatorCb;
		VkDevice device = s_renderVK->m_device;

		vkFreeDescriptorSets(device, s_renderVK->m_descriptorPool, m_maxDescriptors, m_descriptorSet);
		BX_FREE(g_allocator, m_descriptorSet);

		vkUnmapMemory(device, m_deviceMem);

		vkDestroy(m_buffer);

		vkFreeMemory(device
			, m_deviceMem
			, allocatorCb
			);
	}

	void ScratchBufferVK::reset(VkDescriptorBufferInfo& /*_descriptorBufferInfo*/)
	{
		m_pos = 0;
		m_currentDs = 0;
	}

	void* ScratchBufferVK::allocUbv(VkDescriptorBufferInfo& _descriptorBufferInfo, uint32_t _size)
	{
		uint32_t total = bx::strideAlign(_size
			, uint32_t(s_renderVK->m_deviceProperties.limits.minUniformBufferOffsetAlignment)
			);
		_descriptorBufferInfo.buffer = m_buffer;
		_descriptorBufferInfo.offset = m_pos;
		_descriptorBufferInfo.range  = total;

		VkWriteDescriptorSet wds[1];
		wds[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		wds[0].pNext = NULL;
		wds[0].dstSet     = m_descriptorSet[m_currentDs];
		wds[0].dstBinding = DslBinding::UniformBuffer;
		wds[0].dstArrayElement  = 0;
		wds[0].descriptorCount  = 1;
		wds[0].descriptorType   = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		wds[0].pImageInfo       = NULL;
		wds[0].pBufferInfo      = &_descriptorBufferInfo;
		wds[0].pTexelBufferView = NULL;
		vkUpdateDescriptorSets(s_renderVK->m_device, BX_COUNTOF(wds), wds, 0, NULL);

		void* data = &m_data[m_pos];
		m_pos += total;
		++m_currentDs;

		return data;
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

		VkMemoryAllocateInfo ma;
		ma.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		ma.pNext = NULL;
		ma.allocationSize  = mr.size;
		ma.memoryTypeIndex = s_renderVK->selectMemoryType(mr.memoryTypeBits
			, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
			);
		result = vkAllocateMemory(device
			, &ma
			, allocatorCb
			, &m_memory
			);

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

		VkBufferCreateInfo bci;
		bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bci.pNext = NULL;
		bci.flags = 0;
		bci.size  = _size;
		bci.usage = 0
			| (_vertex ? VK_BUFFER_USAGE_VERTEX_BUFFER_BIT : VK_BUFFER_USAGE_INDEX_BUFFER_BIT)
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
		vkGetBufferMemoryRequirements(device
			, m_buffer
			, &mr
			);

		VkMemoryAllocateInfo ma;
		ma.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		ma.pNext = NULL;
		ma.allocationSize  = mr.size;
		ma.memoryTypeIndex = s_renderVK->selectMemoryType(mr.memoryTypeBits
			, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
			);
		VK_CHECK(vkAllocateMemory(device
			, &ma
			, allocatorCb
			, &m_deviceMem
			) );

		if (!m_dynamic)
		{
			void* dst;
			VK_CHECK(vkMapMemory(device, m_deviceMem, 0, ma.allocationSize, 0, &dst) );
			bx::memCopy(dst, _data, _size);
			vkUnmapMemory(device, m_deviceMem);
		}

		VK_CHECK(vkBindBufferMemory(device, m_buffer, m_deviceMem, 0) );
	}

	void BufferVK::update(VkCommandBuffer _commandBuffer, uint32_t _offset, uint32_t _size, void* _data, bool _discard)
	{
		BX_UNUSED(_commandBuffer, _offset, _size, _data, _discard);
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

	void VertexBufferVK::create(uint32_t _size, void* _data, VertexDeclHandle _declHandle, uint16_t _flags)
	{
		BufferVK::create(_size, _data, _flags, true);
		m_decl = _declHandle;
	}

	void ShaderVK::create(const Memory* _mem)
	{
		bx::MemoryReader reader(_mem->data, _mem->size);

		uint32_t magic;
		bx::read(&reader, magic);

		VkShaderStageFlagBits shaderStage;
		BX_UNUSED(shaderStage);
		switch (magic)
		{
		case BGFX_CHUNK_MAGIC_CSH: shaderStage = VK_SHADER_STAGE_COMPUTE_BIT;  break;
		case BGFX_CHUNK_MAGIC_FSH: shaderStage = VK_SHADER_STAGE_FRAGMENT_BIT; break;
		case BGFX_CHUNK_MAGIC_VSH: shaderStage = VK_SHADER_STAGE_VERTEX_BIT;   break;

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
					const UniformRegInfo* info = s_renderVK->m_uniformReg.find(name);
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

		uint32_t shaderSize;
		bx::read(&reader, shaderSize);

#if 1
		const void* code = reader.getDataPtr();
		bx::skip(&reader, shaderSize+1);

		m_code = alloc( ( ( (shaderSize+3)/4)*4) );
		bx::memSet(m_code->data, 0, m_code->size);
		bx::memCopy(m_code->data
			, code
			, shaderSize
			);
#else
#include "../examples/runtime/shaders/spv/vert.spv.h"
#include "../examples/runtime/shaders/spv/frag.spv.h"

		shaderSize = BGFX_CHUNK_MAGIC_VSH == magic
			? sizeof(vs_cubes_spv)
			: sizeof(fs_cubes_spv)
			;
		m_code = alloc(shaderSize);
		bx::memCopy(m_code->data
			, BGFX_CHUNK_MAGIC_VSH == magic
				? vs_cubes_spv
				: fs_cubes_spv
			, shaderSize
			);
#endif // 0

		VkShaderModuleCreateInfo smci;
		smci.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		smci.pNext = NULL;
		smci.flags = 0;
		smci.codeSize = m_code->size;
		smci.pCode    = (const uint32_t*)m_code->data;
		VK_CHECK(vkCreateShaderModule(
			  s_renderVK->m_device
			, &smci
			, s_renderVK->m_allocatorCb
			, &m_module
			) );

		bx::memSet(m_attrMask, 0, sizeof(m_attrMask) );
		m_attrMask[Attrib::Position] = UINT16_MAX;
		m_attrMask[Attrib::Color0]   = UINT16_MAX;
		iohash = 0;

		if (BGFX_CHUNK_MAGIC_VSH == magic)
		{
			m_predefined[0].m_loc   = 0;
			m_predefined[0].m_count = 4;
			m_predefined[0].m_type  = uint8_t(PredefinedUniform::ModelViewProj);
			m_numPredefined = 1;
			m_size = 64;
		}
		else
		{
			m_size = 0;
			m_numPredefined = 0;
		}

		uint8_t numAttrs = 0;
//		bx::read(&reader, numAttrs);
//
//		for (uint32_t ii = 0; ii < numAttrs; ++ii)
//		{
//			uint16_t id;
//			bx::read(&reader, id);
//
//			Attrib::Enum attr = idToAttrib(id);
//
//			if (Attrib::Count != attr)
//			{
//				m_attrMask[attr] = UINT16_MAX;
//			}
//		}

		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(iohash);
		murmur.add(m_code->data, m_code->size);
		murmur.add(numAttrs);
		murmur.add(m_attrMask, numAttrs);
		m_hash = murmur.end();
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

	void TextureVK::destroy()
	{
	}

	void FrameBufferVK::destroy()
	{
	}

	void RendererContextVK::submitBlit(BlitState& _bs, uint16_t _view)
	{
		while (_bs.hasItem(_view) )
		{
			const BlitItem& blit = _bs.advance();
			BX_UNUSED(blit);
		}
	}

	void RendererContextVK::submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter)
	{
		BX_UNUSED(_render, _clearQuad, _textVideoMemBlitter);

		updateResolution(_render->m_resolution);

		int64_t timeBegin = bx::getHPCounter();
		int64_t captureElapsed = 0;

//		m_gpuTimer.begin(m_commandList);

		if (0 < _render->m_iboffset)
		{
//			TransientIndexBuffer* ib = _render->m_transientIb;
//			m_indexBuffers[ib->handle.idx].update(m_commandList, 0, _render->m_iboffset, ib->data);
		}

		if (0 < _render->m_vboffset)
		{
//			TransientVertexBuffer* vb = _render->m_transientVb;
//			m_vertexBuffers[vb->handle.idx].update(m_commandList, 0, _render->m_vboffset, vb->data);
		}

		_render->sort();

		RenderDraw currentState;
		currentState.clear();
		currentState.m_stateFlags = BGFX_STATE_NONE;
		currentState.m_stencil    = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);

		_render->m_hmdInitialized = false;

		const bool hmdEnabled = false;
		ViewState viewState(_render, hmdEnabled);
		viewState.reset(_render, hmdEnabled);

// 		bool wireframe = !!(_render->m_debug&BGFX_DEBUG_WIREFRAME);
// 		setDebugWireframe(wireframe);

		uint16_t currentSamplerStateIdx = kInvalidHandle;
		uint16_t currentProgramIdx      = kInvalidHandle;
		uint32_t currentBindHash        = 0;
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

		VkSemaphore renderWait = m_presentDone[m_backBufferColorIdx];
		VK_CHECK(vkAcquireNextImageKHR(m_device
				, m_swapchain
				, UINT64_MAX
				, renderWait
				, VK_NULL_HANDLE
				, &m_backBufferColorIdx
				) );

		const uint64_t f0 = BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_FACTOR, BGFX_STATE_BLEND_FACTOR);
		const uint64_t f1 = BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_INV_FACTOR, BGFX_STATE_BLEND_INV_FACTOR);


		ScratchBufferVK& scratchBuffer = m_scratchBuffer[m_backBufferColorIdx];
		VkDescriptorBufferInfo descriptorBufferInfo;
		scratchBuffer.reset(descriptorBufferInfo);

		VkCommandBufferBeginInfo cbbi;
		cbbi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		cbbi.pNext = NULL;
		cbbi.flags = 0
			| VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
//			| VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT
			;
		cbbi.pInheritanceInfo = NULL;

		m_commandBuffer = m_commandBuffers[m_backBufferColorIdx];
		VK_CHECK(vkBeginCommandBuffer(m_commandBuffer, &cbbi) );

		setImageMemoryBarrier(m_commandBuffer
			, m_backBufferColorImage[m_backBufferColorIdx]
			, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
			, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
			);

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

		if (0 == (_render->m_debug&BGFX_DEBUG_IFH) )
		{
//			m_batch.begin();

// 			uint8_t eye = 0;
// 			uint8_t restartState = 0;
			viewState.m_rect = _render->m_view[0].m_rect;

			int32_t numItems = _render->m_numRenderItems;
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
					if (beginRenderPass)
					{
						vkCmdEndRenderPass(m_commandBuffer);
						beginRenderPass = false;
					}

					VK_CHECK(vkEndCommandBuffer(m_commandBuffer) );

//					m_batch.flush(m_commandList, true);
					kick(renderWait);
					renderWait = VK_NULL_HANDLE;
finishAll();

					view = key.m_view;
					currentPipeline = VK_NULL_HANDLE;
					currentSamplerStateIdx = kInvalidHandle;
BX_UNUSED(currentSamplerStateIdx);
					currentProgramIdx      = kInvalidHandle;
					hasPredefined          = false;

					fbh = _render->m_view[view].m_fbh;
					setFrameBuffer(fbh);

					viewState.m_rect = _render->m_view[view].m_rect;
					const Rect& rect        = _render->m_view[view].m_rect;
					const Rect& scissorRect = _render->m_view[view].m_scissor;
					viewHasScissor  = !scissorRect.isZero();
					viewScissorRect = viewHasScissor ? scissorRect : rect;

					rpbi.renderArea.offset.x = rect.m_x;
					rpbi.renderArea.offset.y = rect.m_y;
					rpbi.renderArea.extent.width  = rect.m_width;
					rpbi.renderArea.extent.height = rect.m_height;
					VK_CHECK(vkBeginCommandBuffer(m_commandBuffer, &cbbi) );
					vkCmdBeginRenderPass(m_commandBuffer, &rpbi, VK_SUBPASS_CONTENTS_INLINE);
					beginRenderPass = true;

					VkViewport vp;
					vp.x        = rect.m_x;
					vp.y        = rect.m_y;
					vp.width    = rect.m_width;
					vp.height   = rect.m_height;
					vp.minDepth = 0.0f;
					vp.maxDepth = 1.0f;
					vkCmdSetViewport(m_commandBuffer, 0, 1, &vp);

					VkRect2D rc;
					rc.offset.x      = viewScissorRect.m_x;
					rc.offset.y      = viewScissorRect.m_y;
					rc.extent.width  = viewScissorRect.m_x + viewScissorRect.m_width;
					rc.extent.height = viewScissorRect.m_y + viewScissorRect.m_height;
					vkCmdSetScissor(m_commandBuffer, 0, 1, &rc);

					restoreScissor = false;

					Clear& clr = _render->m_view[view].m_clear;
					if (BGFX_CLEAR_NONE != clr.m_flags)
					{
						Rect clearRect = rect;
						clearRect.setIntersect(rect, viewScissorRect);
						clearQuad(clearRect, clr, _render->m_colorPalette);
					}

					prim = s_primInfo[BX_COUNTOF(s_primName)]; // Force primitive type update.

					submitBlit(bs, view);
				}

				if (isCompute)
				{
					if (!wasCompute)
					{
						wasCompute = true;

//						m_commandList->SetComputeRootSignature(m_rootSignature);
//						ID3D12DescriptorHeap* heaps[] = {
//							m_samplerAllocator.getHeap(),
//							scratchBuffer.getHeap(),
//						};
//						m_commandList->SetDescriptorHeaps(BX_COUNTOF(heaps), heaps);
					}

					const RenderCompute& compute = renderItem.compute;

					VkPipeline pipeline = getPipeline(key.m_program);
					if (pipeline != currentPipeline)
					{
						currentPipeline = pipeline;
						vkCmdBindPipeline(m_commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);
						currentBindHash = 0;
					}

//					uint32_t bindHash = bx::hash<bx::HashMurmur2A>(renderBind.m_bind, sizeof(renderBind.m_bind) );
//					if (currentBindHash != bindHash)
//					{
//						currentBindHash  = bindHash;
//
//						Bind* bindCached = bindLru.find(bindHash);
//						if (NULL == bindCached)
//						{
//							D3D12_GPU_DESCRIPTOR_HANDLE srvHandle[BGFX_MAX_COMPUTE_BINDINGS] = {};
//							uint32_t samplerFlags[BGFX_MAX_COMPUTE_BINDINGS] = {};
//
//							for (uint32_t ii = 0; ii < BGFX_MAX_COMPUTE_BINDINGS; ++ii)
//							{
//								const Binding& bind = renderBind.m_bind[ii];
//								if (kInvalidHandle != bind.m_idx)
//								{
//									switch (bind.m_type)
//									{
//									case Binding::Image:
//										{
//											TextureD3D12& texture = m_textures[bind.m_idx];
//
//											if (Access::Read != bind.m_un.m_compute.m_access)
//											{
//												texture.setState(m_commandList, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
//												scratchBuffer.allocUav(srvHandle[ii], texture, bind.m_un.m_compute.m_mip);
//											}
//											else
//											{
//												texture.setState(m_commandList, D3D12_RESOURCE_STATE_GENERIC_READ);
//												scratchBuffer.allocSrv(srvHandle[ii], texture, bind.m_un.m_compute.m_mip);
//												samplerFlags[ii] = texture.m_flags;
//											}
//										}
//										break;
//
//									case Binding::IndexBuffer:
//									case Binding::VertexBuffer:
//										{
//											BufferD3D12& buffer = Binding::IndexBuffer == bind.m_type
//												? m_indexBuffers[bind.m_idx]
//												: m_vertexBuffers[bind.m_idx]
//												;
//
//											if (Access::Read != bind.m_un.m_compute.m_access)
//											{
//												buffer.setState(m_commandList, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
//												scratchBuffer.allocUav(srvHandle[ii], buffer);
//											}
//											else
//											{
//												buffer.setState(m_commandList, D3D12_RESOURCE_STATE_GENERIC_READ);
//												scratchBuffer.allocSrv(srvHandle[ii], buffer);
//											}
//										}
//										break;
//									}
//								}
//							}
//
//							uint16_t samplerStateIdx = getSamplerState(samplerFlags, BGFX_MAX_COMPUTE_BINDINGS, _render->m_colorPalette);
//							if (samplerStateIdx != currentSamplerStateIdx)
//							{
//								currentSamplerStateIdx = samplerStateIdx;
//								m_commandList->SetComputeRootDescriptorTable(Rdt::Sampler, m_samplerAllocator.get(samplerStateIdx) );
//							}
//
//							m_commandList->SetComputeRootDescriptorTable(Rdt::SRV, srvHandle[0]);
//							m_commandList->SetComputeRootDescriptorTable(Rdt::UAV, srvHandle[0]);
//
//							Bind bind;
//							bind.m_srvHandle = srvHandle[0];
//							bind.m_samplerStateIdx = samplerStateIdx;
//							bindLru.add(bindHash, bind, 0);
//						}
//						else
//						{
//							uint16_t samplerStateIdx = bindCached->m_samplerStateIdx;
//							if (samplerStateIdx != currentSamplerStateIdx)
//							{
//								currentSamplerStateIdx = samplerStateIdx;
//								m_commandList->SetComputeRootDescriptorTable(Rdt::Sampler, m_samplerAllocator.get(samplerStateIdx) );
//							}
//							m_commandList->SetComputeRootDescriptorTable(Rdt::SRV, bindCached->m_srvHandle);
//							m_commandList->SetComputeRootDescriptorTable(Rdt::UAV, bindCached->m_srvHandle);
//						}
//					}

					bool constantsChanged = false;
					if (compute.m_uniformBegin < compute.m_uniformEnd
					||  currentProgramIdx != key.m_program)
					{
						rendererUpdateUniforms(this, _render->m_uniformBuffer[compute.m_uniformIdx], compute.m_uniformBegin, compute.m_uniformEnd);

						currentProgramIdx = key.m_program;
						ProgramVK& program = m_program[currentProgramIdx];

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
						ProgramVK& program = m_program[currentProgramIdx];
						viewState.setPredefined<4>(this, view, 0, program, _render, compute);
//						commitShaderConstants(key.m_program, gpuAddress);
//						m_commandList->SetComputeRootConstantBufferView(Rdt::CBV, gpuAddress);
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
//							m_commandList->ExecuteIndirect(ptr, args);
							args += BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
						}
					}
					else
					{
//						m_commandList->Dispatch(compute.m_numX, compute.m_numY, compute.m_numZ);
					}

					continue;
				}

				const RenderDraw& draw = renderItem.draw;

				const bool hasOcclusionQuery = false; //0 != (draw.m_stateFlags & BGFX_STATE_INTERNAL_OCCLUSION_QUERY);
//				if (isValid(draw.m_occlusionQuery)
//				&&  !hasOcclusionQuery
//				&&  !isVisible(_render, draw.m_occlusionQuery, 0 != (draw.m_submitFlags&BGFX_SUBMIT_INTERNAL_OCCLUSION_VISIBLE) ) )
//				{
//					continue;
//				}

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
						BX_UNUSED(s_viewName);
// 						wchar_t* viewNameW = s_viewNameW[view];
// 						viewNameW[3] = L' ';
// 						PIX_ENDEVENT();
// 						PIX_BEGINEVENT(D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0xff), viewNameW);
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
					currentSamplerStateIdx = kInvalidHandle;
					currentProgramIdx      = kInvalidHandle;
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

				if (isValid(draw.m_stream[0].m_handle) )
				{
					const uint64_t state = draw.m_stateFlags;
					bool hasFactor = 0
						|| f0 == (state & f0)
						|| f1 == (state & f1)
						;

					const VertexBufferVK& vb = m_vertexBuffers[draw.m_stream[0].m_handle.idx];
					uint16_t declIdx = !isValid(vb.m_decl) ? draw.m_stream[0].m_decl.idx : vb.m_decl.idx;

					VkPipeline pipeline =
						getPipeline(state
							, draw.m_stencil
							, declIdx
							, key.m_program
							, uint8_t(draw.m_instanceDataStride/16)
							);

					uint16_t scissor = draw.m_scissor;
					uint32_t bindHash = bx::hash<bx::HashMurmur2A>(renderBind.m_bind, sizeof(renderBind.m_bind) );
					if (currentBindHash != bindHash
					||  0 != changedStencil
					|| (hasFactor && blendFactor != draw.m_rgba)
					|| (0 != (BGFX_STATE_PT_MASK & changedFlags)
					||  prim.m_topology != s_primInfo[primIndex].m_topology)
					||  currentState.m_scissor != scissor
					||  pipeline != currentPipeline
					||  hasOcclusionQuery)
					{
//						m_batch.flush(m_commandList);
					}

//					if (currentBindHash != bindHash)
//					{
//						currentBindHash  = bindHash;
//
//						Bind* bindCached = bindLru.find(bindHash);
//						if (NULL == bindCached)
//						{
//							D3D12_GPU_DESCRIPTOR_HANDLE srvHandle[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
//							uint32_t samplerFlags[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
//							{
//								srvHandle[0].ptr = 0;
//								for (uint32_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
//								{
//									const Binding& bind = renderBind.m_bind[stage];
//									if (kInvalidHandle != bind.m_idx)
//									{
//										TextureD3D12& texture = m_textures[bind.m_idx];
//										texture.setState(m_commandList, D3D12_RESOURCE_STATE_GENERIC_READ);
//										scratchBuffer.allocSrv(srvHandle[stage], texture);
//										samplerFlags[stage] = (0 == (BGFX_TEXTURE_INTERNAL_DEFAULT_SAMPLER & bind.m_un.m_draw.m_textureFlags)
//											? bind.m_un.m_draw.m_textureFlags
//											: texture.m_flags
//											) & (BGFX_TEXTURE_SAMPLER_BITS_MASK|BGFX_TEXTURE_BORDER_COLOR_MASK)
//											;
//									}
//									else
//									{
//										bx::memCopy(&srvHandle[stage], &srvHandle[0], sizeof(D3D12_GPU_DESCRIPTOR_HANDLE) );
//										samplerFlags[stage] = 0;
//									}
//								}
//							}
//
//							if (srvHandle[0].ptr != 0)
//							{
//								uint16_t samplerStateIdx = getSamplerState(samplerFlags, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, _render->m_colorPalette);
//								if (samplerStateIdx != currentSamplerStateIdx)
//								{
//									currentSamplerStateIdx = samplerStateIdx;
//									m_commandList->SetGraphicsRootDescriptorTable(Rdt::Sampler, m_samplerAllocator.get(samplerStateIdx) );
//								}
//
//								m_commandList->SetGraphicsRootDescriptorTable(Rdt::SRV, srvHandle[0]);
//
//								Bind bind;
//								bind.m_srvHandle = srvHandle[0];
//								bind.m_samplerStateIdx = samplerStateIdx;
//								bindLru.add(bindHash, bind, 0);
//							}
//						}
//						else
//						{
//							uint16_t samplerStateIdx = bindCached->m_samplerStateIdx;
//							if (samplerStateIdx != currentSamplerStateIdx)
//							{
//								currentSamplerStateIdx = samplerStateIdx;
//								m_commandList->SetGraphicsRootDescriptorTable(Rdt::Sampler, m_samplerAllocator.get(samplerStateIdx) );
//							}
//							m_commandList->SetGraphicsRootDescriptorTable(Rdt::SRV, bindCached->m_srvHandle);
//						}
//					}

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
								rc.extent.width  = viewScissorRect.m_x + viewScissorRect.m_width;
								rc.extent.height = viewScissorRect.m_y + viewScissorRect.m_height;
								vkCmdSetScissor(m_commandBuffer, 0, 1, &rc);
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

							VkRect2D rc;
							rc.offset.x      = scissorRect.m_x;
							rc.offset.y      = scissorRect.m_y;
							rc.extent.width  = scissorRect.m_x + scissorRect.m_width;
							rc.extent.height = scissorRect.m_y + scissorRect.m_height;
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
					||  currentProgramIdx != key.m_program
					||  BGFX_STATE_ALPHA_REF_MASK & changedFlags)
					{
						currentProgramIdx = key.m_program;
						ProgramVK& program = m_program[currentProgramIdx];

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
						ProgramVK& program = m_program[currentProgramIdx];
						uint32_t ref = (newFlags&BGFX_STATE_ALPHA_REF_MASK)>>BGFX_STATE_ALPHA_REF_SHIFT;
						viewState.m_alphaRef = ref/255.0f;
						viewState.setPredefined<4>(this, view, 0, program, _render, draw);
						commitShaderUniforms(m_commandBuffer, key.m_program); //, gpuAddress);
					}


//					vb.setState(_commandList, D3D12_RESOURCE_STATE_GENERIC_READ);

					const VertexDecl& vertexDecl = m_vertexDecls[declIdx];
					uint32_t numIndices = 0;

					VkDeviceSize offset = 0;
					vkCmdBindVertexBuffers(m_commandBuffer
						, 0
						, 1
						, &vb.m_buffer
						, &offset
						);

					if (!isValid(draw.m_indexBuffer) )
					{
						const uint32_t numVertices = UINT32_MAX == draw.m_numVertices
							? vb.m_size / vertexDecl.m_stride
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
//						ib.setState(_commandList, D3D12_RESOURCE_STATE_GENERIC_READ);

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
//						m_batch.flush(m_commandList);
//						m_occlusionQuery.end(m_commandList);
					}
				}
			}

			submitBlit(bs, BGFX_CONFIG_MAX_VIEWS);

//			m_batch.end(m_commandList);
		}

		int64_t timeEnd = bx::getHPCounter();
		int64_t frameTime = timeEnd - timeBegin;

		static int64_t min = frameTime;
		static int64_t max = frameTime;
		min = bx::int64_min(min, frameTime);
		max = bx::int64_max(max, frameTime);

		static uint32_t maxGpuLatency = 0;
		static double   maxGpuElapsed = 0.0f;
		double elapsedGpuMs = 0.0;
BX_UNUSED(maxGpuLatency, maxGpuElapsed, elapsedGpuMs);

		static int64_t presentMin = 0; //m_presentElapsed;
		static int64_t presentMax = 0; //m_presentElapsed;
BX_UNUSED(presentMin, presentMax);
//		presentMin = bx::int64_min(presentMin, m_presentElapsed);
//		presentMax = bx::int64_max(presentMax, m_presentElapsed);

//		m_gpuTimer.end(m_commandList);

//		while (m_gpuTimer.get() )
//		{
//			double toGpuMs = 1000.0 / double(m_gpuTimer.m_frequency);
//			elapsedGpuMs   = m_gpuTimer.m_elapsed * toGpuMs;
//			maxGpuElapsed  = elapsedGpuMs > maxGpuElapsed ? elapsedGpuMs : maxGpuElapsed;
//		}
//		maxGpuLatency = bx::uint32_imax(maxGpuLatency, m_gpuTimer.m_control.available()-1);

		const int64_t timerFreq = bx::getHPFrequency();

		Stats& perfStats = _render->m_perfStats;
		perfStats.cpuTimeBegin  = timeBegin;
		perfStats.cpuTimeEnd    = timeEnd;
		perfStats.cpuTimerFreq  = timerFreq;
//		perfStats.gpuTimeBegin  = m_gpuTimer.m_begin;
//		perfStats.gpuTimeEnd    = m_gpuTimer.m_end;
//		perfStats.gpuTimerFreq  = m_gpuTimer.m_frequency;
//		perfStats.numDraw       = statsKeyType[0];
//		perfStats.numCompute    = statsKeyType[1];
//		perfStats.maxGpuLatency = maxGpuLatency;
		perfStats.gpuMemoryMax  = -INT64_MAX;
		perfStats.gpuMemoryUsed = -INT64_MAX;

		if (_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
//			PIX_BEGINEVENT(D3DCOLOR_RGBA(0x40, 0x40, 0x40, 0xff), L"debugstats");

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
				tvm.printf(0, pos++, BGFX_CONFIG_DEBUG ? 0x89 : 0x8f
					, " %s / " BX_COMPILER_NAME " / " BX_CPU_NAME " / " BX_ARCH_NAME " / " BX_PLATFORM_NAME " "
					, getRendererName()
					);

//				const DXGI_ADAPTER_DESC& desc = m_adapterDesc;
//				char description[BX_COUNTOF(desc.Description)];
//				wcstombs(description, desc.Description, BX_COUNTOF(desc.Description) );
//				tvm.printf(0, pos++, 0x8f, " Device: %s", description);
//
//				char dedicatedVideo[16];
//				bx::prettify(dedicatedVideo, BX_COUNTOF(dedicatedVideo), desc.DedicatedVideoMemory);
//
//				char dedicatedSystem[16];
//				bx::prettify(dedicatedSystem, BX_COUNTOF(dedicatedSystem), desc.DedicatedSystemMemory);
//
//				char sharedSystem[16];
//				bx::prettify(sharedSystem, BX_COUNTOF(sharedSystem), desc.SharedSystemMemory);
//
//				char processMemoryUsed[16];
//				bx::prettify(processMemoryUsed, BX_COUNTOF(processMemoryUsed), bx::getProcessMemoryUsed() );
//
//				tvm.printf(0, pos++, 0x8f, " Memory: %s (video), %s (system), %s (shared), %s (process) "
//					, dedicatedVideo
//					, dedicatedSystem
//					, sharedSystem
//					, processMemoryUsed
//					);

//				DXGI_QUERY_VIDEO_MEMORY_INFO memInfo;
//				DX_CHECK(m_adapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &memInfo) );
//
//				char budget[16];
//				bx::prettify(budget, BX_COUNTOF(budget), memInfo.Budget);
//
//				char currentUsage[16];
//				bx::prettify(currentUsage, BX_COUNTOF(currentUsage), memInfo.CurrentUsage);
//
//				char availableForReservation[16];
//				bx::prettify(availableForReservation, BX_COUNTOF(currentUsage), memInfo.AvailableForReservation);
//
//				char currentReservation[16];
//				bx::prettify(currentReservation, BX_COUNTOF(currentReservation), memInfo.CurrentReservation);
//
//				tvm.printf(0, pos++, 0x8f, " Budget: %s, Usage: %s, AvailRes: %s, CurrRes: %s "
//					, budget
//					, currentUsage
//					, availableForReservation
//					, currentReservation
//					);

				pos = 10;
				tvm.printf(10, pos++, 0x8e, "       Frame: % 7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] / % 6.2f FPS "
					, double(frameTime)*toMs
					, double(min)*toMs
					, double(max)*toMs
					, freq/frameTime
					);
//				tvm.printf(10, pos++, 0x8e, "     Present: % 7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] "
//					, double(m_presentElapsed)*toMs
//					, double(presentMin)*toMs
//					, double(presentMax)*toMs
//					);

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

				double elapsedCpuMs = double(frameTime)*toMs;
				tvm.printf(10, pos++, 0x8e, "   Submitted: %5d (draw %5d, compute %4d) / CPU %7.4f [ms] "
					, _render->m_numRenderItems
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

//				tvm.printf(10, pos++, 0x8e, "       Batch: %7dx%d indirect, %7d immediate "
//					, m_batch.m_stats.m_numIndirect[BatchD3D12::Draw]
//					, m_batch.m_maxDrawPerBatch
//					, m_batch.m_stats.m_numImmediate[BatchD3D12::Draw]
//					);

//				tvm.printf(10, pos++, 0x8e, "              %7dx%d indirect, %7d immediate "
//					, m_batch.m_stats.m_numIndirect[BatchD3D12::DrawIndexed]
//					, m_batch.m_maxDrawPerBatch
//					, m_batch.m_stats.m_numImmediate[BatchD3D12::DrawIndexed]
//					);

 				if (NULL != m_renderdocdll)
 				{
 					tvm.printf(tvm.m_width-27, 0, 0x1f, " [F11 - RenderDoc capture] ");
 				}

				tvm.printf(10, pos++, 0x8e, "      Indices: %7d ", statsNumIndices);
//				tvm.printf(10, pos++, 0x8e, " Uniform size: %7d, Max: %7d ", _render->m_uniformEnd, _render->m_uniformMax);
				tvm.printf(10, pos++, 0x8e, "     DVB size: %7d ", _render->m_vboffset);
				tvm.printf(10, pos++, 0x8e, "     DIB size: %7d ", _render->m_iboffset);

				pos++;
				tvm.printf(10, pos++, 0x8e, " State cache:                        ");
				tvm.printf(10, pos++, 0x8e, " PSO    | Sampler | Bind   | Queued  ");
				tvm.printf(10, pos++, 0x8e, " %6d " //|  %6d | %6d | %6d  "
					, m_pipelineStateCache.getCount()
//					, m_samplerStateCache.getCount()
//					, bindLru.getCount()
//					, m_cmd.m_control.available()
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
//				presentMin = m_presentElapsed;
//				presentMax = m_presentElapsed;
			}

			blit(this, _textVideoMemBlitter, tvm);

//			PIX_ENDEVENT();
		}
		else if (_render->m_debug & BGFX_DEBUG_TEXT)
		{
//			PIX_BEGINEVENT(D3DCOLOR_RGBA(0x40, 0x40, 0x40, 0xff), L"debugtext");

			blit(this, _textVideoMemBlitter, _render->m_textVideoMem);

//			PIX_ENDEVENT();
		}

		if (beginRenderPass)
		{
			vkCmdEndRenderPass(m_commandBuffer);
			beginRenderPass = false;
		}

		setImageMemoryBarrier(m_commandBuffer
			, m_backBufferColorImage[m_backBufferColorIdx]
			, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
			, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
			);

		VK_CHECK(vkEndCommandBuffer(m_commandBuffer) );

		kick(renderWait); //, m_presentDone[m_backBufferColorIdx]);
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

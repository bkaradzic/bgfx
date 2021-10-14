/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"
#include "renderer.h"

#ifdef __ORBIS__

#include "renderer_gnm.h"

#ifdef DEBUG_GAMEFACE
#include <gnm/platform.h>
#include <string>
#endif

#include <memory>
#include <algorithm>
#include <kernel.h>
#include <libsysmodule.h>
#include <video_out.h>
#include <vectormath.h>
#include <texture_tool/filter.h>
#include <texture_tool/gnm_texture_gen.h>
#include <texture_tool/image.h>
#include <texture_tool/image_reader.h>
#include <texture_tool/cube_image.h>
#include <texture_tool/volume_image.h>
#include <texture_tool/mipped_cube_image.h>
#include <texture_tool/mipped_image.h>
#include <texture_tool/mipped_volume_image.h>
#include "data_format_interpreter_gnm.h"

using namespace sce;

namespace
{
	constexpr int kNumGnmRenderContexts = 2;
	constexpr int kMaxMipLevel = 20;

	// kGarlicMemorySize + kOnionMemorySize MUST BE < (BASE_PHYSICAL_MEMORY - HEAP_SIZE)
	uint64_t kGarlicMemorySize = 1936UL * 1024UL * 1024UL;	// Do not make const this way easier to tune it
	uint64_t kNeoExtraGarlicMemorySize = 512UL * 1024UL * 1024UL; // This 512M is equivalent to NEO_PHYSICAL_MEMORY - BASE_PHYSICAL_MEMORY
	uint64_t kOnionMemorySize = 150 * 1024 * 1024;

	uint32_t kCueRingEntries = 64;
	size_t kDCBSizeInBytes = 64 * 1024 * 1024; // Two of these. Comes out of kOnionMemorySize
	size_t kCCBSizeInBytes = 2 * 1024 * 1024; // Two of these. Comes out of kOnionMemorySize

	// Allocate the render target memory
	// https://ps4.siedev.net/resources/documents/SDK/6.500/VideoOut-Reference/0012.html
	// "When allocating direct memory where a buffer will be placed, memory must be allocated with an alignment of 64 KiB or more"
	constexpr uint32_t videoOutBufferAlignment = 64 * 1024 * 1024;

	constexpr uint8_t kDefaultAnisotropyThreshold = 0;
	const uint32_t kDisplayBufferCount = 2;
	const Gnm::ZFormat kZFormat = Gnm::kZFormat32Float;
	const Gnm::StencilFormat kStencilFormat = Gnm::kStencil8;
	const bool kHtileEnabled = true;

	sce::TextureTool::ImageTypes getImageTypeFromTextureType(const sce::Gnm::TextureType textureType, const bool isMipped) {
		switch (textureType) {
		case Gnm::TextureType::kTextureType2d:
			return isMipped ? TextureTool::ImageTypes::k2DImageMipped : TextureTool::ImageTypes::k2DImage;
		case Gnm::TextureType::kTextureType3d:
			return isMipped ? TextureTool::ImageTypes::kVolumeImageMipped : TextureTool::ImageTypes::kVolumeImage;
		case Gnm::TextureType::kTextureTypeCubemap:
			return isMipped ? TextureTool::ImageTypes::kCubeImageMipped : TextureTool::ImageTypes::kCubeImage;
		case Gnm::TextureType::kTextureType1dArray:
		case Gnm::TextureType::kTextureType2dArray:
			return isMipped ? TextureTool::ImageTypes::kImageArrayMipped : TextureTool::ImageTypes::kImageArray;
		case Gnm::TextureType::kTextureType2dMsaa:
		case Gnm::TextureType::kTextureType2dArrayMsaa:
		case Gnm::TextureType::kTextureType1d:
		default:
			BX_ASSERT(false, "Unknown mapping between TextureType and ImageTypes");
			return TextureTool::ImageTypes::kUnknownImage;
		}
	}

	GpuAddress::SurfaceType getSurfaceTypeFromTextureType(const sce::Gnm::TextureType textureType, const bool computeWrite) {
		switch (textureType) {
		case sce::Gnm::kTextureType1d:
		case sce::Gnm::kTextureType1dArray:
		case sce::Gnm::kTextureType2dMsaa:
		case sce::Gnm::kTextureType2d:
			return computeWrite ? GpuAddress::kSurfaceTypeRwTextureFlat : GpuAddress::kSurfaceTypeTextureFlat;
		case sce::Gnm::kTextureType2dArray:
		case sce::Gnm::kTextureType2dArrayMsaa:
		case sce::Gnm::kTextureType3d:
			return computeWrite ? GpuAddress::kSurfaceTypeRwTextureVolume : GpuAddress::kSurfaceTypeTextureVolume;
		case sce::Gnm::kTextureTypeCubemap:
			return computeWrite ? GpuAddress::kSurfaceTypeRwTextureCubemap : GpuAddress::kSurfaceTypeTextureCubemap;
		default:
			BX_ASSERT(false, "Invalid parameter");
		}
		return static_cast<GpuAddress::SurfaceType>(0);
	}

	constexpr bool isTextureTypeMsaa(const Gnm::TextureType type) {
		return type == Gnm::kTextureType2dArrayMsaa || type == Gnm::kTextureType2dMsaa;
	}

	constexpr bool canBeTreatedAs2DTexture(const Gnm::TextureType type) {
		return type == Gnm::kTextureType2d
			|| type == Gnm::kTextureType2dMsaa
			|| type == Gnm::kTextureType1dArray;

	}
	constexpr bool canBeTreatedAs2DTextureArray(const Gnm::TextureType type) {
		return  type == Gnm::kTextureType2dArray
			|| type == Gnm::kTextureType2dArrayMsaa
			|| type == Gnm::kTextureType3d;
	}

	constexpr uint32_t calculateComputeThreadGroupCount(const uint32_t texelCount, const uint32_t threadCount) {
		return std::max(1u, texelCount / threadCount + ((texelCount % threadCount) ? 1u : 0u));
	}

	bool isVrEnabled() {
		return false;
		/*uint64_t sessionFlags = reinterpret_cast<uint64_t>(bgfx::g_platformData.session);
		return (0 != (sessionFlags & BGFX_PLATFORM_SESSION_FLAG_EXTERNAL_SWAPCHAIN));*/
	}
}

namespace bgfx {
	namespace gnm
	{

		static char s_viewName[BGFX_CONFIG_MAX_VIEWS][BGFX_CONFIG_MAX_VIEW_NAME];
		static char* s_view;

		struct BXDeleter {
			void operator()(void* p) {
				if (p) {
					BX_FREE(g_allocator, p);
				}
			}
		};
		template<typename T>
		using UniqueBX = std::unique_ptr<T, BXDeleter>;

		struct PrimInfo
		{
			Gnm::PrimitiveType m_type;
			uint32_t m_min;
			uint32_t m_div;
			uint32_t m_sub;
		};

		static const PrimInfo s_primInfo[] =
		{
			{ Gnm::kPrimitiveTypeTriList,   3, 3, 0 },
			{ Gnm::kPrimitiveTypeTriStrip,  3, 1, 2 },
			{ Gnm::kPrimitiveTypeLineList,  2, 2, 0 },
			{ Gnm::kPrimitiveTypeLineStrip, 2, 1, 1 },
			{ Gnm::kPrimitiveTypePointList, 1, 1, 0 },
			{ Gnm::kPrimitiveTypeNone,      0, 0, 0 },
		};
		BX_STATIC_ASSERT(Topology::Count == BX_COUNTOF(s_primInfo) - 1);

		static const Gnm::BlendMultiplier s_blendFactor[][2] =
		{
			{ Gnm::kBlendMultiplierZero,                    Gnm::kBlendMultiplierZero                  }, // ignored
			{ Gnm::kBlendMultiplierZero,                    Gnm::kBlendMultiplierZero                  }, // ZERO
			{ Gnm::kBlendMultiplierOne,                     Gnm::kBlendMultiplierOne                   }, // ONE
			{ Gnm::kBlendMultiplierSrcColor,                Gnm::kBlendMultiplierSrcAlpha              }, // SRC_COLOR
			{ Gnm::kBlendMultiplierOneMinusSrcColor,        Gnm::kBlendMultiplierOneMinusSrcAlpha      }, // INV_SRC_COLOR
			{ Gnm::kBlendMultiplierSrcAlpha,                Gnm::kBlendMultiplierSrcAlpha              }, // SRC_ALPHA
			{ Gnm::kBlendMultiplierOneMinusSrcAlpha,        Gnm::kBlendMultiplierOneMinusSrcAlpha      }, // INV_SRC_ALPHA
			{ Gnm::kBlendMultiplierDestAlpha,               Gnm::kBlendMultiplierDestAlpha             }, // DST_ALPHA
			{ Gnm::kBlendMultiplierOneMinusDestAlpha,       Gnm::kBlendMultiplierOneMinusDestAlpha     }, // INV_DST_ALPHA
			{ Gnm::kBlendMultiplierDestColor,               Gnm::kBlendMultiplierDestAlpha             }, // DST_COLOR
			{ Gnm::kBlendMultiplierOneMinusDestColor,       Gnm::kBlendMultiplierOneMinusDestAlpha     }, // INV_DST_COLOR
			{ Gnm::kBlendMultiplierSrcAlphaSaturate,        Gnm::kBlendMultiplierOne                   }, // SRC_ALPHA_SAT
			{ Gnm::kBlendMultiplierConstantColor,           Gnm::kBlendMultiplierConstantAlpha         }, // FACTOR
			{ Gnm::kBlendMultiplierOneMinusConstantColor,   Gnm::kBlendMultiplierOneMinusConstantAlpha }, // INV_FACTOR
		};

		static const sce::Gnm::BlendFunc s_blendEquation[] =
		{
			Gnm::kBlendFuncAdd,
			Gnm::kBlendFuncSubtract,
			Gnm::kBlendFuncReverseSubtract,
			Gnm::kBlendFuncMin,
			Gnm::kBlendFuncMax,
		};

#define BGFX_GNM_BLEND_STATE_MASK (0 \
			| BGFX_STATE_BLEND_MASK \
			| BGFX_STATE_BLEND_EQUATION_MASK \
			| BGFX_STATE_BLEND_INDEPENDENT \
			| BGFX_STATE_BLEND_ALPHA_TO_COVERAGE \
			)

#define BGFX_GNM_DEPTH_STENCIL_MASK (0 \
			| BGFX_STATE_WRITE_Z \
			| BGFX_STATE_DEPTH_TEST_MASK \
			)

		static const Gnm::CompareFunc s_cmpFunc[] =
		{
			Gnm::kCompareFuncNever, // ignored
			Gnm::kCompareFuncLess,
			Gnm::kCompareFuncLessEqual,
			Gnm::kCompareFuncEqual,
			Gnm::kCompareFuncGreaterEqual,
			Gnm::kCompareFuncGreater,
			Gnm::kCompareFuncNotEqual,
			Gnm::kCompareFuncNever,
			Gnm::kCompareFuncAlways,
		};

		static const Gnm::DepthCompare s_depthCmpFunc[] =
		{
			Gnm::kDepthCompareNever, // ignored
			Gnm::kDepthCompareLess,
			Gnm::kDepthCompareLessEqual,
			Gnm::kDepthCompareEqual,
			Gnm::kDepthCompareGreaterEqual,
			Gnm::kDepthCompareGreater,
			Gnm::kDepthCompareNotEqual,
			Gnm::kDepthCompareNever,
			Gnm::kDepthCompareAlways,
		};

		struct StencilOp
		{
			Gnm::StencilOp op;
			bool useOne;
		};

		static const StencilOp s_stencilOp[] =
		{
			{ Gnm::kStencilOpZero,      false },
			{ Gnm::kStencilOpKeep,      false },
			{ Gnm::kStencilOpReplaceOp, false },
			{ Gnm::kStencilOpAddWrap,   true  },
			{ Gnm::kStencilOpAddClamp,  true  },
			{ Gnm::kStencilOpSubWrap,   true  },
			{ Gnm::kStencilOpSubClamp,  true  },
			{ Gnm::kStencilOpInvert,    false },
		};

		static const Gnm::PrimitiveSetupCullFaceMode s_cullMode[] =
		{
			Gnm::kPrimitiveSetupCullFaceNone,
			Gnm::kPrimitiveSetupCullFaceFront,
			Gnm::kPrimitiveSetupCullFaceBack,
		};

		struct TextureFormatInfo
		{
			Gnm::DataFormat m_fmt;
			Gnm::DataFormat m_fmtSrgb;
			const Gnm::ZFormat m_depthFmt;
			const Gnm::StencilFormat m_stencilFmt;
			const uint8_t   m_mask;
		};

		static const TextureFormatInfo s_textureFormat[] =
		{
			{ Gnm::kDataFormatBc1Unorm,          Gnm::kDataFormatBc1UnormSrgb,      Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // BC1
			{ Gnm::kDataFormatBc2Unorm,          Gnm::kDataFormatBc2UnormSrgb,      Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // BC2
			{ Gnm::kDataFormatBc3Unorm,          Gnm::kDataFormatBc3UnormSrgb,      Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // BC3
			{ Gnm::kDataFormatBc4Unorm,          Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // BC4
			{ Gnm::kDataFormatBc5Unorm,          Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // BC4
			{ Gnm::kDataFormatBc6Sf16,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // BC6H
			{ Gnm::kDataFormatBc7Unorm,          Gnm::kDataFormatBc7UnormSrgb,      Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // BC7
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // ETC1
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // ETC2
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // ETC2A
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // ETC2A1
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // PTC12
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // PTC14
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // PTC12A
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // PTC14A
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // PTC22
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // PTC24
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0   }, // ATC
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0   }, // ATCE
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0   }, // ATCI
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0   }, // ASTC4x4
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0   }, // ASTC5x5
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0   }, // ASTC6x6
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0   }, // ASTC8x5
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0   }, // ASTC8x6
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0   }, // ASTC10x5
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0   }, // Unknown
			{ Gnm::kDataFormatR1Unorm,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x1 }, // R1
			{ Gnm::kDataFormatA8Unorm,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x1 }, // A8
			{ Gnm::kDataFormatR8Unorm,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x1 }, // R8
			{ Gnm::kDataFormatR8Sint,            Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x1 }, // R8I
			{ Gnm::kDataFormatR8Uint,            Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x1 }, // R8U
			{ Gnm::kDataFormatR8Snorm,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x1 }, // R8S
			{ Gnm::kDataFormatR16Unorm,          Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x1 }, // R16
			{ Gnm::kDataFormatR16Sint,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x1 }, // R16I
			{ Gnm::kDataFormatR16Uint,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x1 }, // R16U
			{ Gnm::kDataFormatR16Float,          Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x1 }, // R16F
			{ Gnm::kDataFormatR16Snorm,          Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x1 }, // R16S
			{ Gnm::kDataFormatR32Sint,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x1 }, // R32I
			{ Gnm::kDataFormatR32Uint,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x1 }, // R32U
			{ Gnm::kDataFormatR32Float,          Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x1 }, // R32F
			{ Gnm::kDataFormatR8G8Unorm,         Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x3 }, // RG8
			{ Gnm::kDataFormatR8G8Sint,          Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x3 }, // RG8I
			{ Gnm::kDataFormatR8G8Uint,          Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x3 }, // RG8U
			{ Gnm::kDataFormatR8G8Snorm,         Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x3 }, // RG8S
			{ Gnm::kDataFormatR16G16Unorm,       Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x3 }, // RG16
			{ Gnm::kDataFormatR16G16Sint,        Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x3 }, // RG16I
			{ Gnm::kDataFormatR16G16Uint,        Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x3 }, // RG16U
			{ Gnm::kDataFormatR16G16Float,       Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x3 }, // RG16F
			{ Gnm::kDataFormatR16G16Snorm,       Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x3 }, // RG16S
			{ Gnm::kDataFormatR32G32Sint,        Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x3 }, // RG32I
			{ Gnm::kDataFormatR32G32Uint,        Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x3 }, // RG32U
			{ Gnm::kDataFormatR32G32Float,       Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x3 }, // RG32F
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x7 }, // RGB8
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x7 }, // RGB8I
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x7 }, // RGB8U
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x7 }, // RGB8S
			{ Gnm::kDataFormatR9G9B9E5Float,     Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x7 }, // RGB9E5F
			{ Gnm::kDataFormatB8G8R8A8Unorm,     Gnm::kDataFormatB8G8R8A8UnormSrgb, Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // BGRA8
			{ Gnm::kDataFormatR8G8B8A8Unorm,     Gnm::kDataFormatR8G8B8A8UnormSrgb, Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // RGBA8
			{ Gnm::kDataFormatR8G8B8A8Sint,      Gnm::kDataFormatR8G8B8A8UnormSrgb, Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // RGBA8I
			{ Gnm::kDataFormatR8G8B8A8Uint,      Gnm::kDataFormatR8G8B8A8UnormSrgb, Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // RGBA8U
			{ Gnm::kDataFormatR8G8B8A8Snorm,     Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // RGBA8S
			{ Gnm::kDataFormatR16G16B16A16Unorm, Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // RGBA16
			{ Gnm::kDataFormatR16G16B16A16Sint,  Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // RGBA16I
			{ Gnm::kDataFormatR16G16B16A16Uint,  Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // RGBA16U
			{ Gnm::kDataFormatR16G16B16A16Float, Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // RGBA16F
			{ Gnm::kDataFormatR16G16B16A16Snorm, Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // RGBA16S
			{ Gnm::kDataFormatR32G32B32A32Sint,  Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // RGBA32I
			{ Gnm::kDataFormatR32G32B32A32Uint,  Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // RGBA32U
			{ Gnm::kDataFormatR32G32B32A32Float, Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // RGBA32F
			{ Gnm::kDataFormatB5G6R5Unorm,       Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x7 }, // R5G6B5
			{ Gnm::kDataFormatB4G4R4A4Unorm,     Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // RGBA4
			{ Gnm::kDataFormatB5G5R5A1Unorm,     Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // RGB5A1
			{ Gnm::kDataFormatR10G10B10A2Unorm,  Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0xf }, // RGB10A2
			{ Gnm::kDataFormatR11G11B10Float,    Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x7 }, // RG11B10F
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0   }, // UnknownDepth
			{ Gnm::kDataFormatR16Unorm,          Gnm::kDataFormatInvalid,           Gnm::kZFormat16,      Gnm::kStencilInvalid, 0x1 }, // D16
			{ Gnm::kDataFormatR32Float,          Gnm::kDataFormatInvalid,           Gnm::kZFormat32Float, Gnm::kStencilInvalid, 0x1 }, // D24
			{ Gnm::kDataFormatR32Float,          Gnm::kDataFormatInvalid,           Gnm::kZFormat32Float, Gnm::kStencil8,       0x1 }, // D24S8
			{ Gnm::kDataFormatR32Float,          Gnm::kDataFormatInvalid,           Gnm::kZFormat32Float, Gnm::kStencilInvalid, 0x1 }, // D32
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x1 }, // D16F
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencilInvalid, 0x1 }, // D24F
			{ Gnm::kDataFormatR32Float,          Gnm::kDataFormatInvalid,           Gnm::kZFormat32Float, Gnm::kStencilInvalid, 0x1 }, // D32F
			{ Gnm::kDataFormatInvalid,           Gnm::kDataFormatInvalid,           Gnm::kZFormatInvalid, Gnm::kStencil8,       0x1 }, // D0S8
		};
		BX_STATIC_ASSERT(TextureFormat::Count == BX_COUNTOF(s_textureFormat));

		static const Gnm::DataFormat s_attribType[][4][2] =
		{
			{ // Uint8
				{ Gnm::kDataFormatR8Uint,            Gnm::kDataFormatR8Unorm           },
				{ Gnm::kDataFormatR8G8Uint,          Gnm::kDataFormatR8G8Unorm         },
				{ Gnm::kDataFormatR8G8B8A8Uint,      Gnm::kDataFormatR8G8B8A8Unorm     },
				{ Gnm::kDataFormatR8G8B8A8Uint,      Gnm::kDataFormatR8G8B8A8Unorm     },
			},
			//{ // Int8
			//	{ Gnm::kDataFormatR8Sint,            Gnm::kDataFormatR8Snorm           },
			//	{ Gnm::kDataFormatR8G8Sint,          Gnm::kDataFormatR8G8Snorm         },
			//	{ Gnm::kDataFormatR8G8B8A8Sint,      Gnm::kDataFormatR8G8B8A8Snorm     },
			//	{ Gnm::kDataFormatR8G8B8A8Sint,      Gnm::kDataFormatR8G8B8A8Snorm     },
			//},
			{ // Uint10
				{ Gnm::kDataFormatR10G10B10A2Uint,   Gnm::kDataFormatR10G10B10A2Unorm  },
				{ Gnm::kDataFormatR10G10B10A2Uint,   Gnm::kDataFormatR10G10B10A2Unorm  },
				{ Gnm::kDataFormatR10G10B10A2Uint,   Gnm::kDataFormatR10G10B10A2Unorm  },
				{ Gnm::kDataFormatR10G10B10A2Uint,   Gnm::kDataFormatR10G10B10A2Unorm  },
			},
			//{ // UInt16
			//	{ Gnm::kDataFormatR16Uint,           Gnm::kDataFormatR16Unorm          },
			//	{ Gnm::kDataFormatR16G16Uint,        Gnm::kDataFormatR16G16Unorm       },
			//	{ Gnm::kDataFormatR16G16B16A16Uint,  Gnm::kDataFormatR16G16B16A16Unorm },
			//	{ Gnm::kDataFormatR16G16B16A16Uint,  Gnm::kDataFormatR16G16B16A16Unorm },
			//},
			{ // Int16
				{ Gnm::kDataFormatR16Sint,           Gnm::kDataFormatR16Snorm          },
				{ Gnm::kDataFormatR16G16Sint,        Gnm::kDataFormatR16G16Snorm       },
				{ Gnm::kDataFormatR16G16B16A16Sint,  Gnm::kDataFormatR16G16B16A16Snorm },
				{ Gnm::kDataFormatR16G16B16A16Sint,  Gnm::kDataFormatR16G16B16A16Sint  },
			},
			{ // Half
				{ Gnm::kDataFormatR16Float,          Gnm::kDataFormatR16Float          },
				{ Gnm::kDataFormatR16G16Float,       Gnm::kDataFormatR16G16Float       },
				{ Gnm::kDataFormatR16G16B16A16Float, Gnm::kDataFormatR16G16B16A16Float },
				{ Gnm::kDataFormatR16G16B16A16Float, Gnm::kDataFormatR16G16B16A16Float },
			},
			{ // Float
				{ Gnm::kDataFormatR32Float,          Gnm::kDataFormatR32Float          },
				{ Gnm::kDataFormatR32G32Float,       Gnm::kDataFormatR32G32Float       },
				{ Gnm::kDataFormatR32G32B32Float,    Gnm::kDataFormatR32G32B32Float    },
				{ Gnm::kDataFormatR32G32B32A32Float, Gnm::kDataFormatR32G32B32A32Float },
			},
		};
		BX_STATIC_ASSERT(AttribType::Count == BX_COUNTOF(s_attribType));

		struct MSAASampleInfo {
			std::vector<Gnm::NumSamples> m_numSampleLookup;
			Gnm::NumSamples m_maxSamples;
			Gnm::NumFragments m_maxFragments;
		};

		// only go to Gnm::kNumSamples4 to save 250MB of memory in 4K mode. Also 8 samples not visually needed in 4K mode.
		static MSAASampleInfo s_MaxMSAASampleInfo_4K = {
			{ Gnm::kNumSamples1, Gnm::kNumSamples2, Gnm::kNumSamples4 },
			Gnm::kNumSamples4,
			Gnm::kNumFragments4
		};

		// setMaxAnchorSamples() doesn't allow to set Gnm::kNumSamples16
		static MSAASampleInfo s_MaxMSAASampleInfo_1080p = {
			{ Gnm::kNumSamples1, Gnm::kNumSamples2, Gnm::kNumSamples4, Gnm::kNumSamples8 },
			Gnm::kNumSamples8,
			Gnm::kNumFragments8
		};

		struct InternalRenderContextGNM
		{
			Gnmx::GnmxGfxContext m_GFXContext;

			GnmAllocator::Unique<uint8_t> m_CueHeap; //Constant Update Engine Heap pointer
			GnmAllocator::Unique<uint8_t> m_DCBBuffer; //Draw Command Buffer pointer
			GnmAllocator::Unique<uint8_t> m_CCBBuffer; //Constant Command Buffer pointer

			volatile uint32_t* m_GPUContextLabel = nullptr;

			void setRenderTarget(uint32_t rtSlot, const Gnm::RenderTarget* target) {
				BX_ASSERT(rtSlot < BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS, "rtSlot invalid too high");
				m_GFXContext.setRenderTarget(rtSlot, target);
				m_currentRenderTarget[rtSlot] = target;
			}

			void setDepthRenderTarget(const Gnm::DepthRenderTarget* depthTarget) {
				m_GFXContext.setDepthRenderTarget(depthTarget);
				m_currentDepthRenderTarget = depthTarget;
			}

			template<typename Callable>
			void withRenderTarget(uint32_t rtSlot, const Gnm::RenderTarget* tempRenderTarget, Callable&& codeToWorkWithTempRenderTarget) {
				BX_ASSERT(rtSlot < BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS, "rtSlot invalid too high");
				m_GFXContext.setRenderTarget(rtSlot, tempRenderTarget);
				codeToWorkWithTempRenderTarget();
				m_GFXContext.setRenderTarget(rtSlot, m_currentRenderTarget[rtSlot]);
			}

			template<typename Callable>
			void withDepthRenderTarget(const Gnm::DepthRenderTarget* tempDepthRenderTarget, Callable&& codeToWorkWithTempDepthRenderTarget) {
				m_GFXContext.setDepthRenderTarget(tempDepthRenderTarget);
				codeToWorkWithTempDepthRenderTarget();
				m_GFXContext.setDepthRenderTarget(m_currentDepthRenderTarget);
			}

			const Gnm::RenderTarget* m_currentRenderTarget[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS] = { };
			const Gnm::DepthRenderTarget* m_currentDepthRenderTarget = nullptr;
		};

		struct RenderContextState // BGFX style enum
		{
			enum Enum
			{
				RenderContextFree = 0,
				RenderContextInUse,
			};
		};

		enum class RenderContextFlowState : uint8_t
		{
			BeginRenderFrame = 0,
			RenderFrame,
			SubmitAndFlip
		};

		static const Gnm::WrapMode s_textureWrapMode[] =
		{
			Gnm::kWrapModeWrap,
			Gnm::kWrapModeMirror,
			Gnm::kWrapModeClampLastTexel,
			Gnm::kWrapModeClampBorder
		};

		static const Gnm::FilterMode s_minMaxFilter[] =
		{
			Gnm::kFilterModeBilinear,
			Gnm::kFilterModePoint,
			Gnm::kFilterModeAnisoBilinear
			//Gnm::kFilterModeAnisoPoint Not used
		};

		static const Gnm::MipFilterMode s_mipFilterMode[] =
		{
			Gnm::kMipFilterModeLinear,
			Gnm::kMipFilterModePoint,
			Gnm::kMipFilterModeNone
		};

		struct TextureStageGNM {
			TextureStageGNM() {
				clear();
			}

			void clear() {
				m_bufferBound = 0;
				bx::memSet(m_bufferHandles, 0, sizeof(m_bufferHandles));
				bx::memSet(m_tex, 0, sizeof(m_tex));
				bx::memSet(m_sampler, 0, sizeof(m_sampler));
			}


			uint32_t m_bufferBound;
			uint16_t m_bufferHandles[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
			Gnm::Texture m_tex[Gnm::kSlotCountSampler];
			Gnm::Sampler m_sampler[Gnm::kSlotCountSampler];
		};

		extern EmbeddedPixelShaderWithSource sPixelClearShader;
		extern EmbeddedComputeShaderWithSource sComputeSetUintShader;
		extern EmbeddedComputeShaderWithSource sComputeSetUintFastShader;
		extern EmbeddedPixelShaderWithSource sCopyShader;

		extern EmbeddedComputeShaderWithSource sComputeCopyTtoTShader;
		extern EmbeddedComputeShaderWithSource sComputeCopyTtoTArrayShader;
		extern EmbeddedComputeShaderWithSource sComputeCopyTArraytoTArrayShader;
		extern EmbeddedComputeShaderWithSource sComputeCopyTtoCShader;

		extern EmbeddedComputeShaderWithSource sComputeCopyBuffer;

		EmbeddedComputeShaderWithSource* chooseCopyTextureShader(const Gnm::TextureType srcType, const Gnm::TextureType dstType) {
			if (canBeTreatedAs2DTexture(srcType)) {
				//Source is a 2D texture
				if (canBeTreatedAs2DTexture(dstType)) {
					return &sComputeCopyTtoTShader;
				}
				else if (canBeTreatedAs2DTextureArray(dstType)) {
					return &sComputeCopyTtoTArrayShader;
				}
				else if (dstType == Gnm::kTextureTypeCubemap) {
					return &sComputeCopyTtoCShader;
				}
			}
			else if (canBeTreatedAs2DTextureArray(srcType)) {
				if (canBeTreatedAs2DTextureArray(dstType)) {
					return &sComputeCopyTArraytoTArrayShader;
				}
				else {
					BX_ASSERT(false, "We currently only support Texture Array to Texture Array copying");
				}
			}
			else if (srcType == Gnm::kTextureTypeCubemap) {
				BX_ASSERT(false, "We currently do not support copying from TextureCubes");
			}

			return nullptr;
		}

		void ProgramGNM::create(const ShaderGNM* _vsh, const ShaderGNM* _fsh) {
			BX_ASSERT(nullptr != _vsh->m_vertexShader, "Vertex shader doesn't exist.");
			if (nullptr == _vsh->m_vertexShader)
			{
				return;
			}

			m_vsh = _vsh;
			::memcpy(&m_predefined[0], _vsh->m_predefined, _vsh->m_numPredefined * sizeof(PredefinedUniform));
			m_numPredefined = _vsh->m_numPredefined;

			m_attributesSlot = _vsh->m_attributesSlot;

			m_numAttributes = _vsh->m_numAttributes;

			if (nullptr != _fsh) {
				BX_ASSERT(NULL != _fsh->m_pixelShader, "Fragment shader doesn't exist.");
				if (nullptr == _fsh->m_pixelShader)
				{
					return;
				}
				m_fsh = _fsh;
				::memcpy(&m_predefined[m_numPredefined], _fsh->m_predefined, _fsh->m_numPredefined * sizeof(PredefinedUniform));
				m_numPredefined += _fsh->m_numPredefined;
			}
		}

		void ProgramGNM::destroy() {
			m_numPredefined = 0;
			m_vsh = nullptr;
			m_fsh = nullptr;
		}


		struct CommandBufferDataBuffer {
			CommandBufferDataBuffer(Gnmx::GnmxGfxContext& _gfxc, size_t _size)
				: m_size(_size)
				, m_gfxc(_gfxc)
			{
				realloc();
			}

			const size_t m_size;
			Gnmx::GnmxGfxContext& m_gfxc;

			uint8_t* m_data = nullptr;

			void realloc()
			{
				if (m_size == 0)
				{
					m_data = nullptr;
				}
				else
				{
					uint8_t* oldPtr = m_data;

					m_data = reinterpret_cast<uint8_t*>(m_gfxc.allocateFromCommandBuffer(m_size, Gnm::kEmbeddedDataAlignment4));
					BX_ASSERT(m_data != nullptr, "Cannot allocate memory from CommandBuffer");

					if (oldPtr != nullptr)
					{
						memcpy(m_data, oldPtr, m_size);
					}
				}
			}
		};

		struct CommandBufferConstantBuffer {
			CommandBufferConstantBuffer(Gnmx::GnmxGfxContext& _gfxc, const ProgramGNM& _program)
				: m_fsData(_gfxc, _program.m_fsh != nullptr ? _program.m_fsh->m_constantBufferSize : 0)
				, m_vsData(_gfxc, _program.m_vsh != nullptr ? _program.m_vsh->m_constantBufferSize : 0)
			{

			}

			void vsWrite(const uint8_t* _data, const size_t _dstOffset, const size_t _size)
			{
				_write(m_vsDirty, m_vsData, _data, _dstOffset, _size);
			}

			void fsWrite(const uint8_t* _data, const size_t _dstOffset, const size_t _size)
			{
				_write(m_fsDirty, m_fsData, _data, _dstOffset, _size);
			}

			void commit()
			{
				_commit(Gnm::kShaderStageVs, m_vsDirty, m_vsData);
				_commit(Gnm::kShaderStagePs, m_fsDirty, m_fsData);
			}

		private:
			void _commit(const Gnm::ShaderStage _stage, bool& _isTargetDirty, CommandBufferDataBuffer& _data)
			{
				if (_isTargetDirty)
				{
					Gnm::Buffer constantBuffer;
					constantBuffer.initAsConstantBuffer(_data.m_data, _data.m_size);
					constantBuffer.setResourceMemoryType(Gnm::kResourceMemoryTypeRO); // it's a constant buffer, so read-only is OK

					_data.m_gfxc.setConstantBuffers(_stage, 0, 1, &constantBuffer);

					_isTargetDirty = false;
				}
			}

			void _write(bool& _isTargetDirty, CommandBufferDataBuffer& _target, const uint8_t* _data, const size_t _dstOffset, const size_t _size)
			{
				if (!_isTargetDirty)
				{
					// It wasn't dirty, so already committed, copy on write
					_target.realloc();
					_isTargetDirty = true;
				}

				BX_ASSERT(_dstOffset + _size <= _target.m_size, "Out of bound write to constant buffer memory");
				memcpy(_target.m_data + _dstOffset, _data, _size);
			}

			CommandBufferDataBuffer m_fsData;
			bool m_fsDirty = true;

			CommandBufferDataBuffer m_vsData;
			bool m_vsDirty = true;
		};

		template <typename T>
		T* allocateFromCommandBuffer(sce::Gnmx::GnmxGfxContext& gfxc, int numElements, sce::Gnm::EmbeddedDataAlignment align)
		{
			return static_cast<T*>(gfxc.allocateFromCommandBuffer(sizeof(T) * numElements, align));
		}

		template <typename T>
		T* allocateFromCommandBuffer(sce::Gnmx::GnmxDrawCommandBuffer& dcb, int numElements, sce::Gnm::EmbeddedDataAlignment align)
		{
			return static_cast<T*>(dcb.allocateFromCommandBuffer(sizeof(T) * numElements, align));
		}

		struct RendererContextGNM : public RendererContextI
		{
		public:
			RendererContextGNM();
			~RendererContextGNM();

			struct StatsDataForSubmit
			{
				uint32_t statsNumPrimsSubmitted[BX_COUNTOF(s_primInfo)] = {};
				uint32_t statsNumPrimsRendered[BX_COUNTOF(s_primInfo)] = {};
				uint32_t statsNumInstances[BX_COUNTOF(s_primInfo)] = {};
				uint32_t statsNumDrawIndirect[BX_COUNTOF(s_primInfo)] = {};
				uint32_t statsNumIndices = 0;
				uint32_t statsKeyType[2] = {};
				int64_t captureElapsed = 0;
			};

			bool init(const Init& _init);
			void shutdown();

			RendererType::Enum getRendererType() const override;
			uint64_t getRendererVersion() const;
			const char* getRendererName() const override;
			bool isDeviceRemoved() override;
			void flip() override;

			void createIndexBuffer(IndexBufferHandle _handle, const Memory* _mem, uint16_t _flags) override;
			void destroyIndexBuffer(IndexBufferHandle _handle) override;
			void createVertexLayout(VertexLayoutHandle _handle, const VertexLayout& _decl) override;
			void destroyVertexLayout(VertexLayoutHandle _handle) override;
			void createVertexBuffer(VertexBufferHandle _handle, const Memory* _mem, VertexLayoutHandle _declHandle, uint16_t _flags) override;
			void destroyVertexBuffer(VertexBufferHandle _handle) override;
			void createDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size, uint16_t _flags) override;
			void updateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) override;
			void destroyDynamicIndexBuffer(IndexBufferHandle _handle) override;
			void createDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size, uint16_t _flags) override;
			void updateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) override;
			void destroyDynamicVertexBuffer(VertexBufferHandle _handle) override;
			void createShader(ShaderHandle _handle, const Memory* _mem) override;
			void destroyShader(ShaderHandle _handle) override;
			void createProgram(ProgramHandle _handle, ShaderHandle _vsh, ShaderHandle _fsh) override;
			void destroyProgram(ProgramHandle _handle) override;
			void* createTexture(TextureHandle _handle, const Memory* _mem, uint64_t _flags, uint8_t _skip) override;
			void wrapExternalTexture(TextureHandle _handle, RendererType::Enum _type, void* _texturePtr, void* _deferredRef);
			void updateTextureBegin(TextureHandle _handle, uint8_t _side, uint8_t _mip) override;
			void updateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem) override;
			void updateTextureEnd() override;
			void readTexture(TextureHandle _handle, void* _data, uint8_t _mip) override;
			void resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, uint16_t _numLayers) override;
			void overrideInternal(TextureHandle _handle, uintptr_t _ptr);
			uintptr_t getInternal(TextureHandle _handle) override;
			void destroyTexture(TextureHandle _handle) override;
			void createShaderBuffer(ShaderBufferHandle _handle, uint32_t _size, uint32_t _stride) override;
			void updateShaderBuffer(ShaderBufferHandle _handle, const Memory* _mem) override;
			void destroyShaderBuffer(ShaderBufferHandle _handle) override;
			void createFrameBuffer(FrameBufferHandle _handle, uint8_t _num, const Attachment* _attachment) override;
			void createFrameBuffer(FrameBufferHandle _handle, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat) override;
			void destroyFrameBuffer(FrameBufferHandle _handle) override;
			void createUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name) override;
			void destroyUniform(UniformHandle _handle) override;
			void requestScreenShot(FrameBufferHandle _handle, const char* _filePath) override;
			void updateViewName(ViewId _id, const char* _name) override;
			void updateUniform(uint16_t _loc, const void* _data, uint32_t _size) override;
			void setMarker(const char* _marker, uint16_t _size) override;
			void invalidateOcclusionQuery(OcclusionQueryHandle _handle) override;
			void setName(Handle _handle, const char* _name, uint16_t _len) override;
			void submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) override;
			void blitSetup(TextVideoMemBlitter& _blitter) override;
			void blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices) override;

			void _initGnmRenderContexts();
			void _initBackBuffers();
			void _initDepthTarget();
			void _initEmbeddedShadersForClear();
			void _initCopyShader();
			void _initCaps();
			void _shutdownEmbeddedShadersForClear();
			void _shutdownCopyShader();
			void _waitGPUIdleBeforeShutdown();

			void _clearMemoryToUints(sce::Gnmx::GnmxGfxContext& gfxc, const sce::Gnm::RenderTarget* renderTarget, void* dest, uint32_t destUints, uint32_t* source, uint32_t srcUints);
			void _copyBuffer(sce::Gnmx::GnmxGfxContext& gfxc, const Gnm::Buffer* bufferDst, const Gnm::Buffer* bufferSrc);
			void _clearRenderTarget(sce::Gnmx::GnmxGfxContext& gfxc, const RenderTargetWithSliceInfo* rtsi, uint32_t* source, uint32_t sourceUints);
			void _clearRenderTarget(sce::Gnmx::GnmxGfxContext& gfxc, const RenderTargetWithSliceInfo* rtsi, uint32_t clearColorRGBA);
			void _clearRenderTarget(sce::Gnmx::GnmxGfxContext& gfxc, const RenderTargetWithSliceInfo* rtsi, const float colorVec[4]);
			void _synchronizeComputeToGraphics(sce::Gnmx::GnmxDrawCommandBuffer* dcb);
			void _clearRenderTargetPartial(sce::Gnmx::GnmxGfxContext& gfxc, const RenderTargetWithSliceInfo* rtsi, const Rect* _prect, const float colorVec[4]);
			void _setupDepthStencilClearParams(sce::Gnmx::GnmxGfxContext& gfxc, const Clear& _clear);
			void _clearDepthStencilBuffer(sce::Gnmx::GnmxGfxContext& gfxc, const Gnm::DepthRenderTarget* depthTarget, const Rect* _prect, const Clear& _clear);
			void _submitDraws(Gnmx::GnmxGfxContext& gfxc, Frame* _render, ClearQuad& _clearQuad, RenderDraw& currentState, RenderBind& currentBind, uint8_t primIndex, PrimInfo& prim, StatsDataForSubmit& stats);
			void _beginRenderFrame(Gnmx::GnmxGfxContext& gfxc);
			void _handleCompute(bool& wasCompute, Frame* _render, const RenderBind& renderBind, uint16_t view, const RenderItem& renderItem, SortKey& key, uint16_t programIdx);
			void _setScissor(Gnmx::GnmxGfxContext& gfxc, Frame* _render, const Rect& viewScissorRect, uint16_t scissor);
			void _bindTextures(Frame* _render, RenderBind& currentBind, const RenderBind& renderBind, bool programChanged);
			void _setVertexLayoutAndBindVertexBuffers(Gnmx::GnmxGfxContext& gfxc, RenderDraw& currentState, const RenderDraw& draw, uint16_t programIdx);
			void _drawIndexed(Gnmx::GnmxGfxContext& gfxc, RenderDraw& currentState, const RenderDraw& draw, uint8_t primIndex, PrimInfo& prim, StatsDataForSubmit& stats);
			void _setProgram(Gnmx::GnmxGfxContext& gfxc, uint16_t programIdx);
			void _clearCmaskSurface(sce::Gnmx::GnmxGfxContext& gfxc, const RenderTargetWithSliceInfo* rtsi);
			void _updateResolutionReset(const Resolution& _resolution);
			void _enableMSAA(sce::Gnmx::GnmxGfxContext& gfxc, bool enableMSAA = true);
			void _setupScreenViewportCurrentRenderTarget(sce::Gnmx::GnmxGfxContext& gfxc, uint32_t left, uint32_t top, uint32_t right, uint32_t bottom, float zScale, float zOffset);
			void _setScreenScissor(sce::Gnmx::GnmxGfxContext& gfxc, int32_t left, int32_t top, int32_t right, int32_t bottom);

			bool setFrameBuffer(Gnmx::GnmxGfxContext& gfxc, FrameBufferHandle _fbh, bool _msaa = true, bool _needPresent = true);
			void clearQuad(Gnmx::GnmxGfxContext& gfxc, ClearQuad& _clearQuad, const Rect& _rect, const Clear& _clear, const float _palette[][4]);
			void clear(Gnmx::GnmxGfxContext& gfxc, const Clear& _clear, const Rect* _prect, const float _palette[][4]);
			void submitBlit(BlitState& _bs, uint16_t _view);
			void setBlendState(Gnmx::GnmxGfxContext& gfxc, uint64_t _state, uint32_t _rgba = 0);
			void setDepthStencilState(Gnmx::GnmxGfxContext& gfxc, uint64_t _state, uint64_t _stencil = 0);
			void setRasterizerState(Gnmx::GnmxGfxContext& gfxc, uint64_t _state, bool _wireframe = false);
			void setShaderUniform(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs, CommandBufferConstantBuffer& _constantBuffers);
			void setShaderUniform4f(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs, CommandBufferConstantBuffer& _constantBuffers);
			void setShaderUniform4x4f(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs, CommandBufferConstantBuffer& _constantBuffers);
			void commitTextureStage();
			void commitShaderConstants(CommandBufferConstantBuffer& _constantBuffers);
			void commit(UniformBuffer& _uniformBuffer, CommandBufferConstantBuffer& _constantBuffer);

			Gnm::Sampler* getSampler(uint32_t _flags, const float _rgba[4]);
			void invalidateTextureStage();

			Gnm::GpuMode m_featureLevel;
			int m_videoOutHandle = -1;
			SceKernelEqueue m_eopEventQueue = nullptr;

			GnmAllocator m_garlicAllocator;
			GnmAllocator m_onionAllocator;
			InternalRenderContextGNM m_internalRenderContextGnm[kNumGnmRenderContexts];
			InternalRenderContextGNM* m_currentInternalRenderContext = m_internalRenderContextGnm;
			uint32_t m_currentInternalRenderContextIndex = 0;

			bool m_needPresent = false;
			RenderContextFlowState m_renderContextFlowState = RenderContextFlowState::BeginRenderFrame;

			Resolution m_resolution;
			Gnm::NumSamples m_numSamples;

			DisplayBuffer m_displayBuffers[kDisplayBufferCount];
			uint32_t m_currentBackBufferIndex = 0;

			Gnm::OwnerHandle m_ownerHandle = 0;

			RenderTargetGNM m_backBuffers[kDisplayBufferCount];

			DepthRenderTargetGNM m_depthTarget;

			ShaderGNM m_shaders[BGFX_CONFIG_MAX_SHADERS];
			ProgramGNM m_program[BGFX_CONFIG_MAX_PROGRAMS];
			TextureGNM m_textures[BGFX_CONFIG_MAX_TEXTURES];
			VertexLayout m_vertexDecls[BGFX_CONFIG_MAX_VERTEX_LAYOUTS];
			FrameBufferGNM m_frameBuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS];
			VertexBufferGNM m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
			IndexBufferGNM m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
			ShaderBufferGNM m_shaderBuffers[BGFX_CONFIG_MAX_SHADER_BUFFERS];

			BorderColorTableGNM m_borderColorTable;

			ProgramGNM* m_currentProgram = nullptr;

			TextureStageGNM m_textureStage;
			StateCacheT<Gnm::Sampler> m_samplerCache;

			FrameBufferHandle m_fbh = BGFX_INVALID_HANDLE;
			bool m_rtMsaa = true;

			MSAASampleInfo* m_msaaSampleInfo = nullptr;

			uint32_t m_MRTmask;

			UniformRegistry m_uniformReg;
			UniqueBX<uint8_t> m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];

			static ViewState s_viewState;
			static Rect s_currentScissor;
		};

		/*static*/ ViewState RendererContextGNM::s_viewState;
		/*static*/ Rect RendererContextGNM::s_currentScissor;

		static RendererContextGNM* s_renderGNM;

		RendererContextI* rendererCreate(const Init& _init)
		{
			s_renderGNM = BX_NEW(g_allocator, RendererContextGNM);
			if (!s_renderGNM->init(_init))
			{
				BX_DELETE(g_allocator, s_renderGNM);
				s_renderGNM = NULL;
			}
			return s_renderGNM;
		}

		void rendererDestroy()
		{
			s_renderGNM->shutdown();
			BX_DELETE(g_allocator, s_renderGNM);
			s_renderGNM = NULL;
		}

#if BGFX_CONFIG_DEBUG
		struct renderExtents
		{
			uint32_t width;
			uint32_t height;
		};

		renderExtents getRenderExtents()
		{
			renderExtents re;
			if (s_renderGNM != nullptr & s_renderGNM->m_currentInternalRenderContext != nullptr)
			{	// BBI TODO (dgalloway 3) this debug check only checks against [0]
				if (s_renderGNM->m_currentInternalRenderContext->m_currentRenderTarget[0] != nullptr)
				{
					re.width = s_renderGNM->m_currentInternalRenderContext->m_currentRenderTarget[0]->getWidth();
					re.height = s_renderGNM->m_currentInternalRenderContext->m_currentRenderTarget[0]->getHeight();
				}
				else if (s_renderGNM->m_currentInternalRenderContext->m_currentDepthRenderTarget != nullptr)
				{
					re.width = s_renderGNM->m_currentInternalRenderContext->m_currentDepthRenderTarget->getWidth();
					re.height = s_renderGNM->m_currentInternalRenderContext->m_currentDepthRenderTarget->getHeight();
				}
				else
				{
					BX_ASSERT(false, "Render context has no renderable targets.");
				}
			}
			else
			{
				BX_ASSERT(false, "Render context is not valid.");
			}
			return re;
		}
#endif

	} /* namespace gnm */
} // namespace bgfx

//----------------------------
// Definitions
//----------------------------
namespace bgfx {
	namespace gnm {

		RendererContextGNM::RendererContextGNM()
			: m_featureLevel(Gnm::getGpuMode()) // Will return 1 for NEO mode, 0 for default less powerful mode
		{
		}

		RendererContextGNM::~RendererContextGNM()
		{
			const int32_t ret = Gnm::submitDone();

			if (ret != SCE_OK)
			{
				bx::debugPrintf("Gnm::submitDone failed: 0x%08X\n", ret);
				BX_ASSERT(false, "Gnm::submitDone failed: 0x%08X\n", ret);
			}
		}

		bool RendererContextGNM::init(const Init& _init)
		{
			m_resolution = _init.resolution;
			// No need for 4k if PSVR is enabled
			if (isVrEnabled()) {
				m_resolution.width = 1920;
				m_resolution.height = 1080;
			}
			// If m_resolution is set not to 1080p or 4K then the flip will fail!
			BX_ASSERT((m_resolution.height == 1080 && m_resolution.width == 1920) || (m_resolution.height == 2160 && m_resolution.width == 3840), "Bad resolution passed to RendererContextGNM::Init()");

			if (m_resolution.height > 1080) {
				m_msaaSampleInfo = &s_MaxMSAASampleInfo_4K;
			}
			else {
				m_msaaSampleInfo = &s_MaxMSAASampleInfo_1080p;
			}

			// If the option aa level is higher than supported msaa level, reduce it
			m_numSamples = m_msaaSampleInfo->m_numSampleLookup.at(std::min(static_cast<size_t>((m_resolution.reset & BGFX_RESET_MSAA_MASK) >> BGFX_RESET_MSAA_SHIFT), m_msaaSampleInfo->m_numSampleLookup.size() - 1));


			m_videoOutHandle = sceVideoOutOpen(SCE_USER_SERVICE_USER_ID_SYSTEM, SCE_VIDEO_OUT_BUS_TYPE_MAIN, 0, nullptr);

			if (m_videoOutHandle < 0)
			{
				BX_TRACE("Init error: m_videoOutHandle has error 0x%08X", m_videoOutHandle);
				return false;
			}

			// Initialize the flip rate: 0: 60Hz, 1: 30Hz or 2: 20Hz
			int ret = sceVideoOutSetFlipRate(m_videoOutHandle, 0);
			if (ret != SCE_OK) {
				BX_TRACE("Init error: sceVideoOutSetFlipRate failed: 0x%08X\n", ret);

				shutdown();

				return false;
			}

			ret = Gnm::registerOwner(&m_ownerHandle, "bgfx");

			ret = sceKernelCreateEqueue(&m_eopEventQueue, "EOP QUEUE");
			if (ret != SCE_OK) {
				BX_TRACE("sceKernelCreateEqueue failed: 0x%08X\n", ret);

				shutdown();

				return false;
			}

			// Register for the end-of-pipe events
			ret = Gnm::addEqEvent(m_eopEventQueue, Gnm::kEqEventGfxEop, NULL);
			if (ret != SCE_OK) {
				BX_TRACE("Gnm::addEqEvent failed: 0x%08X\n", ret);

				shutdown();

				return false;
			}

			// Init reserved part of view name.
			for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
			{
				bx::snprintf(s_viewName[ii], BGFX_CONFIG_MAX_VIEW_NAME_RESERVED + 1, "%3d   ", ii);
			}

			// Garlic (GPU) and Onion (CPU) memory
			uint64_t garlicMemSize = kGarlicMemorySize;
			if (m_featureLevel == Gnm::kGpuModeNeo) {
				garlicMemSize += kNeoExtraGarlicMemorySize;
			}
			m_garlicAllocator.initialize(SCE_KERNEL_WC_GARLIC, garlicMemSize, true);
			m_onionAllocator.initialize(SCE_KERNEL_WB_ONION, kOnionMemorySize, true);

			_initGnmRenderContexts();

			_initBackBuffers();
			_initDepthTarget();

			_initEmbeddedShadersForClear();
			_initCopyShader();

			bx::memSet(m_uniforms, 0, sizeof(m_uniforms));

			_initCaps();
			// TODO BORDER COLOR: m_borderColorTable.init();
			// Success
			return true;
		}

		void RendererContextGNM::_initCaps()
		{
			g_caps.supported = 0
				| BGFX_CAPS_ALPHA_TO_COVERAGE
				| BGFX_CAPS_COMPUTE
				| BGFX_CAPS_CONSERVATIVE_RASTER
				| BGFX_CAPS_DRAW_INDIRECT
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
				| BGFX_CAPS_TEXTURE_CUBE_ARRAY
				| BGFX_CAPS_TEXTURE_READ_BACK
				| BGFX_CAPS_VERTEX_ATTRIB_HALF
				| BGFX_CAPS_VERTEX_ATTRIB_UINT10
				/*| BGFX_CAPS_VERTEX_ATTRIB_SINT8
				| BGFX_CAPS_VERTEX_ATTRIB_UINT16*/
				| BGFX_CAPS_STRUCTURED_BUFFERS
				| BGFX_CAPS_HDR10

				// Confirmed ones below are not supported
				//| BGFX_CAPS_BLEND_INDEPENDENT
				//| BGFX_CAPS_FRAGMENT_ORDERING
				//| BGFX_CAPS_HIDPI

				// These are set elsewhere in the code
				//| BGFX_CAPS_GRAPHICS_DEBUGGER
				//| BGFX_CAPS_RENDERER_MULTITHREADED
				;

			for (uint32_t formatIdx = 0; formatIdx < TextureFormat::Count; ++formatIdx)
			{
				switch (formatIdx)
				{
					// Confirmed ones below are not supported.
				case TextureFormat::ETC1:         //!< ETC1 RGB8
				case TextureFormat::ETC2:         //!< ETC2 RGB8
				case TextureFormat::ETC2A:        //!< ETC2 RGBA8
				case TextureFormat::ETC2A1:       //!< ETC2 RGB8A1
				case TextureFormat::PTC12:        //!< PVRTC1 RGB 2BPP
				case TextureFormat::PTC14:        //!< PVRTC1 RGB 4BPP
				case TextureFormat::PTC12A:       //!< PVRTC1 RGBA 2BPP
				case TextureFormat::PTC14A:       //!< PVRTC1 RGBA 4BPP
				case TextureFormat::PTC22:        //!< PVRTC2 RGBA 2BPP
				case TextureFormat::PTC24:        //!< PVRTC2 RGBA 4BPP
				case TextureFormat::ATC:          //!< ATC RGB 4BPP
				case TextureFormat::ATCE:         //!< ATCE RGBA 8 BPP explicit alpha
				case TextureFormat::ATCI:         //!< ATCI RGBA 8 BPP interpolated alpha
				case TextureFormat::ASTC4x4:      //!< ASTC 4x4 8.0 BPP
				case TextureFormat::ASTC5x5:      //!< ASTC 5x5 5.12 BPP
				case TextureFormat::ASTC6x6:      //!< ASTC 6x6 3.56 BPP
				case TextureFormat::ASTC8x5:      //!< ASTC 8x5 3.20 BPP
				case TextureFormat::ASTC8x6:      //!< ASTC 8x6 2.67 BPP
				case TextureFormat::ASTC10x5:     //!< ASTC 10x5 2.56 BPP
				case TextureFormat::Unknown:      // Compressed formats above.
				case TextureFormat::RGB8:
				case TextureFormat::RGB8I:
				case TextureFormat::RGB8U:
				case TextureFormat::RGB8S:
				case TextureFormat::UnknownDepth: // Depth formats below.
				case TextureFormat::D24:
				case TextureFormat::D32:
				case TextureFormat::D16F:
				case TextureFormat::D24F:
					g_caps.formats[formatIdx] = 0;
					break;

					// Set same flag to all supported formats.
				default:
					g_caps.formats[formatIdx] = 0
						| BGFX_CAPS_FORMAT_TEXTURE_NONE
						| BGFX_CAPS_FORMAT_TEXTURE_2D
						| BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB
						| BGFX_CAPS_FORMAT_TEXTURE_3D
						| BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB
						| BGFX_CAPS_FORMAT_TEXTURE_CUBE
						| BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB
						| BGFX_CAPS_FORMAT_TEXTURE_VERTEX
						//| BGFX_CAPS_FORMAT_TEXTURE_IMAGE
						| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
						| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA
						| BGFX_CAPS_FORMAT_TEXTURE_MSAA
						| BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN

						// These are set elsewhere in the code.
						//| BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED
						//| BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED
						//| BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED
						;
					break;
				}
			}

			g_caps.limits.maxTextureSize = 16384;
			g_caps.limits.maxTextureLayers = 8192;
			g_caps.limits.maxFBAttachments = BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS;	// Couldn't find max frame buffer attachments in the document.
			g_caps.limits.maxVertexStreams = Gnm::kSlotCountVertexBuffer;
			g_caps.limits.maxTextureSamplers = Gnm::kSlotCountSampler;

			const bool isNeo = (Gnm::getGpuMode() == Gnm::kGpuModeNeo);
			g_caps.numGPUs = 1;
			g_caps.gpu[0].vendorId = g_caps.vendorId = BGFX_PCI_ID_AMD;
			g_caps.gpu[0].deviceId = g_caps.deviceId = isNeo ? 1 : 0;

			/*bx::strCopy(g_caps.chipsetName, static_cast<int32_t>(BX_COUNTOF(g_caps.chipsetName)), isNeo ? "GCN NEO" : "GCN BASE");
			bx::strCopy(g_caps.gpu[0].chipsetName, static_cast<int32_t>(BX_COUNTOF(g_caps.gpu[0].chipsetName)), g_caps.chipsetName);
			bx::strCopy(g_caps.rendererVersion, static_cast<int32_t>(BX_COUNTOF(g_caps.rendererVersion)), isNeo ? "GNM NEO" : "GNM");

			g_caps.displayWidth = m_resolution.width;
			g_caps.displayHeight = m_resolution.height;

			g_caps.gpu[0].dedicatedVideoMemory = g_caps.dedicatedVideoMemory = m_garlicAllocator.getTotalActualSizeAllocated() + m_garlicAllocator.getTotalActualSizeFree();*/
		}

		void RendererContextGNM::shutdown()
		{
			// TODO BORDER COLOR: m_borderColorTable.shutdown();
			_shutdownCopyShader();
			_shutdownEmbeddedShadersForClear();

			for (int i = 0; i < kNumGnmRenderContexts; ++i)
			{
				m_internalRenderContextGnm[i].m_CueHeap = nullptr;
				m_internalRenderContextGnm[i].m_DCBBuffer = nullptr;
				m_internalRenderContextGnm[i].m_CCBBuffer = nullptr;

				if (m_internalRenderContextGnm[i].m_GPUContextLabel)
				{
					m_onionAllocator.release((void*)m_internalRenderContextGnm[i].m_GPUContextLabel);
					m_internalRenderContextGnm[i].m_GPUContextLabel = nullptr;
				}
			}

			for (uint32_t i = 0; i < kDisplayBufferCount; ++i)
			{
				m_displayBuffers[i].destroy();
				m_backBuffers[i].destroy();
			}

			m_depthTarget.destroy();
			m_depthTarget.m_hTileBuffer.destroy();
			m_depthTarget.m_stencilBuffer.destroy();
			m_depthTarget.m_depthRenderTarget.setAddresses(nullptr, nullptr);
			m_depthTarget.m_depthRenderTarget.setHtileAddress(nullptr);

			for (uint32_t i = 0; i < BGFX_CONFIG_MAX_TEXTURES; ++i) {
				m_textures[i].destroy();
			}

			m_garlicAllocator.releaseAllMarked();
			m_onionAllocator.releaseAllMarked();

			if (m_eopEventQueue != nullptr)
			{
				// Unregister the EOP event queue
				int ret = Gnm::deleteEqEvent(m_eopEventQueue, Gnm::kEqEventGfxEop);
				if (ret != SCE_OK)
				{
					BX_TRACE("Gnm::deleteEqEvent failed: 0x%08X\n", ret);
				}

				// Destroy the EOP event queue
				ret = sceKernelDeleteEqueue(m_eopEventQueue);
				if (ret != SCE_OK)
				{
					BX_TRACE("sceKernelDeleteEqueue failed: 0x%08X\n", ret);
				}

				m_eopEventQueue = nullptr;
			}

			m_videoOutHandle = -1;
		}

		RendererType::Enum RendererContextGNM::getRendererType() const
		{
			return RendererType::Gnm;
		}

		uint64_t RendererContextGNM::getRendererVersion() const
		{
			return static_cast<uint64_t>(m_featureLevel); // Will return 1 for NEO mode, 0 for default less powerful mode
		}

		const char* RendererContextGNM::getRendererName() const
		{
			return BGFX_RENDERER_GNM_NAME;
		}

		bool RendererContextGNM::isDeviceRemoved()
		{
			return false; // This doesn't happen on ORBIS
		}

		void RendererContextGNM::flip()
		{
			BX_TRACE("Flip");
			if (m_renderContextFlowState == RenderContextFlowState::SubmitAndFlip)
			{
				// m_needPresent will remain false if we do not render to the backbuffer
				// but in PSVR we ONLY render to the framebuffers and NEVER to the backbuffer
				// therefore we need to skip this step.
				if (!m_needPresent && !isVrEnabled())
				{
					m_renderContextFlowState = RenderContextFlowState::RenderFrame; // not submitting so don't need begin either
					return;
				}

				Gnmx::GnmxGfxContext& gfxc = m_currentInternalRenderContext->m_GFXContext;

				if (m_displayBuffers[m_currentBackBufferIndex].m_rtsi.m_renderTarget.getCmaskFastClearEnable()) {
					Gnmx::eliminateFastClear(&gfxc, &m_displayBuffers[m_currentBackBufferIndex].m_rtsi.m_renderTarget);
				}

				gfxc.waitForGraphicsWrites(m_displayBuffers[m_currentBackBufferIndex].m_rtsi.m_renderTarget.getBaseAddress256ByteBlocks(), (m_displayBuffers[m_currentBackBufferIndex].m_rtsi.m_renderTarget.getSliceSizeInBytes() * 1) >> 8,
					Gnm::kWaitTargetSlotCb0 | Gnm::kWaitTargetSlotDb, Gnm::kCacheActionWriteBackAndInvalidateL1andL2, Gnm::kExtendedCacheActionFlushAndInvalidateCbCache |
					Gnm::kExtendedCacheActionFlushAndInvalidateDbCache, Gnm::kStallCommandBufferParserDisable);

				if (m_rtMsaa) {
					Gnmx::hardwareMsaaResolve(&gfxc, &m_backBuffers[m_currentBackBufferIndex].m_rtsi.m_renderTarget, &m_displayBuffers[m_currentBackBufferIndex].m_rtsi.m_renderTarget);
				}


				// Write the GPU label that determines the render context state (free)
				// and trigger a software interrupt to signal the EOP event queue
				// NOTE: for this basic sample we are submitting a single GfxContext
				// per frame. Submitting multiple GfxContext-s per frame is allowed.
				// Multiple contexts are processed in order, i.e.: they start in
				// submission order and end in submission order.
				gfxc.writeAtEndOfPipeWithInterrupt(
					Gnm::kEopFlushCbDbCaches,
					Gnm::kEventWriteDestMemory,
					const_cast<uint32_t*>(m_currentInternalRenderContext->m_GPUContextLabel),
					Gnm::kEventWriteSource32BitsImmediate,
					RenderContextState::RenderContextFree,
					Gnm::kCacheActionWriteBackAndInvalidateL1andL2,
					Gnm::kCachePolicyLru);

				int ret = 0;
				const bool vrEnabled = isVrEnabled();

				// In non-VR Mode, submit commands before calling submitDone, as we don't have a dependency on reprojection
				// but still need to ensure that long main thread frames don't cause us to fail cert.
				if (!vrEnabled) {
					ret = gfxc.submitAndFlip(m_videoOutHandle,
						m_displayBuffers[m_currentBackBufferIndex].m_displayIndex,
						(m_resolution.reset & BGFX_RESET_VSYNC) ? SCE_VIDEO_OUT_FLIP_MODE_VSYNC : SCE_VIDEO_OUT_FLIP_MODE_HSYNC,
						0);
				}

				int submitDoneRet = 0;
				if ((submitDoneRet = Gnm::submitDone()) != SCE_OK)
				{
					bx::debugPrintf("Gnm::submitDone failed: 0x%08X\n", submitDoneRet);
					BX_ASSERT(false, "Gnm::submitDone failed: 0x%08X\n", submitDoneRet);
				}

				// In VR Mode, submit commands after calling submitDone to ensure that we never create
				// a race between the CPU and the GPU that decreases PSVR performance.
				// We also call submitDone after reprojection to ensure that long main thread frames don't
				// cause us to fail cert.
				if (vrEnabled) {
					ret = gfxc.submit();
				}

				if (ret != sce::Gnm::kSubmissionSuccess) {
					// Analyze the error code to determine whether the command buffers
					// have been submitted to the GPU or not
					if (ret & sce::Gnm::kStatusMaskError) {
						// Error codes in the kStatusMaskError family block submissions
						// so we need to mark this render context as not-in-flight
						m_currentInternalRenderContext->m_GPUContextLabel[0] = RenderContextState::RenderContextFree;
					}

					bx::debugPrintf("GfxContext::submitAndFlip failed: 0x%08X\n", ret);
					BX_ASSERT(false, "GfxContext::submitAndFlip failed : 0x%08X\n", ret);
				}

				// Rotate the display buffers
				m_currentBackBufferIndex = (m_currentBackBufferIndex + 1) % kDisplayBufferCount;

				// Rotate the render contexts
				m_currentInternalRenderContextIndex = (m_currentInternalRenderContextIndex + 1) % kNumGnmRenderContexts;
				m_currentInternalRenderContext = &m_internalRenderContextGnm[m_currentInternalRenderContextIndex];

				m_renderContextFlowState = RenderContextFlowState::BeginRenderFrame;
				m_needPresent = false;
			}
		}

		void RendererContextGNM::createIndexBuffer(IndexBufferHandle _handle, const Memory* _mem, uint16_t _flags)
		{
			m_indexBuffers[_handle.idx].create(_mem->size, _mem->data, _flags);
		}

		void RendererContextGNM::destroyIndexBuffer(IndexBufferHandle _handle)
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void RendererContextGNM::createVertexLayout(VertexLayoutHandle _handle, const VertexLayout& _decl)
		{
			VertexLayout& decl = m_vertexDecls[_handle.idx];
			::memcpy(&decl, &_decl, sizeof(VertexLayout));
			dump(decl);
		}

		void RendererContextGNM::destroyVertexLayout(VertexLayoutHandle _handle)
		{
		}

		void RendererContextGNM::createVertexBuffer(VertexBufferHandle _handle, const Memory* _mem, VertexLayoutHandle _declHandle, uint16_t _flags)
		{
			m_vertexBuffers[_handle.idx].create(_mem->size, _mem->data, _declHandle, _flags);
		}

		void RendererContextGNM::destroyVertexBuffer(VertexBufferHandle _handle)
		{
			m_vertexBuffers[_handle.idx].destroy();
		}

		void RendererContextGNM::createDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size, uint16_t _flags)
		{
			m_indexBuffers[_handle.idx].create(_size, nullptr, _flags);
		}

		void RendererContextGNM::updateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem)
		{
			m_indexBuffers[_handle.idx].update(_offset, bx::uint32_min(_size, _mem->size), _mem->data);
		}

		void RendererContextGNM::destroyDynamicIndexBuffer(IndexBufferHandle _handle)
		{
			m_indexBuffers[_handle.idx].destroy();
		}

		void RendererContextGNM::createDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size, uint16_t _flags)
		{
			VertexLayoutHandle declHandle = BGFX_INVALID_HANDLE;
			m_vertexBuffers[_handle.idx].create(_size, nullptr, declHandle, _flags);
		}

		void RendererContextGNM::updateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem)
		{
			m_vertexBuffers[_handle.idx].update(_offset, bx::uint32_min(_size, _mem->size), _mem->data);
		}

		void RendererContextGNM::destroyDynamicVertexBuffer(VertexBufferHandle _handle)
		{
			m_vertexBuffers[_handle.idx].destroy();
		}

		void RendererContextGNM::createShader(ShaderHandle _handle, const Memory* _mem)
		{
			// BBI-NOTE (dgalloway)  - for debugging only need to make s_ctx global for this to work
			//BX_TRACE("Shader name: %s  idx: %d", bgfx::s_ctx->m_shaderRef[_handle.idx].m_name.getPtr() , _handle.idx);
			m_shaders[_handle.idx].create(_mem);
		}

		void RendererContextGNM::destroyShader(ShaderHandle _handle)
		{
			m_shaders[_handle.idx].destroy();
		}

		void RendererContextGNM::createProgram(ProgramHandle _handle, ShaderHandle _vsh, ShaderHandle _fsh)
		{
			m_program[_handle.idx].create(&m_shaders[_vsh.idx], isValid(_fsh) ? &m_shaders[_fsh.idx] : NULL);
		}

		void RendererContextGNM::destroyProgram(ProgramHandle _handle)
		{
			m_program[_handle.idx].destroy();
		}

		void* RendererContextGNM::createTexture(TextureHandle _handle, const Memory* _mem, uint64_t _flags, uint8_t _skip)
		{
			return m_textures[_handle.idx].create(_mem, _flags, _skip);
		}

		void RendererContextGNM::wrapExternalTexture(TextureHandle _handle, RendererType::Enum _type, void* _texturePtr, void* _deferredRef)
		{
			BX_ASSERT(_type == RendererType::Gnm, "Implementation only compatible with Gnm textures");
			m_textures[_handle.idx].wrapExternal(*reinterpret_cast<sce::Gnm::Texture*>(_texturePtr), *reinterpret_cast<TextureRef*>(_deferredRef));
		}

		void RendererContextGNM::updateTextureBegin(TextureHandle _handle, uint8_t _side, uint8_t _mip)
		{
			BX_UNUSED(_handle/*, _side, _mip*/);
		}

		void RendererContextGNM::updateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem)
		{
			m_textures[_handle.idx].update(_side, _mip, _rect, _z, _depth, _pitch, _mem);
		}

		void RendererContextGNM::updateTextureEnd()
		{
		}

		void RendererContextGNM::readTexture(TextureHandle _handle, void* _data, uint8_t _mip)
		{
			const TextureGNM& texture = m_textures[_handle.idx];

			GpuAddress::TilingParameters tilingParams;
			tilingParams.initFromTexture(&texture.m_internalTexture, _mip, 0);
			GpuAddress::detileSurface(_data, texture.m_internalTexture.getBaseAddress(), &tilingParams);
		}

		void RendererContextGNM::resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, uint16_t _numLayers)
		{
			TextureGNM& texture = m_textures[_handle.idx];

			// External textures manage their memory externally and therefore
			// Should not be resized within BGFX
			if (texture.m_isExternal) {
				return;
			}

			if (texture.m_width == _width
				&& texture.m_height == _height
				&& texture.m_numMips == _numMips) {
				return;
			}
			uint32_t size = sizeof(uint32_t) + sizeof(TextureCreate);
			const Memory* mem = alloc(size);

			bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
			uint32_t magic = BGFX_CHUNK_MAGIC_TEX;
			bx::write(&writer, magic);

			TextureCreate tc;
			tc.m_width = _width;
			tc.m_height = _height;
			tc.m_depth = 0;
			tc.m_numLayers = _numLayers;
			tc.m_numMips = _numMips;
			tc.m_format = TextureFormat::Enum(texture.m_requestedFormat);
			tc.m_cubeMap = false;
			tc.m_mem = NULL;
			bx::write(&writer, tc);

			texture.destroy();
			texture.create(mem, texture.m_flags, 0);
			if (texture.m_BoundFrameBuffer) {
				texture.m_BoundFrameBuffer->updateTextureBindings();
			}
			release(mem);
		}

		void RendererContextGNM::overrideInternal(TextureHandle _handle, uintptr_t _ptr)
		{
			m_textures[_handle.idx].overrideInternal(_ptr, 0);
		}

		uintptr_t RendererContextGNM::getInternal(TextureHandle _handle)
		{
			SCE_GNM_ASSERT(false);
			return uintptr_t(nullptr);
		}

		void RendererContextGNM::destroyTexture(TextureHandle _handle)
		{
			m_textures[_handle.idx].destroy();
		}

		void RendererContextGNM::createShaderBuffer(ShaderBufferHandle _handle, uint32_t _size, uint32_t _stride)
		{
			m_shaderBuffers[_handle.idx].create(_size, NULL, BGFX_BUFFER_COMPUTE_READ, _stride, false);
		}

		void RendererContextGNM::updateShaderBuffer(ShaderBufferHandle _handle, const Memory* _mem)
		{
			m_shaderBuffers[_handle.idx].update(0, _mem->size, _mem->data);
		}

		void RendererContextGNM::destroyShaderBuffer(ShaderBufferHandle _handle)
		{
			m_shaderBuffers[_handle.idx].destroy();
		}

		void RendererContextGNM::createFrameBuffer(FrameBufferHandle _handle, uint8_t _num, const Attachment* _attachment)
		{
			FrameBufferGNM& frameBuffer = m_frameBuffers[_handle.idx];
			frameBuffer.destroy();
			frameBuffer.create(_num, _attachment);
		}

		void RendererContextGNM::createFrameBuffer(FrameBufferHandle _handle, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat)
		{
			BX_ASSERT(false, "createFrameBuffer with window handle not supported on this platform");
		}

		void RendererContextGNM::destroyFrameBuffer(FrameBufferHandle _handle)
		{
			m_frameBuffers[_handle.idx].destroy();
		}

		void RendererContextGNM::createUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name)
		{
			if (m_uniforms[_handle.idx]) {
				destroyUniform(_handle);
			}
			//uint32_t size = BX_ALIGN_16(g_uniformTypeSize[_type] * _num);
			uint32_t value = g_uniformTypeSize[_type] * _num;
			uint32_t mask = 0xf;
			uint32_t size = ((value)+(mask)) & ((~0) & (~(mask)));

			UniqueBX<uint8_t>& data = m_uniforms[_handle.idx];
			data = UniqueBX<uint8_t>(static_cast<uint8_t*>(BX_ALLOC(g_allocator, size)));
			bx::memSet(data.get(), 0, size);
			m_uniformReg.add(_handle, _name);
		}

		void RendererContextGNM::destroyUniform(UniformHandle _handle)
		{
			m_uniforms[_handle.idx] = nullptr;
			m_uniformReg.remove(_handle);
		}

		void RendererContextGNM::requestScreenShot(FrameBufferHandle _handle, const char* _filePath)
		{
			constexpr int kMainRenderTargetIndex = 0;
			Gnm::RenderTarget* renderTarget = nullptr;

			if (!isValid(_handle)) {
				// Get Previous backbuffer
				renderTarget = &m_backBuffers[(m_currentBackBufferIndex + kDisplayBufferCount - 1) % kDisplayBufferCount].m_rtsi.m_renderTarget;
			}
			else {
				renderTarget = &m_frameBuffers[_handle.idx].m_renderTargets[kMainRenderTargetIndex].m_rtsi.m_renderTarget;
			}


			if (renderTarget) {
				const uint32_t width = renderTarget->getWidth();
				const uint32_t height = renderTarget->getHeight();
				const uint32_t texelByteWidth = renderTarget->getDataFormat().getBytesPerElement();
				const uint32_t rowPitch = texelByteWidth * width;

				UniqueBX<uint8_t> data(static_cast<uint8_t*>(BX_ALLOC(g_allocator, height * rowPitch)));
				if (!data) {
					BX_WARN(false, "requestScreenShot: Failed to allocate necessary memory");
					g_callback->screenShot(_filePath, width, height, rowPitch, nullptr, height * rowPitch, false);
					return;
				}

				GpuAddress::TilingParameters tilingParams;
				int32_t result = tilingParams.initFromRenderTarget(renderTarget, 0);
				if (GpuAddress::kStatusSuccess != result) {
					BX_WARN(false, "requestScreenShot: Failed to initialize tiling parameters, exiting");
					g_callback->screenShot(_filePath, width, height, rowPitch, nullptr, height * rowPitch, false);
					return;
				}

				GpuAddress::detileSurface(data.get(),
					renderTarget->getBaseAddress(),
					&tilingParams);

				bimg::imageSwizzleBgra8(data.get(), rowPitch, width, height, data.get(), rowPitch);
				g_callback->screenShot(_filePath, width, height, rowPitch, data.get(), height * rowPitch, false);
			}
			else {
				g_callback->screenShot(_filePath, 0, 0, 0, nullptr, 0, false);
			}
		}

		void RendererContextGNM::updateViewName(ViewId _id, const char* _name)
		{
			bx::strCopy(&s_viewName[_id][BGFX_CONFIG_MAX_VIEW_NAME_RESERVED]
				, BX_COUNTOF(s_viewName[0]) - BGFX_CONFIG_MAX_VIEW_NAME_RESERVED
				, _name
			);
		}

		void RendererContextGNM::updateUniform(uint16_t _loc, const void* _data, uint32_t _size)
		{
			::memcpy(m_uniforms[_loc].get(), _data, _size);
		}

		void RendererContextGNM::setMarker(const char* _marker, uint16_t _size)
		{
			Gnmx::GnmxGfxContext& gfxc = m_currentInternalRenderContext->m_GFXContext; // TODO GNM - have a more multithreading friendly solution
			gfxc.setMarker(_marker);
		}

		void RendererContextGNM::invalidateOcclusionQuery(OcclusionQueryHandle _handle)
		{
		}

		void RendererContextGNM::setName(Handle _handle, const char* _name, uint16_t _len)
		{
			if (_handle.type == Handle::Texture) {
				TextureGNM& texture = m_textures[_handle.idx];
				texture.m_name = _name;
				//TODO: Add ability to set name in gpu
				m_textures[_handle.idx].registerResource(_name, Gnm::kResourceTypeTextureBaseAddress);

			}
			else if (_handle.type == Handle::Shader) {
				ShaderGNM& shader = m_shaders[_handle.idx];
				shader.m_name = _name;
			}
		}

		// Only updating resolution flags (such as BGFX_RESET_VSYNC) is supported
		void RendererContextGNM::_updateResolutionReset(const Resolution& _resolution) {
			if ((m_resolution.reset & BGFX_RESET_MSAA_MASK) != (_resolution.reset & BGFX_RESET_MSAA_MASK)) {
				// If the option aa level is higher than supported msaa level, reduce it
				m_numSamples = m_msaaSampleInfo->m_numSampleLookup.at(std::min(static_cast<size_t>((_resolution.reset & BGFX_RESET_MSAA_MASK) >> BGFX_RESET_MSAA_SHIFT), m_msaaSampleInfo->m_numSampleLookup.size() - 1));
			}
			m_resolution.reset = _resolution.reset;
		}

		void RendererContextGNM::_enableMSAA(sce::Gnmx::GnmxGfxContext& gfxc, bool enableMSAA) {
			if (enableMSAA) {
				Gnm::DepthEqaaControl eqaaCtl;
				eqaaCtl.init();
				eqaaCtl.setMaxAnchorSamples(m_numSamples);
				eqaaCtl.setPsSampleIterationCount(Gnm::kNumSamples1);
				eqaaCtl.setMaskExportNumSamples(m_numSamples);
				eqaaCtl.setAlphaToMaskSamples(m_numSamples);
				gfxc.setDepthEqaaControl(eqaaCtl);
				gfxc.setAaDefaultSampleLocations(m_numSamples);
			}
			else {
				gfxc.setAaDefaultSampleLocations(Gnm::kNumSamples1);
			}
		}

		void RendererContextGNM::_setupScreenViewportCurrentRenderTarget(sce::Gnmx::GnmxGfxContext& gfxc, uint32_t left, uint32_t top, uint32_t right, uint32_t bottom, float zScale, float zOffset) {
#if BGFX_CONFIG_DEBUG
			renderExtents re = getRenderExtents();
			BX_ASSERT((right <= re.width && bottom <= re.height),
				"Gnm::_setupScreenViewportCurrentRenderTarget: screen extent is larger than target. screen: %d x %d target %d x %d\n",
				right, bottom, re.width, re.height);
#endif
			gfxc.setupScreenViewport(left, top, right, bottom, zScale, zOffset);
		}

		void RendererContextGNM::_setScreenScissor(sce::Gnmx::GnmxGfxContext& gfxc, int32_t left, int32_t top, int32_t right, int32_t bottom) {
#if BGFX_CONFIG_DEBUG
			renderExtents re = getRenderExtents();
			BX_ASSERT((right <= re.width && bottom <= re.height),
				"Gnm::_setScreenScissor: screen extent is larger than target. screen: %d x %d render target %d x %d\n",
				right, bottom, re.width, re.height);
#endif
			gfxc.setScreenScissor(left, top, right, bottom);
		}

		void RendererContextGNM::submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter)
		{
			_updateResolutionReset(_render->m_resolution);

			int64_t timeBegin = bx::getHPCounter();

#if GNM_TODO
			uint32_t frameQueryIdx = UINT32_MAX;

			if (m_timerQuerySupport)
			{
				frameQueryIdx = m_gpuTimer.begin(BGFX_CONFIG_MAX_VIEWS);
			}
#endif

			if (0 < _render->m_iboffset)
			{
				TransientIndexBuffer* ib = _render->m_transientIb;
				m_indexBuffers[ib->handle.idx].update(0, _render->m_iboffset, ib->data);
			}

			if (0 < _render->m_vboffset)
			{
				TransientVertexBuffer* vb = _render->m_transientVb;
				m_vertexBuffers[vb->handle.idx].update(0, _render->m_vboffset, vb->data);
			}

			_render->sort();

			RenderDraw currentState;
			currentState.clear();
			currentState.m_stateFlags = BGFX_STATE_NONE;
			currentState.m_stencil = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);

			RenderBind currentBind;
			currentBind.clear();

			const uint64_t primType = _render->m_debug & BGFX_DEBUG_WIREFRAME ? BGFX_STATE_PT_LINES : 0;
			uint8_t primIndex = uint8_t(primType >> BGFX_STATE_PT_SHIFT);
			PrimInfo prim = s_primInfo[primIndex];

			StatsDataForSubmit stats;

#if GNM_TODO
			Profiler<TimerQueryD3D11> profiler(
				_render
				, m_gpuTimer
				, s_viewName
				, m_timerQuerySupport
			);

			m_occlusionQuery.resolve(_render);
#endif

			if (0 == (_render->m_debug & BGFX_DEBUG_IFH))
			{
				Gnmx::GnmxGfxContext& gfxc = m_currentInternalRenderContext->m_GFXContext; // TODO GNM - have a more multithreading friendly solution
				_submitDraws(gfxc, _render, _clearQuad, currentState, currentBind, primIndex, prim, stats);
			}

			int64_t timeEnd = bx::getHPCounter();
			int64_t frameTime = timeEnd - timeBegin;

			static int64_t min = frameTime;
			static int64_t max = frameTime;
			min = min > frameTime ? frameTime : min;
			max = max < frameTime ? frameTime : max;

#if GNM_TODO // unused variable warnings
			static uint32_t maxGpuLatency = 0;
			static double   maxGpuElapsed = 0.0f;
			double elapsedGpuMs = 0.0;
#endif

#if GNM_TODO
			if (UINT32_MAX != frameQueryIdx)
			{
				m_gpuTimer.end(frameQueryIdx);

				const TimerQueryD3D11::Result& result = m_gpuTimer.m_result[BGFX_CONFIG_MAX_VIEWS];
				double toGpuMs = 1000.0 / double(result.m_frequency);
				elapsedGpuMs = (result.m_end - result.m_begin) * toGpuMs;
				maxGpuElapsed = elapsedGpuMs > maxGpuElapsed ? elapsedGpuMs : maxGpuElapsed;

				maxGpuLatency = bx::uint32_imax(maxGpuLatency, result.m_pending - 1);
			}
#endif

			const int64_t timerFreq = bx::getHPFrequency();

			Stats& perfStats = _render->m_perfStats;
			perfStats.cpuTimeBegin = timeBegin;
			perfStats.cpuTimeEnd = timeEnd;
			perfStats.cpuTimerFreq = timerFreq;
#if GNM_TODO
			const TimerQueryD3D11::Result& result = m_gpuTimer.m_result[BGFX_CONFIG_MAX_VIEWS];
			perfStats.gpuTimeBegin = result.m_begin;
			perfStats.gpuTimeEnd = result.m_end;
			perfStats.gpuTimerFreq = result.m_frequency;
			perfStats.numDraw = stats.statsKeyType[0];
			perfStats.numCompute = stats.statsKeyType[1];
			perfStats.maxGpuLatency = maxGpuLatency;
			::memcpy(perfStats.numPrims, stats.statsNumPrimsRendered, sizeof(perfStats.numPrims));
#endif

#if GNM_TODO
			if (_render->m_debug & (BGFX_DEBUG_IFH | BGFX_DEBUG_STATS))
			{
				_drawDebugStats(_render, _textVideoMemBlitter, stats, minFrameTime, maxFrameTime, maxGpuLatency, maxGpuElapsed);
			}
			else if (_render->m_debug & BGFX_DEBUG_TEXT)
			{
				blit(this, _textVideoMemBlitter, _render->m_textVideoMem);
			}
#endif

			Gnm::submitDone();
		}

		void RendererContextGNM::blitSetup(TextVideoMemBlitter& _blitter)
		{
		}

		void RendererContextGNM::blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices)
		{
		}


		void RendererContextGNM::_initGnmRenderContexts()
		{
			for (int i = 0; i < kNumGnmRenderContexts; ++i)
			{
				// Allocate the CUE heap memory
				m_internalRenderContextGnm[i].m_CueHeap = m_garlicAllocator.allocateUnique<uint8_t>(Gnmx::ConstantUpdateEngine::computeHeapSize(kCueRingEntries), Gnm::kAlignmentOfBufferInBytes, Gnm::kResourceTypeConstantCommandBufferBaseAddress, "cue memory");
				BX_ASSERT(m_internalRenderContextGnm[i].m_CueHeap != nullptr, "Cannot allocate the CUE heap memory");
				// Allocate the draw command buffer
				m_internalRenderContextGnm[i].m_DCBBuffer = m_onionAllocator.allocateUnique<uint8_t>(kDCBSizeInBytes, Gnm::kAlignmentOfBufferInBytes, Gnm::kResourceTypeDrawCommandBufferBaseAddress, "draw cmd buffer");
				BX_ASSERT(m_internalRenderContextGnm[i].m_DCBBuffer != nullptr, "Cannot allocate the draw command buffer memory");
				// Allocate the constants command buffer
				m_internalRenderContextGnm[i].m_CCBBuffer = m_onionAllocator.allocateUnique<uint8_t>(kCCBSizeInBytes, Gnm::kAlignmentOfBufferInBytes, Gnm::kResourceTypeConstantCommandBufferBaseAddress, "const cmd buffer");
				BX_ASSERT(m_internalRenderContextGnm[i].m_CCBBuffer != nullptr, "Cannot allocate the constants command buffer memory");

				m_internalRenderContextGnm[i].m_GFXContext.init(
					m_internalRenderContextGnm[i].m_CueHeap.get(),	//Constant Update Engine Heap pointer
					kCueRingEntries,
					m_internalRenderContextGnm[i].m_DCBBuffer.get(),	//Draw Command Buffer pointer
					kDCBSizeInBytes,
					m_internalRenderContextGnm[i].m_CCBBuffer.get(),	//Constant Command Buffer pointer
					kCCBSizeInBytes);

				m_internalRenderContextGnm[i].m_GPUContextLabel = (volatile uint32_t*)m_onionAllocator.allocate(4, 8, Gnm::kResourceTypeLabel, "GPUContextLabel");
				BX_ASSERT(m_internalRenderContextGnm[i].m_GPUContextLabel, "Failed to allocate GPUContextLabel");
				m_internalRenderContextGnm[i].m_GPUContextLabel[0] = RenderContextState::RenderContextFree;
			}
		}

		void RendererContextGNM::_initBackBuffers()
		{
			// Convenience array used by sceVideoOutRegisterBuffers()
			void* surfaceAddresses[kDisplayBufferCount];

			// Compute the tiling mode for the render target
			Gnm::TileMode tileMode;
			Gnm::DataFormat format = Gnm::kDataFormatB8G8R8A8Unorm;
			int ret = GpuAddress::computeSurfaceTileMode(
				m_featureLevel, // NEO or base
				&tileMode,										// Tile mode pointer
				GpuAddress::kSurfaceTypeColorTargetDisplayable,	// Surface type
				format,											// Surface format
				1);												// Elements per pixel
			BX_ASSERT(ret == SCE_OK, "Unable to compute surface tile mode");

			// Initialize the render target descriptor
			Gnm::RenderTargetSpec spec;
			spec.init();
			spec.m_width = m_resolution.width;
			spec.m_height = m_resolution.height;
			spec.m_pitch = 0;
			spec.m_numSlices = 1;
			spec.m_colorFormat = format;
			spec.m_colorTileModeHint = tileMode;
			spec.m_minGpuMode = m_featureLevel;
			spec.m_numSamples = m_msaaSampleInfo->m_maxSamples;
			spec.m_numFragments = m_msaaSampleInfo->m_maxFragments;
			spec.m_flags.enableCmaskFastClear = 1;
			spec.m_flags.enableFmaskCompression = 1;

			// Initialize all the display buffers
			for (uint32_t i = 0; i < kDisplayBufferCount; ++i)
			{
				DisplayBuffer& displayBuffer = m_displayBuffers[i];
				ret = displayBuffer.m_rtsi.m_renderTarget.init(&spec);
				BX_ASSERT(ret == SCE_OK, "Unable to initialize render target");

				const Gnm::SizeAlign rtSizeAlign = displayBuffer.m_rtsi.m_renderTarget.getColorSizeAlign();
				const Gnm::SizeAlign cmaskSizeAlign = displayBuffer.m_rtsi.m_renderTarget.getCmaskSizeAlign();
				const Gnm::SizeAlign fmaskSizeAlign = displayBuffer.m_rtsi.m_renderTarget.getFmaskSizeAlign();

				displayBuffer.m_gpuBuffer = m_garlicAllocator.allocateUnique<uint8_t>(rtSizeAlign.m_size, rtSizeAlign.m_align, Gnm::ResourceType::kResourceTypeRenderTargetBaseAddress, "displaybuffer rt");
				BX_ASSERT(displayBuffer.m_gpuBuffer != nullptr, "Unable to allocate surface address memory");
				displayBuffer.m_cmaskBuffer = m_garlicAllocator.allocateUnique<uint8_t>(cmaskSizeAlign.m_size, cmaskSizeAlign.m_align, Gnm::ResourceType::kResourceTypeRenderTargetCMaskAddress, "cmask");
				displayBuffer.m_fmaskBuffer = m_garlicAllocator.allocateUnique<uint8_t>(fmaskSizeAlign.m_size, fmaskSizeAlign.m_align, Gnm::ResourceType::kResourceTypeRenderTargetFMaskAddress, "fmask");

				displayBuffer.m_rtsi.m_renderTarget.setFmaskCompressionEnable(true);
				displayBuffer.m_rtsi.m_renderTarget.setCmaskFastClearEnable(true);
				displayBuffer.m_rtsi.m_renderTarget.setAddresses(displayBuffer.m_gpuBuffer.get(), displayBuffer.m_cmaskBuffer.get(), displayBuffer.m_fmaskBuffer.get());
				displayBuffer.m_rtsi.m_numSlices = displayBuffer.m_rtsi.m_renderTarget.getLastArraySliceIndex() - displayBuffer.m_rtsi.m_renderTarget.getBaseArraySliceIndex() + 1;
				displayBuffer.m_displayIndex = i;
			}

			spec.m_numSamples = Gnm::kNumSamples1;
			spec.m_numFragments = Gnm::kNumFragments1;
			spec.m_flags.enableCmaskFastClear = 0;
			spec.m_flags.enableFmaskCompression = 0;

			for (uint32_t i = 0; i < kDisplayBufferCount; ++i) {
				RenderTargetGNM& backBuffer = m_backBuffers[i];
				ret = backBuffer.m_rtsi.m_renderTarget.init(&spec);
				BX_ASSERT(ret == SCE_OK, "Unable to initialize render target");
				const Gnm::SizeAlign rtSizeAlign = backBuffer.m_rtsi.m_renderTarget.getColorSizeAlign();

				backBuffer.create(rtSizeAlign.m_size, videoOutBufferAlignment);
				surfaceAddresses[i] = backBuffer.m_gpuMemory.get();
				backBuffer.m_rtsi.m_renderTarget.setAddresses(surfaceAddresses[i], nullptr, nullptr);
				backBuffer.m_rtsi.m_numSlices = backBuffer.m_rtsi.m_renderTarget.getLastArraySliceIndex() - backBuffer.m_rtsi.m_renderTarget.getBaseArraySliceIndex() + 1;
			}

			SceVideoOutBufferAttribute videoOutBufferAttribute;
			sceVideoOutSetBufferAttribute(
				&videoOutBufferAttribute,
				SCE_VIDEO_OUT_PIXEL_FORMAT_B8_G8_R8_A8_SRGB,
				SCE_VIDEO_OUT_TILING_MODE_TILE,
				SCE_VIDEO_OUT_ASPECT_RATIO_16_9,
				m_backBuffers[0].m_rtsi.m_renderTarget.getWidth(),
				m_backBuffers[0].m_rtsi.m_renderTarget.getHeight(),
				m_backBuffers[0].m_rtsi.m_renderTarget.getPitch());

			// Register the buffers to the slot: [0..kDisplayBufferCount-1]
			ret = sceVideoOutRegisterBuffers(
				m_videoOutHandle,
				0, // Start index
				surfaceAddresses,
				kDisplayBufferCount,
				&videoOutBufferAttribute);

			BX_ASSERT(ret >= SCE_OK, "Unable to register buffer");
		}

		void RendererContextGNM::_initDepthTarget()
		{
			// Compute the tiling mode for the depth buffer
			Gnm::DataFormat depthFormat = Gnm::DataFormat::build(kZFormat);
			Gnm::TileMode depthTileMode;
			int ret = GpuAddress::computeSurfaceTileMode(
				m_featureLevel, // NEO or Base
				&depthTileMode,									// Tile mode pointer
				GpuAddress::kSurfaceTypeDepthOnlyTarget,		// Surface type
				depthFormat,									// Surface format
				1);												// Elements per pixel
			BX_ASSERT(ret == SCE_OK, "Unable to compute surface tile mode for depth target");

			// Initialize the depth buffer descriptor
			Gnm::SizeAlign stencilSizeAlign;
			Gnm::SizeAlign htileSizeAlign;

			Gnm::DepthRenderTargetSpec spec;
			spec.init();
			spec.m_width = m_resolution.width;
			spec.m_height = m_resolution.height;
			spec.m_pitch = 0;
			spec.m_numSlices = 1;
			spec.m_zFormat = depthFormat.getZFormat();
			spec.m_stencilFormat = kStencilFormat;
			spec.m_tileModeHint = depthTileMode;
			spec.m_minGpuMode = m_featureLevel;
			spec.m_numFragments = m_msaaSampleInfo->m_maxFragments;
			spec.m_flags.enableHtileAcceleration = kHtileEnabled ? 1 : 0;

			ret = m_depthTarget.m_depthRenderTarget.init(&spec);
			BX_ASSERT(ret == SCE_OK, "Unable to initialize depth target");

			Gnm::SizeAlign depthTargetSizeAlign = m_depthTarget.m_depthRenderTarget.getZSizeAlign();

			m_depthTarget.create(depthTargetSizeAlign.m_size, depthTargetSizeAlign.m_align, kHtileEnabled, kStencilFormat);
		}

		// This _waitGPUIdleBeforeShutdown() function is reference - not currently used:
		void RendererContextGNM::_waitGPUIdleBeforeShutdown()
		{
			// Wait for the GPU to be idle before deallocating its resources
			for (uint32_t i = 0; i < kNumGnmRenderContexts; ++i)
			{
				int safetyCounter = 1000;

				if (m_internalRenderContextGnm[i].m_GPUContextLabel)
				{
					while (m_internalRenderContextGnm[i].m_GPUContextLabel[0] != RenderContextState::RenderContextFree && safetyCounter-- > 0)
					{
						sceKernelUsleep(1000);
					}
				}
			}
		}

		void RendererContextGNM::_clearMemoryToUints(sce::Gnmx::GnmxGfxContext& gfxc, const sce::Gnm::RenderTarget* renderTarget, void* dest, uint32_t destUints, uint32_t* source, uint32_t srcUints) {
			BX_ASSERT(&gfxc == &m_currentInternalRenderContext->m_GFXContext, "Mismatch in gfxc");
			m_currentInternalRenderContext->withRenderTarget(0, renderTarget, [this, &gfxc, dest, destUints, source, srcUints]() {

				const bool srcUintsIsPowerOfTwo = (srcUints & (srcUints - 1)) == 0;

				gfxc.setCsShader(srcUintsIsPowerOfTwo ? sComputeSetUintFastShader.m_xxShader : sComputeSetUintShader.m_xxShader,
					srcUintsIsPowerOfTwo ? &sComputeSetUintFastShader.m_offsetsTable : &sComputeSetUintShader.m_offsetsTable);

				Gnm::Buffer destinationBuffer;
				destinationBuffer.initAsDataBuffer(dest, sce::Gnm::kDataFormatR32Uint, destUints);
				destinationBuffer.setResourceMemoryType(sce::Gnm::kResourceMemoryTypeGC);
				gfxc.setRwBuffers(sce::Gnm::kShaderStageCs, 0, 1, &destinationBuffer);

				Gnm::Buffer sourceBuffer;
				sourceBuffer.initAsDataBuffer(source, sce::Gnm::kDataFormatR32Uint, srcUints);
				sourceBuffer.setResourceMemoryType(sce::Gnm::kResourceMemoryTypeRO);
				gfxc.setBuffers(sce::Gnm::kShaderStageCs, 0, 1, &sourceBuffer);

				struct Constants
				{
					uint32_t m_destUints;
					uint32_t m_srcUints;
				};
				Constants* constants = allocateFromCommandBuffer<Constants>(gfxc, 1, sce::Gnm::kEmbeddedDataAlignment4);
				constants->m_destUints = destUints;
				constants->m_srcUints = srcUints - (srcUintsIsPowerOfTwo ? 1 : 0);
				sce::Gnm::Buffer constantBuffer;
				constantBuffer.initAsConstantBuffer(constants, sizeof(*constants));
				gfxc.setConstantBuffers(Gnm::kShaderStageCs, 0, 1, &constantBuffer);

				gfxc.dispatch((destUints + sce::Gnm::kThreadsPerWavefront - 1) / sce::Gnm::kThreadsPerWavefront, 1, 1);

				_synchronizeComputeToGraphics(&gfxc.m_dcb);
				});
		}


		// The buffer sizes need to be multiples of 16 and allocated using Gnm::kAlignmentOfBufferInBytes alignment.
		// When you use the copy it is important to create some temporary Gnm : Buffer objects that have sce : Gnm::kDataFormatR32G32B32A32Uint(aka uint4)
		// Set the number of elements correctly as number of uint4s because that's what the compute shader expects. 
		// See the cs_copybuffer_c.pssl for the shader code and look at _clearMemoryToUints for a related example.
		void RendererContextGNM::_copyBuffer(sce::Gnmx::GnmxGfxContext& gfxc, const Gnm::Buffer* bufferDst, const Gnm::Buffer* bufferSrc)
		{
			gfxc.setBuffers(Gnm::kShaderStageCs, 0, 1, bufferSrc);
			gfxc.setRwBuffers(Gnm::kShaderStageCs, 0, 1, bufferDst);

			gfxc.setCsShader(sComputeCopyBuffer.m_xxShader, &sComputeCopyBuffer.m_offsetsTable);

			gfxc.dispatch((bufferDst->getNumElements() + Gnm::kThreadsPerWavefront - 1) / Gnm::kThreadsPerWavefront, 1, 1);

			_synchronizeComputeToGraphics(&gfxc.m_dcb);
		}

		void RendererContextGNM::_synchronizeComputeToGraphics(sce::Gnmx::GnmxDrawCommandBuffer* dcb)
		{
			volatile uint64_t* label = allocateFromCommandBuffer<volatile uint64_t>(*dcb, 1, sce::Gnm::kEmbeddedDataAlignment8);
			*label = 0x0; // set the memory to have the val 0
			dcb->writeAtEndOfShader(sce::Gnm::kEosCsDone, (void*)(label), 0x1); // tell the CP to write a 1 into the memory only when all compute shaders have finished
			dcb->waitOnAddress((void*)(label), 0xffffffff, sce::Gnm::kWaitCompareFuncEqual, 0x1); // tell the CP to wait until the memory has the val 1
			dcb->flushShaderCachesAndWait(sce::Gnm::kCacheActionWriteBackAndInvalidateL1andL2, 0, sce::Gnm::kStallCommandBufferParserDisable); // tell the CP to flush the L1$ and L2$
		}

		void RendererContextGNM::_clearRenderTargetPartial(sce::Gnmx::GnmxGfxContext& gfxc, const RenderTargetWithSliceInfo* rtsi, const Rect* _prect, const float colorVec[4]) {
			gfxc.pushMarker("_clearRenderTargetPartial");

			setBlendState(gfxc, 0);

			sce::Gnm::DbRenderControl dbRenderControl;
			dbRenderControl.init();
			gfxc.setDbRenderControl(dbRenderControl);

			Gnm::DepthStencilControl depthControl;
			depthControl.init(); // default always pass
			gfxc.setDepthStencilControl(depthControl);

			Gnm::StencilOpControl stencilOpControl;
			stencilOpControl.init();
			gfxc.setStencilOpControl(stencilOpControl);

			//Actually clear it
			BX_ASSERT(sPixelClearShader.m_xxShader != nullptr, "sPixelClearShader.m_xxShader should be non-null");
			gfxc.setRenderTargetMask(0xF); // RGBA of render target 0

			BX_ASSERT(&gfxc == &m_currentInternalRenderContext->m_GFXContext, "Mismatch in gfxc");
			m_currentInternalRenderContext->withRenderTarget(0, &rtsi->m_renderTarget, [&gfxc, &colorVec, _prect, this]() {
				gfxc.setPsShader(sPixelClearShader.m_xxShader, &sPixelClearShader.m_offsetsTable);
				float* constantBuffer = allocateFromCommandBuffer<float>(gfxc, 4, sce::Gnm::kEmbeddedDataAlignment4);
				for (int i = 0; i < 4; ++i)
				{
					constantBuffer[i] = colorVec[i];
				}
				sce::Gnm::Buffer buffer;
				buffer.initAsConstantBuffer(constantBuffer, sizeof(float) * 4);
				buffer.setResourceMemoryType(sce::Gnm::kResourceMemoryTypeRO); // it's a constant buffer, so read-only is OK
				gfxc.setConstantBuffers(sce::Gnm::kShaderStagePs, 0, 1, &buffer);

				BX_ASSERT(_prect != nullptr, "_prect must be non NULL for _clearRenderTargetPartial()");

				this->_setupScreenViewportCurrentRenderTarget(gfxc, _prect->m_x, _prect->m_y, _prect->m_x + _prect->m_width, _prect->m_y + _prect->m_height, 1.0f, 0.0f);
				gfxc.setScreenScissor(_prect->m_x, _prect->m_y, _prect->m_x + _prect->m_width, _prect->m_y + _prect->m_height);

				sce::Gnmx::renderFullScreenQuad(&gfxc);

				});

			gfxc.setScreenScissor(s_currentScissor.m_x, s_currentScissor.m_y, s_currentScissor.m_x + s_currentScissor.m_width, s_currentScissor.m_y + s_currentScissor.m_height);
			gfxc.popMarker();
		}

		void RendererContextGNM::_clearRenderTarget(sce::Gnmx::GnmxGfxContext& gfxc, const RenderTargetWithSliceInfo* rtsi, uint32_t* source, uint32_t sourceUints) {
			_clearMemoryToUints(gfxc, &rtsi->m_renderTarget, rtsi->m_renderTarget.getBaseAddress(), rtsi->m_renderTarget.getSliceSizeInBytes() * rtsi->m_numSlices / sizeof(uint32_t), source, sourceUints);
		}

		void RendererContextGNM::_clearRenderTarget(sce::Gnmx::GnmxGfxContext& gfxc, const RenderTargetWithSliceInfo* rtsi, uint32_t clearColorRGBA) {
			sce::Vectormath::Scalar::Aos::Vector4 colorVec((clearColorRGBA >> 24) & 0xff, (clearColorRGBA >> 16) & 0xff, (clearColorRGBA >> 8) & 0xff, clearColorRGBA & 0xff);
			colorVec *= (1.0f / 255.0f);
			uint32_t* source = allocateFromCommandBuffer<uint32_t>(gfxc, 4, sce::Gnm::kEmbeddedDataAlignment4);
			uint32_t dwords = 0;
			DataFormatInterpreter::dataFormatEncoder(source, &dwords, (DataFormatInterpreter::Reg32*)&colorVec, rtsi->m_renderTarget.getDataFormat());
			_clearRenderTarget(gfxc, rtsi, source, dwords);
		}

		void RendererContextGNM::_clearRenderTarget(sce::Gnmx::GnmxGfxContext& gfxc, const RenderTargetWithSliceInfo* rtsi, const float colorVec[4]) {
			uint32_t* source = allocateFromCommandBuffer<uint32_t>(gfxc, 4, sce::Gnm::kEmbeddedDataAlignment4);
			uint32_t dwords = 0;
			DataFormatInterpreter::dataFormatEncoder(source, &dwords, (DataFormatInterpreter::Reg32*)colorVec, rtsi->m_renderTarget.getDataFormat());
			_clearRenderTarget(gfxc, rtsi, source, dwords);
		}

		void RendererContextGNM::_clearCmaskSurface(sce::Gnmx::GnmxGfxContext& gfxc, const RenderTargetWithSliceInfo* rtsi) {
			SCE_GNM_ASSERT_MSG(rtsi->m_renderTarget.getCmaskAddress() != NULL, "target (0x%p) has no CMASK surface.", target);
			gfxc.triggerEvent(Gnm::kEventTypeFlushAndInvalidateCbMeta);
			uint32_t clearValue = 0x00000000;
			if (rtsi->m_renderTarget.getDccCompressionEnable() && rtsi->m_renderTarget.getCmaskFastClearEnable())
			{
				if (rtsi->m_renderTarget.getFmaskCompressionEnable())
					clearValue = 0xcccccccc; // CMask Fast Clear is disabled, FMask Compression Enabled
				else
					clearValue = 0xffffffff; // CMask Fast Clear is disabled.
			}

			uint32_t* source = allocateFromCommandBuffer<uint32_t>(gfxc, 1, sce::Gnm::kEmbeddedDataAlignment4);

			*source = clearValue;
			_clearMemoryToUints(gfxc, &rtsi->m_renderTarget, rtsi->m_renderTarget.getCmaskAddress(), rtsi->m_renderTarget.getCmaskSliceSizeInBytes() * rtsi->m_numSlices / sizeof(uint32_t), source, 1);
		}

		void RendererContextGNM::_setupDepthStencilClearParams(sce::Gnmx::GnmxGfxContext& gfxc, const Clear& _clear)
		{
			const bool clearDepth = (BGFX_CLEAR_DEPTH & _clear.m_flags) != 0;
			const bool clearStencil = (BGFX_CLEAR_STENCIL & _clear.m_flags) != 0;

			sce::Gnm::DbRenderControl dbRenderControl;
			dbRenderControl.init();
			dbRenderControl.setDepthClearEnable(clearDepth);
			dbRenderControl.setStencilClearEnable(clearStencil);
			gfxc.setDbRenderControl(dbRenderControl);

			Gnm::DepthStencilControl depthControl;
			depthControl.init();
			if (clearDepth)
			{
				depthControl.setDepthControl(Gnm::kDepthControlZWriteEnable, Gnm::kCompareFuncAlways);
			}
			else
			{
				depthControl.setDepthControl(Gnm::kDepthControlZWriteDisable, Gnm::kCompareFuncNever);
			}
			if (clearStencil)
			{
				depthControl.setStencilFunction(Gnm::kCompareFuncAlways);
			}
			else
			{
				depthControl.setStencilFunction(Gnm::kCompareFuncNever);
			}
			depthControl.setDepthEnable(clearDepth);
			depthControl.setStencilEnable(clearStencil);
			gfxc.setDepthStencilControl(depthControl);

			if (clearStencil)
			{
				Gnm::StencilOpControl stencilOpControl;
				stencilOpControl.init();
				stencilOpControl.setStencilOps(Gnm::kStencilOpReplaceTest, Gnm::kStencilOpReplaceTest, Gnm::kStencilOpReplaceTest);
				gfxc.setStencilOpControl(stencilOpControl);
				const Gnm::StencilControl stencilControl = { 0xff, 0xff, 0xff, 0xff };
				gfxc.setStencil(stencilControl);
				gfxc.setStencilClearValue(_clear.m_stencil);
			}
			if (clearDepth) {
				gfxc.setDepthClearValue(_clear.m_depth);
			}
		}

		void RendererContextGNM::_clearDepthStencilBuffer(sce::Gnmx::GnmxGfxContext& gfxc, const Gnm::DepthRenderTarget* depthTarget, const Rect* _prect, const Clear& _clear)
		{
			gfxc.pushMarker("clearDepthAndStencilBuffer No HTile");

			_setupDepthStencilClearParams(gfxc, _clear);

			//Actually clear it
			BX_ASSERT(sPixelClearShader.m_xxShader != nullptr, "sPixelClearShader.m_xxShader should be non-null");
			gfxc.setRenderTargetMask(0x0);
			gfxc.setPsShader(sPixelClearShader.m_xxShader, &sPixelClearShader.m_offsetsTable);
			float* constantBuffer = allocateFromCommandBuffer<float>(gfxc, 4, sce::Gnm::kEmbeddedDataAlignment4);
			constantBuffer[0] = constantBuffer[1] = constantBuffer[2] = constantBuffer[3] = 0.0f;
			sce::Gnm::Buffer buffer;
			buffer.initAsConstantBuffer(constantBuffer, sizeof(float) * 4);
			buffer.setResourceMemoryType(sce::Gnm::kResourceMemoryTypeRO); // it's a constant buffer, so read-only is OK
			gfxc.setConstantBuffers(sce::Gnm::kShaderStagePs, 0, 1, &buffer);

			const uint32_t width = depthTarget->getWidth();
			const uint32_t height = depthTarget->getHeight();
			gfxc.setScreenScissor(0, 0, width, height);
			if (_prect == nullptr)
			{
				_setupScreenViewportCurrentRenderTarget(gfxc, 0, 0, depthTarget->getWidth(), depthTarget->getHeight(), 1.0f, 0.0f);
			}
			else
			{
				Rect depthRect{ 0, 0, (uint16_t)depthTarget->getWidth() , (uint16_t)depthTarget->getHeight() };
				depthRect.intersect(*_prect);
				_setupScreenViewportCurrentRenderTarget(gfxc, depthRect.m_x, depthRect.m_y, depthRect.m_x + depthRect.m_width, depthRect.m_y + depthRect.m_height, 1.0f, 0.0f);
			}
			const uint32_t firstSlice = depthTarget->getBaseArraySliceIndex();
			const uint32_t lastSlice = depthTarget->getLastArraySliceIndex();
			sce::Gnm::DepthRenderTarget dtCopy = *depthTarget;


			for (uint32_t iSlice = firstSlice; iSlice <= lastSlice; ++iSlice)
			{
				dtCopy.setArrayView(iSlice, iSlice);
				BX_ASSERT(&gfxc == &m_currentInternalRenderContext->m_GFXContext, "Mismatch in gfxc");
				m_currentInternalRenderContext->withDepthRenderTarget(&dtCopy, [&gfxc]() {
					sce::Gnmx::renderFullScreenQuad(&gfxc);
					});
			}
			gfxc.setScreenScissor(s_currentScissor.m_x, s_currentScissor.m_y, s_currentScissor.m_x + s_currentScissor.m_width, s_currentScissor.m_y + s_currentScissor.m_height);


			gfxc.setRenderTargetMask(0xF);

			sce::Gnm::DbRenderControl defaultdbRenderControl;
			defaultdbRenderControl.init();
			gfxc.setDbRenderControl(defaultdbRenderControl);

			gfxc.popMarker();
		}

		void RendererContextGNM::_submitDraws(Gnmx::GnmxGfxContext& gfxc, Frame* _render, ClearQuad& _clearQuad, RenderDraw& currentState, RenderBind& currentBind, uint8_t primIndex, PrimInfo& prim, StatsDataForSubmit& stats)
		{
			bool wireframe = !!(_render->m_debug & BGFX_DEBUG_WIREFRAME);

			const bool hmdEnabled = false;
			s_viewState.reset(_render/*, hmdEnabled*/);

			uint16_t programIdx = kInvalidHandle;
			SortKey key;
			uint16_t view = UINT16_MAX;
			FrameBufferHandle fbh = { BGFX_CONFIG_MAX_FRAME_BUFFERS };

			bool wasCompute = false;
			bool viewHasScissor = false;
			Rect viewScissorRect;
			viewScissorRect.clear();

			bgfx::BlitState bs(_render);

			// Beginning of render frame
			_beginRenderFrame(gfxc);

			if (m_renderContextFlowState != RenderContextFlowState::RenderFrame)
			{
				return;
			}

			gfxc.setPrimitiveType(prim.m_type);

			// reset the framebuffer to be the backbuffer; depending on the swap effect,
			// if we don't do this we'll only see one frame of output and then nothing
			setFrameBuffer(gfxc, BGFX_INVALID_HANDLE, m_rtMsaa, false);

			bool viewRestart = false;
			uint8_t restartState = 0;
			s_viewState.m_rect = _render->m_view[0].m_rect;

			std::unique_ptr<CommandBufferConstantBuffer> programCb;

			int32_t numItems = _render->m_numRenderItems;
			for (int32_t item = 0, restartItem = numItems; item < numItems || restartItem < numItems;)
			{
				const uint64_t encodedKey = _render->m_sortKeys[item];
				const bool isCompute = key.decode(encodedKey, _render->m_viewRemap);
				stats.statsKeyType[isCompute]++;

				const bool viewChanged = 0
					|| key.m_view != view
					|| item == numItems
					;

				const uint32_t itemIdx = _render->m_sortValues[item];
				const RenderItem& renderItem = _render->m_renderItem[itemIdx];
				const RenderBind& renderBind = _render->m_renderItemBind[itemIdx];
				++item;

				if (viewChanged)
				{
					if (1 == restartState)
					{
						restartState = 2;
						item = restartItem;
						restartItem = numItems;
						view = UINT16_MAX;
						continue;
					}

					view = key.m_view;
					programIdx = kInvalidHandle;

					if (_render->m_view[view].m_fbh.idx != fbh.idx)
					{
						fbh = _render->m_view[view].m_fbh;
						// If previous FrameBuffer is resolved, reset primitive type
						if (setFrameBuffer(gfxc, fbh)) {
							prim = s_primInfo[Topology::Count]; // Force primitive type update after clear quad.
						}
					}

					/*viewRestart = ((BGFX_VIEW_STEREO == (_render->m_view[view].m_flags & BGFX_VIEW_STEREO)));*/
					viewRestart &= hmdEnabled;

					gfxc.popMarker();
					s_view = s_viewName[view];
					gfxc.pushMarker(s_view);
#ifdef DEBUG_GAMEFACE
					// BBI-NOTE (dgalloway) Gameface renders are elusive so for debugging with Razor
					// we need this code to detect a Gameface view and do a GPU capture
					static int count = 0;
					static int volatile enable = 0;

					// BBI-NOTE set enable to true in debugger to capture several frames of captures to c:\razor\GameFace\
						// Increase count if more are desired
					if (enable && bx::strFind(s_view, "Gameface") != NULL)
					{
						std::string count_string = std::to_string(count);
						if (count < 3 && !sce::Gnm::isCaptureInProgress()) {
							std::string filename = "/host/c:\\razor\\gameface\\PS4GPUgameface";
							filename = filename + count_string + ".rzrx";
							count++;
							sce::Gnm::CaptureStatus estatus = sce::Gnm::triggerCapture(filename.c_str());
						}
					}
#endif
					if (viewRestart)
					{
						if (0 == restartState)
						{
							restartState = 1;
							restartItem = item - 1;
						}

						restartState &= 1;
					}

#if GNM_TODO
					if (item > 1)
					{
						profiler.end();
					}
					profiler.begin(view);
#endif

					s_viewState.m_rect = _render->m_view[view].m_rect;

					if (viewRestart)
					{
						s_viewState.m_rect.m_x = 0;
						s_viewState.m_rect.m_width /= 2;
					}

					const Rect& scissorRect = _render->m_view[view].m_scissor;
					viewHasScissor = !scissorRect.isZero();
					viewScissorRect = viewHasScissor ? scissorRect : s_viewState.m_rect;

					// The z-scale and z-offset values are used to specify the transformation
					// from clip-space to screen-space
					_setupScreenViewportCurrentRenderTarget(
						gfxc,
						s_viewState.m_rect.m_x,
						s_viewState.m_rect.m_y,
						s_viewState.m_rect.m_x + s_viewState.m_rect.m_width,
						s_viewState.m_rect.m_y + s_viewState.m_rect.m_height,
						1.0f,
						0.0f);

					_setScreenScissor(
						gfxc,
						viewScissorRect.m_x,
						viewScissorRect.m_y,
						viewScissorRect.m_x + viewScissorRect.m_width,
						viewScissorRect.m_y + viewScissorRect.m_height);

					Clear& clr = _render->m_view[view].m_clear;

					if (BGFX_CLEAR_NONE != (clr.m_flags & BGFX_CLEAR_MASK))
					{
						clearQuad(gfxc, _clearQuad, s_viewState.m_rect, clr, _render->m_colorPalette);
						prim = s_primInfo[Topology::Count]; // Force primitive type update after clear quad.
					}

					submitBlit(bs, view);
				}

				if (isCompute)
				{
					_handleCompute(wasCompute, _render, renderBind, view, renderItem, key, programIdx);
					continue;
				}

				bool resetState = viewChanged || wasCompute;

				if (wasCompute)
				{
					programIdx = kInvalidHandle;
					m_currentProgram = NULL;

#if GNM_TODO
					invalidateCompute();
#endif
				}

				const RenderDraw& draw = renderItem.draw;

#if GNM_TODO
				const bool hasOcclusionQuery = 0 != (draw.m_stateFlags & BGFX_STATE_INTERNAL_OCCLUSION_QUERY);
				{
					const bool occluded = true
						&& isValid(draw.m_occlusionQuery)
						&& !hasOcclusionQuery
						&& !isVisible(_render, draw.m_occlusionQuery, 0 != (draw.m_submitFlags & BGFX_SUBMIT_INTERNAL_OCCLUSION_VISIBLE))
						;

					if (occluded
						|| _render->m_frameCache.isZeroArea(viewScissorRect, draw.m_scissor))
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
#endif

				const uint64_t newFlags = draw.m_stateFlags;
				uint64_t changedFlags = currentState.m_stateFlags ^ draw.m_stateFlags;
				currentState.m_stateFlags = newFlags;

				const uint64_t newStencil = draw.m_stencil;
				uint64_t changedStencil = currentState.m_stencil ^ draw.m_stencil;
				currentState.m_stencil = newStencil;

				if (resetState)
				{
					wasCompute = false;

					currentState.clear();
					currentState.m_scissor = !draw.m_scissor;
					changedFlags = BGFX_STATE_MASK;
					changedStencil = packStencil(BGFX_STENCIL_MASK, BGFX_STENCIL_MASK);
					currentState.m_stateFlags = newFlags;
					currentState.m_stencil = newStencil;

					currentBind.clear();

					setBlendState(gfxc, newFlags);
					setDepthStencilState(gfxc, newFlags, packStencil(BGFX_STENCIL_DEFAULT, BGFX_STENCIL_DEFAULT));

					const uint64_t pt = newFlags & BGFX_STATE_PT_MASK;
					primIndex = uint8_t(pt >> BGFX_STATE_PT_SHIFT);
				}

				if (prim.m_type != s_primInfo[primIndex].m_type)
				{
					prim = s_primInfo[primIndex];
					gfxc.setPrimitiveType(prim.m_type);
				}

				uint16_t scissor = draw.m_scissor;
				if (currentState.m_scissor != scissor)
				{
					currentState.m_scissor = scissor;

					_setScissor(gfxc, _render, viewScissorRect, scissor);
				}

				if ((BGFX_GNM_DEPTH_STENCIL_MASK & changedFlags) || changedStencil)
				{
					setDepthStencilState(gfxc, newFlags, newStencil);
				}

				if ((BGFX_GNM_BLEND_STATE_MASK & changedFlags) || (currentState.m_rgba != draw.m_rgba))
				{
					setBlendState(gfxc, newFlags, draw.m_rgba);
					currentState.m_rgba = draw.m_rgba;
				}

				if ((BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_RGB) & changedFlags) {


					uint32_t writeRGBAMask = (0
						| (newFlags & BGFX_STATE_WRITE_R ? 0x11111111 : 0)
						| (newFlags & BGFX_STATE_WRITE_G ? 0x22222222 : 0)
						| (newFlags & BGFX_STATE_WRITE_B ? 0x44444444 : 0)
						| (newFlags & BGFX_STATE_WRITE_A ? 0x88888888 : 0)
						);

					gfxc.setRenderTargetMask(writeRGBAMask & m_MRTmask);
				}

				if ((0
					| BGFX_STATE_CULL_MASK
					| BGFX_STATE_ALPHA_REF_MASK
					| BGFX_STATE_PT_MASK
					| BGFX_STATE_POINT_SIZE_MASK
					| BGFX_STATE_MSAA
					| BGFX_STATE_LINEAA
					| BGFX_STATE_CONSERVATIVE_RASTER
					) & changedFlags)
				{
					if ((0
						| BGFX_STATE_CULL_MASK
						| BGFX_STATE_MSAA
						| BGFX_STATE_LINEAA
						| BGFX_STATE_CONSERVATIVE_RASTER
						) & changedFlags)
					{
						setRasterizerState(gfxc, newFlags, wireframe);
					}

					if (BGFX_STATE_ALPHA_REF_MASK & changedFlags)
					{
						uint32_t ref = (newFlags & BGFX_STATE_ALPHA_REF_MASK) >> BGFX_STATE_ALPHA_REF_SHIFT;
						s_viewState.m_alphaRef = ref / 255.0f;
					}

					const uint64_t pt = newFlags & BGFX_STATE_PT_MASK;
					primIndex = uint8_t(pt >> BGFX_STATE_PT_SHIFT);
					if (prim.m_type != s_primInfo[primIndex].m_type)
					{
						prim = s_primInfo[primIndex];
						gfxc.setPrimitiveType(prim.m_type);
					}
				}

				bool programChanged = false;
				bool constantsChanged = draw.m_uniformBegin < draw.m_uniformEnd;
				rendererUpdateUniforms(this, _render->m_uniformBuffer[draw.m_uniformIdx], draw.m_uniformBegin, draw.m_uniformEnd);

				if (key.m_program.idx != programIdx)
				{
					programIdx = key.m_program.idx;

					_setProgram(gfxc, programIdx);

					programCb = std::make_unique<CommandBufferConstantBuffer>(gfxc, m_program[programIdx]);

					programChanged =
						constantsChanged = true;
				}

				if (kInvalidHandle != programIdx)
				{
					if (!programCb)
					{
						BX_ASSERT(false, "Constant buffers not created for this program");
						continue;
					}

					ProgramGNM& program = m_program[programIdx];

					if (constantsChanged)
					{
						UniformBuffer* vcb = program.m_vsh->m_constantBuffer;
						if (NULL != vcb)
						{
							commit(*vcb, *programCb.get());
						}

						if (NULL != program.m_fsh) {
							UniformBuffer* fcb = program.m_fsh->m_constantBuffer;
							if (NULL != fcb)
							{
								commit(*fcb, *programCb.get());
							}
						}
					}

					s_viewState.setPredefined<4>(this, view, program, _render, draw, *programCb.get());

					if (constantsChanged
						|| program.m_numPredefined > 0)
					{
						commitShaderConstants(*programCb.get());
					}
				}

				_bindTextures(_render, currentBind, renderBind, programChanged);

				if (programChanged || hasVertexStreamChanged(currentState, draw))
				{
					_setVertexLayoutAndBindVertexBuffers(gfxc, currentState, draw, programIdx);
				}

				if (currentState.m_indexBuffer.idx != draw.m_indexBuffer.idx)
				{
					currentState.m_indexBuffer = draw.m_indexBuffer;

					uint16_t handle = draw.m_indexBuffer.idx;
					if (kInvalidHandle != handle)
					{
						IndexBufferGNM& ib = m_indexBuffers[handle];
						if (ib.m_flags & BGFX_BUFFER_INDEX32)
						{
							gfxc.setIndexSize(Gnm::kIndexSize32);
						}
						else
						{
							gfxc.setIndexSize(Gnm::kIndexSize16);
						}
					}
				}

				if (0 != currentState.m_streamMask)
				{
#if GNM_TODO
					if (hasOcclusionQuery)
					{
						m_occlusionQuery.begin(_render, draw.m_occlusionQuery);
					}
#endif

					_drawIndexed(gfxc, currentState, draw, primIndex, prim, stats);

#if GNM_TODO
					if (hasOcclusionQuery)
					{
						m_occlusionQuery.end();
					}
#endif
				}
			}

#if GNM_TODO
			if (wasCompute)
			{
				invalidateCompute();
			}
#endif

			submitBlit(bs, BGFX_CONFIG_MAX_VIEWS);

#if GNM_TODO
			if (0 < _render->m_numRenderItems)
			{
				if (0 != (m_resolution.reset & BGFX_RESET_FLUSH_AFTER_RENDER))
				{
					m_deviceCtx->Flush();
				}

				stats.captureElapsed = -bx::getHPCounter();
				capture();
				stats.captureElapsed += bx::getHPCounter();

				profiler.end();
			}
#endif
			// set FrameBuffer to nothing once complete all draw calls
			// this ensures that any framebuffer currently set can handle
			// msaa resolution if needed.
			// This fixes an issue where we were getting items flickering
			// with msaa enabled due to the fact they were not resolving.
			setFrameBuffer(gfxc, BGFX_INVALID_HANDLE, m_rtMsaa, false);

			BX_ASSERT(m_renderContextFlowState == RenderContextFlowState::RenderFrame, "Expected m_renderContextFlowState == RenderContextFlowState::RenderFrame");
			m_renderContextFlowState = RenderContextFlowState::SubmitAndFlip;
		}

		void RendererContextGNM::_beginRenderFrame(Gnmx::GnmxGfxContext& gfxc)
		{
			if (m_renderContextFlowState == RenderContextFlowState::BeginRenderFrame)
			{
				// Wait until the context label has been written to make sure that the
				// GPU finished parsing the command buffers before overwriting them
				while (m_currentInternalRenderContext->m_GPUContextLabel[0] != RenderContextState::RenderContextFree)
				{
					// Wait for the EOP event
					SceKernelEvent eopEvent;
					int count;
					int ret = sceKernelWaitEqueue(m_eopEventQueue, &eopEvent, 1, &count, NULL);
					if (ret != SCE_OK)
					{
						bx::debugPrintf("sceKernelWaitEqueue failed: 0x%08X\n", ret);
					}
				}

				// Reset the flip GPU label
				m_currentInternalRenderContext->m_GPUContextLabel[0] = RenderContextState::RenderContextInUse;

				// Reset the graphical context and initialize the hardware state
				gfxc.reset();
				gfxc.initializeDefaultHardwareState();

				// In a real-world scenario, any rendering of off-screen buffers or
				// other compute related processing would go here

				// The waitUntilSafeForRendering stalls the GPU until the scan-out
				// operations on the current display buffer have been completed.
				// This command is not blocking for the CPU.
				//
				// NOTE
				// This command should be used right before writing the display buffer.
				//
				gfxc.waitUntilSafeForRendering(m_videoOutHandle, m_displayBuffers[m_currentBackBufferIndex].m_displayIndex);

				m_garlicAllocator.releaseAllMarked();
				m_onionAllocator.releaseAllMarked();

				// Clear cmask.
				// Clear color doesn't set up yet, so clear without specific color
				// Because of texture tiling, partially clearing cmask is hard, so clear entire cmask in the beginning,
				// and set up clear color in clear()
				_clearCmaskSurface(gfxc, &m_displayBuffers[m_currentBackBufferIndex].m_rtsi);
				for (int i = 0; i < BGFX_CONFIG_MAX_FRAME_BUFFERS; ++i) {
					if (m_frameBuffers[i].m_num > 0 && m_frameBuffers[i].m_frameBufferMSAA) {
						for (int j = 0; j < m_frameBuffers[i].m_num; ++j) {
							if (m_frameBuffers[i].m_intermediateRenderTargets[j].m_rtsi.m_renderTarget.getWidth() != 0) {
								_clearCmaskSurface(gfxc, &m_frameBuffers[i].m_intermediateRenderTargets[j].m_rtsi);
							}
						}
					}
				}

				// Setup the viewport to match the entire screen.
				// The z-scale and z-offset values are used to specify the transformation
				// from clip-space to screen-space
				gfxc.setupScreenViewport(
					0,			// Left
					0,			// Top
					m_displayBuffers[m_currentBackBufferIndex].m_rtsi.m_renderTarget.getWidth(),
					m_displayBuffers[m_currentBackBufferIndex].m_rtsi.m_renderTarget.getHeight(),
					1.0f,		// Z-scale
					0.0f);		// Z-offset

				m_renderContextFlowState = RenderContextFlowState::RenderFrame;

				// Turn on msaa
				m_rtMsaa = true;
				_enableMSAA(gfxc);

				Gnm::ScanModeControlAa msaa = Gnm::ScanModeControlAa::kScanModeControlAaEnable;
				gfxc.setScanModeControl(msaa, Gnm::ScanModeControlViewportScissor::kScanModeControlViewportScissorEnable);

				// Bind the render targets to the context
				m_currentInternalRenderContext->setRenderTarget(0, &m_displayBuffers[m_currentBackBufferIndex].m_rtsi.m_renderTarget);
			}
		}

		bool RendererContextGNM::setFrameBuffer(Gnmx::GnmxGfxContext& gfxc, FrameBufferHandle _fbh, bool _msaa, bool _needPresent)
		{
			uint32_t mask = 0xf;

			bool resetPrimitiveType = false;
			if (isValid(m_fbh)) {
				FrameBufferGNM& oldFrameBuffer = m_frameBuffers[m_fbh.idx];

				if (m_fbh.idx != _fbh.idx) {
					oldFrameBuffer.resolve();
					resetPrimitiveType = true;

					//Write resource barriers to ensure can be used correctly later
					oldFrameBuffer.transitionTo(FrameBufferGNM::ResourceTransition::TargetToTexture);
				}
			}

			// FrameBuffer msaa states set when it creates and will not change
			bool enableMSAA = isValid(_fbh) ? m_frameBuffers[_fbh.idx].m_frameBufferMSAA : m_rtMsaa;
			m_fbh = _fbh;
			_enableMSAA(gfxc, enableMSAA);

			if (!isValid(_fbh))
			{
				// Bind the render & depth targets to the context
				if (enableMSAA) {
					m_currentInternalRenderContext->setRenderTarget(0, &m_displayBuffers[m_currentBackBufferIndex].m_rtsi.m_renderTarget);
				}
				else {
					m_currentInternalRenderContext->setRenderTarget(0, &m_backBuffers[m_currentBackBufferIndex].m_rtsi.m_renderTarget);
				}
				m_currentInternalRenderContext->setDepthRenderTarget(&m_depthTarget.m_depthRenderTarget);
				BX_ASSERT(&gfxc == &m_currentInternalRenderContext->m_GFXContext, "Mismatch in gfxc");

				m_needPresent |= _needPresent;
			}
			else
			{
				invalidateTextureStage();
				FrameBufferGNM& frameBuffer = m_frameBuffers[_fbh.idx];
				frameBuffer.set();
				frameBuffer.transitionTo(FrameBufferGNM::ResourceTransition::TextureToTarget);
				mask = frameBuffer.m_mask;
			}

			m_MRTmask = mask;

			return resetPrimitiveType;
		}

		void RendererContextGNM::clearQuad(Gnmx::GnmxGfxContext& gfxc, ClearQuad& _clearQuad, const Rect& _rect, const Clear& _clear, const float _palette[][4])
		{
			uint32_t width;
			uint32_t height;

			if (isValid(m_fbh))
			{
				const FrameBufferGNM& fb = m_frameBuffers[m_fbh.idx];
				width = fb.m_width;
				height = fb.m_height;
			}
			else
			{
				width = m_resolution.width;
				height = m_resolution.height;
			}

			if (0 == _rect.m_x
				&& 0 == _rect.m_y
				&& width == _rect.m_width
				&& height == _rect.m_height)
			{
				clear(gfxc, _clear, nullptr, _palette);
			}
			else
			{
				clear(gfxc, _clear, &_rect, _palette);
			}
		}

		void RendererContextGNM::clear(Gnmx::GnmxGfxContext& gfxc, const Clear& _clear, const Rect* _prect, const float _palette[][4])
		{
			if (isValid(m_fbh))
			{
				FrameBufferGNM& frameBuffer = m_frameBuffers[m_fbh.idx];
				frameBuffer.clear(_clear, _prect, _palette);
			}
			else
			{
				if (BGFX_CLEAR_COLOR & _clear.m_flags)
				{
					if (BGFX_CLEAR_COLOR_USE_PALETTE & _clear.m_flags)
					{
						uint8_t index = _clear.m_index[0];
						if (UINT8_MAX != index)
						{
							if (_prect != nullptr)
							{
								if (m_rtMsaa) {
									_clearRenderTargetPartial(gfxc, &m_displayBuffers[m_currentBackBufferIndex].m_rtsi, _prect, _palette[index]);
								}
								_clearRenderTargetPartial(gfxc, &m_backBuffers[m_currentBackBufferIndex].m_rtsi, _prect, _palette[index]);
							}
							else
							{
								if (m_rtMsaa) {
									const uint32_t  cmaskClearColor[2] =
									{
									  (((uint32_t)_palette[index][3] * 255) << 24 | (uint32_t)(_palette[index][0] * 255) << 16 | (uint32_t)(_palette[index][1] * 255) << 8 | (uint32_t)(_palette[index][2] * 255) << 0),
									  0,
									};
									m_displayBuffers[m_currentBackBufferIndex].m_rtsi.m_renderTarget.setCmaskClearColor(cmaskClearColor[0], cmaskClearColor[1]);

									_clearCmaskSurface(gfxc, &m_displayBuffers[m_currentBackBufferIndex].m_rtsi);
								}
								_clearRenderTarget(gfxc, &m_backBuffers[m_currentBackBufferIndex].m_rtsi, _palette[index]);
							}
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

						if (_prect != nullptr)
						{
							if (m_rtMsaa) {
								_clearRenderTargetPartial(gfxc, &m_displayBuffers[m_currentBackBufferIndex].m_rtsi, _prect, frgba);
							}
							_clearRenderTargetPartial(gfxc, &m_backBuffers[m_currentBackBufferIndex].m_rtsi, _prect, frgba);
						}
						else
						{
							if (m_rtMsaa) {
								const uint32_t  cmaskClearColor[2] =
								{
								  (((uint32_t)frgba[3] * 255) << 24 | (uint32_t)(frgba[0] * 255) << 16 | (uint32_t)(frgba[1] * 255) << 8 | (uint32_t)(frgba[2] * 255) << 0),
								  0,
								};
								m_displayBuffers[m_currentBackBufferIndex].m_rtsi.m_renderTarget.setCmaskClearColor(cmaskClearColor[0], cmaskClearColor[1]);
								_clearCmaskSurface(gfxc, &m_displayBuffers[m_currentBackBufferIndex].m_rtsi);
							}
							_clearRenderTarget(gfxc, &m_backBuffers[m_currentBackBufferIndex].m_rtsi, frgba);
						}
					}
				}

				if ((BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL) & _clear.m_flags)
				{
					_clearDepthStencilBuffer(gfxc, &m_depthTarget.m_depthRenderTarget, _prect, _clear);
				}
			}
		}

		void RendererContextGNM::submitBlit(BlitState& _bs, uint16_t _view)
		{
			struct TexCopyCBuffer {
				//Padded to 16 byte alignment
				uint32_t dest_offset[4];
				uint32_t src_offset[4];
				uint32_t tex_size[4];
				uint32_t dst_mip;
				uint32_t src_mip;
			};

			constexpr uint32_t kXThreadCount = 8;
			constexpr uint32_t kYThreadCount = 8;
			constexpr uint32_t kZThreadCount = 1;

			auto& gfxc = m_currentInternalRenderContext->m_GFXContext;
			bool blitted = false;
			if (_bs.hasItem(_view)) {
#if BGFX_CONFIG_DEBUG
				gfxc.setMarker("Submit Blit");
#endif
				blitted = true;
			}
			while (_bs.hasItem(_view)) {
				const BlitItem& blit = _bs.advance();

				TextureGNM& src = m_textures[blit.m_src.idx];
				TextureGNM& dst = m_textures[blit.m_dst.idx];
				dst.m_internalTexture.setResourceMemoryType(Gnm::kResourceMemoryTypeGC);

				gfxc.waitForGraphicsWrites(src.m_internalTexture.getBaseAddress256ByteBlocks(), (src.m_internalTexture.getSizeAlign().m_size) >> 8,
					Gnm::kWaitTargetSlotCb0 | Gnm::kWaitTargetSlotDb, Gnm::kCacheActionWriteBackAndInvalidateL1andL2, Gnm::kExtendedCacheActionFlushAndInvalidateCbCache |
					Gnm::kExtendedCacheActionFlushAndInvalidateDbCache, Gnm::kStallCommandBufferParserDisable);

				const uint32_t srcWidth = bx::uint32_min(src.m_width, blit.m_srcX + blit.m_width) - blit.m_srcX;
				const uint32_t srcHeight = bx::uint32_min(src.m_height, blit.m_srcY + blit.m_height) - blit.m_srcY;
				const uint32_t srcDepth = bx::uint32_min(src.m_depth, blit.m_srcZ + blit.m_depth) - blit.m_srcZ;
				const uint32_t dstWidth = bx::uint32_min(dst.m_width, blit.m_dstX + blit.m_width) - blit.m_dstX;
				const uint32_t dstHeight = bx::uint32_min(dst.m_height, blit.m_dstY + blit.m_height) - blit.m_dstY;
				const uint32_t dstDepth = bx::uint32_min(dst.m_depth, blit.m_dstZ + blit.m_depth) - blit.m_dstZ;
				const uint32_t width = bx::uint32_min(srcWidth, dstWidth);
				const uint32_t height = bx::uint32_min(srcHeight, dstHeight);
				const uint32_t depth = bx::uint32_min(srcDepth, dstDepth);

				const Gnm::TextureType srcType = src.m_internalTexture.getTextureType();
				const Gnm::TextureType dstType = dst.m_internalTexture.getTextureType();

				BX_ASSERT(srcType != Gnm::kTextureType1d || dstType != Gnm::kTextureType1d, "1D textures currently unsupported");
				gfxc.setTextures(Gnm::kShaderStageCs, 0, 1, &src.m_internalTexture);
				gfxc.setRwTextures(Gnm::kShaderStageCs, 1, 1, &dst.m_internalTexture);

				TexCopyCBuffer* cBuffer = allocateFromCommandBuffer<TexCopyCBuffer>(gfxc, 1, sce::Gnm::kEmbeddedDataAlignment4);
				bx::memSet(cBuffer, 0, sizeof(*cBuffer));

				cBuffer->src_offset[0] = blit.m_srcX;
				cBuffer->src_offset[1] = blit.m_srcY;
				cBuffer->src_offset[2] = blit.m_srcZ;

				cBuffer->dest_offset[0] = blit.m_dstX;
				cBuffer->dest_offset[1] = blit.m_dstY;
				cBuffer->dest_offset[2] = blit.m_dstZ;

				cBuffer->tex_size[0] = width;
				cBuffer->tex_size[1] = height;
				cBuffer->tex_size[2] = depth;

				cBuffer->src_mip = blit.m_srcMip;
				cBuffer->dst_mip = blit.m_dstMip;

				Gnm::Buffer constantBuffer;
				constantBuffer.initAsConstantBuffer(cBuffer, sizeof(*cBuffer));
				gfxc.setConstantBuffers(Gnm::kShaderStageCs, 0, 1, &constantBuffer);

				EmbeddedComputeShaderWithSource* chosenShader = chooseCopyTextureShader(srcType, dstType);
				BX_ASSERT(chosenShader != nullptr, "Unsupported Copy shader");
				if (chosenShader == nullptr) {
					continue;
				}
				gfxc.setCsShader(chosenShader->m_xxShader, &chosenShader->m_offsetsTable);

				const uint32_t xGroupCount = calculateComputeThreadGroupCount(width, kXThreadCount);
				const uint32_t yGroupCount = calculateComputeThreadGroupCount(height, kYThreadCount);
				const uint32_t zGroupCount = calculateComputeThreadGroupCount(depth, kZThreadCount);
				gfxc.dispatch(xGroupCount, yGroupCount, zGroupCount);

				//Force synchronization of dst texture before leaving
				gfxc.waitForGraphicsWrites(dst.m_internalTexture.getBaseAddress256ByteBlocks(), (dst.m_internalTexture.getSizeAlign().m_size) >> 8,
					Gnm::kWaitTargetSlotCb0 | Gnm::kWaitTargetSlotDb, Gnm::kCacheActionWriteBackAndInvalidateL1andL2, Gnm::kExtendedCacheActionFlushAndInvalidateCbCache |
					Gnm::kExtendedCacheActionFlushAndInvalidateDbCache, Gnm::kStallCommandBufferParserDisable);
			}
			if (blitted) {
				gfxc.submit();
				_synchronizeComputeToGraphics(&gfxc.m_dcb);
			}
		}

		void RendererContextGNM::_handleCompute(bool& wasCompute, Frame* _render, const RenderBind& renderBind, uint16_t view, const RenderItem& renderItem, SortKey& key, uint16_t programIdx)
		{
		}

		void RendererContextGNM::_setScissor(Gnmx::GnmxGfxContext& gfxc, Frame* _render, const Rect& viewScissorRect, uint16_t scissor)
		{
			// In case we are drawing to a framebuffer with dimensions other than the screen size
			Rect screenRect;
			if (isValid(m_fbh))
			{
				screenRect.m_x = 0;
				screenRect.m_y = 0;
				screenRect.m_width = m_frameBuffers[m_fbh.idx].m_width;
				screenRect.m_height = m_frameBuffers[m_fbh.idx].m_height;
			}
			else
			{
				screenRect.m_x = 0;
				screenRect.m_y = 0;
				screenRect.m_width = m_backBuffers[m_currentBackBufferIndex].m_rtsi.m_renderTarget.getWidth();
				screenRect.m_height = m_backBuffers[m_currentBackBufferIndex].m_rtsi.m_renderTarget.getHeight();
			}

			if (UINT16_MAX == scissor)
			{
				Rect scissorRect;
				scissorRect.setIntersect(viewScissorRect, screenRect);
				// In the case scissor isn't used, viewScissorRect comes in with screen dimensions.			screenRect.m_x = 0;
				_setScreenScissor(gfxc, scissorRect.m_x, scissorRect.m_y, scissorRect.m_x + scissorRect.m_width, scissorRect.m_y + scissorRect.m_height);
				s_currentScissor = scissorRect;
			}
			else
			{
				Rect scissorRect;
				scissorRect.setIntersect(screenRect, _render->m_frameCache.m_rectCache.m_cache[scissor]);
				_setScreenScissor(gfxc, scissorRect.m_x, scissorRect.m_y, scissorRect.m_x + scissorRect.m_width, scissorRect.m_y + scissorRect.m_height);
				s_currentScissor = scissorRect;
			}
		}

		void RendererContextGNM::_bindTextures(Frame* _render, RenderBind& currentBind, const RenderBind& renderBind, bool programChanged) {
			uint32_t changes = 0;
			BX_STATIC_ASSERT(Gnm::kSlotCountSampler <= BGFX_CONFIG_MAX_TEXTURE_SAMPLERS);
			for (uint8_t stage = 0; stage < Gnm::kSlotCountSampler; ++stage) {
				const Binding& bind = renderBind.m_bind[stage];
				Binding& current = currentBind.m_bind[stage];
				if (current.m_idx != bind.m_idx
					|| current.m_type != bind.m_type
					|| current.m_samplerFlags != bind.m_samplerFlags
					|| programChanged) {
					if (kInvalidHandle != bind.m_idx) {
						switch (bind.m_type) {
						case Binding::Texture:
						{
							TextureGNM& texture = m_textures[bind.m_idx];
							m_textureStage.m_tex[stage] = texture.m_internalTexture;

							const uint32_t flags = 0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & bind.m_samplerFlags)
								? bind.m_samplerFlags
								: texture.m_flags;
							const uint32_t index = (flags & BGFX_SAMPLER_BORDER_COLOR_MASK) >> BGFX_SAMPLER_BORDER_COLOR_SHIFT;

							Gnm::Sampler* sampler = getSampler(flags, _render->m_colorPalette[index]);

							BX_ASSERT(sampler != nullptr, "Failed to find sampler");
							m_textureStage.m_sampler[stage] = *sampler;

							m_textureStage.m_bufferBound &= ~(1 << stage);
						}
						break;
						case Binding::ShaderBuffer:
						{
							BX_TRACE("Binding::ShaderBuffer");
							m_textureStage.m_bufferHandles[stage] = bind.m_idx;
							ShaderBufferGNM& buffer = m_shaderBuffers[bind.m_idx];
							//m_textureStage.m_sampler[stage] = something null  but it should be zeroed check BBI TODO (dgalloway 1)
							m_textureStage.m_bufferBound |= 1 << stage;
						}
						break;

						case Binding::IndexBuffer:
						case Binding::VertexBuffer:
						{
							// BBI TODO (dgalloway 3) - currently Index and Vertex buffers are not bound to fragments in Badger as ShaderBuffers are more versatile
							BX_TRACE("Binding::IndexBuffer or Binding::VertexBuffer - NOT IMPLEMENTED");
						}
						break;
						}
					}
					else {
						m_textureStage.m_tex[stage] = Gnm::Texture();
						m_textureStage.m_sampler[stage] = Gnm::Sampler();
					}
					++changes;
				}
				current = bind;
			}
			if (0 < changes) {
				commitTextureStage();
			}
		}

		void RendererContextGNM::_setVertexLayoutAndBindVertexBuffers(Gnmx::GnmxGfxContext& gfxc, RenderDraw& currentState, const RenderDraw& draw, uint16_t programIdx)
		{
			currentState.m_streamMask = draw.m_streamMask;
			currentState.m_instanceDataBuffer.idx = draw.m_instanceDataBuffer.idx;
			currentState.m_instanceDataOffset = draw.m_instanceDataOffset;
			currentState.m_instanceDataStride = draw.m_instanceDataStride;

			std::array<VertexBufferGNM*, BGFX_CONFIG_MAX_VERTEX_STREAMS> buffers;
			std::array<const VertexLayout*, BGFX_CONFIG_MAX_VERTEX_STREAMS> decls;
			std::array<uint32_t, BGFX_CONFIG_MAX_VERTEX_STREAMS> strides;
			std::array<uint32_t, BGFX_CONFIG_MAX_VERTEX_STREAMS> offsets;
			std::fill(buffers.begin(), buffers.end(), nullptr);
			std::fill(decls.begin(), decls.end(), nullptr);
			std::fill(strides.begin(), strides.end(), 0);
			std::fill(offsets.begin(), offsets.end(), 0);

			uint32_t numVertices = draw.m_numVertices;
			uint8_t  numStreams = 0;

			if (UINT8_MAX != draw.m_streamMask)
			{
				for (uint32_t idx = 0, streamMask = draw.m_streamMask, ntz = bx::uint32_cnttz(streamMask)
					; 0 != streamMask
					; streamMask >>= 1, idx += 1, ntz = bx::uint32_cnttz(streamMask), ++numStreams
					)
				{
					streamMask >>= ntz;
					idx += ntz;

					currentState.m_stream[idx].m_layoutHandle = draw.m_stream[idx].m_layoutHandle;
					currentState.m_stream[idx].m_handle = draw.m_stream[idx].m_handle;
					currentState.m_stream[idx].m_startVertex = draw.m_stream[idx].m_startVertex;

					const uint16_t handle = draw.m_stream[idx].m_handle.idx;
					VertexBufferGNM& vb = m_vertexBuffers[handle];
					const uint16_t decl = !isValid(vb.m_decl) ? draw.m_stream[idx].m_layoutHandle.idx : vb.m_decl.idx;
					const VertexLayout& vertexDecl = m_vertexDecls[decl];
					const uint32_t stride = vertexDecl.m_stride;

					buffers[numStreams] = &vb;
					strides[numStreams] = stride;
					offsets[numStreams] = draw.m_stream[idx].m_startVertex * stride;
					decls[numStreams] = &vertexDecl;

					numVertices = bx::uint32_min(UINT32_MAX == draw.m_numVertices
						? vb.m_size / stride
						: draw.m_numVertices
						, numVertices
					);
				}
			}

			currentState.m_numVertices = numVertices;

			if (0 < numStreams)
			{
				uint32_t usedSlotsRangeMax = 0;
				BX_ASSERT(programIdx < BGFX_CONFIG_MAX_PROGRAMS, "Bad m_program array access");
				ProgramGNM program = m_program[programIdx];

				std::array<Gnm::Buffer, Attrib::Count> vertexElements;
				std::array<Gnm::Buffer*, Attrib::Count> enabledVertexElements;

				std::fill(enabledVertexElements.begin(), enabledVertexElements.end(), nullptr);

				for (uint8_t stream = 0; stream < numStreams; ++stream)
				{
					VertexBufferGNM* vertexBuffer = buffers[stream];
					const VertexLayout* vertexDecl = decls[stream];

					for (uint32_t attr = 0; attr < Attrib::Count; ++attr)
					{
						int8_t vertexElementIndex = program.m_attributesSlot[attr];
						if (vertexElementIndex >= 0 && UINT16_MAX != vertexDecl->m_attributes[attr])
						{
							usedSlotsRangeMax = std::max(usedSlotsRangeMax, static_cast<uint32_t>(vertexElementIndex) + 1);

							uint8_t num;
							AttribType::Enum type;
							bool normalized;
							bool asInt;
							vertexDecl->decode((bgfx::Attrib::Enum)attr, num, type, normalized, asInt);

							Gnm::DataFormat dataFormat = s_attribType[type][num - 1][normalized];

							Gnm::Buffer& gnmBuffer = vertexElements[vertexElementIndex];
							enabledVertexElements[vertexElementIndex] = &gnmBuffer;

							uint8_t* bufferCalc = vertexBuffer->m_gpuMemory.get();
							bufferCalc += offsets[stream] + vertexDecl->m_offset[attr];
							gnmBuffer.initAsVertexBuffer(bufferCalc, dataFormat, vertexDecl->m_stride, (vertexBuffer->m_size - offsets[stream]) / strides[stream]);
						}
					}
				}

				if (usedSlotsRangeMax > 0)
				{
					const auto rangeBegin = enabledVertexElements.begin();
					const auto rangeEnd = enabledVertexElements.begin() + usedSlotsRangeMax;

					bool hasEmptySlot = std::find(rangeBegin, rangeEnd, nullptr) != rangeEnd;
					if (hasEmptySlot)
					{
						for (int i = 0; i < usedSlotsRangeMax; i++)
						{
							if (enabledVertexElements[i] != nullptr)
							{
								gfxc.setVertexBuffers(Gnm::kShaderStageVs, i, 1, enabledVertexElements[i]);
							}
						}
					}
					else
					{
						gfxc.setVertexBuffers(Gnm::kShaderStageVs, 0, usedSlotsRangeMax, enabledVertexElements[0]);
					}
				}
				else
				{
					gfxc.setVertexBuffers(Gnm::kShaderStageVs, 0, 0, nullptr);
				}

				if (isValid(draw.m_instanceDataBuffer))
				{
					const VertexBufferGNM& inst = m_vertexBuffers[draw.m_instanceDataBuffer.idx];
					const uint32_t instStride = draw.m_instanceDataStride;
					const uint32_t numInstanceData = instStride / 16;

					Gnm::Buffer gnmInstanceBuffer[numInstanceData];

					/*std::vector<Gnm::Buffer> gnmInstanceBuffer;
					gnmInstanceBuffer.reserve(numInstanceData);*/



					uint8_t* bufferCalc = inst.m_gpuMemory.get();
					bufferCalc += draw.m_instanceDataOffset;

					for (uint32_t i = 0; i < numInstanceData; ++i) {
						gnmInstanceBuffer[i].initAsVertexBuffer(bufferCalc, Gnm::kDataFormatR32G32B32A32Float, instStride, draw.m_numInstances);
						gnmInstanceBuffer[i].setResourceMemoryType(Gnm::kResourceMemoryTypeRO);

						gfxc.setVertexBuffers(Gnm::kShaderStageVs, usedSlotsRangeMax + i, 1, &gnmInstanceBuffer[i]);

						bufferCalc += 16;
					}
				}

			}
			else
			{
				gfxc.setVertexBuffers(Gnm::kShaderStageVs, 0, 0, nullptr);
			}
		}

		void RendererContextGNM::_drawIndexed(Gnmx::GnmxGfxContext& gfxc, RenderDraw& currentState, const RenderDraw& draw, uint8_t primIndex, PrimInfo& prim, StatsDataForSubmit& stats)
		{
			uint32_t numVertices = currentState.m_numVertices;
			uint32_t numIndices = 0;
			uint32_t numPrimsSubmitted = 0;
			uint32_t numInstances = draw.m_numInstances;
			uint32_t numPrimsRendered = 0;
			uint32_t numDrawIndirect = 0;

			BX_ASSERT(!isValid(draw.m_indirectBuffer), "m_indirectBuffer not supported");
			if (isValid(draw.m_indirectBuffer))
			{
				BX_TRACE("indirect buffer");
			}

#if GNM_TODO // Indirect Buffer
			if (isValid(draw.m_indirectBuffer))
			{
				const VertexBufferD3D11& vb = m_vertexBuffers[draw.m_indirectBuffer.idx];
				ID3D11Buffer* ptr = vb.m_ptr;

				if (isValid(draw.m_indexBuffer))
				{
					numDrawIndirect = UINT16_MAX == draw.m_numIndirect
						? vb.m_size / BGFX_CONFIG_DRAW_INDIRECT_STRIDE
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
						? vb.m_size / BGFX_CONFIG_DRAW_INDIRECT_STRIDE
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
#endif
			{
				struct SetAndRestoreNumInstances {
					SetAndRestoreNumInstances(Gnmx::GnmxGfxContext& gfxc, const uint32_t numInstances) : m_gfxc(gfxc),
						m_moreThanOneInstance(numInstances > 1) {
						if (m_moreThanOneInstance) {
							m_gfxc.setNumInstances(numInstances);
							m_gfxc.setInstanceStepRate(1, 1);
						}
					}

					~SetAndRestoreNumInstances() {
						if (m_moreThanOneInstance) {
							// Restore
							m_gfxc.setNumInstances(1);
						}
					}

					Gnmx::GnmxGfxContext& m_gfxc;
					bool m_moreThanOneInstance;
				} setAndRestoreNumInstances(gfxc, numInstances);

				if (isValid(draw.m_indexBuffer))
				{
					if (UINT32_MAX == draw.m_numIndices)
					{
						const IndexBufferGNM& ib = m_indexBuffers[draw.m_indexBuffer.idx];
						const uint32_t indexSize = 0 == (ib.m_flags & BGFX_BUFFER_INDEX32) ? 2 : 4;
						numIndices = ib.m_size / indexSize;
						numPrimsSubmitted = numIndices / prim.m_div - prim.m_sub;
						numPrimsRendered = numPrimsSubmitted * draw.m_numInstances;

						gfxc.drawIndex(numIndices, ib.m_gpuMemory.get());
					}
					else if (prim.m_min <= draw.m_numIndices)
					{
						numIndices = draw.m_numIndices;
						numPrimsSubmitted = numIndices / prim.m_div - prim.m_sub;
						numPrimsRendered = numPrimsSubmitted * draw.m_numInstances;

						const IndexBufferGNM& ib = m_indexBuffers[draw.m_indexBuffer.idx];
						if (draw.m_startIndex == 0)
						{
							gfxc.drawIndex(numIndices, ib.m_gpuMemory.get());
						}
						else
						{
							const uint32_t indexSize = 0 == (ib.m_flags & BGFX_BUFFER_INDEX32) ? 2 : 4;
							uint8_t* calcOffsetMem = ib.m_gpuMemory.get();
							calcOffsetMem += indexSize * draw.m_startIndex;
							gfxc.drawIndex(numIndices, calcOffsetMem);
						}
					}
				}
				else
				{
					numPrimsSubmitted = numVertices / prim.m_div - prim.m_sub;
					numPrimsRendered = numPrimsSubmitted * draw.m_numInstances;

					gfxc.drawIndexAuto(numVertices);
				}
			}

			stats.statsNumPrimsSubmitted[primIndex] += numPrimsSubmitted;
			stats.statsNumPrimsRendered[primIndex] += numPrimsRendered;
			stats.statsNumInstances[primIndex] += numInstances;
			stats.statsNumDrawIndirect[primIndex] += numDrawIndirect;
			stats.statsNumIndices += numIndices;
		}

		void RendererContextGNM::_setProgram(Gnmx::GnmxGfxContext& gfxc, uint16_t programIdx)
		{
			if (kInvalidHandle == programIdx)
			{
				m_currentProgram = NULL;

				gfxc.setActiveShaderStages(Gnm::kActiveShaderStagesVsPs);
				gfxc.setVsShader(nullptr, 0, nullptr);
				gfxc.setPsShader(nullptr);
			}
			else
			{
				ProgramGNM& program = m_program[programIdx];
				m_currentProgram = &program;

				gfxc.setActiveShaderStages(Gnm::kActiveShaderStagesVsPs);

				if (nullptr != program.m_vsh)
				{
					EmbeddedVertexShaderWithSource* embeddedVertexShader = program.m_vsh->m_vertexShader;
					gfxc.setVsShader(embeddedVertexShader->m_xxShader, embeddedVertexShader->m_fetchShaderModifier, embeddedVertexShader->m_fetchShader);
				}
				else
				{
					gfxc.setVsShader(nullptr, 0, nullptr);
				}

				if (nullptr != program.m_fsh)
				{
					EmbeddedPixelShaderWithSource* embeddedPixelShader = program.m_fsh->m_pixelShader;
					gfxc.setPsShader(embeddedPixelShader->m_xxShader, &embeddedPixelShader->m_offsetsTable);
				}
				else
				{
					gfxc.setPsShader(nullptr);
				}
			}
		}

		void RendererContextGNM::setBlendState(Gnmx::GnmxGfxContext& gfxc, uint64_t _state, uint32_t _rgba)
		{
			Gnm::BlendControl blendControl;
			blendControl.init();

			if ((BGFX_STATE_BLEND_MASK & _state) == 0)
			{
				blendControl.setBlendEnable(false);
			}
			else
			{
				blendControl.setBlendEnable(true);
				blendControl.setSeparateAlphaEnable(true);

				BX_ASSERT((BGFX_STATE_BLEND_INDEPENDENT & _state) == 0, "Independent blending per frame buffer not supported");

				const uint32_t blend = uint32_t((_state & BGFX_STATE_BLEND_MASK) >> BGFX_STATE_BLEND_SHIFT);
				const uint32_t srcRGB = (blend) & 0xf;
				const uint32_t dstRGB = (blend >> 4) & 0xf;
				const uint32_t srcA = (blend >> 8) & 0xf;
				const uint32_t dstA = (blend >> 12) & 0xf;

				const uint32_t equ = uint32_t((_state & BGFX_STATE_BLEND_EQUATION_MASK) >> BGFX_STATE_BLEND_EQUATION_SHIFT);
				const uint32_t equRGB = (equ) & 0x7;
				const uint32_t equA = (equ >> 3) & 0x7;

				blendControl.setColorEquation(s_blendFactor[srcRGB][0], s_blendEquation[equRGB], s_blendFactor[dstRGB][0]);
				blendControl.setAlphaEquation(s_blendFactor[srcA][1], s_blendEquation[equA], s_blendFactor[dstA][1]);
			}

			gfxc.setBlendControl(0, blendControl);

			const uint64_t f0 = BGFX_STATE_BLEND_FACTOR;
			const uint64_t f1 = BGFX_STATE_BLEND_INV_FACTOR;
			const uint64_t f2 = BGFX_STATE_BLEND_FACTOR << 4;
			const uint64_t f3 = BGFX_STATE_BLEND_INV_FACTOR << 4;
			bool hasFactor = 0
				|| f0 == (_state & f0)
				|| f1 == (_state & f1)
				|| f2 == (_state & f2)
				|| f3 == (_state & f3)
				;

			float blendFactor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
			if (hasFactor) {
				blendFactor[0] = ((_rgba >> 24)) / 255.0f;
				blendFactor[1] = ((_rgba >> 16) & 0xff) / 255.0f;
				blendFactor[2] = ((_rgba >> 8) & 0xff) / 255.0f;
				blendFactor[3] = ((_rgba) & 0xff) / 255.0f;
			}

			gfxc.setBlendColor(blendFactor[0], blendFactor[1], blendFactor[2], blendFactor[3]);
		}

		void RendererContextGNM::setDepthStencilState(Gnmx::GnmxGfxContext& gfxc, uint64_t _state, uint64_t _stencil)
		{
			Gnm::DepthStencilControl dsc;
			dsc.init();

			const Gnm::DepthControlZWrite zwrite = !!(BGFX_STATE_WRITE_Z & _state)
				? Gnm::kDepthControlZWriteEnable
				: Gnm::kDepthControlZWriteDisable
				;
			const uint32_t func = (_state & BGFX_STATE_DEPTH_TEST_MASK) >> BGFX_STATE_DEPTH_TEST_SHIFT;
			dsc.setDepthEnable(0 != func);
			dsc.setDepthControl(zwrite, s_cmpFunc[func]);

			if (0 != _stencil)
			{
				const uint32_t fstencil = unpackStencil(0, _stencil);
				uint32_t bstencil = unpackStencil(1, _stencil);
				const bool frontAndBack = bstencil != BGFX_STENCIL_NONE && bstencil != fstencil;
				bstencil = frontAndBack ? bstencil : fstencil;

				dsc.setStencilEnable(true);
				dsc.setSeparateStencilEnable(frontAndBack);

				const Gnm::CompareFunc frontCmp = s_cmpFunc[(fstencil & BGFX_STENCIL_TEST_MASK) >> BGFX_STENCIL_TEST_SHIFT];
				dsc.setStencilFunction(frontCmp);

				const uint32_t frontOpFailS = (fstencil & BGFX_STENCIL_OP_FAIL_S_MASK) >> BGFX_STENCIL_OP_FAIL_S_SHIFT;
				const uint32_t frontOpPassZ = (fstencil & BGFX_STENCIL_OP_PASS_Z_MASK) >> BGFX_STENCIL_OP_PASS_Z_SHIFT;
				const uint32_t frontOpFailZ = (fstencil & BGFX_STENCIL_OP_FAIL_Z_MASK) >> BGFX_STENCIL_OP_FAIL_Z_SHIFT;

				const Gnm::StencilOp fstencilFail = s_stencilOp[frontOpFailS].op;
				const Gnm::StencilOp fstencilZPass = s_stencilOp[frontOpPassZ].op;
				const Gnm::StencilOp fstencilZFail = s_stencilOp[frontOpFailZ].op;
				Gnm::StencilOpControl soc;
				soc.setStencilOps(fstencilFail, fstencilZPass, fstencilZFail);

				const uint32_t frontRef = (fstencil & BGFX_STENCIL_FUNC_REF_MASK) >> BGFX_STENCIL_FUNC_REF_SHIFT;
				const uint32_t frontRmask = (fstencil & BGFX_STENCIL_FUNC_RMASK_MASK) >> BGFX_STENCIL_FUNC_RMASK_SHIFT;

				const bool frontUseOne = false
					|| s_stencilOp[frontOpFailS].useOne
					|| s_stencilOp[frontOpPassZ].useOne
					|| s_stencilOp[frontOpFailZ].useOne
					;

				Gnm::StencilControl fsc;
				fsc.m_testVal = frontRef;
				fsc.m_mask = frontRmask;
				fsc.m_writeMask = UINT8_MAX;
				fsc.m_opVal = frontUseOne ? 1 : frontRef;

				if (!frontAndBack)
				{
					gfxc.setStencil(fsc);
				}
				else
				{
					const Gnm::CompareFunc backCmp = s_cmpFunc[(bstencil & BGFX_STENCIL_TEST_MASK) >> BGFX_STENCIL_TEST_SHIFT];
					dsc.setStencilFunctionBack(backCmp);

					const uint32_t backOpFailS = (bstencil & BGFX_STENCIL_OP_FAIL_S_MASK) >> BGFX_STENCIL_OP_FAIL_S_SHIFT;
					const uint32_t backOpPassZ = (bstencil & BGFX_STENCIL_OP_PASS_Z_MASK) >> BGFX_STENCIL_OP_PASS_Z_SHIFT;
					const uint32_t backOpFailZ = (bstencil & BGFX_STENCIL_OP_FAIL_Z_MASK) >> BGFX_STENCIL_OP_FAIL_Z_SHIFT;
					const Gnm::StencilOp bstencilFail = s_stencilOp[backOpFailS].op;
					const Gnm::StencilOp bstencilZPass = s_stencilOp[backOpPassZ].op;
					const Gnm::StencilOp bstencilZFail = s_stencilOp[backOpFailZ].op;
					soc.setStencilOpsBack(bstencilFail, bstencilZPass, bstencilZFail);

					const uint32_t backRef = (bstencil & BGFX_STENCIL_FUNC_REF_MASK) >> BGFX_STENCIL_FUNC_REF_SHIFT;
					const uint32_t backRmask = (bstencil & BGFX_STENCIL_FUNC_RMASK_MASK) >> BGFX_STENCIL_FUNC_RMASK_SHIFT;

					const bool backUseOne = false
						|| s_stencilOp[backOpFailS].useOne
						|| s_stencilOp[backOpPassZ].useOne
						|| s_stencilOp[backOpFailZ].useOne
						;

					Gnm::StencilControl bsc;
					bsc.m_testVal = backRef;
					bsc.m_mask = backRmask;
					bsc.m_writeMask = UINT8_MAX;
					bsc.m_opVal = backUseOne ? 1 : backRef;

					gfxc.setStencilSeparate(fsc, bsc);
				}

				gfxc.setStencilOpControl(soc);
			}

			gfxc.setDepthStencilControl(dsc);

			// The DB will update HTILE even when we've turned off depth operations,
			// so unbind depth rendertarget to prevent misread HTILE when depth and stencil are disabled
			// https://ps4.siedev.net/forums/thread/411260/
			if (!dsc.getDepthEnable() && !dsc.getStencilEnable()) {
				gfxc.setDepthRenderTarget(nullptr);
			}
			else {
				gfxc.setDepthRenderTarget(m_currentInternalRenderContext->m_currentDepthRenderTarget);
			}
		}

		void RendererContextGNM::setRasterizerState(Gnmx::GnmxGfxContext& gfxc, uint64_t _state, bool _wireframe)
		{
			Gnm::PrimitiveSetup primSetup;
			primSetup.init();

			uint32_t cull = (_state & BGFX_STATE_CULL_MASK) >> BGFX_STATE_CULL_SHIFT;
			BX_ASSERT(cull < BX_COUNTOF(s_cullMode), "Unexpected cull mode");

			primSetup.setCullFace(s_cullMode[cull]);
			primSetup.setFrontFace(Gnm::kPrimitiveSetupFrontFaceCw); // In BGFX the convention is Front Face is CW

			Gnm::PrimitiveSetupPolygonMode polygonMode = _wireframe ? Gnm::kPrimitiveSetupPolygonModeLine : Gnm::kPrimitiveSetupPolygonModeFill;
			primSetup.setPolygonMode(polygonMode, polygonMode);

			gfxc.setPrimitiveSetup(primSetup);

			BX_ASSERT((_state & BGFX_STATE_CONSERVATIVE_RASTER) == 0, "Please implement conservative rasterization");
			BX_ASSERT((_state & BGFX_STATE_LINEAA) == 0, "Please implement line anti-aliasing");
		}

		void RendererContextGNM::setShaderUniform(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs, CommandBufferConstantBuffer& _constantBuffers)
		{
			if (_flags & BGFX_UNIFORM_FRAGMENTBIT)
			{
				_constantBuffers.fsWrite(reinterpret_cast<const uint8_t*>(_val), _regIndex, _numRegs * 16);
			}
			else
			{
				_constantBuffers.vsWrite(reinterpret_cast<const uint8_t*>(_val), _regIndex, _numRegs * 16);
			}
		}

		void RendererContextGNM::setShaderUniform4f(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs, CommandBufferConstantBuffer& _constantBuffers)
		{
			setShaderUniform(_flags, _regIndex, _val, _numRegs, _constantBuffers);
		}

		void RendererContextGNM::setShaderUniform4x4f(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs, CommandBufferConstantBuffer& _constantBuffers)
		{
			setShaderUniform(_flags, _regIndex, _val, _numRegs, _constantBuffers);
		}

		void RendererContextGNM::commitShaderConstants(CommandBufferConstantBuffer& constantBuffers)
		{
			constantBuffers.commit();
		}


		// BBI-TODO (dgalloway 1) clean up usage of commitTextureStage as a way to unbind shader/buffer resources by doing setTextures with null elements.
		void RendererContextGNM::commitTextureStage() {
			Gnmx::GnmxGfxContext& gfxc = m_currentInternalRenderContext->m_GFXContext;

			gfxc.setTextures(sce::Gnm::ShaderStage::kShaderStageVs, 0, Gnm::kSlotCountSampler, m_textureStage.m_tex);
			gfxc.setSamplers(sce::Gnm::ShaderStage::kShaderStageVs, 0, Gnm::kSlotCountSampler, m_textureStage.m_sampler);

			gfxc.setTextures(sce::Gnm::ShaderStage::kShaderStagePs, 0, Gnm::kSlotCountSampler, m_textureStage.m_tex);
			gfxc.setSamplers(sce::Gnm::ShaderStage::kShaderStagePs, 0, Gnm::kSlotCountSampler, m_textureStage.m_sampler);

			// bind shaderbuffers
			for (int stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
			{
				if (m_textureStage.m_bufferBound & (1 << stage))
				{
					uint16_t idx = m_textureStage.m_bufferHandles[stage];
					ShaderBufferGNM& buffer = m_shaderBuffers[idx];
					uint32_t index = buffer.m_gpuBufferIndex;
					gfxc.setBuffers(sce::Gnm::ShaderStage::kShaderStagePs, stage, 1, &buffer.m_buffer[index]);
					gfxc.setBuffers(sce::Gnm::ShaderStage::kShaderStageVs, stage, 1, &buffer.m_buffer[index]);
				}
			}
		}

		void RendererContextGNM::commit(UniformBuffer& _uniformBuffer, CommandBufferConstantBuffer& _constantBuffers)
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
					data = _uniformBuffer.read(g_uniformTypeSize[type] * num);
				}
				else
				{
					UniformHandle handle;
					::memcpy(&handle, _uniformBuffer.read(sizeof(UniformHandle)), sizeof(UniformHandle));
					data = (const char*)m_uniforms[handle.idx].get();
				}

#define CASE_IMPLEMENT_UNIFORM(_uniform, _dxsuffix, _type) \
case UniformType::_uniform: \
case UniformType::_uniform| kUniformFragmentBit: \
		{ \
			setShaderUniform(uint8_t(type), loc, data, num, _constantBuffers); \
		} \
		break;

				switch ((uint32_t)type)
				{
				case UniformType::Mat3:
				case UniformType::Mat3 | kUniformFragmentBit: \
				{
					float* value = (float*)data;
					for (uint32_t ii = 0, count = num / 3; ii < count; ++ii, loc += 3 * 16, value += 9)
					{
						Matrix4 mtx;
						mtx.un.val[0] = value[0];
						mtx.un.val[1] = value[1];
						mtx.un.val[2] = value[2];
						mtx.un.val[3] = 0.0f;
						mtx.un.val[4] = value[3];
						mtx.un.val[5] = value[4];
						mtx.un.val[6] = value[5];
						mtx.un.val[7] = 0.0f;
						mtx.un.val[8] = value[6];
						mtx.un.val[9] = value[7];
						mtx.un.val[10] = value[8];
						mtx.un.val[11] = 0.0f;
						setShaderUniform(uint8_t(type), loc, &mtx.un.val[0], 3, _constantBuffers);
					}
				}
				break;

				CASE_IMPLEMENT_UNIFORM(Sampler, S, int);
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

		Gnm::Sampler* RendererContextGNM::getSampler(uint32_t _flags, const float _rgba[4]) {
			const uint32_t index = (_flags & BGFX_SAMPLER_BORDER_COLOR_MASK) >> BGFX_SAMPLER_BORDER_COLOR_SHIFT;
			_flags &= BGFX_SAMPLER_BITS_MASK;

			// Force both min+max anisotropic, can't be set individually.
			_flags |= 0 != (_flags & (BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC))
				? BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC
				: 0
				;

			constexpr float zero_f[] = { 0.0f, 0.0f ,0.0f, 0.0f };
			uint32_t hash;
			Gnm::Sampler* sampler{ nullptr };

			if (!needBorderColor(_flags)) {
				bx::HashMurmur2A murmur;
				murmur.begin();
				murmur.add(_flags);
				murmur.add(-1);
				hash = murmur.end();
				_rgba = zero_f;

				sampler = m_samplerCache.find(hash);
			}
			else {
				bx::HashMurmur2A murmur;
				murmur.begin();
				murmur.add(_flags);
				murmur.add(index);
				hash = murmur.end();
				_rgba = nullptr == _rgba ? zero_f : _rgba;

				sampler = m_samplerCache.find(hash);
			}

			if (nullptr == sampler) {
				const uint32_t cmpFunc = (_flags & BGFX_SAMPLER_COMPARE_MASK) >> BGFX_SAMPLER_COMPARE_SHIFT;
				const Gnm::FilterMode minFilter = s_minMaxFilter[(_flags & BGFX_SAMPLER_MIN_MASK) >> BGFX_SAMPLER_MIN_SHIFT];
				const Gnm::FilterMode magFilter = s_minMaxFilter[(_flags & BGFX_SAMPLER_MAG_MASK) >> BGFX_SAMPLER_MAG_SHIFT];
				const Gnm::MipFilterMode mipFilter = s_mipFilterMode[(_flags & BGFX_SAMPLER_MIP_MASK) >> BGFX_SAMPLER_MIP_SHIFT];

				Gnm::Sampler newSampler;
				newSampler.init();
				newSampler.setXyFilterMode(magFilter, minFilter);
				newSampler.setMipFilterMode(mipFilter);
				newSampler.setWrapMode(
					s_textureWrapMode[(_flags & BGFX_SAMPLER_U_MASK) >> BGFX_SAMPLER_U_SHIFT],
					s_textureWrapMode[(_flags & BGFX_SAMPLER_V_MASK) >> BGFX_SAMPLER_V_SHIFT],
					s_textureWrapMode[(_flags & BGFX_SAMPLER_W_MASK) >> BGFX_SAMPLER_W_SHIFT]);
				newSampler.setLodBias(float(BGFX_CONFIG_MIP_LOD_BIAS), float(BGFX_CONFIG_MIP_LOD_BIAS));

				// Setting AnisotropyThreshold to 0 sets default behavior
				newSampler.setAnisotropyThreshold(kDefaultAnisotropyThreshold);
				newSampler.setDepthCompareFunction(s_depthCmpFunc[cmpFunc]);

				// TODO BORDER COLOR: newSampler.setBorderColor(Gnm::BorderColor::kBorderColorFromTable);
				// TODO BORDER COLOR: newSampler.setBorderColorTableIndex(s_renderGNM->m_borderColorTable.getIndexFromColor(_rgba));
				// values are set to be within a range of 0-16, but set with
				// a u4-8 fixed point variable. Max Lod is 16.0
				newSampler.setLodRange(Gnmx::convertF32ToU4_8(0.0f), Gnmx::convertF32ToU4_8(15.9f));
				sampler = m_samplerCache.add(hash, std::move(newSampler));
			}

			return sampler;
		}


		void RendererContextGNM::invalidateTextureStage() {
			m_textureStage.clear();
			commitTextureStage(); // relies on setTextures() side effect where null textures are unbound
		}

		void ShaderGNM::create(const Memory* _mem)
		{
			bx::MemoryReader reader(_mem->data, _mem->size);

			uint32_t magic;
			bx::read(&reader, magic);

			bool fragment = isShaderType(magic, 'F');

			uint32_t hashIn{};
			bx::read(&reader, hashIn);

			uint32_t hashOut{};
			if (isShaderVerLess(magic, 6))
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
				, fragment ? "Fragment" : isShaderType(magic, 'V') ? "Vertex" : "Compute"
				, count
			);

			uint8_t fragmentBit = fragment ? kUniformFragmentBit : 0;

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

					const char* kind = "invalid";

					PredefinedUniform::Enum predefined = nameToPredefinedUniformEnum(name);
					if (PredefinedUniform::Count != predefined)
					{
						kind = "predefined";
						m_predefined[m_numPredefined].m_loc = regIndex;
						m_predefined[m_numPredefined].m_count = regCount;
						m_predefined[m_numPredefined].m_type = uint8_t(predefined | fragmentBit);
						m_numPredefined++;
					}
					else if (0 == (kUniformSamplerBit & type))
					{
						const UniformRegInfo* info = s_renderGNM->m_uniformReg.find(name);
						BX_WARN(NULL != info, "User defined uniform '%s' is not found, it won't be set.", name);

						if (NULL != info)
						{
							if (NULL == m_constantBuffer)
							{
								m_constantBuffer = UniformBuffer::create(1024);
							}

							kind = "user";
							// BBI-NOTE (dgalloway)  - I replaced regCount * num with just regCount since the compiler now outputs the correct regCount now
							m_constantBuffer->writeUniformHandle((UniformType::Enum)(type | fragmentBit), regIndex, info->m_handle, regCount);
						}
					}
					else
					{
						kind = "sampler";
					}

					UniformType::Enum uniformType = UniformType::Enum(type & ~kUniformMask);

					BX_TRACE("\t%s: %s (%s), num %2d, r.index %3d, r.count %2d"
						, kind
						, name
						, getUniformTypeName(uniformType)
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

			const uint32_t* source = reinterpret_cast<const uint32_t*>(reader.getDataPtr());
			bx::skip(&reader, shaderSize + 1);

			uint8_t numAttrs = 0;
			bx::read(&reader, numAttrs);

			bool isInstanced[numAttrs];
			bool atLeastOneInstanced = false;
			bx::memSet(isInstanced, 0, sizeof(isInstanced));

			bx::memSet(m_attrMask, 0, sizeof(m_attrMask));
			m_numAttributes = 0;

			std::fill(m_attributesSlot.begin(), m_attributesSlot.end(), -1);

			for (uint32_t ii = 0; ii < numAttrs; ++ii)
			{
				uint8_t slotPlusInstanceFlag;
				bx::read(&reader, slotPlusInstanceFlag);

				constexpr uint8_t IS_INSTANCE_FLAG = 128;
				if (slotPlusInstanceFlag & IS_INSTANCE_FLAG) {
					isInstanced[ii] = true;
					atLeastOneInstanced = true;
				}
				const uint8_t slot = slotPlusInstanceFlag & ~IS_INSTANCE_FLAG;

				uint16_t id;
				bx::read(&reader, id);

				Attrib::Enum attr = idToAttrib(id);

				if (Attrib::Count != attr)
				{
					m_attrMask[attr] = UINT16_MAX;
					m_attributesSlot[attr] = static_cast<int8_t>(slot);
					m_numAttributes++;
				}
			}

			if (isShaderType(magic, 'F'))
			{
				BX_ASSERT(m_pixelShader == nullptr, "No m_pixelShader set");
				m_pixelShader = BX_NEW(g_allocator, EmbeddedPixelShaderWithSource);
				m_pixelShader->m_source = source;
				m_pixelShader->initialize(s_renderGNM->m_garlicAllocator, s_renderGNM->m_onionAllocator, "ShaderGNM pixel");
			}
			else if (isShaderType(magic, 'V'))
			{
				BX_ASSERT(m_vertexShader == nullptr, "No m_vertexShader set");
				m_vertexShader = BX_NEW(g_allocator, EmbeddedVertexShaderWithSource);
				m_vertexShader->m_source = source;
				m_vertexShader->initialize(s_renderGNM->m_garlicAllocator, s_renderGNM->m_onionAllocator, "ShaderGNM vertex");
				if (atLeastOneInstanced) {
					Gnm::FetchShaderInstancingMode instancingData[numAttrs];
					for (int i = 0; i < numAttrs; ++i) {
						instancingData[i] = isInstanced[i] ? Gnm::kFetchShaderUseInstanceId : Gnm::kFetchShaderUseVertexIndex;
					}

					m_vertexShader->initializeFetchShader(s_renderGNM->m_garlicAllocator, instancingData, numAttrs);
				}
				else {
					m_vertexShader->initializeFetchShader(s_renderGNM->m_garlicAllocator);
				}
			}
			else
			{
				BGFX_FATAL(isShaderType(magic, 'C'), bgfx::Fatal::InvalidShader, "Expected shader to be frag,vert, or compute.");
			}

			uint16_t constantBufferSize = 0;
			bx::read(&reader, constantBufferSize);

			if (0 < constantBufferSize)
			{
				m_constantBufferSize = constantBufferSize;
				BX_TRACE("\tCB size: %lu", m_constantBufferSize);
			}
		}

		void ShaderGNM::destroy()
		{
			if (NULL != m_constantBuffer)
			{
				UniformBuffer::destroy(m_constantBuffer);
				m_constantBuffer = NULL;
			}

			m_constantBufferSize = 0;
			m_numPredefined = 0;

			if (m_pixelShader != nullptr)
			{
				m_pixelShader->shutdown(s_renderGNM->m_garlicAllocator, s_renderGNM->m_onionAllocator);
				BX_FREE(g_allocator, m_pixelShader);
				m_pixelShader = nullptr;
			}

			if (m_vertexShader != nullptr)
			{
				m_vertexShader->shutdown(s_renderGNM->m_garlicAllocator, s_renderGNM->m_onionAllocator);
				BX_FREE(g_allocator, m_vertexShader);
				m_vertexShader = nullptr;
			}
		}

		sce::Gnm::ResourceHandle registerResource(const char* _name, Gnm::ResourceType _resourceType, const void* _data, uint32_t _size)
		{
			Gnm::ResourceHandle handle = 0;

			if (0 != s_renderGNM->m_ownerHandle)
			{
				auto status = (Gnm::registerResource(
					&handle
					, s_renderGNM->m_ownerHandle
					, _data
					, _size
					, _name
					, _resourceType
					, 0
				));

				if (status != SCE_GNM_OK)
				{
					BX_ASSERT(false, "Failed to register resource");
				}
			}

			return handle;
		}

		void unregisterResource(Gnm::ResourceHandle _handle)
		{
			if (0 != _handle)
			{
				Gnm::unregisterResource(_handle); // BBI-TODO (dgalloway 2) GNM_CHECK
			}
		}


		sce::Gnm::TextureSpec TextureGNM::textureSpecFromImageContainer(const bimg::ImageContainer& imageContainer, const uint8_t _skip, const uint8_t startLod, const bool isMsaaEnabled) {

			const bimg::ImageBlockInfo& blockInfo = bimg::getBlockInfo(bimg::TextureFormat::Enum(imageContainer.m_format));

			m_width = bx::uint32_max(blockInfo.blockWidth, imageContainer.m_width >> startLod);
			m_height = bx::uint32_max(blockInfo.blockHeight, imageContainer.m_height >> startLod);
			m_depth = imageContainer.m_depth > 1 ? imageContainer.m_depth : 1;

			m_requestedFormat = uint8_t(imageContainer.m_format);
			m_textureFormat = uint8_t(getViableTextureFormat(imageContainer));

			Gnm::TextureSpec spec;
			spec.init();
			spec.m_width = m_width;
			spec.m_height = m_height;
			spec.m_depth = m_depth;
			spec.m_pitch = 0; // auto-detect the pitch
			spec.m_numMipLevels = uint32_t(m_numMips);
			spec.m_numSlices = imageContainer.m_numLayers;
			spec.m_numFragments = Gnm::kNumFragments1;
			spec.m_minGpuMode = Gnm::getGpuMode();
			spec.m_format = s_textureFormat[m_textureFormat].m_fmt;

			GpuAddress::SurfaceFlags surfaceFlags;
			bx::memSet(&surfaceFlags, 0, sizeof(surfaceFlags));

			if (imageContainer.m_cubeMap) {
				spec.m_textureType = sce::Gnm::kTextureTypeCubemap;
				surfaceFlags.m_cube = 1;
			}
			else if (imageContainer.m_numLayers > 1) {
				spec.m_textureType = isMsaaEnabled ? sce::Gnm::kTextureType2dArrayMsaa : sce::Gnm::kTextureType2dArray;
			}
			else if (imageContainer.m_depth > 1) {
				spec.m_textureType = sce::Gnm::kTextureType3d;
				surfaceFlags.m_volume = 1;
			}
			else
			{
				spec.m_textureType = isMsaaEnabled ? sce::Gnm::kTextureType2dMsaa : sce::Gnm::kTextureType2d; // or array and/or MSAA
			}
			const bool isDepth = bimg::isDepth(bimg::TextureFormat::Enum(m_textureFormat));

			Gnm::MicroTileMode microTileMode = isDepth ? Gnm::kMicroTileModeDepth : Gnm::kMicroTileModeDisplay;
			surfaceFlags.m_texCompatible = (Gnm::getGpuMode() == Gnm::kGpuModeNeo) ? 1 : 0;
			const bool computeWrite = (0 != (m_flags & BGFX_TEXTURE_COMPUTE_WRITE)) || (0 != (m_flags & BGFX_TEXTURE_BLIT_DST));
			const bool isRenderTarget = (0 != (m_flags & BGFX_TEXTURE_RT_MASK));
			Gnm::ArrayMode arrayMode;
			GpuAddress::SurfaceType surfaceType;
			if (isDepth) {
				surfaceType = GpuAddress::kSurfaceTypeDepthTarget;
			}
			else if (isRenderTarget) {
				surfaceType = GpuAddress::kSurfaceTypeColorTarget;
			}
			else {
				surfaceType = getSurfaceTypeFromTextureType(spec.m_textureType, computeWrite);
			}
			GpuAddress::getArrayModeForSurfaceType(spec.m_minGpuMode, &arrayMode, surfaceType, 1 << spec.m_numFragments);
			GpuAddress::computeSurfaceTileMode(spec.m_minGpuMode, &spec.m_tileModeHint, arrayMode, surfaceFlags, spec.m_format, 1 << spec.m_numFragments, microTileMode);

			return spec;
		}

		void TextureGNM::allocateTexture(const sce::Gnm::SizeAlign& sizeAlign) {
			const char* textureName = m_name.empty() ? "Texture" : m_name.data();
			m_gpuMemory = s_renderGNM->m_garlicAllocator.allocateUnique<uint8_t>(sizeAlign.m_size, sizeAlign.m_align, Gnm::kResourceTypeTextureBaseAddress, textureName);

			m_internalTexture.setBaseAddress(m_gpuMemory.get());
			m_size = sizeAlign.m_size;
		}


		void* TextureGNM::createAsTexture2D(const bimg::ImageContainer& _imageContainer, const Gnm::TextureSpec& _spec, const Memory* _mem, const uint8_t _startLod) {
			const bool convert = m_textureFormat != m_requestedFormat;
			const uint8_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat));
			//TODO: Compressed images?
			//const bool compressed = bimg::isCompressed(bimg::TextureFormat::Enum(m_textureFormat));


			// BBI-NOTE (dgalloway) this code change is to make also allocate stencil GPU memory at texture creation time.
			// This is how bgfx perceives depth and stencil as depthstencil so it makes bookkeeping more in line if they are managed together.
			if (bimg::isDepth(bimg::TextureFormat::Enum(m_textureFormat)))
			{
				const TextureFormatInfo& tfi = s_textureFormat[m_textureFormat];
				Gnm::ZFormat depthFmt = kZFormat;
				Gnm::DataFormat format = Gnm::DataFormat::build(depthFmt);
				Gnm::StencilFormat stencilFmt = tfi.m_stencilFmt;

				Gnm::TileMode depthTileMode;
				GpuAddress::computeSurfaceTileMode(
					Gnm::getGpuMode()
					, &depthTileMode
					, Gnm::kStencilInvalid == stencilFmt
					? GpuAddress::kSurfaceTypeDepthOnlyTarget		// no stencil
					: GpuAddress::kSurfaceTypeDepthTarget			// kSurfaceDepthTarget implies a stencil target
					, format
					, 1
				);

				Gnm::DepthRenderTargetSpec drts;
				drts.init();
				drts.m_width = _spec.m_width;
				drts.m_height = _spec.m_height;
				drts.m_pitch = 0;
				drts.m_numSlices = 1;
				drts.m_zFormat = depthFmt;
				drts.m_stencilFormat = stencilFmt;
				drts.m_tileModeHint = depthTileMode;
				drts.m_minGpuMode = Gnm::getGpuMode();
				drts.m_numFragments = Gnm::kNumFragments1;
				drts.m_flags.enableHtileAcceleration = false;

				Gnm::DepthRenderTarget drt;
				int32_t result = drt.init(&drts);

				if (SCE_OK != result)
				{
					BX_TRACE("depth buffer init failed 0x%08x.", result);
					return nullptr;
				}

				Gnm::SizeAlign dsa = drt.getZSizeAlign();

				allocateTexture(dsa);

				if (stencilFmt != Gnm::kStencilInvalid)
				{ // need stencil
					Gnm::SizeAlign ssa = drt.getStencilSizeAlign();
					const char* textureName = m_name.empty() ? "Stencil" : m_name.data();
					m_gpuStencilMemory = s_renderGNM->m_garlicAllocator.allocateUnique<uint8_t>(ssa.m_size, ssa.m_align, Gnm::kResourceTypeTextureBaseAddress, textureName);
				}
			}
			else
			{
				const Gnm::SizeAlign newSizeAlign = m_internalTexture.getSizeAlign();
				allocateTexture(newSizeAlign);
			}

			for (uint8_t lod = 0, num = _spec.m_numMipLevels; lod < num; ++lod) {
				bimg::ImageMip mip;

				if (bimg::imageGetRawData(_imageContainer, 0, lod + _startLod, _mem->data, _mem->size, mip)) {

					UniqueBX<uint8_t> temp;

					if (convert) {
						uint32_t srcpitch = mip.m_width * bpp / 8;
						uint32_t mipsize = mip.m_width * mip.m_height * bpp / 8;
						temp = UniqueBX<uint8_t>((uint8_t*)BX_ALLOC(g_allocator, mipsize));
						bimg::imageDecodeToBgra8(g_allocator, temp.get(), mip.m_data, mip.m_width, mip.m_height, srcpitch, mip.m_format);
					}

					const uint32_t arraySlice = 0;
					GpuAddress::TilingParameters tilingParams;
					tilingParams.initFromTexture(&m_internalTexture, lod, arraySlice);

					uint64_t size{ 0 };
					uint64_t offset{ 0 };
					GpuAddress::computeTextureSurfaceOffsetAndSize(&offset, &size, &m_internalTexture, lod, arraySlice);

					GpuAddress::tileSurface(m_gpuMemory.get() + offset, convert ? temp.get() : mip.m_data, &tilingParams);
				}
			}

			m_created = true;

			return &m_internalTexture;
		}

		void* TextureGNM::createAsCubeMap(const bimg::ImageContainer& _imageContainer, const sce::Gnm::TextureSpec& _spec, const Memory* _mem, const uint8_t _startLod) {
			const uint16_t kNumSides = static_cast<uint16_t>(_spec.m_numSlices * 6);
			m_depth = 6;
			const bool convert = m_textureFormat != m_requestedFormat;
			const uint8_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat));
			//TODO: Compressed images?
			//const bool compressed = bimg::isCompressed(bimg::TextureFormat::Enum(m_textureFormat));

			const Gnm::SizeAlign newSizeAlign = m_internalTexture.getSizeAlign();
			allocateTexture(newSizeAlign);

			for (uint16_t side = 0; side < kNumSides; ++side) {
				for (uint8_t lod = 0, num = _spec.m_numMipLevels; lod < num; ++lod) {
					bimg::ImageMip mip;
					if (bimg::imageGetRawData(_imageContainer, side, lod + _startLod, _mem->data, _mem->size, mip)) {

						UniqueBX<uint8_t> temp;
						if (convert) {
							uint32_t srcpitch = mip.m_width * bpp / 8;
							temp = UniqueBX<uint8_t>((uint8_t*)BX_ALLOC(g_allocator, mip.m_width * mip.m_height * bpp / 8));
							bimg::imageDecodeToBgra8(g_allocator, temp.get(), mip.m_data, mip.m_width, mip.m_height, srcpitch, mip.m_format);
						}

						GpuAddress::TilingParameters tilingParams;
						tilingParams.initFromTexture(&m_internalTexture, lod, side);

						uint64_t size{ 0 };
						uint64_t offset{ 0 };
						GpuAddress::computeTextureSurfaceOffsetAndSize(&offset, &size, &m_internalTexture, lod, side);

						GpuAddress::tileSurface(m_gpuMemory.get() + offset, convert ? temp.get() : mip.m_data, &tilingParams);
					}
				}
			}

			m_created = true;

			return &m_internalTexture;
		}

		void* TextureGNM::createAsTextureVolume(const bimg::ImageContainer& _imageContainer, const sce::Gnm::TextureSpec& _spec, const Memory* _mem, const uint8_t _startLod) {

			const bool convert = m_textureFormat != m_requestedFormat;
			const uint8_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat));
			//TODO: Compressed images?
			//const bool compressed = bimg::isCompressed(bimg::TextureFormat::Enum(m_textureFormat));

			const uint32_t depth = _spec.m_depth > 1 ? _spec.m_depth : _spec.m_numSlices;

			const Gnm::SizeAlign newSizeAlign = m_internalTexture.getSizeAlign();
			allocateTexture(newSizeAlign);

			for (uint16_t side = 0; side < depth; ++side) {
				for (uint8_t lod = 0, num = _spec.m_numMipLevels; lod < num; ++lod) {
					bimg::ImageMip mip;
					if (bimg::imageGetRawData(_imageContainer, side, lod + _startLod, _mem->data, _mem->size, mip)) {
						UniqueBX<uint8_t> temp;
						if (convert) {
							uint32_t srcpitch = mip.m_width * bpp / 8;
							temp = UniqueBX<uint8_t>((uint8_t*)BX_ALLOC(g_allocator, mip.m_width * mip.m_height * bpp / 8));
							bimg::imageDecodeToBgra8(g_allocator, temp.get(), mip.m_data, mip.m_width, mip.m_height, srcpitch, mip.m_format);
						}

						GpuAddress::TilingParameters tilingParams;
						tilingParams.initFromTexture(&m_internalTexture, lod, side);

						uint64_t size{ 0 };
						uint64_t offset{ 0 };
						GpuAddress::computeTextureSurfaceOffsetAndSize(&offset, &size, &m_internalTexture, lod, side);

						GpuAddress::tileSurface(m_gpuMemory.get() + offset, convert ? temp.get() : mip.m_data, &tilingParams);
					}
				}
			}

			m_created = true;

			return &m_internalTexture;
		}

		void* TextureGNM::create(const Memory* _mem, uint32_t _flags, uint8_t _skip)
		{
			BX_ASSERT(!m_created, "Texture should not already have been created by this point!");

			bimg::ImageContainer imageContainer;
			if (bimg::imageParse(imageContainer, _mem->data, _mem->size))
			{
				m_flags = _flags;
				const bool isMsaaEnabled = 0 != (m_flags & BGFX_TEXTURE_MSAA_SAMPLE);

				m_numMips = imageContainer.m_numMips;
				const uint8_t startLod = uint8_t(bx::uint32_min(_skip, m_numMips - 1));
				m_numMips -= startLod;

				Gnm::TextureSpec spec = textureSpecFromImageContainer(imageContainer, _skip, startLod, isMsaaEnabled);

				const bool swizzle = TextureFormat::BGRA8 == m_textureFormat && 0 != (m_flags & BGFX_TEXTURE_COMPUTE_WRITE);

				BX_TRACE("Texture %s (requested: %s), layers %d, %dx%d%s%s%s."
					, getName((TextureFormat::Enum)m_textureFormat)
					, getName((TextureFormat::Enum)m_requestedFormat)
					, spec.m_depth
					, spec.m_width
					, spec.m_height
					, imageContainer.m_cubeMap ? "x6" : ""
					, 0 != (m_flags & BGFX_TEXTURE_RT_MASK) ? " (render target)" : ""
					, swizzle ? " (swizzle BGRA8 -> RGBA8)" : ""
				);

				int32_t status = m_internalTexture.init(&spec);

				if (status != SCE_GNM_OK)
				{
					BX_ASSERT(false, "Failed to initialize texture resource");
					return nullptr;
				}

				const bool computeWrite = (0 != (m_flags & BGFX_TEXTURE_COMPUTE_WRITE)) || (0 != (m_flags & BGFX_TEXTURE_BLIT_DST));
				m_internalTexture.setResourceMemoryType((m_flags & BGFX_TEXTURE_RT_MASK) || computeWrite ? Gnm::kResourceMemoryTypeGC : Gnm::kResourceMemoryTypeRO);

				if (spec.m_textureType == Gnm::kTextureType3d
					|| spec.m_textureType == Gnm::kTextureType2dArray
					|| spec.m_textureType == Gnm::kTextureType2dArrayMsaa) {
					return createAsTextureVolume(imageContainer, spec, _mem, startLod);
				}
				else if (spec.m_textureType == Gnm::kTextureTypeCubemap) {
					return createAsCubeMap(imageContainer, spec, _mem, startLod);
				}
				else {
					return createAsTexture2D(imageContainer, spec, _mem, startLod);
				}
			}

			return nullptr;
		}

		void TextureGNM::registerResource(const char* _name, Gnm::ResourceType _resourceType)
		{
			gnm::unregisterResource(m_handle);
			m_handle = gnm::registerResource(_name,
				_resourceType,
				m_gpuMemory.get(),
				m_size);
			//tag(*this, _name); // BBI-TODO (dgalloway 3) Sony Memory analyzer
		}

		void TextureGNM::destroy()
		{
			gnm::unregisterResource(m_handle);
			m_gpuMemory = nullptr;
			m_gpuStencilMemory = nullptr;
			m_internalTexture = Gnm::Texture();
			m_Mips.clear();
			m_created = false;
			m_isExternal = false;
		}

		void TextureGNM::overrideInternal(uintptr_t _ptr, uint32_t _flags)
		{
			BX_UNUSED(_ptr/*, _flags*/);
			BX_ASSERT(false, "TextureGNM::overrideInternal not implemented.");
		}

		void TextureGNM::update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem)
		{
			BX_UNUSED(_side/*, _mip, _rect, _z, _depth, _pitch, _mem*/);

			if (m_gpuMemory) {
				const Gnm::TextureType textureType = m_internalTexture.getTextureType();

				const bool isTextureArray = textureType == Gnm::kTextureType2dArray
					|| textureType == Gnm::kTextureType2dArrayMsaa;

				const uint32_t arraySlice = isTextureArray ? _z : _side;
				const uint32_t srcpitch = UINT16_MAX == _pitch ? _rect.m_width : _pitch;

				GpuAddress::TilingParameters tilingParams;
				tilingParams.initFromTexture(&m_internalTexture, _mip, arraySlice);

				uint64_t size{ 0 };
				uint64_t offset{ 0 };
				GpuAddress::computeTextureSurfaceOffsetAndSize(&offset, &size, &m_internalTexture, _mip, arraySlice);

				GpuAddress::SurfaceRegion region;
				region.m_top = _rect.m_y;
				region.m_left = _rect.m_x;
				region.m_right = _rect.m_x + _rect.m_width;
				region.m_bottom = _rect.m_y + _rect.m_height;
				region.m_front = isTextureArray ? 0 : _z;
				region.m_back = region.m_front + _depth;

				// BBI-NOTE: (dgalloway) this assumes that textures have a 1:1 correspondence between texels and elements.
				// srcpitch is in elements where elements can have multiple texels per element when using BCn or 1-bit per pixel formats.
				BX_ASSERT(m_internalTexture.getDataFormat().getTexelsPerElement() == 1, "Texels per element not equal one");
				GpuAddress::tileSurfaceRegion(m_gpuMemory.get() + offset, _mem->data, &tilingParams, &region, srcpitch, srcpitch * _rect.m_height);
			}
		}

		void TextureGNM::commit(TextureStageGNM& ts, uint32_t _stage, uint32_t _flags, const float _palette[][4])
		{
			ts.m_tex[_stage] = m_internalTexture;

			uint32_t flags = 0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & _flags)
				? _flags
				: m_flags;
			uint32_t index = (flags & BGFX_SAMPLER_BORDER_COLOR_MASK) >> BGFX_SAMPLER_BORDER_COLOR_SHIFT;

			Gnm::Sampler* sampler = s_renderGNM->getSampler(flags
				, _palette[index]);

			BX_ASSERT(sampler != nullptr, "Failed to find sampler") {
				ts.m_sampler[_stage] = *sampler;
			}
		}

		void TextureGNM::resolve() const
		{
			BX_ASSERT(false, "TextureGNM::resolve not implemented.");
		}

		void TextureGNM::wrapExternal(sce::Gnm::Texture const& _externalTexture, TextureRef& ref)
		{
			m_internalTexture = _externalTexture;
			m_textureFormat = m_requestedFormat = [](sce::Gnm::DataFormat rhs) {
				sce::Gnm::RenderTargetChannelOrder lOrder = {}, rOrder = {};
				sce::Gnm::RenderTargetChannelType  lType = {}, rType = {};
				rhs.getRenderTargetChannelOrder(&rOrder);
				rhs.getRenderTargetChannelType(&rType);

				// TODO: is there a beter way to reverse-lookup in GNM?
				for (std::uint8_t i = 0; i < std::uint8_t(TextureFormat::Count); ++i)
				{
					auto const& lhs = s_textureFormat[i].m_fmt;
					if (lhs.m_asInt == Gnm::kDataFormatInvalid.m_asInt)
					{
						continue;
					}
					lhs.getRenderTargetChannelOrder(&lOrder);
					lhs.getRenderTargetChannelType(&lType);

					if (lOrder == rOrder && lType == rType
						&& lhs.getRenderTargetFormat() == rhs.getRenderTargetFormat()) {
						return static_cast<TextureFormat::Enum>(i);
					}
				}
				return TextureFormat::Unknown;
			}
			(m_internalTexture.getDataFormat());
			m_width = m_internalTexture.getWidth();
			m_height = m_internalTexture.getHeight();
			m_depth = m_internalTexture.getDepth();
			m_numMips = m_internalTexture.getLastMipLevel() + 1;
			m_flags |= isTextureTypeMsaa(m_internalTexture.getTextureType()) ? BGFX_TEXTURE_RT_MSAA_X4 : 0; //any msaa level will do, just set to anything that isn't BGFX_TEXTURE_RT
			m_created = true;
			m_isExternal = true;

			ref.init(
				BackbufferRatio::Count
				, m_width
				, m_height
				, m_depth
				, static_cast<TextureFormat::Enum>(m_textureFormat)
				, 0
				, m_numMips
				, m_internalTexture.getLastArraySliceIndex() + 1
				, true
				, true
				, false
				, m_flags);
		}

		void GPUmem::_create(uint32_t _size, uint32_t alignment, const sce::Gnm::ResourceType resourceType, const char* name, void* _data, uint16_t _flags)
		{
			m_size = _size;
			m_flags = _flags;
			// TODO - later handle _flags BGFX_BUFFER_DRAW_INDIRECT

			m_gpuMemory = s_renderGNM->m_garlicAllocator.allocateUnique<uint8_t>(_size, alignment, resourceType, name);
			BX_ASSERT(m_gpuMemory != nullptr, " GPUmem::_create failed to allocate m_gpuMemory");

			if (_data != nullptr) // Could be null on create for dynamic index buffers
			{
				memcpy(m_gpuMemory.get(), _data, _size);
			}
		}

		void GPUmem::update(uint32_t _offset, uint32_t _size, void* _data)
		{
			BX_ASSERT(_size + _offset <= m_size, "GPUmem overflow!");

			uint8_t* byteDst = m_gpuMemory.get();
			BX_ASSERT(byteDst != nullptr, "GPUmem::update m_gpuMemory somehow is null");
			byteDst += _offset;

			memcpy(byteDst, _data, _size);
		}

		void GPUmem::destroy() {
			if (m_gpuMemory != nullptr)
			{
				m_gpuMemory = nullptr;
			}
		}

		void BufferGNM::create(uint32_t _size, void* _data, uint16_t _flags, uint16_t _stride, bool _vertex)
		{
			BX_UNUSED(_stride/*, _vertex*/);
			BX_ASSERT(_stride != 0, "Zero length stride");

			m_size = _size;
			m_stride = _stride;
			m_flags = _flags;
			m_numElements = _size / _stride;
			m_gpuBufferIndex = 0;

			m_ptr[0]._create(_size, sce::Gnm::kAlignmentOfBufferInBytes, sce::Gnm::kResourceTypeBufferBaseAddress, "ShaderBufferGNM", _data, _flags);
			m_buffer[0].initAsRegularBuffer(m_ptr[0].m_gpuMemory.get(), _stride, m_numElements);
			m_buffer[0].setResourceMemoryType(Gnm::kResourceMemoryTypeRO);

			m_ptr[1]._create(_size, sce::Gnm::kAlignmentOfBufferInBytes, sce::Gnm::kResourceTypeBufferBaseAddress, "ShaderBufferGNM", _data, _flags);
			m_buffer[1].initAsRegularBuffer(m_ptr[1].m_gpuMemory.get(), _stride, m_numElements);
			m_buffer[1].setResourceMemoryType(Gnm::kResourceMemoryTypeRO);

			if (NULL != _data)
			{
				m_ptr[0].update(0, _size, _data);
			}
		}

		// BBI-NOTE (dgalloway) This update is written to only support full buffer updates.
		// That is, everything that will be needed in the next frame is being updated and there is no reliance on previous buffer contents.
		// This is due to the double buffer nature.
		// A sub buffer type update would need more logic to combine the previous buffer and a naive approach would be slow because reading from Garlic from CPU is VERY slow.
		void BufferGNM::update(uint32_t _offset, uint32_t _size, void* _data)
		{
			if (_size > 0)
			{
				m_gpuBufferIndex++;
				m_gpuBufferIndex %= 2;
				m_ptr[m_gpuBufferIndex].update(_offset, _size, _data);
			}
		}

		void BufferGNM::destroy()
		{
			m_ptr[0].m_gpuMemory.release();
			m_ptr[1].m_gpuMemory.release();
		}

		void FrameBufferGNM::create(uint8_t _num, const Attachment* _attachment)
		{
			m_numTh = _num;
			::memcpy(m_attachment, _attachment, _num * sizeof(Attachment));

			// FrameBuffer rendertargets have to same msaa states
			for (uint32_t ii = 0; ii < m_numTh; ++ii) {
				TextureHandle handle = m_attachment[ii].handle;

				if (isValid(handle))
				{
					const TextureGNM& texture = s_renderGNM->m_textures[handle.idx];

					if (!(bimg::isDepth(bimg::TextureFormat::Enum(texture.m_textureFormat))))
					{
						uint32_t msaaFlags = texture.m_flags & BGFX_TEXTURE_RT_MASK;
						m_frameBufferMSAA = (msaaFlags != BGFX_TEXTURE_RT && msaaFlags != 0);
					}
				}
			}

			m_needPresent = false;

			postReset();
		}

		void FrameBufferGNM::destroy()
		{
			for (uint32_t ii = 0; ii < m_numTh; ++ii) {
				TextureHandle handle = m_attachment[ii].handle;
				if (isValid(handle)) {
					const TextureGNM& texture = s_renderGNM->m_textures[handle.idx];
					if (!(bimg::isDepth(bimg::TextureFormat::Enum(texture.m_textureFormat)))) {
						s_renderGNM->m_textures[handle.idx].m_BoundFrameBuffer = nullptr;
					}
				}
			}
			for (int i = 0; i < m_num; ++i) {
				m_renderTargets[i].destroy();
				m_renderTargets[i].m_rtsi.m_renderTarget = Gnm::RenderTarget();
				m_intermediateRenderTargets[i].destroy();
				m_intermediateRenderTargets[i].m_rtsi.m_renderTarget = Gnm::RenderTarget();
			}

			if (m_haveDepthAttachment)
			{
				m_depthRenderTarget.setStencilReadAddress(nullptr);
				m_depthRenderTarget.setStencilWriteAddress(nullptr);
				m_depthRenderTarget = Gnm::DepthRenderTarget();
			}


			m_numTh = 0;
			m_num = 0;
			m_width = 0;
			m_height = 0;
			m_haveDepthAttachment = false;

			bx::memSet(m_attachment, 0, sizeof(m_attachment));
		}

		void FrameBufferGNM::preReset(bool _force /*= false*/)
		{
		}

		void FrameBufferGNM::postReset()
		{
			m_width = 0;
			m_height = 0;
			m_num = 0;
			m_haveDepthAttachment = false;

			uint32_t shift = 0;

			if (0 < m_numTh)
			{
				for (uint32_t ii = 0; ii < m_numTh; ++ii)
				{
					TextureHandle handle = m_attachment[ii].handle;
					if (isValid(handle))
					{
						TextureGNM& texture = s_renderGNM->m_textures[handle.idx];
						texture.m_BoundFrameBuffer = this;
						if (0 == m_width)
						{
							m_width = texture.m_width;
							m_height = texture.m_height;
						}

						int32_t result = -1;

						if (bimg::isDepth(bimg::TextureFormat::Enum(texture.m_textureFormat)))
						{  // BBI-TODO (dgalloway 3) setting the mip level range on the internal texture may not be necessary or desired
							uint32_t numSlices = texture.m_internalTexture.getLastArraySliceIndex() - texture.m_internalTexture.getBaseArraySliceIndex() + 1;
							m_numSlicesDepth = numSlices;

							texture.m_internalTexture.setMipLevelRange(m_attachment[ii].mip, m_attachment[ii].mip);

							const TextureFormatInfo& tfi = s_textureFormat[texture.m_textureFormat];
							Gnm::ZFormat depthFmt = tfi.m_depthFmt;
							Gnm::DataFormat format = Gnm::DataFormat::build(depthFmt);
							Gnm::StencilFormat stencilFmt = tfi.m_stencilFmt;

							Gnm::TileMode depthTileMode;
							GpuAddress::computeSurfaceTileMode(
								Gnm::getGpuMode()
								, &depthTileMode
								, Gnm::kStencilInvalid == tfi.m_stencilFmt
								? GpuAddress::kSurfaceTypeDepthOnlyTarget
								: GpuAddress::kSurfaceTypeDepthTarget
								, format
								, 1
							);

							Gnm::DepthRenderTargetSpec drts;
							drts.init();
							drts.m_width = texture.m_width;
							drts.m_height = texture.m_height;
							drts.m_pitch = 0;
							drts.m_numSlices = 1;
							drts.m_zFormat = depthFmt;
							drts.m_stencilFormat = stencilFmt;
							drts.m_tileModeHint = depthTileMode;
							drts.m_minGpuMode = Gnm::getGpuMode();
							drts.m_numFragments = Gnm::kNumFragments1;
							drts.m_flags.enableHtileAcceleration = false;

							m_depthRenderTarget.init(&drts);

							BX_ASSERT((m_numSlicesDepth < 2) || ((m_numSlicesDepth > 1) && (stencilFmt == Gnm::kStencilInvalid)), "Stencil array not tested");

							m_depthRenderTarget.setAddresses(texture.m_gpuMemory.get(), texture.m_gpuStencilMemory.get());  // BBI-NOTE (dgalloway) arrays of depth + stencil have not been tested

							if (1 < texture.m_internalTexture.getTotalArraySliceCount())
							{
								m_depthRenderTarget.setArrayView(m_attachment[ii].layer, m_attachment[ii].layer);
							}

							m_haveDepthAttachment = true;
						}
						else
						{
							Gnm::RenderTarget& renderTarget = m_renderTargets[m_num].m_rtsi.m_renderTarget;
							result = renderTarget.initFromTexture(&texture.m_internalTexture, m_attachment[ii].mip);
							uint32_t numSlices = texture.m_internalTexture.getLastArraySliceIndex() - texture.m_internalTexture.getBaseArraySliceIndex() + 1;
							m_renderTargets[m_num].m_rtsi.m_numSlices = numSlices;

							DisplayBuffer* intermediateDisplayBuffer;

							if (m_frameBufferMSAA) {
								intermediateDisplayBuffer = &m_intermediateRenderTargets[ii];
								_initMsaaRenderTargetFromTexture(renderTarget.getDataFormat(), *intermediateDisplayBuffer, texture, ii);
								intermediateDisplayBuffer->m_rtsi.m_numSlices = numSlices;
							}

							if (texture.m_internalTexture.getTextureType() == Gnm::kTextureTypeCubemap || texture.m_internalTexture.getTextureType() == Gnm::kTextureType2dArray)
							{
								renderTarget.setArrayView(m_attachment[ii].layer, m_attachment[ii].layer);
								if (m_frameBufferMSAA) {
									intermediateDisplayBuffer->m_rtsi.m_renderTarget.setArrayView(m_attachment[ii].layer, m_attachment[ii].layer);
								}
							}

							m_num++;

							m_mask |= s_textureFormat[texture.m_textureFormat].m_mask << shift;
							shift += 4;

							// resolve target has to disable fmask compression
							renderTarget.setFmaskCompressionEnable(false);
						}

						BX_ASSERT(!result, "Render target creation failed")
					}
				}
			}
		}

		void FrameBufferGNM::resolve()
		{
			if (0 < m_num && m_frameBufferMSAA)
			{
				Gnmx::GfxContext& gfxc = s_renderGNM->m_currentInternalRenderContext->m_GFXContext;
				for (uint32_t ii = 0; ii < m_num; ++ii)
				{
					TextureHandle handle = m_attachment[ii].handle;
					if (isValid(handle) && m_renderTargets[ii].m_rtsi.m_renderTarget.getWidth() != 0)
					{
						Gnm::RenderTarget& renderTarget = m_intermediateRenderTargets[ii].m_rtsi.m_renderTarget;

						Gnm::WaitTargetSlot waitSlot = static_cast<Gnm::WaitTargetSlot>(Gnm::kWaitTargetSlotCb0 << ii);

						gfxc.waitForGraphicsWrites(renderTarget.getBaseAddress256ByteBlocks(), (renderTarget.getSliceSizeInBytes() * 1) >> 8,
							waitSlot | Gnm::kWaitTargetSlotDb, Gnm::kCacheActionWriteBackAndInvalidateL1andL2, Gnm::kExtendedCacheActionFlushAndInvalidateCbCache |
							Gnm::kExtendedCacheActionFlushAndInvalidateDbCache, Gnm::kStallCommandBufferParserDisable);

						Gnmx::hardwareMsaaResolve(&gfxc, &m_renderTargets[ii].m_rtsi.m_renderTarget, &renderTarget);
					}
				}
			}
		}

		void FrameBufferGNM::clear(const Clear& _clear, const Rect* _prect, const float _palette[][4])
		{
			auto& gfxc = s_renderGNM->m_currentInternalRenderContext->m_GFXContext;

			if (m_haveDepthAttachment)
			{
				if ((BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL) & _clear.m_flags)
				{
					s_renderGNM->_clearDepthStencilBuffer(gfxc, &m_depthRenderTarget, _prect, _clear);
				}
			}

			for (uint32_t ii = 0; ii < m_num; ++ii)
			{
				if (BGFX_CLEAR_COLOR & _clear.m_flags)
				{

					RenderTargetWithSliceInfo* rtsi;

					if (m_frameBufferMSAA) {
						rtsi = &m_intermediateRenderTargets[ii].m_rtsi;
					}
					else {
						rtsi = &m_renderTargets[ii].m_rtsi;
					}

					if (BGFX_CLEAR_COLOR_USE_PALETTE & _clear.m_flags)
					{
						uint8_t index = _clear.m_index[0];
						if (UINT8_MAX != index)
						{
							if (_prect != nullptr) {
								s_renderGNM->_clearRenderTargetPartial(gfxc, rtsi, _prect, _palette[index]);
							}
							else
							{
								// clear without cmask				
								s_renderGNM->_clearRenderTarget(gfxc, rtsi, _palette[index]);
							}
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


						if (_prect != nullptr) {
							s_renderGNM->_clearRenderTargetPartial(gfxc, rtsi, _prect, frgba);
						}
						else {
							// clear without cmask
							s_renderGNM->_clearRenderTarget(gfxc, rtsi, frgba);
						}

					}
				}
			}
		}

		void FrameBufferGNM::transitionTo(ResourceTransition transition) {

			bool enabledMSAA = m_frameBufferMSAA;
			for (uint32_t ii = 0; ii < m_num; ++ii) {
				{
					sce::Gnmx::ResourceBarrier resourceBarrier;
					if (transition == ResourceTransition::TargetToTexture) {
						if (enabledMSAA) {
							resourceBarrier.init(&m_intermediateRenderTargets[ii].m_rtsi.m_renderTarget, Gnmx::ResourceBarrier::kUsageRenderTarget, Gnmx::ResourceBarrier::kUsageRoTexture);
						}
						else {
							resourceBarrier.init(&m_renderTargets[ii].m_rtsi.m_renderTarget, Gnmx::ResourceBarrier::kUsageRenderTarget, Gnmx::ResourceBarrier::kUsageRoTexture);
						}
					}
					else {
						BX_ASSERT(transition == ResourceTransition::TextureToTarget, "Please implement extra FrameBufferGNM transitions");
						if (enabledMSAA) {
							resourceBarrier.init(&m_intermediateRenderTargets[ii].m_rtsi.m_renderTarget, Gnmx::ResourceBarrier::kUsageRoTexture, Gnmx::ResourceBarrier::kUsageRenderTarget);
						}
						else {
							resourceBarrier.init(&m_renderTargets[ii].m_rtsi.m_renderTarget, Gnmx::ResourceBarrier::kUsageRoTexture, Gnmx::ResourceBarrier::kUsageRenderTarget);
						}
					}
					s_renderGNM->m_currentInternalRenderContext->m_GFXContext.writeResourceBarrier(&resourceBarrier);
				}
			}

			if (m_haveDepthAttachment) {
				sce::Gnmx::ResourceBarrier depthResourceBarrier;
				if (transition == ResourceTransition::TargetToTexture) {
					depthResourceBarrier.init(&m_depthRenderTarget, Gnmx::ResourceBarrier::kUsageDepthSurface, Gnmx::ResourceBarrier::kUsageRoTexture);
				}
				else {
					BX_ASSERT(transition == ResourceTransition::TextureToTarget, "Please implement extra FrameBufferGNM transition");
					depthResourceBarrier.init(&m_depthRenderTarget, Gnmx::ResourceBarrier::kUsageRoTexture, Gnmx::ResourceBarrier::kUsageDepthSurface);
				}
				s_renderGNM->m_currentInternalRenderContext->m_GFXContext.writeResourceBarrier(&depthResourceBarrier);
			}
		}

		void FrameBufferGNM::set()
		{
			bool enabledMSAA = m_frameBufferMSAA;

			if (0 < m_num) {

				for (uint32_t ii = 0; ii < m_num; ++ii) {

					if (enabledMSAA) {
						s_renderGNM->m_currentInternalRenderContext->setRenderTarget(ii, &m_intermediateRenderTargets[ii].m_rtsi.m_renderTarget);

						// draw render target's image into intermediate render target
						// because in some case render target keep update without clearing,
						// but intermediate render target has to clear after resolve,
						// so copy render target image before draw the others.
						Gnm::Texture texture;
						texture.initFromRenderTarget(&m_renderTargets[ii].m_rtsi.m_renderTarget, false);

						_drawTexture(m_intermediateRenderTargets[ii].m_rtsi.m_renderTarget, texture, ii);
					}
					else
					{
						s_renderGNM->m_currentInternalRenderContext->setRenderTarget(ii, &m_renderTargets[ii].m_rtsi.m_renderTarget);
					}
				}
			}
			else {
				s_renderGNM->m_currentInternalRenderContext->setRenderTarget(0, nullptr);
			}

			if (m_haveDepthAttachment) {
				s_renderGNM->m_currentInternalRenderContext->setDepthRenderTarget(&m_depthRenderTarget);
			}
			else {
				s_renderGNM->m_currentInternalRenderContext->setDepthRenderTarget(nullptr);
			}
		}

		// This function assumes the framebuffer has already been created so some of the local variables have already been set
		void FrameBufferGNM::updateTextureBindings() {
			if (0 < m_numTh) {
				for (uint32_t ii = 0; ii < m_numTh; ++ii) {
					TextureHandle handle = m_attachment[ii].handle;
					if (isValid(handle)) {
						TextureGNM& texture = s_renderGNM->m_textures[handle.idx];

						int32_t result = -1;
						if ((bimg::isDepth(bimg::TextureFormat::Enum(texture.m_textureFormat))))
						{
							// BBI-NOTE (dgalloway) this code hasn't been refactored to use the new stencil memory allocations
							// Badger doesn't currently use this code path.

							BGFX_FATAL(false, bgfx::Fatal::DebugCheck, "Unsupported code path");

							const Gnm::SizeAlign oldStencilSizeAlign = m_depthRenderTarget.getStencilSizeAlign();
							result = m_depthRenderTarget.initFromTexture(&texture.m_internalTexture, NULL, 0, NULL);
							m_depthRenderTarget.setStencilFormat(kStencilFormat);
						}
						else {
							Gnm::RenderTarget& renderTarget = m_renderTargets[ii].m_rtsi.m_renderTarget;
							result = renderTarget.initFromTexture(&texture.m_internalTexture, 0);
							const uint32_t numSlices = renderTarget.getLastArraySliceIndex() - renderTarget.getBaseArraySliceIndex() + 1;
							m_renderTargets[ii].m_rtsi.m_numSlices = numSlices;

							// resolve target has to disable fmask compression
							renderTarget.setFmaskCompressionEnable(false);

							if (m_frameBufferMSAA) {
								_initMsaaRenderTargetFromTexture(renderTarget.getDataFormat(), m_intermediateRenderTargets[ii], texture, ii);
								m_intermediateRenderTargets[ii].m_rtsi.m_numSlices = numSlices; // renderTarget.getLastArraySliceIndex() - renderTarget.getBaseArraySliceIndex() + 1
							}
						}

						BX_ASSERT(!result, "Render target creation failed")
					}
				}
			}
		}

		void FrameBufferGNM::_initMsaaRenderTargetFromTexture(const Gnm::DataFormat& colorFormat, DisplayBuffer& msaaRenderTarget, const gnm::TextureGNM& texture, uint32_t slot) {
			Gnm::RenderTarget& intermediateRenderTarget = msaaRenderTarget.m_rtsi.m_renderTarget;

			Gnm::RenderTargetSpec spec;
			spec.init();
			spec.m_width = texture.m_width;
			spec.m_height = texture.m_height;
			spec.m_pitch = 0;
			spec.m_numSlices = 1;
			spec.m_colorFormat = colorFormat;
			spec.m_colorTileModeHint = texture.m_internalTexture.getTileMode();
			spec.m_minGpuMode = s_renderGNM->m_featureLevel;
			spec.m_numSamples = s_renderGNM->m_msaaSampleInfo->m_maxSamples;
			spec.m_numFragments = s_renderGNM->m_msaaSampleInfo->m_maxFragments;
			spec.m_flags.enableCmaskFastClear = 1;
			spec.m_flags.enableFmaskCompression = 1;

			intermediateRenderTarget.init(&spec);

			const Gnm::SizeAlign rtSizeAlign = intermediateRenderTarget.getColorSizeAlign();
			const Gnm::SizeAlign cmaskSizeAlign = intermediateRenderTarget.getCmaskSizeAlign();
			const Gnm::SizeAlign fmaskSizeAlign = intermediateRenderTarget.getFmaskSizeAlign();

			GnmAllocator& allocator = s_renderGNM->m_garlicAllocator;

			msaaRenderTarget.m_gpuBuffer = allocator.allocateUnique<uint8_t>(rtSizeAlign.m_size, rtSizeAlign.m_align, Gnm::ResourceType::kResourceTypeRenderTargetBaseAddress, "displaybuffer rt");
			msaaRenderTarget.m_cmaskBuffer = allocator.allocateUnique<uint8_t>(cmaskSizeAlign.m_size, cmaskSizeAlign.m_align, Gnm::ResourceType::kResourceTypeRenderTargetCMaskAddress, "cmask");
			msaaRenderTarget.m_fmaskBuffer = allocator.allocateUnique<uint8_t>(fmaskSizeAlign.m_size, fmaskSizeAlign.m_align, Gnm::ResourceType::kResourceTypeRenderTargetFMaskAddress, "fmask");

			intermediateRenderTarget.setFmaskCompressionEnable(true);
			intermediateRenderTarget.setCmaskFastClearEnable(true);
			intermediateRenderTarget.setAddresses(msaaRenderTarget.m_gpuBuffer.get(), msaaRenderTarget.m_cmaskBuffer.get(), msaaRenderTarget.m_fmaskBuffer.get());

			_drawTexture(intermediateRenderTarget, texture.m_internalTexture, slot);
		}

		void FrameBufferGNM::_drawTexture(Gnm::RenderTarget& renderTarget, const sce::Gnm::Texture& texture, uint32_t slot) {

			Gnmx::GnmxGfxContext& gfxc = s_renderGNM->m_currentInternalRenderContext->m_GFXContext;
			s_renderGNM->m_currentInternalRenderContext->withRenderTarget(slot, &renderTarget, [&gfxc, &texture, &renderTarget] {
				Gnm::BlendControl blendControl;
				blendControl.init();
				blendControl.setBlendEnable(false);
				gfxc.setBlendControl(0, blendControl);
				gfxc.setRenderTargetMask(0x0000000F); // enable MRT0 output only
				gfxc.setDepthStencilDisable();
				uint32_t texRight = texture.getWidth();
				uint32_t texBottom = texture.getHeight();
				uint32_t rtRight = renderTarget.getWidth();
				uint32_t rtBottom = renderTarget.getHeight();
				rtRight = texRight > rtRight ? rtRight : texRight;
				rtBottom = texBottom > rtBottom ? rtBottom : texBottom;
				gfxc.setupScreenViewport(0, 0, rtRight, rtBottom, 1.f, 0.f);
				gfxc.setPsShader(sCopyShader.m_xxShader, &sCopyShader.m_offsetsTable);
				gfxc.setTextures(Gnm::kShaderStagePs, 0, 1, &texture);
				Gnmx::renderFullScreenQuad(&gfxc);
				}
			);
		}

		void BorderColorTableGNM::init() {
			// Alignment based on specification of datatable
			BX_ASSERT(mColorTable == nullptr, "Cannot initialize twice");
			mColorTable = static_cast<float*>(s_renderGNM->m_garlicAllocator.allocate(
				sizeof(float) * kFloatPerColor * mMaxTableSize,
				kTableAlignment,
				Gnm::kResourceTypeGenericBuffer,
				"BorderColorTable"));

			s_renderGNM->m_currentInternalRenderContext->m_GFXContext.setBorderColorTableAddr(mColorTable);
		}
		void BorderColorTableGNM::shutdown() {
			s_renderGNM->m_currentInternalRenderContext->m_GFXContext.setBorderColorTableAddr(nullptr);
			if (mColorTable != nullptr) {
				s_renderGNM->m_garlicAllocator.release(mColorTable);
			}
			mColorTable = nullptr;
		}
		float* BorderColorTableGNM::getFloat4FromIndex(uint32_t index) {
			BX_ASSERT(index < mCurrentIndex, "Must grab a valid index");
			return mColorTable + index * kFloatPerColor;
		}
		uint32_t BorderColorTableGNM::getIndexFromColor(const float* color) {
			BX_ASSERT(color != nullptr, "Cannot pass null values")
				constexpr uint8_t maxColorValue = 255;
			uint32_t packedColor{ 0 };
			for (uint32_t i = 0; i < kFloatPerColor; ++i) {
				uint8_t val = std::min(static_cast<uint8_t>(round(color[i] * 255.0f)), maxColorValue);
				packedColor |= val;
				if (i < 3) {
					packedColor = packedColor << 8;
				}
			}

			auto iter = mColorToIndexMap.find(packedColor);
			if (iter != mColorToIndexMap.end()) {
				return iter->second;
			}
			else {
				const uint32_t indexToReturn = mCurrentIndex++;
				mColorToIndexMap.insert({ packedColor, indexToReturn });
				::memcpy(getFloat4FromIndex(indexToReturn), color, sizeof(float) * 4);
				return indexToReturn;
			}
		}





#if 0 // Actual Shader source for pixel_clear_p.pssl
		/* SIE CONFIDENTIAL
		PlayStation(R)4 Programmer Tool Runtime Library Release 06.508.001
		* Copyright (C) 2013 Sony Interactive Entertainment Inc.
		* All Rights Reserved.
		*/

#include "shader_base.h"

		struct PS_OUT {
			float4 Color : S_TARGET_OUTPUT0;
		};

		ConstantBuffer pix_clear_constants : register(c0) {
			float4 m_color;
		};


		PS_OUT main() {
			PS_OUT output = (PS_OUT)0;
			output.Color = m_color;
			return output;
		}
#endif

		//static shader binary
		const uint32_t sPixelClear[] =
		{
			0x74620400, 0x0868a147, 0x00000000, 0x03000101,
			0x000000ac, 0x00000000, 0x00000000, 0x00000000,
			0x00000000, 0x72646853, 0x00020007, 0x03001002,
			0x00000000, 0x0100005c, 0x00000000, 0x00000040,
			0xffffffff, 0x002c0000, 0x00000008, 0x00000000,
			0x00000004, 0x00000002, 0x00000002, 0x00000000,
			0x00000000, 0x00000010, 0x0000000f, 0x00000000,
			0x00000002, 0xbeeb03ff, 0x00000007, 0xc2800100,
			0xbf8c007f, 0x7e020201, 0x7e000203, 0x5e020200,
			0x5e000002, 0xf8001c0f, 0x00000001, 0xbf810000,
			0x0001e8cd, 0x00000004, 0x00000002, 0x00000342,
			0x67462cac, 0x5362724f, 0x07726468, 0x00002c41,
			0x050c0102, 0x0868a147, 0x00000000, 0x4e4bc8eb,
			0x00000001, 0x00000000, 0x00000001, 0x00000000,
			0x00000100, 0x00000000, 0x00000044, 0x00000000,
			0x00000010, 0x006a0416, 0x00000001, 0x00000000,
			0x00000038, 0x03000103, 0x00000000, 0x00000010,
			0x00000000, 0xffffffff, 0x00000000, 0xffffffff,
			0x0000002c, 0x00000030, 0x00003803, 0x00000000,
			0x0000002e, 0x00000035, 0x5f786970, 0x61656c63,
			0x6f635f72, 0x6174736e, 0x0073746e, 0x6f635f6d,
			0x00726f6c, 0x5f6f6e28, 0x656d616e, 0x616d0029,
			0x432e6e69, 0x726f6c6f, 0x545f5300, 0x45475241,
			0x554f5f54, 0x54555054, 0x00000000, 0x00000000
		};

#if 0 // Actual Shader source for cs_set_uint_c.pssl
		/* SIE CONFIDENTIAL
		PlayStation(R)4 Programmer Tool Runtime Library Release 06.508.001
		* Copyright (C) 2013 Sony Interactive Entertainment Inc.
		* All Rights Reserved.
		*/

#include "shader_base.h"

#define THREADS_PER_WAVEFRONT 64

		RW_DataBuffer<uint> Destination : register(u0);
		DataBuffer<uint> Source : register(t0);
		ConstantBuffer Constants : register(c0) { uint m_destUints; uint m_srcUints; };

		[NUM_THREADS(THREADS_PER_WAVEFRONT, 1, 1)]
		void main(uint ID : S_DISPATCH_THREAD_ID) {
			if (ID < m_destUints)
				Destination[ID] = Source[ID % m_srcUints];
		}
#endif

		const uint32_t sComputeShaderSetUint[] =
		{
			0x74620400, 0x88d49e3f, 0x00000000, 0x03000102,
			0x00000158, 0x00000000, 0x00010040, 0x00000001,
			0x00000000, 0x72646853, 0x00020007, 0x03000d04,
			0x00000000, 0x03000114, 0x00000000, 0x00000034,
			0xffffffff, 0x002c0041, 0x00000098, 0x00000040,
			0x00000001, 0x00000001, 0x00000000, 0x00000000,
			0x00040004, 0x00080002, 0xbeeb03ff, 0x0000001e,
			0x8f6a860c, 0xc2060900, 0x4a04006a, 0xbf8c007f,
			0x7da8040c, 0xbf88002d, 0xc2050901, 0xbf8c007f,
			0x7e000c0a, 0x7e005700, 0x100000ff, 0x4f800000,
			0x7e060f00, 0xd2ec6a00, 0x0202060a, 0x4c080080,
			0xd10a0008, 0x00020280, 0xd2000000, 0x00220104,
			0xd2d40001, 0x00020700, 0x4c000303, 0x4a020303,
			0xd2000000, 0x00220101, 0xd2d40000, 0x00020500,
			0xd2d20001, 0x0002000a, 0x4c060302, 0x7d86060a,
			0xd18c0008, 0x00020302, 0x87ea6a08, 0x50000080,
			0xd2506a00, 0x002200c1, 0xbf010a80, 0x85ea807e,
			0x000000c1, 0xd2d60000, 0x0002000a, 0x4c000102,
			0xe0002000, 0x80000000, 0xd1a80000, 0x00020406,
			0xbf8c0f70, 0xe0102000, 0x80010002, 0xbf810000,
			0xcd118d4d, 0x000001e8, 0x00000008, 0x00000000,
			0x00040004, 0x00080002, 0x00000342, 0x67462cac,
			0x5362724f, 0x07726468, 0x0000d851, 0x050c0302,
			0x88d49e3f, 0x00000000, 0xd035cdd2, 0x00000003,
			0x00000000, 0x00000002, 0x00000000, 0x00000001,
			0x00000000, 0x00000044, 0x00000000, 0x00000008,
			0x006a0416, 0x00000002, 0x00000000, 0x0000008c,
			0x00000000, 0x00000000, 0x000c000c, 0x00000000,
			0x00000002, 0x0000007e, 0x00000000, 0x00000000,
			0x000c0100, 0x00000000, 0x00000002, 0x00000072,
			0x0300010c, 0x00000000, 0x00000004, 0x00000000,
			0xffffffff, 0x00000000, 0xffffffff, 0x00000059,
			0x00000061, 0x0300010c, 0x00000004, 0x00000004,
			0x00000000, 0xffffffff, 0x00000000, 0xffffffff,
			0x0000004b, 0x0000003d, 0x0000290c, 0x00000000,
			0x00000046, 0x0000002d, 0x736e6f43, 0x746e6174,
			0x65440073, 0x6e697473, 0x6f697461, 0x6f53006e,
			0x65637275, 0x645f6d00, 0x55747365, 0x73746e69,
			0x6f6e2800, 0x6d616e5f, 0x6d002965, 0x6372735f,
			0x746e6955, 0x44490073, 0x00000000,
		};

#if 0 // Actual Shader source for cs_set_uint_fast_c.pssl
		/* SIE CONFIDENTIAL
		PlayStation(R)4 Programmer Tool Runtime Library Release 06.508.001
		* Copyright (C) 2013 Sony Interactive Entertainment Inc.
		* All Rights Reserved.
		*/

#include "shader_base.h"

#define THREADS_PER_WAVEFRONT 64

		RW_DataBuffer<uint> Destination : register(u0);
		DataBuffer<uint> Source : register(t0);
		ConstantBuffer Constants : register(c0) { uint m_destUints; uint m_srcUintsMinusOne; };

		[NUM_THREADS(THREADS_PER_WAVEFRONT, 1, 1)]
		void main(uint ID : S_DISPATCH_THREAD_ID) {
			if (ID < m_destUints)
				Destination[ID] = Source[ID & m_srcUintsMinusOne]; // Notice fast version uses & operator instead of %
		}
#endif

		const uint32_t sComputeShaderSetUintFast[] =
		{
			0x74620400, 0x14dfaffd, 0x00000000, 0x03000102,
			0x000000d0, 0x00000000, 0x00010040, 0x00000001,
			0x00000000, 0x72646853, 0x00020007, 0x03000d04,
			0x00000000, 0x0300008c, 0x00000000, 0x00000034,
			0xffffffff, 0x002c0040, 0x00000098, 0x00000040,
			0x00000001, 0x00000001, 0x00000000, 0x00000000,
			0x00040004, 0x00080002, 0xbeeb03ff, 0x0000000d,
			0x8f6a860c, 0xc2060900, 0x4a00006a, 0xbf8c007f,
			0x7da8000c, 0xbf88000a, 0xc2040901, 0xbf8c007f,
			0x36020008, 0xe0002000, 0x80000101, 0xd1a80000,
			0x00020006, 0xbf8c0f70, 0xe0102000, 0x80010100,
			0xbf810000, 0xcd118d4d, 0x000001e8, 0x00000008,
			0x00000000, 0x00040004, 0x00080002, 0x00000000,
			0x00000342, 0x67462cac, 0x5362724f, 0x07726468,
			0x00004c51, 0x050c0303, 0x14dfaffd, 0x00000000,
			0x6edb2cc6, 0x00000003, 0x00000000, 0x00000002,
			0x00000000, 0x00000001, 0x00000000, 0x0000004c,
			0x00000000, 0x00000008, 0x006a0416, 0x00000002,
			0x00000000, 0x0000008c, 0x00000000, 0x00000000,
			0x000c000c, 0x00000000, 0x00000002, 0x0000007e,
			0x00000000, 0x00000000, 0x000c0100, 0x00000000,
			0x00000002, 0x00000072, 0x0300010c, 0x00000000,
			0x00000004, 0x00000000, 0xffffffff, 0x00000000,
			0xffffffff, 0x00000059, 0x00000061, 0x0300010c,
			0x00000004, 0x00000004, 0x00000000, 0xffffffff,
			0x00000000, 0xffffffff, 0x0000004b, 0x0000003d,
			0x0000290c, 0x00000000, 0x0000004e, 0x0000002d,
			0x736e6f43, 0x746e6174, 0x65440073, 0x6e697473,
			0x6f697461, 0x6f53006e, 0x65637275, 0x645f6d00,
			0x55747365, 0x73746e69, 0x6f6e2800, 0x6d616e5f,
			0x6d002965, 0x6372735f, 0x746e6955, 0x6e694d73,
			0x6e4f7375, 0x44490065, 0x00000000,
		};


#if 0 // Actual Shader source for TextureToTexture.pssl
		RW_Texture2D<int4> dest_tex : register(u1);
		Texture2D<int4> src_tex : register(t0);

		ConstantBuffer cbuf : register(c0) {
			uint3 dest_offset;
			uint3 src_offset;
			uint3 tex_size;
			uint dst_mip;
			uint src_mip;
		};

		[NUM_THREADS(8, 8, 1)]
		void main(uint3 position : S_DISPATCH_THREAD_ID) {
			if (all(position.xy < tex_size.xy)) {
				dest_tex.MipMaps(dst_mip, position.xy + dest_offset.xy) = src_tex.MipMaps(src_mip, position.xy + src_offset.xy);
			}
		}
#endif

		const uint32_t sComputeShaderCopyTexToTex[] =
		{
			0x74620400, 0x87d26f43, 0x00000000, 0x03000102,
			0x0000011c, 0x00000000, 0x00080008, 0x00000001,
			0x00000000, 0x72646853, 0x00020007, 0x03000e04,
			0x00000000, 0x040000d4, 0x00000000, 0x00000038,
			0xffffffff, 0x002c00c1, 0x0000099c, 0x00000008,
			0x00000008, 0x00000001, 0x00000000, 0x03000000,
			0x00080002, 0x000c011b, 0x03100104, 0xbeeb03ff,
			0x00000016, 0x8f6a830e, 0x8f10830f, 0xc2470908,
			0x4a06006a, 0xd2ba0001, 0x04050010, 0xbf8c007f,
			0xd1880010, 0x0002020f, 0x7d88060e, 0x87ea106a,
			0xbeea246a, 0xbf880012, 0xc2c80900, 0xc24c090b,
			0xc0c40d00, 0xbf8c007f, 0x4a000614, 0x7e040219,
			0xd2ba0004, 0x040d0010, 0xd2ba0005, 0x04050011,
			0xd2ba0001, 0x04050015, 0xf0040f00, 0x00000000,
			0x7e0c0218, 0xbf8c0f70, 0xf0240f00, 0x00020004,
			0xbf810000, 0x01e8cd1f, 0x00000afa, 0x00000800,
			0xcd9f0000, 0x00000000, 0x00000014, 0x03000000,
			0x00080002, 0x000c011b, 0x03100104, 0x00000342,
			0x67462cac, 0x5362724f, 0x07726468, 0x00008851,
			0x050c0402, 0x87d26f43, 0x00000000, 0xee61e571,
			0x00000003, 0x00000000, 0x00000005, 0x00000000,
			0x00000001, 0x00000000, 0x0000005c, 0x00000000,
			0x00000000, 0x000b0502, 0x00000000, 0x00000000,
			0x000000f8, 0x00000001, 0x00000010, 0x000b000e,
			0x00000000, 0x00000000, 0x000000e8, 0x00000000,
			0x00000034, 0x006a0416, 0x00000005, 0x00000000,
			0x000000d9, 0x0300010e, 0x00000000, 0x0000000c,
			0x00000000, 0xffffffff, 0x00000000, 0xffffffff,
			0x000000be, 0x000000c6, 0x0300010e, 0x00000010,
			0x0000000c, 0x00000000, 0xffffffff, 0x00000000,
			0xffffffff, 0x000000b0, 0x000000a2, 0x0300010e,
			0x00000020, 0x0000000c, 0x00000000, 0xffffffff,
			0x00000000, 0xffffffff, 0x00000097, 0x0000007e,
			0x0300010c, 0x0000002c, 0x00000004, 0x00000000,
			0xffffffff, 0x00000000, 0xffffffff, 0x0000007c,
			0x0000005a, 0x0300010c, 0x00000030, 0x00000004,
			0x00000000, 0xffffffff, 0x00000000, 0xffffffff,
			0x00000060, 0x00000036, 0x0000290e, 0x00000000,
			0x00000058, 0x00000026, 0x5f637273, 0x00786574,
			0x74736564, 0x7865745f, 0x75626300, 0x65640066,
			0x6f5f7473, 0x65736666, 0x6e280074, 0x616e5f6f,
			0x0029656d, 0x5f637273, 0x7366666f, 0x74007465,
			0x735f7865, 0x00657a69, 0x5f747364, 0x0070696d,
			0x5f637273, 0x0070696d, 0x69736f70, 0x6e6f6974,
			0x00000000, 0x00000000
		};


#if 0 // Actual Shader source for TextureToTextureArray.pssl
		RW_Texture2D_Array<int4> dest_tex : register(u1);
		Texture2D<int4> src_tex : register(t0);

		ConstantBuffer cbuf : register(c0) {
			uint3 dest_offset;
			uint3 src_offset;
			uint3 tex_size;
			uint dst_mip;
			uint src_mip;
		};

		[NUM_THREADS(8, 8, 1)]
		void main(uint3 position : S_DISPATCH_THREAD_ID) {
			if (all(position < tex_size)) {
				dest_tex.MipMaps(dst_mip, position + dest_offset) = src_tex.MipMaps(src_mip, position.xy + src_offset.xy);
			}
		}
#endif

		const uint32_t sComputeShaderCopyTexToTexArray[] =
		{
			0x74620400, 0x5fa5267a, 0x00000000, 0x03000102,
			0x0000013c, 0x00000000, 0x00080008, 0x00000001,
			0x00000000, 0x72646853, 0x00020007, 0x03000e04,
			0x00000000, 0x040000f4, 0x00000000, 0x00000038,
			0xffffffff, 0x002c00c1, 0x00000b9c, 0x00000008,
			0x00000008, 0x00000001, 0x00000000, 0x03000000,
			0x00080002, 0x000c011b, 0x03100104, 0xbeeb03ff,
			0x0000001a, 0xc28a0908, 0x8f6a830e, 0x8f0e830f,
			0xbf8c007f, 0xbf0a1610, 0xd2ba0004, 0x0401006a,
			0xd2ba0005, 0x0405000e, 0xd188000e, 0x00020a15,
			0xd1880012, 0x00020814, 0x85ea807e, 0x87ea6a0e,
			0x87ea6a12, 0xbeea246a, 0xbf880015, 0xc2ca0900,
			0xc249090b, 0xc0c40d00, 0xbf8c007f, 0xd2ba0000,
			0x04110018, 0xd2ba0001, 0x04150019, 0x7e040213,
			0xf0040f00, 0x00000000, 0x7e0c0216, 0x4a080814,
			0xd2ba0005, 0x04150015, 0xd2ba0006, 0x04190010,
			0x7e0e0212, 0xbf8c0f70, 0xf0244f00, 0x00020004,
			0xbf810000, 0x01e8cd1f, 0x00000afa, 0x00000800,
			0xeddf0000, 0x00000000, 0x00000014, 0x03000000,
			0x00080002, 0x000c011b, 0x03100104, 0x00000342,
			0x67462cac, 0x5362724f, 0x07726468, 0x0000a851,
			0x050c0402, 0x5fa5267a, 0x00000000, 0x8c8c1933,
			0x00000003, 0x00000000, 0x00000005, 0x00000000,
			0x00000001, 0x00000000, 0x0000005c, 0x00000000,
			0x00000000, 0x000b0502, 0x00000000, 0x00000000,
			0x000000f8, 0x00000001, 0x00000010, 0x000b0011,
			0x00000000, 0x00000000, 0x000000e8, 0x00000000,
			0x00000034, 0x006a0416, 0x00000005, 0x00000000,
			0x000000d9, 0x0300010e, 0x00000000, 0x0000000c,
			0x00000000, 0xffffffff, 0x00000000, 0xffffffff,
			0x000000be, 0x000000c6, 0x0300010e, 0x00000010,
			0x0000000c, 0x00000000, 0xffffffff, 0x00000000,
			0xffffffff, 0x000000b0, 0x000000a2, 0x0300010e,
			0x00000020, 0x0000000c, 0x00000000, 0xffffffff,
			0x00000000, 0xffffffff, 0x00000097, 0x0000007e,
			0x0300010c, 0x0000002c, 0x00000004, 0x00000000,
			0xffffffff, 0x00000000, 0xffffffff, 0x0000007c,
			0x0000005a, 0x0300010c, 0x00000030, 0x00000004,
			0x00000000, 0xffffffff, 0x00000000, 0xffffffff,
			0x00000060, 0x00000036, 0x0000290e, 0x00000000,
			0x00000058, 0x00000026, 0x5f637273, 0x00786574,
			0x74736564, 0x7865745f, 0x75626300, 0x65640066,
			0x6f5f7473, 0x65736666, 0x6e280074, 0x616e5f6f,
			0x0029656d, 0x5f637273, 0x7366666f, 0x74007465,
			0x735f7865, 0x00657a69, 0x5f747364, 0x0070696d,
			0x5f637273, 0x0070696d, 0x69736f70, 0x6e6f6974,
			0x00000000, 0x00000000
		};


#if 0 // Actual Shader source for TextureArrayToTextureArray.pssl
		RW_Texture2D_Array<int4> dest_tex : register(u1);
		Texture2D_Array<int4> src_tex : register(t0);

		ConstantBuffer cbuf : register(c0) {
			uint3 dest_offset;
			uint3 src_offset;
			uint3 tex_size;
			uint dst_mip;
			uint src_mip;
		};

		[NUM_THREADS(8, 8, 1)]
		void main(uint3 position : S_DISPATCH_THREAD_ID) {
			if (all(position < tex_size)) {
				dest_tex.MipMaps(dst_mip, position + dest_offset) = src_tex.MipMaps(src_mip, position + src_offset);
			}
		}
#endif

		const uint32_t sComputeShaderCopyTexArrayToTexArray[] =
		{
			0x74620400, 0x63da7135, 0x00000000, 0x03000102,
			0x0000014c, 0x00000000, 0x00080008, 0x00000001,
			0x00000000, 0x72646853, 0x00020007, 0x03000e04,
			0x00000000, 0x04000104, 0x00000000, 0x00000038,
			0xffffffff, 0x002c00c1, 0x00000b9c, 0x00000008,
			0x00000008, 0x00000001, 0x00000000, 0x03000000,
			0x00080002, 0x000c011b, 0x03100104, 0xbeeb03ff,
			0x0000001c, 0xc28a0908, 0x8f6a830e, 0x8f0e830f,
			0xbf8c007f, 0xbf0a1610, 0xd2ba0004, 0x0401006a,
			0xd2ba0005, 0x0405000e, 0xd188000e, 0x00020a15,
			0xd1880012, 0x00020814, 0x85ea807e, 0x87ea6a0e,
			0x87ea6a12, 0xbeea246a, 0xbf880018, 0xc2ca0900,
			0xc249090b, 0xc0c40d00, 0xbf8c007f, 0x7e04021a,
			0xd2ba0000, 0x04110018, 0xd2ba0001, 0x04150019,
			0xd2ba0002, 0x04090010, 0x7e060213, 0xf0044f00,
			0x00000000, 0x7e0c0216, 0x4a080814, 0xd2ba0005,
			0x04150015, 0xd2ba0006, 0x04190010, 0x7e0e0212,
			0xbf8c0f70, 0xf0244f00, 0x00020004, 0xbf810000,
			0x01e8cd5f, 0x00000afa, 0x00000800, 0xeddf0000,
			0x00000000, 0x00000014, 0x03000000, 0x00080002,
			0x000c011b, 0x03100104, 0x00000000, 0x00000342,
			0x67462cac, 0x5362724f, 0x07726468, 0x0000b451,
			0x050c0403, 0x63da7135, 0x00000000, 0x05d581a4,
			0x00000003, 0x00000000, 0x00000005, 0x00000000,
			0x00000001, 0x00000000, 0x0000005c, 0x00000000,
			0x00000000, 0x000b0506, 0x00000000, 0x00000000,
			0x000000f8, 0x00000001, 0x00000010, 0x000b0011,
			0x00000000, 0x00000000, 0x000000e8, 0x00000000,
			0x00000034, 0x006a0416, 0x00000005, 0x00000000,
			0x000000d9, 0x0300010e, 0x00000000, 0x0000000c,
			0x00000000, 0xffffffff, 0x00000000, 0xffffffff,
			0x000000be, 0x000000c6, 0x0300010e, 0x00000010,
			0x0000000c, 0x00000000, 0xffffffff, 0x00000000,
			0xffffffff, 0x000000b0, 0x000000a2, 0x0300010e,
			0x00000020, 0x0000000c, 0x00000000, 0xffffffff,
			0x00000000, 0xffffffff, 0x00000097, 0x0000007e,
			0x0300010c, 0x0000002c, 0x00000004, 0x00000000,
			0xffffffff, 0x00000000, 0xffffffff, 0x0000007c,
			0x0000005a, 0x0300010c, 0x00000030, 0x00000004,
			0x00000000, 0xffffffff, 0x00000000, 0xffffffff,
			0x00000060, 0x00000036, 0x0000290e, 0x00000000,
			0x00000058, 0x00000026, 0x5f637273, 0x00786574,
			0x74736564, 0x7865745f, 0x75626300, 0x65640066,
			0x6f5f7473, 0x65736666, 0x6e280074, 0x616e5f6f,
			0x0029656d, 0x5f637273, 0x7366666f, 0x74007465,
			0x735f7865, 0x00657a69, 0x5f747364, 0x0070696d,
			0x5f637273, 0x0070696d, 0x69736f70, 0x6e6f6974,
			0x00000000, 0x00000000
		};

#if 0 // Actual Shader source for copytexture2d_p.pssl
		/* SIE CONFIDENTIAL
		PlayStation(R)4 Programmer Tool Runtime Library Release 06.508.001
		* Copyright (C) 2013 Sony Interactive Entertainment Inc.
		* All Rights Reserved.
		*/

		Texture2D<float4> texture;

		float4 main(float4 position : S_POSITION) : S_TARGET_OUTPUT
		{
			return texture[(uint2)position.xy];
		}
#endif

			const uint32_t sCopyShaderSetUint[] = {
				0x74620400, 0x333394b0, 0x00000000, 0x03000101,
				0x000000b4, 0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x72646853, 0x00020007, 0x03001002,
				0x00000000, 0x01000064, 0x00000000, 0x00000040,
				0xffffffff, 0x002c0040, 0x00000010, 0x00000000,
				0x00000004, 0x00000302, 0x00000302, 0x00000000,
				0x00000000, 0x00000010, 0x0000000f, 0x00000000,
				0x03000000, 0xbeeb03ff, 0x00000008, 0x7e000f02,
				0x7e020f03, 0xf0000f00, 0x00000000, 0xbf8c0f70,
				0x5e000300, 0x5e020702, 0xf8001c0f, 0x00000100,
				0xbf810000, 0x0000001f, 0x00000004, 0x03000000,
				0x00000000, 0x00000342, 0x67462cac, 0x5362724f,
				0x07726468, 0x00003041, 0x050c0103, 0x333394b0,
				0x00000000, 0x82d3dadd, 0x00000001, 0x00000000,
				0x00000000, 0x00000000, 0x00000101, 0x00000000,
				0x00000034, 0x00000000, 0x00000000, 0x00030502,
				0x00000000, 0x00000000, 0x00000024, 0x00002e03,
				0x00000000, 0x00000020, 0x00000025, 0x00003803,
				0x00000000, 0x00000024, 0x00000025, 0x74786574,
				0x00657275, 0x69736f70, 0x6e6f6974, 0x505f5300,
				0x5449534f, 0x004e4f49, 0x6e69616d, 0x545f5300,
				0x45475241, 0x554f5f54, 0x54555054, 0x00000000
		};

#if 0 // Actual Shader source for TextureToTextureCube.pssl
		// Changed RW_TextureCube to RW_TextureCube_Array
		// https://ps4.siedev.net/technotes/view/965
		RW_TextureCube_Array<int4> dest_tex : register(u1);
		Texture2D<int4> src_tex : register(t0);

		ConstantBuffer cbuf : register(c0) {
			uint3 dest_offset;
			uint3 src_offset;
			uint3 tex_size;
			uint dst_mip;
			uint src_mip;
		};

		[NUM_THREADS(8, 8, 1)]
		void main(uint3 position : S_DISPATCH_THREAD_ID) {
			if (all(position < tex_size)) {
				dest_tex.MipMaps(dst_mip, int4(position + dest_offset, 0)) = src_tex.MipMaps(src_mip, position.xy + src_offset.xy);
			}
		}
#endif

		const uint32_t sComputeShaderCopyTexToTexCube[]
		{
			0x16820400, 0x17bd527e, 0x00000000, 0x03000102,
			0x00000174, 0x00000000, 0x00080008, 0x00000001,
			0x00000000, 0x72646853, 0x00020007, 0x03000e04,
			0x00000000, 0x0400012c, 0x00000000, 0x00000038,
			0xffffffff, 0x002c00c1, 0x00000b9c, 0x00000008,
			0x00000008, 0x00000001, 0x00000000, 0x03000000,
			0x00080002, 0x000c011b, 0x03100104, 0xbeeb03ff,
			0x00000021, 0xc28a0908, 0x8f6a830e, 0x8f0e830f,
			0xbf8c007f, 0xbf0a1610, 0xd2ba0004, 0x0401006a,
			0xd2ba0005, 0x0405000e, 0xd188000e, 0x00020a15,
			0xd1880012, 0x00020814, 0x85ea807e, 0x87ea6a0e,
			0x87ea6a12, 0xbeea246a, 0xbf880023, 0xc2ca0900,
			0xc249090b, 0xc0c40d00, 0xbf8c007f, 0xd2ba0000,
			0x04110018, 0xd2ba0001, 0x04150019, 0x7e040213,
			0xf0040f00, 0x00000000, 0x93eaff0c, 0x000d0000,
			0x936a866a, 0x816a856a, 0x87006aff, 0x00001fff,
			0x8701ff0c, 0xffffe000, 0x7e0c0216, 0xd2ba0004,
			0x04110014, 0xd2ba0005, 0x04150015, 0xd2ba0006,
			0x04190010, 0x7e0e0212, 0x880c0100, 0x876aff0b,
			0x0fffffff, 0x880b6aff, 0xd0000000, 0xbf8c0f70,
			0xf0244f00, 0x00020004, 0xbf810000, 0x01e8cd1f,
			0x00000afa, 0x00000800, 0xddbf0000, 0x00000000,
			0x00000014, 0x03000000, 0x00080002, 0x000c011b,
			0x03100104, 0x00000342, 0xb1682057, 0x5362724f,
			0x07726468, 0x0000e051, 0x050c0402, 0x17bd527e,
			0x00000000, 0x2b10b038, 0x00000003, 0x00000000,
			0x00000005, 0x00000000, 0x00000001, 0x00000000,
			0x0000005c, 0x00000000, 0x00000000, 0x000b0502,
			0x00000000, 0x00000000, 0x000000f8, 0x00000001,
			0x00000010, 0x000b001e, 0x00000000, 0x00000000,
			0x000000e8, 0x00000000, 0x00000034, 0x006a0416,
			0x00000005, 0x00000000, 0x000000d9, 0x0300010e,
			0x00000000, 0x0000000c, 0x00000000, 0xffffffff,
			0x00000000, 0xffffffff, 0x000000be, 0x000000c6,
			0x0300010e, 0x00000010, 0x0000000c, 0x00000000,
			0xffffffff, 0x00000000, 0xffffffff, 0x000000b0,
			0x000000a2, 0x0300010e, 0x00000020, 0x0000000c,
			0x00000000, 0xffffffff, 0x00000000, 0xffffffff,
			0x00000097, 0x0000007e, 0x0300010c, 0x0000002c,
			0x00000004, 0x00000000, 0xffffffff, 0x00000000,
			0xffffffff, 0x0000007c, 0x0000005a, 0x0300010c,
			0x00000030, 0x00000004, 0x00000000, 0xffffffff,
			0x00000000, 0xffffffff, 0x00000060, 0x00000036,
			0x0000290e, 0x00000000, 0x00000058, 0x00000026,
			0x5f637273, 0x00786574, 0x74736564, 0x7865745f,
			0x75626300, 0x65640066, 0x6f5f7473, 0x65736666,
			0x6e280074, 0x616e5f6f, 0x0029656d, 0x5f637273,
			0x7366666f, 0x74007465, 0x735f7865, 0x00657a69,
			0x5f747364, 0x0070696d, 0x5f637273, 0x0070696d,
			0x69736f70, 0x6e6f6974, 0x00000000, 0x00000000
		};


#if 0 // Actual Shader source for cs_copybuffer_c.pssl
		/* SIE CONFIDENTIAL
		PlayStation(R)4 Programmer Tool Runtime Library Release 07.008.001
		* Copyright (C) 2013 Sony Interactive Entertainment Inc.
		*/

		DataBuffer<uint4> Src;
		RW_DataBuffer<uint4> Dst;

		[NUM_THREADS(64, 1, 1)]
		void main(uint threadID : S_DISPATCH_THREAD_ID)
		{
			Dst[threadID] = Src[threadID];
		}
#endif
		const uint32_t sComputeShaderCopyBuffer[]
		{
			0x5c060400, 0x7589d6b6, 0x00000000, 0x03000102,
			0x000000a4, 0x00000000, 0x00010040, 0x00000001,
			0x00000000, 0x72646853, 0x00020007, 0x03000c04,
			0x00000000, 0x02000064, 0x00000000, 0x00000030,
			0xffffffff, 0x002c0041, 0x00000090, 0x00000040,
			0x00000001, 0x00000001, 0x00000000, 0x00000000,
			0x00040004, 0xbeeb03ff, 0x00000008, 0x8f6a8608,
			0xd2ba0004, 0x0401006a, 0xe00c2000, 0x80000004,
			0xbf8c0f70, 0xe01c2000, 0x80010004, 0xbf810000,
			0x00d18d7d, 0x00000004, 0x00000000, 0x00040004,
			0x00000000, 0x00000342, 0x95c06021, 0x5362724f,
			0x07726468, 0x00002c51, 0x050c0203, 0x7589d6b6,
			0x00000000, 0x2d26e0bb, 0x00000002, 0x00000000,
			0x00000000, 0x00000000, 0x00000001, 0x00000000,
			0x0000001c, 0x00000000, 0x00000000, 0x000f0100,
			0x00000000, 0x00000000, 0x0000002c, 0x00000000,
			0x00000000, 0x000f000c, 0x00000000, 0x00000000,
			0x00000018, 0x0000290c, 0x00000000, 0x00000010,
			0x00000015, 0x00637253, 0x00747344, 0x65726874,
			0x44496461, 0x6f6e2800, 0x6d616e5f, 0x00002965,
		};

		//static shader
		EmbeddedPixelShaderWithSource sPixelClearShader = { sPixelClear, nullptr, {} };
		EmbeddedComputeShaderWithSource sComputeSetUintShader = { sComputeShaderSetUint, nullptr, {} };
		EmbeddedComputeShaderWithSource sComputeSetUintFastShader = { sComputeShaderSetUintFast, nullptr, {} };
		EmbeddedPixelShaderWithSource sCopyShader = { sCopyShaderSetUint, nullptr, {} };

		EmbeddedComputeShaderWithSource sComputeCopyTtoTShader = { sComputeShaderCopyTexToTex, nullptr, {} };
		EmbeddedComputeShaderWithSource sComputeCopyTtoTArrayShader = { sComputeShaderCopyTexToTexArray, nullptr, {} };
		EmbeddedComputeShaderWithSource sComputeCopyTArraytoTArrayShader = { sComputeShaderCopyTexArrayToTexArray, nullptr, {} };
		EmbeddedComputeShaderWithSource sComputeCopyTtoCShader = { sComputeShaderCopyTexToTexCube, nullptr, {} };

		EmbeddedComputeShaderWithSource sComputeCopyBuffer = { sComputeShaderCopyBuffer, nullptr, {} };

		void RendererContextGNM::_initEmbeddedShadersForClear()
		{
			//Allocate static shaders for screen clearing
			sPixelClearShader.initialize(m_garlicAllocator, m_onionAllocator, "clear_embedded_binps");
			sComputeSetUintShader.initialize(m_garlicAllocator, m_onionAllocator, "clear_embedded_bincs");
			sComputeSetUintFastShader.initialize(m_garlicAllocator, m_onionAllocator, "clear_embedded_fast_bincs");

			//Texture copy shaders
			sComputeCopyTtoTShader.initialize(m_garlicAllocator, m_onionAllocator, "copy_texture_to_texture");
			sComputeCopyTtoTArrayShader.initialize(m_garlicAllocator, m_onionAllocator, "copy_texture_to_texture_array");
			sComputeCopyTArraytoTArrayShader.initialize(m_garlicAllocator, m_onionAllocator, "copy_texture_array_to_texture_array");
			sComputeCopyTtoCShader.initialize(m_garlicAllocator, m_onionAllocator, "copy_texture_to_texture_cube");

			//Shaderbuffer shaders
			sComputeCopyBuffer.initialize(m_garlicAllocator, m_onionAllocator, "copy_buffer_to_rwbuffer");
		}

		void RendererContextGNM::_shutdownEmbeddedShadersForClear()
		{
			sPixelClearShader.shutdown(m_garlicAllocator, m_onionAllocator);
			sComputeSetUintShader.shutdown(m_garlicAllocator, m_onionAllocator);
			sComputeSetUintFastShader.shutdown(m_garlicAllocator, m_onionAllocator);

			//Texture copy shaders
			sComputeCopyTtoTShader.shutdown(m_garlicAllocator, m_onionAllocator);
			sComputeCopyTtoTArrayShader.shutdown(m_garlicAllocator, m_onionAllocator);
			sComputeCopyTArraytoTArrayShader.shutdown(m_garlicAllocator, m_onionAllocator);
			sComputeCopyTtoCShader.shutdown(m_garlicAllocator, m_onionAllocator);

			//Shadebuffer shaders
			sComputeCopyBuffer.shutdown(m_garlicAllocator, m_onionAllocator);
		}

		void RendererContextGNM::_initCopyShader() {
			//Allocate static shaders for screen clearing
			sCopyShader.initialize(m_garlicAllocator, m_onionAllocator, "copy_embedded_binps");
		}

		void RendererContextGNM::_shutdownCopyShader() {
			sCopyShader.shutdown(m_garlicAllocator, m_onionAllocator);
		}
	} /* namespace gnm */
} // namespace bgfx

#else

namespace bgfx {
	namespace gnm {

		RendererContextI* rendererCreate(const Init& _init)
		{
			BX_UNUSED(_init);
			return NULL;
		}

		void rendererDestroy()
		{
		}

	} /* namespace gnm */
} // namespace bgfx

#endif

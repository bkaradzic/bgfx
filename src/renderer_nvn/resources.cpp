/********************************************************
*   (c) Mojang. All rights reserved                     *
*   (c) Microsoft. All rights reserved.                 *
*********************************************************/

#include "../bgfx_p.h"

#if BGFX_CONFIG_RENDERER_NVN

#include "resources.h"
#include <bimg/bimg.h>
#include <nvn/nvn.h>
#include <nn/nn_Log.h>

namespace bgfx { namespace nvn
{
	extern NVNdevice* g_nvnDevice;

	struct TextureFormatInfo
	{
		NVNformat m_fmt;
		NVNformat m_fmtDsv;
		NVNformat m_fmtSrgb;
		uint16_t m_caps;
	};

#define TEXTURE_CAPS_NONE (BGFX_CAPS_FORMAT_TEXTURE_NONE)
#define TEXTURE_CAPS_STANDARD (BGFX_CAPS_FORMAT_TEXTURE_2D | BGFX_CAPS_FORMAT_TEXTURE_3D | BGFX_CAPS_FORMAT_TEXTURE_CUBE | BGFX_CAPS_FORMAT_TEXTURE_VERTEX)
#define TEXTURE_CAPS_FRAMEBUFFER (TEXTURE_CAPS_STANDARD | BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER)
#define TEXTURE_CAPS_IMAGE (BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ | BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE)
#define TEXTURE_CAPS_SRGB (BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB | BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB | BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB)
#define TEXTURE_CAPS_EMULATED (BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED | BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED | BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED)

	static const TextureFormatInfo s_textureFormat[] =
	{
		{ NVN_FORMAT_RGBA_DXT1,			NVN_FORMAT_NONE,				NVN_FORMAT_RGBA_DXT1_SRGB,		TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_SRGB }, // BC1
		{ NVN_FORMAT_RGBA_DXT3,			NVN_FORMAT_NONE,				NVN_FORMAT_RGBA_DXT3_SRGB,		TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_SRGB }, // BC2
		{ NVN_FORMAT_RGBA_DXT5,			NVN_FORMAT_NONE,				NVN_FORMAT_RGBA_DXT5_SRGB,		TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_SRGB }, // BC3
		{ NVN_FORMAT_RGTC1_UNORM,		NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD }, // BC4
		{ NVN_FORMAT_RGTC2_UNORM,		NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD }, // BC5
		{ NVN_FORMAT_BPTC_SFLOAT,		NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD }, // BC6H
		{ NVN_FORMAT_BPTC_UNORM,		NVN_FORMAT_NONE,				NVN_FORMAT_BPTC_UNORM_SRGB,		TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_SRGB }, // BC7
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_EMULATED }, // ETC1
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_EMULATED }, // ETC2
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_EMULATED }, // ETC2A
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_EMULATED }, // ETC2A1
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_EMULATED }, // PTC12
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_EMULATED }, // PTC14
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_EMULATED }, // PTC12A
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_EMULATED }, // PTC14A
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_EMULATED }, // PTC22
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_EMULATED }, // PTC24
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_EMULATED }, // ATC
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_EMULATED }, // ATCE
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_EMULATED }, // ATCI
		{ NVN_FORMAT_RGBA_ASTC_4x4,		NVN_FORMAT_NONE,				NVN_FORMAT_RGBA_ASTC_4x4_SRGB,	TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_SRGB }, // ASTC4x4
		{ NVN_FORMAT_RGBA_ASTC_5x5,		NVN_FORMAT_NONE,				NVN_FORMAT_RGBA_ASTC_5x5_SRGB,	TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_SRGB }, // ASTC5x5
		{ NVN_FORMAT_RGBA_ASTC_6x6,		NVN_FORMAT_NONE,				NVN_FORMAT_RGBA_ASTC_6x6_SRGB,	TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_SRGB }, // ASTC6x6
		{ NVN_FORMAT_RGBA_ASTC_8x5,		NVN_FORMAT_NONE,				NVN_FORMAT_RGBA_ASTC_8x5_SRGB,	TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_SRGB }, // ASTC8x5
		{ NVN_FORMAT_RGBA_ASTC_8x6,		NVN_FORMAT_NONE,				NVN_FORMAT_RGBA_ASTC_8x6_SRGB,	TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_SRGB }, // ASTC8x6
		{ NVN_FORMAT_RGBA_ASTC_10x5,	NVN_FORMAT_NONE,				NVN_FORMAT_RGBA_ASTC_10x5_SRGB,	TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_SRGB }, // ASTC10x5
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_NONE }, // Unknown
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_EMULATED }, // R1
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_EMULATED }, // A8
		{ NVN_FORMAT_R8,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER | TEXTURE_CAPS_IMAGE}, // R8
		{ NVN_FORMAT_R8I,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // R8I
		{ NVN_FORMAT_R8UI,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // R8U
		{ NVN_FORMAT_R8SN,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // R8S
		{ NVN_FORMAT_R16,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER | TEXTURE_CAPS_IMAGE }, // R16
		{ NVN_FORMAT_R16I,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // R16I
		{ NVN_FORMAT_R16,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // R16U
		{ NVN_FORMAT_R16F,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER | TEXTURE_CAPS_IMAGE }, // R16F
		{ NVN_FORMAT_R16SN,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // R16S
		{ NVN_FORMAT_R32I,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // R32I
		{ NVN_FORMAT_R32UI,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // R32U
		{ NVN_FORMAT_R32F,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER | TEXTURE_CAPS_IMAGE }, // R32F
		{ NVN_FORMAT_RG8,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER | TEXTURE_CAPS_IMAGE }, // RG8
		{ NVN_FORMAT_RG8I,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // RG8I
		{ NVN_FORMAT_RG8UI,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // RG8U
		{ NVN_FORMAT_RG8SN,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // RG8S
		{ NVN_FORMAT_RG16,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER | TEXTURE_CAPS_IMAGE }, // RG16
		{ NVN_FORMAT_RG16I,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // RG16I
		{ NVN_FORMAT_RG16UI,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // RG16U
		{ NVN_FORMAT_RG16F,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER | TEXTURE_CAPS_IMAGE }, // RG16F
		{ NVN_FORMAT_RG16SN,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // RG16S
		{ NVN_FORMAT_RG32I,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // RG32I
		{ NVN_FORMAT_RG32UI,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // RG32U
		{ NVN_FORMAT_RG32F,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER | TEXTURE_CAPS_IMAGE }, // RG32F
		{ NVN_FORMAT_RGB8,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER }, // RGB8
		{ NVN_FORMAT_RGB8I,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD }, // RGB8I
		{ NVN_FORMAT_RGB8UI,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD }, // RGB8U
		{ NVN_FORMAT_RGB8SN,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD }, // RGB8S
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_NONE }, // RGB9E5F
		{ NVN_FORMAT_BGRA8,				NVN_FORMAT_NONE,				NVN_FORMAT_BGRA8_SRGB,			TEXTURE_CAPS_FRAMEBUFFER | TEXTURE_CAPS_SRGB }, // BGRA8
		{ NVN_FORMAT_RGBA8,				NVN_FORMAT_NONE,				NVN_FORMAT_RGBA8_SRGB,			TEXTURE_CAPS_FRAMEBUFFER | TEXTURE_CAPS_SRGB | TEXTURE_CAPS_IMAGE }, // RGBA8
		{ NVN_FORMAT_RGBA8I,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // RGBA8I
		{ NVN_FORMAT_RGBA8UI,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // RGBA8U
		{ NVN_FORMAT_RGBA8SN,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // RGBA8S
		{ NVN_FORMAT_RGBA16,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER | TEXTURE_CAPS_IMAGE }, // RGBA16
		{ NVN_FORMAT_RGBA16I,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // RGBA16I
		{ NVN_FORMAT_RGBA16UI,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE}, // RGBA16U
		{ NVN_FORMAT_RGBA16F,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER | TEXTURE_CAPS_IMAGE }, // RGBA16F
		{ NVN_FORMAT_RGBA16SN,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // RGBA16S
		{ NVN_FORMAT_RGBA32I,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // RGBA32I
		{ NVN_FORMAT_RGBA32UI,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_STANDARD | TEXTURE_CAPS_IMAGE }, // RGBA32U
		{ NVN_FORMAT_RGBA32F,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER | TEXTURE_CAPS_IMAGE }, // RGBA32F
		{ NVN_FORMAT_BGR565,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER }, // R5G6B5
		{ NVN_FORMAT_RGBA4,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER }, // RGBA4
		{ NVN_FORMAT_RGB5A1,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER }, // RGB5A1
		{ NVN_FORMAT_RGB10A2,			NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER | TEXTURE_CAPS_IMAGE }, // RGB10A2
		{ NVN_FORMAT_R11G11B10F,		NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER | TEXTURE_CAPS_IMAGE }, // RG11B10F
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_NONE }, // UnknownDepth
		{ NVN_FORMAT_DEPTH16,			NVN_FORMAT_DEPTH16,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER }, // D16
		{ NVN_FORMAT_DEPTH24,			NVN_FORMAT_DEPTH24,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER }, // D24
		{ NVN_FORMAT_DEPTH24_STENCIL8,	NVN_FORMAT_DEPTH24_STENCIL8,	NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER }, // D24S8
		{ NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER }, // D32
		{ NVN_FORMAT_DEPTH32F,			NVN_FORMAT_DEPTH32F,			NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER }, // D16F
		{ NVN_FORMAT_DEPTH32F,			NVN_FORMAT_DEPTH32F,			NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER }, // D24F
		{ NVN_FORMAT_DEPTH32F,			NVN_FORMAT_DEPTH32F,			NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER }, // D32F
		{ NVN_FORMAT_DEPTH24_STENCIL8,	NVN_FORMAT_DEPTH24_STENCIL8,	NVN_FORMAT_NONE,				TEXTURE_CAPS_FRAMEBUFFER }, // D0S8
	};

	static_assert(TextureFormat::Count == BX_COUNTOF(s_textureFormat), "");

	//
	//
	//

	void CopyOperation::createBuffer(size_t _size, CopyOperation::Data* _data)
	{
		_data->m_size = _size;

		size_t poolSize = nn::util::align_up(_size, NVN_MEMORY_POOL_STORAGE_GRANULARITY);
		_data->m_mem = BX_ALIGNED_ALLOC(&g_allocatorNVN, poolSize, NVN_MEMORY_POOL_STORAGE_ALIGNMENT);

		NVNmemoryPoolBuilder poolBuilder;
		nvnMemoryPoolBuilderSetDefaults(&poolBuilder);
		nvnMemoryPoolBuilderSetDevice(&poolBuilder, g_nvnDevice);
		nvnMemoryPoolBuilderSetFlags(&poolBuilder, NVN_MEMORY_POOL_FLAGS_CPU_UNCACHED_BIT | NVN_MEMORY_POOL_FLAGS_GPU_CACHED_BIT);
		nvnMemoryPoolBuilderSetStorage(&poolBuilder, _data->m_mem, poolSize);
		if (nvnMemoryPoolInitialize(&_data->m_pool, &poolBuilder) == NVN_FALSE)
		{
			BX_ASSERT(false, "Failed to create memory pool.");
		}

		NVNbufferBuilder bufferBuilder;
		nvnBufferBuilderSetDefaults(&bufferBuilder);
		nvnBufferBuilderSetDevice(&bufferBuilder, g_nvnDevice);
		nvnBufferBuilderSetStorage(&bufferBuilder, &_data->m_pool, 0, _size);
		if (nvnBufferInitialize(&_data->m_buffer, &bufferBuilder) == NVN_FALSE)
		{
			BX_ASSERT(false, "Failed to create buffer.");
		}
	}

	//
	//
	//

	uint16_t TextureNVN::getCaps(TextureFormat::Enum _fmt)
	{
		return s_textureFormat[_fmt].m_caps;
	}

	void TextureNVN::create(NVNdevice* _device, NVNtextureBuilder& _builder)
	{
		BX_ASSERT(!m_created, "Texture should be destroyed first");

		nvnTextureBuilderSetDevice(&_builder, _device);
		size_t storageSize = nvnTextureBuilderGetStorageSize(&_builder);

		m_pool.Init(nullptr, storageSize, NVN_MEMORY_POOL_FLAGS_CPU_NO_ACCESS_BIT | NVN_MEMORY_POOL_FLAGS_GPU_CACHED_BIT | NVN_MEMORY_POOL_FLAGS_COMPRESSIBLE_BIT, _device);

		nvnTextureBuilderSetStorage(&_builder, m_pool.GetMemoryPool(), 0);

		if (nvnTextureInitialize(&m_ptr, &_builder) == NVN_FALSE)
		{
			BX_ASSERT(false, "Texture creation failed.");
		}

		m_created = true;
	}

	void TextureNVN::create(NVNdevice* _device, const Memory* _mem, uint64_t _flags, uint8_t _skip, CopyOperation& _copyOp)
	{
		BX_ASSERT(!m_created, "Texture should be destroyed first");

		bimg::ImageContainer imageContainer;

		if (bimg::imageParse(imageContainer, _mem->data, _mem->size))
		{
			uint8_t numMips = imageContainer.m_numMips;
			uint8_t startLod = uint8_t(bx::uint32_min(_skip, numMips - 1));
			numMips -= startLod;
			const bimg::ImageBlockInfo& blockInfo = bimg::getBlockInfo(imageContainer.m_format);
			uint32_t textureWidth = bx::uint32_max(blockInfo.blockWidth, imageContainer.m_width >> startLod);
			uint32_t textureHeight = bx::uint32_max(blockInfo.blockHeight, imageContainer.m_height >> startLod);
			uint16_t numLayers = imageContainer.m_numLayers;

			m_flags = _flags;
			m_width = textureWidth;
			m_height = textureHeight;
			m_depth = imageContainer.m_depth;
			m_requestedFormat = uint8_t(imageContainer.m_format);
			m_textureFormat = uint8_t(getViableTextureFormat(imageContainer));
			const bool convert = m_textureFormat != m_requestedFormat;
			const uint8_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat));

			if (imageContainer.m_cubeMap)
			{
				BX_ASSERT(numLayers == 1, "Cubemap arrays not supported.");
				numLayers = 6;
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

			const bool compressed = bimg::isCompressed(bimg::TextureFormat::Enum(m_textureFormat));
			const bool swizzle = TextureFormat::BGRA8 == m_textureFormat && 0 != (m_flags & BGFX_TEXTURE_COMPUTE_WRITE);

			//const bool writeOnly = 0 != (m_flags & BGFX_TEXTURE_RT_WRITE_ONLY);
			const bool computeWrite = 0 != (m_flags & BGFX_TEXTURE_COMPUTE_WRITE);
			const bool renderTarget = 0 != (m_flags & BGFX_TEXTURE_RT_MASK);
			const bool srgb = 0 != (m_flags & BGFX_TEXTURE_SRGB);
			const bool readBack = 0 != (m_flags & BGFX_TEXTURE_READ_BACK);
			//const bool blit = 0 != (m_flags & BGFX_TEXTURE_BLIT_DST);

		/*	BX_TRACE("Texture %3d: %s (requested: %s), %dx%d%s RT[%c], BO[%c], CW[%c]%s."
				, this - s_renderNVN->m_textures
				, getName((TextureFormat::Enum)m_textureFormat)
				, getName((TextureFormat::Enum)m_requestedFormat)
				, textureWidth
				, textureHeight
				, imageContainer.m_cubeMap ? "x6" : ""
				, renderTarget ? 'x' : ' '
				, writeOnly ? 'x' : ' '
				, computeWrite ? 'x' : ' '
				, swizzle ? " (swizzle BGRA8 -> RGBA8)" : ""
			);*/

			NVNtextureBuilder textureBuilder;
			nvnTextureBuilderSetDefaults(&textureBuilder);
			nvnTextureBuilderSetDevice(&textureBuilder, _device);

			NVNformat format = srgb ? s_textureFormat[m_textureFormat].m_fmtSrgb : s_textureFormat[m_textureFormat].m_fmt;

			int flags = 0;
			int poolFlags = NVN_MEMORY_POOL_FLAGS_GPU_CACHED_BIT;

			if (bimg::isDepth(bimg::TextureFormat::Enum(m_textureFormat)))
			{
				BX_ASSERT(!readBack, "Depth buffers need compressible bit set which is incompatible with readback support.");
				format = s_textureFormat[m_textureFormat].m_fmtDsv;
				flags |= NVN_TEXTURE_FLAGS_COMPRESSIBLE_BIT;
			}
			else if (renderTarget)
			{
				BX_ASSERT(!srgb, "Can't have a SRGB RenderTarget");
				flags |= NVN_TEXTURE_FLAGS_COMPRESSIBLE_BIT;
			}

			if (readBack)
			{
				flags &= ~NVN_TEXTURE_FLAGS_COMPRESSIBLE_BIT; // readback doesn't work when this is enabled
				poolFlags |= NVN_MEMORY_POOL_FLAGS_CPU_UNCACHED_BIT;
			}
			else
			{
				poolFlags |= NVN_MEMORY_POOL_FLAGS_CPU_NO_ACCESS_BIT | NVN_MEMORY_POOL_FLAGS_COMPRESSIBLE_BIT;
			}

			if (computeWrite)
			{
				flags |= NVN_TEXTURE_FLAGS_IMAGE_BIT;
			}

			nvnTextureBuilderSetFlags(&textureBuilder, flags);

			nvnTextureBuilderSetFormat(&textureBuilder, format);

			switch (m_type)
			{
			case Texture2D:
				if (imageContainer.m_numLayers > 1)
				{
					nvnTextureBuilderSetSize3D(&textureBuilder, textureWidth, textureHeight, imageContainer.m_numLayers);
					nvnTextureBuilderSetTarget(&textureBuilder, NVN_TEXTURE_TARGET_2D_ARRAY);
				}
				else
				{
					nvnTextureBuilderSetSize2D(&textureBuilder, textureWidth, textureHeight);
					nvnTextureBuilderSetTarget(&textureBuilder, NVN_TEXTURE_TARGET_2D);
				}
				break;
			case TextureCube:
				if (imageContainer.m_numLayers > 1)
				{
					nvnTextureBuilderSetSize3D(&textureBuilder, textureWidth, textureHeight, imageContainer.m_numLayers);
					nvnTextureBuilderSetTarget(&textureBuilder, NVN_TEXTURE_TARGET_CUBEMAP_ARRAY);
				}
				else
				{
					nvnTextureBuilderSetSize2D(&textureBuilder, textureWidth, textureHeight);
					nvnTextureBuilderSetTarget(&textureBuilder, NVN_TEXTURE_TARGET_CUBEMAP);
				}
				break;
			case Texture3D:
				nvnTextureBuilderSetSize3D(&textureBuilder, textureWidth, textureHeight, m_depth);
				nvnTextureBuilderSetTarget(&textureBuilder, NVN_TEXTURE_TARGET_3D);
				break;
			}

			nvnTextureBuilderSetLevels(&textureBuilder, (m_numMips != 0) ? m_numMips : 1);

			if (swizzle)
			{
				// map BGRA to RGBA
				nvnTextureBuilderSetSwizzle(&textureBuilder,
					NVN_TEXTURE_SWIZZLE_B,
					NVN_TEXTURE_SWIZZLE_G,
					NVN_TEXTURE_SWIZZLE_R,
					NVN_TEXTURE_SWIZZLE_A);
			}

			size_t storageSize = nvnTextureBuilderGetStorageSize(&textureBuilder);
			m_pool.Init(nullptr, storageSize, poolFlags, _device);
			nvnTextureBuilderSetStorage(&textureBuilder, m_pool.GetMemoryPool(), 0);
			if (nvnTextureInitialize(&m_ptr, &textureBuilder) == NVN_FALSE)
			{
				BX_ASSERT(false, "Texture creation failed.");
			}

			m_created = true;

			struct ImageInfo
			{
				const uint8_t* m_data;
				uint8_t m_mip;
				uint16_t m_layer;
				uint32_t m_pitch;
				uint32_t m_width;
				uint32_t m_height;
				uint32_t m_depth;
				uint32_t m_size;
				uint32_t m_offset;
				uint32_t m_blockSize;
				bimg::TextureFormat::Enum m_format;
			};

			ImageInfo* imageInfo = (ImageInfo*)alloca(numLayers * numMips * sizeof(ImageInfo));
			int numImageInfo = 0;

			const uint32_t alignment = 1;

			uint32_t bufferSize = 0;

			uint16_t numSides = numLayers * ((m_type == TextureCube) ? 6 : 1);

			for (uint16_t layer = 0; layer < numLayers; ++layer)
			{
				for (uint8_t lod = 0; lod < numMips; ++lod)
				{
					uint8_t curLod = lod + startLod;

					bimg::ImageMip mip;
					if (bimg::imageGetRawData(imageContainer, layer, curLod, _mem->data, _mem->size, mip))
					{
						uint32_t pitch = bx::strideAlign(mip.m_width * bpp / 8, alignment);
						uint32_t slice = bx::strideAlign(mip.m_height * pitch, alignment);

						if (compressed)
						{
							pitch = bx::strideAlign((mip.m_width / blockInfo.blockWidth) * mip.m_blockSize, alignment);
							slice = bx::strideAlign((mip.m_height / blockInfo.blockHeight) * pitch, alignment);
						}

						uint32_t size = slice * mip.m_depth;

						ImageInfo& info = imageInfo[numImageInfo++];
						info.m_mip = lod;
						info.m_layer = layer;
						info.m_pitch = pitch;
						info.m_width = mip.m_width;
						info.m_height = mip.m_height;
						info.m_depth = mip.m_depth;
						info.m_size = size;
						info.m_data = mip.m_data;
						info.m_offset = bufferSize;
						info.m_blockSize = mip.m_blockSize;
						info.m_format = mip.m_format;

						bufferSize += nn::util::align_up(size, NVN_MEMORY_POOL_STORAGE_GRANULARITY); // make sure each subcopy is aligned
					}
				}
			}

			if (numImageInfo != 0)
			{
				_copyOp.m_data = (CopyOperation::Data*)BX_ALLOC(&g_allocatorNVN, sizeof(CopyOperation::Data));
				_copyOp.createBuffer(bufferSize, _copyOp.m_data);
				_copyOp.m_ops.reserve(numImageInfo);

				uint8_t* dst = (uint8_t*)nvnBufferMap(&_copyOp.m_data->m_buffer);

				int tileSize = compressed ? 4 : 1;

				for (int i = 0; i < numImageInfo; ++i)
				{
					const ImageInfo& info = imageInfo[i];

					if (convert)
					{
						bimg::imageDecodeToBgra8(
							&g_allocatorNVN
							, dst + info.m_offset
							, info.m_data
							, info.m_width
							, info.m_height
							, info.m_pitch
							, info.m_format
						);
					}
					else if (compressed)
					{
						bimg::imageCopy(
							dst + info.m_offset
							, info.m_height / blockInfo.blockHeight
							, (info.m_width / blockInfo.blockWidth) * info.m_blockSize
							, info.m_depth
							, info.m_data
							, info.m_pitch
						);
					}
					else
					{
						bimg::imageCopy(dst + info.m_offset, info.m_height, info.m_pitch, info.m_depth, info.m_data, info.m_pitch);
					}

					CopyOperation::Op op;
					op.m_type = CopyOperation::Op::Texture;
					op.m_dstTexture = &m_ptr;
					op.m_offset = info.m_offset;
					op.m_memSize = info.m_size;

					nvnTextureViewSetDefaults(&op.m_dstView);
					nvnTextureViewSetLevels(&op.m_dstView, info.m_mip, 1);

					if (m_type != TextureNVN::Enum::Texture3D)
					{
						nvnTextureViewSetLayers(&op.m_dstView, info.m_layer, 1);
					}

					op.m_dstRegion.xoffset = 0;
					op.m_dstRegion.yoffset = 0;
					op.m_dstRegion.zoffset = 0;
					op.m_dstRegion.width = m_width >> (startLod + info.m_mip);
					op.m_dstRegion.height = m_height >> (startLod + info.m_mip);
					op.m_dstRegion.depth = std::max(m_depth >> (startLod + info.m_mip), 1u);

					_copyOp.m_ops.push_back(op);
				}

				nvnBufferFlushMappedRange(&_copyOp.m_data->m_buffer, 0, bufferSize);
			}
		}
	}

	void TextureNVN::destroy()
	{
		if (m_created)
		{
			nvnTextureFinalize(&m_ptr);
			m_pool.Shutdown();
			m_created = false;
		}
	}

	void TextureNVN::update(NVNcommandBuffer* _commandList, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem)
	{
#if 0
		bool isTextureArray = false;

		CopyOperation copyOp;
		copyOp.m_data = (CopyOperation::Data*)BX_ALLOC(&g_allocatorNVN, sizeof(CopyOperation::Data));

		CopyOperation::Op op;
		op.m_type = CopyOperation::Op::Texture;
		op.m_dstTexture = &m_ptr;
		op.m_offset = 0;
		op.m_memSize = 0;

		nvnTextureViewSetDefaults(&op.m_dstView);
		nvnTextureViewSetLayers(&op.m_dstView, isTextureArray ? _z : _side, 1);
		nvnTextureViewSetLevels(&op.m_dstView, _mip, 1);

		op.m_dstRegion.xoffset = _rect.m_x;
		op.m_dstRegion.yoffset = _rect.m_y;
		op.m_dstRegion.zoffset = _z;
		op.m_dstRegion.width = _rect.m_width;
		op.m_dstRegion.height = _rect.m_height;
		op.m_dstRegion.depth = 1;

		copyOp.m_ops.push_back(op);
#endif

		// TODO
		/*D3D12_RESOURCE_STATES state = setState(_commandList, D3D12_RESOURCE_STATE_COPY_DEST);

		bool isTextureArray = (m_srvd.ViewDimension == D3D12_SRV_DIMENSION_TEXTURE2DARRAY);

		const uint32_t subres = _mip + ((isTextureArray ? _z : _side) * m_numMips);
		const uint32_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat));
		const uint32_t rectpitch = _rect.m_width*bpp / 8;
		const uint32_t srcpitch = UINT16_MAX == _pitch ? rectpitch : _pitch;

		D3D12_RESOURCE_DESC desc = getResourceDesc(m_ptr);

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

		D3D12_RANGE readRange = { 0, 0 };
		DX_CHECK(staging->Map(0, &readRange, (void**)&data));
		for (uint32_t ii = 0, height = _rect.m_height; ii < height; ++ii)
		{
			::memcpy(&data[ii*rowPitch], &_mem->data[ii*srcpitch], srcpitch);
		}
		D3D12_RANGE writeRange = { 0, _rect.m_height*srcpitch };
		staging->Unmap(0, &writeRange);

		D3D12_BOX box;
		box.left = 0;
		box.top = 0;
		box.right = box.left + _rect.m_width;
		box.bottom = box.top + _rect.m_height;
		box.front = isTextureArray ? 0 : _z;
		box.back = box.front + _depth;

		D3D12_TEXTURE_COPY_LOCATION dst = { m_ptr,   D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX, {        } };
		dst.SubresourceIndex = subres;
		D3D12_TEXTURE_COPY_LOCATION src = { staging, D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,  { layout } };
		_commandList->CopyTextureRegion(&dst, _rect.m_x, _rect.m_y, 0, &src, &box);

		setState(_commandList, state);

		s_renderD3D12->m_cmd.release(staging);*/
	}

	//void TextureNVN::commit(uint8_t /*_stage*/, uint32_t /*_flags*/, const float /*_palette[][4]*/)
	//{
	//	/*uint32_t flags = 0 == (BGFX_TEXTURE_INTERNAL_DEFAULT_SAMPLER & _flags)
	//		? _flags
	//		: m_flags
	//		;
	//	uint32_t index = (flags & BGFX_TEXTURE_BORDER_COLOR_MASK) >> BGFX_TEXTURE_BORDER_COLOR_SHIFT;
	//	ts.m_sampler[_stage] = s_renderNVN->getSamplerState(flags, _palette[index]);*/
	//}

	//
	//
	//

	void SamplerNVN::create(int index, const NVNsamplerBuilder& _desc)
	{
		if (m_created)
		{
			destroy();
		}

		nvnSamplerInitialize(&m_sampler, &_desc);

		m_desc = _desc;
		m_index = index;
	}

	void SamplerNVN::destroy()
	{
		if (m_created)
		{
			nvnSamplerFinalize(&m_sampler);
			m_index = 0;
			m_created = false;
		}
	}

	//
	//
	//

	void SwapChainNVN::create(int _textureCount, NVNnativeWindow _nativeWindow, NVNdevice* _device, const bgfx::Resolution& _size, const bgfx::TextureFormat::Enum _colorFormat, const bgfx::TextureFormat::Enum _depthFormat)
	{
		BX_ASSERT(!bimg::isDepth((bimg::TextureFormat::Enum)_colorFormat), "Color shouldn't be a depth format");
		BX_ASSERT(bimg::isDepth((bimg::TextureFormat::Enum)_depthFormat), "Depth should be a depth format");

		BX_ASSERT(!m_created, "Should destroy first");

		m_numTextures = _textureCount;

		nvnSyncInitialize(&m_windowSync, _device);

		NVNwindowBuilder windowBuilder;

		nvnWindowBuilderSetDefaults(&windowBuilder);
		nvnWindowBuilderSetDevice(&windowBuilder, _device);
		nvnWindowBuilderSetNativeWindow(&windowBuilder, _nativeWindow);

		std::vector<NVNtexture*> nvnColors;

		nvnColors.resize(_textureCount);
		m_colorTextures.resize(_textureCount);

		for (int i = 0; i < _textureCount; i++) {
			NVNtextureBuilder colorBuilder;
			nvnTextureBuilderSetDefaults(&colorBuilder);
			nvnTextureBuilderSetDevice(&colorBuilder, _device);
			nvnTextureBuilderSetFlags(&colorBuilder, NVN_TEXTURE_FLAGS_DISPLAY_BIT | NVN_TEXTURE_FLAGS_COMPRESSIBLE_BIT);
			nvnTextureBuilderSetTarget(&colorBuilder, NVN_TEXTURE_TARGET_2D);
			nvnTextureBuilderSetFormat(&colorBuilder, s_textureFormat[_colorFormat].m_fmt);
			nvnTextureBuilderSetSize2D(&colorBuilder, _size.width, _size.height);

			m_colorTextures[i].create(_device, colorBuilder);

			nvnColors[i] = &m_colorTextures[i].m_ptr;
		}

		NVNtextureBuilder depthBuilder;
		nvnTextureBuilderSetDefaults(&depthBuilder);
		nvnTextureBuilderSetDevice(&depthBuilder, _device);
		nvnTextureBuilderSetFlags(&depthBuilder, NVN_TEXTURE_FLAGS_COMPRESSIBLE_BIT);
		nvnTextureBuilderSetTarget(&depthBuilder, NVN_TEXTURE_TARGET_2D);
		nvnTextureBuilderSetFormat(&depthBuilder, s_textureFormat[_depthFormat].m_fmtDsv);
		nvnTextureBuilderSetSize2D(&depthBuilder, _size.width, _size.height);

		m_depthTexture.create(_device, depthBuilder);

		nvnWindowBuilderSetTextures(&windowBuilder, _textureCount, nvnColors.data());
		nvnWindowInitialize(&m_window, &windowBuilder);

		m_created = true;
	}

	void SwapChainNVN::destroy()
	{
		if (m_created)
		{
			nvnWindowFinalize(&m_window);

			for (int i = 0; i < m_numTextures; i++)
			{
				m_colorTextures[i].destroy();
			}

			m_depthTexture.destroy();

			nvnSyncFinalize(&m_windowSync);

			m_created = false;
		}
	}

	BackBuffer SwapChainNVN::acquireNext()
	{
		BX_ASSERT(m_created, "SwapChain wasn't created");
		if (nvnWindowAcquireTexture(&m_window, &m_windowSync, &m_current) != NVN_WINDOW_ACQUIRE_TEXTURE_RESULT_SUCCESS)
		{
			BX_ASSERT(false, "AcquireNext failed");
		}

		nvnSyncWait(&m_windowSync, NVN_WAIT_TIMEOUT_MAXIMUM);

		return get();
	}

	BackBuffer SwapChainNVN::get()
	{
		BX_ASSERT(m_created, "SwapChain wasn't created");
		return BackBuffer{ &m_colorTextures[m_current], &m_depthTexture };
	}

	void SwapChainNVN::present(NVNqueue* _queue)
	{
		BX_ASSERT(m_created, "SwapChain wasn't created");
		nvnQueuePresentTexture(_queue, &m_window, m_current);
	}

	//
	//
	//

	void OutOfCommandBufferMemoryEventCallback(NVNcommandBuffer* cmdBuf, NVNcommandBufferMemoryEvent event, size_t minSize, void* callbackData);

	void CommandListNVN::init(NVNdevice* _device)
	{
		m_device = _device;
		m_poolCommand.Init(nullptr, BGFX_CONFIG_NVN_COMMAND_BUFFER_COMMAND_SIZE, NVN_MEMORY_POOL_FLAGS_CPU_UNCACHED_BIT | NVN_MEMORY_POOL_FLAGS_GPU_CACHED_BIT, _device);
		m_poolControl.Init(nullptr, BGFX_CONFIG_NVN_COMMAND_BUFFER_CONTROL_SIZE, NVN_MEMORY_POOL_FLAGS_CPU_CACHED_BIT | NVN_MEMORY_POOL_FLAGS_GPU_NO_ACCESS_BIT, _device);

		nvnCommandBufferInitialize(&m_cmd, m_device);
	}

	void CommandListNVN::shutdown()
	{
		nvnCommandBufferFinalize(&m_cmd);
	}

	void CommandListNVN::begin(const char* name)
	{
		NN_PERF_BEGIN_MEASURE_NAME_GPU(&m_cmd, name);

		_resetState();

		nvnCommandBufferAddCommandMemory(&m_cmd, m_poolCommand.GetMemoryPool(), 0, BGFX_CONFIG_NVN_COMMAND_BUFFER_COMMAND_SIZE);
		nvnCommandBufferAddControlMemory(&m_cmd, m_poolControl.GetMemory(), BGFX_CONFIG_NVN_COMMAND_BUFFER_CONTROL_SIZE);

		nvnCommandBufferBeginRecording(&m_cmd);
	}

	void CommandListNVN::submit(NVNqueue* queue, NVNsync* fence)
	{
		NVNcommandHandle cmdHandle = _end();
		nvnQueueSubmitCommands(queue, 1, &cmdHandle);

		nvnQueueFenceSync(queue, fence, NVN_SYNC_CONDITION_ALL_GPU_COMMANDS_COMPLETE, 0);
		nvnQueueFlush(queue);
	}

	NVNcommandBuffer* CommandListNVN::get()
	{
		return &m_cmd;
	}

	void CommandListNVN::getUsage(size_t& _usageCommand, size_t& _usageControl) const
	{
		_usageCommand = m_usageCommand;
		_usageControl = m_usageControl;
	}

	NVNcommandHandle CommandListNVN::_end()
	{
		NN_PERF_END_MEASURE_GPU(&m_cmd);

		NVNcommandHandle handle = nvnCommandBufferEndRecording(&m_cmd);

		m_usageCommand = nvnCommandBufferGetCommandMemoryUsed(&m_cmd);
		m_usageControl = nvnCommandBufferGetControlMemoryUsed(&m_cmd);

		return handle;
	}

	void CommandListNVN::_resetState()
	{
		for (int i = 0; i < m_currentColor.size(); i++)
		{
			m_currentColor[i] = nullptr;
		}

		m_currentDepth = nullptr;

		m_currentIndexBufferIndexType = NVNindexType::NVN_INDEX_TYPE_UNSIGNED_SHORT;
		m_currentIndexBufferAddress = 0;
	}

	//
	//
	//

	CommandQueueNVN::CommandQueueNVN()
		: m_control(CommandListCount)
	{
	}

	void CommandQueueNVN::init(NVNdevice* _device, SwapChainNVN* _swapChain)
	{
		m_Device = _device;
		m_SwapChain = _swapChain;

		{
			int commandMemorySize = 64 * 1024; // 64 * 1024 is NVN_DEVICE_INFO_QUEUE_COMMAND_MEMORY_DEFAULT_SIZE

			NVNqueueBuilder queueBuilder;
			nvnQueueBuilderSetDevice(&queueBuilder, m_Device);
			nvnQueueBuilderSetDefaults(&queueBuilder);
			nvnQueueBuilderSetCommandMemorySize(&queueBuilder, commandMemorySize);
			if (nvnQueueInitialize(&m_GfxQueue, &queueBuilder) != NVN_TRUE)
			{
				BX_ASSERT(false, "nvnQueueInitialize");
			}
		}

		for (auto& fence : m_fences)
		{
			nvnSyncInitialize(&fence, m_Device);
		}

		for (auto& cmdList : m_commandList)
		{
			cmdList.init(m_Device);
		}

		nvnSyncInitialize(&m_idleSync, m_Device);
	}

	void CommandQueueNVN::shutdown()
	{
		nvnSyncFinalize(&m_idleSync);

		for (NVNsync& fence : m_fences)
		{
			nvnSyncFinalize(&fence);
		}

		for (CommandListNVN& cmdList : m_commandList)
		{
			cmdList.shutdown();
		}

		nvnQueueFinalize(&m_GfxQueue);
	}

	CommandListNVN* CommandQueueNVN::alloc(const char* name)
	{
		while (0 == m_control.reserve(1))
		{
			consume();
		}

		CommandListNVN* commandList = &m_commandList[m_control.m_current];
		commandList->begin(name);

		return commandList;
	}

	NVNsync* CommandQueueNVN::kick()
	{
		CommandListNVN* commandList = &m_commandList[m_control.m_current];

		CpuMeasureScope("ExecuteCommand");

		NVNsync* fence = &m_fences[m_control.m_current];
		commandList->submit(&m_GfxQueue, fence);

		m_control.commit(1);

		return fence;
	}

	bool CommandQueueNVN::waitIsFenceSignaled(NVNsync* _waitFence, const uint64_t _ms)
	{
		if (_waitFence)
		{
			const NVNsyncWaitResult result = nvnSyncWait(_waitFence, _ms);

			return
				(result == NVNsyncWaitResult::NVN_SYNC_WAIT_RESULT_CONDITION_SATISFIED) ||
				(result == NVNsyncWaitResult::NVN_SYNC_WAIT_RESULT_ALREADY_SIGNALED);
		}
		else
		{
			return true;
		}
	}

	void CommandQueueNVN::finish(NVNsync* _waitFence, bool _finishAll)
	{
		if (_waitFence)
		{
			waitIsFenceSignaled(_waitFence);
		}

		while (0 < m_control.available())
		{
			consume(0);
		}

		BX_ASSERT(0 == m_control.available(), "");
	}

	void CommandQueueNVN::waitForIdle()
	{
		// TODO REMOVE THAT, THE MEMORY POOLS SHOULD BE PER COMMANDLIST OR USE A PROPER RING BUFFER
		nvnQueueFenceSync(&m_GfxQueue, &m_idleSync, NVN_SYNC_CONDITION_ALL_GPU_COMMANDS_COMPLETE, 0);
		nvnQueueFlush(&m_GfxQueue);
		const auto waitResult = nvnSyncWait(&m_idleSync, NVN_WAIT_TIMEOUT_MAXIMUM);

		BX_UNUSED(waitResult);
	}

	void CommandQueueNVN::flush()
	{
		CpuMeasureScope("PresentTexture");
		nvnQueueFlush(&m_GfxQueue);
	}

	bool CommandQueueNVN::consume(const uint64_t _ms)
	{
		NVNsync& fence = m_fences[m_control.m_read];

		if (waitIsFenceSignaled(&fence, _ms))
		{
			m_control.consume(1);
			return true;
		}

		return false;
	}

	//
	//
	//

	uint32_t ShaderUniformBuffer::computeHash(const std::vector<UniformReference>& _uniforms, const uint32_t _stage)
	{
		uint32_t size = (uint32_t)(_uniforms.size() * sizeof(UniformReference));
		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add((void*)_uniforms.data(), size);
		murmur.add(_stage);
		return murmur.end();
	}

	void ShaderUniformBuffer::create(uint32_t _size, std::vector<UniformReference>&& _uniforms)
	{
		m_uniforms = std::move(_uniforms);
		m_size = _size;

		m_buffer = BX_NEW(&g_allocatorNVN, BufferNVN);
		m_buffer->create(m_size, nullptr, 0, 0, BufferNVN::Usage::UniformBuffer);
	}

	void ShaderUniformBuffer::destroy()
	{
		m_uniforms.clear();
		m_size = 0;
		BX_DELETE(&g_allocatorNVN, m_buffer);
		m_buffer = nullptr;
	}

	bool ShaderUniformBuffer::update(NVNcommandBuffer* _cmdBuf)
	{
		bool dirty = false;

		for (UniformReference& uniformRef : m_uniforms)
		{
			if (uniformRef.m_data != nullptr)
			{
				if (uniformRef.m_dirtySize > 0)
				{
					nvnCommandBufferUpdateUniformBuffer(_cmdBuf, m_buffer->m_gpuAddress, m_size, uniformRef.m_index, uniformRef.m_dirtySize, uniformRef.m_data);
					uniformRef.m_dirtySize = 0;
					dirty = true;
				}
			}
		}

		return dirty;
	}

	//
	//
	//

	void UniformBufferRegistry::destroy()
	{
		for (Entry& e : m_buffers)
		{
			e.m_buffer.destroy();
		}

		m_buffers.clear();
	}

	uint32_t UniformBufferRegistry::find(const uint32_t _hash) const
	{
		uint32_t count = (uint32_t)m_buffers.size();
		for (uint32_t index = 0; index < count; ++index)
		{
			if (m_buffers[index].m_hash == _hash)
			{
				return index;
			}
		}

		return InvalidEntry;
	}

	uint32_t UniformBufferRegistry::add(const uint32_t _hash, ShaderUniformBuffer&& _buf)
	{
		uint32_t index = (uint32_t)m_buffers.size();

		Entry e;
		e.m_hash = _hash;
		e.m_buffer = std::move(_buf);
		m_buffers.push_back(std::move(e));

		return index;
	}

	ShaderUniformBuffer& UniformBufferRegistry::get(const uint32_t _index)
	{
		BX_ASSERT(_index < m_buffers.size(), "Invalid uniform buffer.");
		return m_buffers[_index].m_buffer;
	}

	//
	//
	//

	void ShaderNVN::create(NVNdevice* _device, const Memory* _mem, UniformRegistry& _uniformRegistry, UniformBufferRegistry& _uniformBuffers)
	{
		bx::MemoryReader reader(_mem->data, _mem->size);

		uint32_t magic;
		bx::read(&reader, magic);

		const bool hasTexData = !isShaderVerLess(magic, 8);
		const bool hasTexFormat = !isShaderVerLess(magic, 10);

		uint32_t hashIn;
		bx::read(&reader, hashIn);

		uint32_t hashOut;
		bx::read(&reader, hashOut);

		m_stage = NVNshaderStage::NVN_SHADER_STAGE_LARGE;
		const char* kStageName[6] =
		{
			"vertex",
			"fragment",
			"geometry",
			"tess control",
			"tess eval",
			"compute"
		};

		if (isShaderType(magic, 'F'))
		{
			m_stage = NVNshaderStage::NVN_SHADER_STAGE_FRAGMENT;
		}
		else if (isShaderType(magic, 'V'))
		{
			m_stage = NVNshaderStage::NVN_SHADER_STAGE_VERTEX;
		}
		else if (isShaderType(magic, 'C'))
		{
			m_stage = NVNshaderStage::NVN_SHADER_STAGE_COMPUTE;
		}

		BX_ASSERT(m_stage != NVNshaderStage::NVN_SHADER_STAGE_LARGE, "Invalid shader stage");

		const bool fragment = (NVNshaderStage::NVN_SHADER_STAGE_FRAGMENT == m_stage);
		const uint8_t fragmentBit = fragment ? kUniformFragmentBit : 0;

		const auto readUniformBlock = [&](const uint8_t uniformBufferIndex, std::vector<ShaderUniformBuffer::UniformReference>* uniforms)
		{
			uint16_t count;
			bx::read(&reader, count);

			if (uniforms != nullptr)
			{
				uniforms->resize(count);
				memset(uniforms->data(), 0, count * sizeof(ShaderUniformBuffer::UniformReference));
			}

			for (size_t i = 0; i < count; i++)
			{
				uint8_t nameSize = 0;
				bx::read(&reader, nameSize);

				char name[256] = {};
				bx::read(&reader, &name, nameSize);

				uint8_t type;
				bx::read(&reader, type);

				uint8_t num = 0;
				bx::read(&reader, num);

				uint16_t regIndex = 0;
				bx::read(&reader, regIndex);

				uint16_t regCount = 0;
				bx::read(&reader, regCount);

				if (hasTexData)
				{
					uint16_t texInfo = 0;
					bx::read(&reader, texInfo);
				}

				if (hasTexFormat)
				{
					uint16_t texFormat = 0;
					bx::read(&reader, texFormat);
				}

				if (uniforms != nullptr)
				{
					BX_ASSERT(0 == (kUniformSamplerBit & type), "Sampler found in uniform block, not supported.");

					ShaderUniformBuffer::UniformReference& u = (*uniforms)[i];
					u.m_index = regIndex; // actually byte offset
					u.m_count = regCount * num; // actually size in bytes
					u.m_data = nullptr;

					PredefinedUniform::Enum predefined = nameToPredefinedUniformEnum(name);
					if (PredefinedUniform::Count != predefined)
					{
						m_predefined[m_numPredefined].m_loc = regIndex;
						m_predefined[m_numPredefined].m_count = regCount / 16; // this has to be the number of vector registers (16 bytes)
						m_predefined[m_numPredefined].m_type = uint8_t(predefined | fragmentBit);
						m_numPredefined++;

						u.m_predefined = predefined;
						u.m_handle = BGFX_INVALID_HANDLE;
					}
					else
					{
						const UniformRegInfo* info = _uniformRegistry.find(name);
						BX_ASSERT(info != nullptr, "Unknown uniform: %s", name);
						u.m_handle = info->m_handle;
						u.m_predefined = PredefinedUniform::Count;
					}
				}
			}
		};

		// All uniforms
		readUniformBlock(0, nullptr);

		// Global uniforms (ie: samplers)
		readUniformBlock(0, nullptr);

		// Uniform Blocks
		uint8_t uniformBlockCount = 0;
		bx::read(&reader, uniformBlockCount);

		for (int uniformBlockIdx = 0; uniformBlockIdx < uniformBlockCount; uniformBlockIdx++)
		{
			uint8_t nameSize = 0;
			bx::read(&reader, nameSize);

			char name[256] = {};
			bx::read(&reader, &name, nameSize);

			uint8_t slot;
			bx::read(&reader, slot);

			uint32_t uniformSize;
			bx::read(&reader, uniformSize);

			BX_ASSERT(uniformBlockIdx < std::numeric_limits<uint8_t>::max(), "Too many uniform blocks");

			std::vector<ShaderUniformBuffer::UniformReference> uniformRefs;
			readUniformBlock(static_cast<uint8_t>(uniformBlockIdx), &uniformRefs);

			uint32_t cbHash = ShaderUniformBuffer::computeHash(uniformRefs, 0);

			uint32_t index = _uniformBuffers.find(cbHash);
			if (index == UniformBufferRegistry::InvalidEntry)
			{
				// add
				ShaderUniformBuffer cb;
				cb.create(uniformSize, std::move(uniformRefs));
				index = _uniformBuffers.add(cbHash, std::move(cb));
			}

			UniformBufferBinding binding;
			binding.m_handle = index;
			binding.m_slot = slot;

			m_constantBuffers.push_back(binding);
		}

		// Stage inputs

		bx::memSet(m_attrMask, 0, sizeof(m_attrMask));
		bx::memSet(m_attrRemap, 0xFF, sizeof(m_attrRemap));

		uint32_t stageInputCount = 0;
		bx::read(&reader, stageInputCount);

		for (size_t stageInputIdx = 0; stageInputIdx < stageInputCount; stageInputIdx++)
		{
			uint8_t type;
			bx::read(&reader, type);

			bgfx::Attrib::Enum attr = (bgfx::Attrib::Enum)type;

			uint8_t nameSize = 0;
			bx::read(&reader, nameSize);

			char name[256] = {};
			bx::read(&reader, &name, nameSize);

			int32_t location = 0;
			bx::read(&reader, location);

			if (Attrib::Count != attr)
			{
				m_attrMask[attr] = UINT16_MAX;
				m_attrRemap[attr] = static_cast<uint8_t>(location);
			}
		}

		uint32_t shaderControlSize = 0;
		uint32_t shaderCodeSize = 0;

		bx::read(&reader, shaderControlSize);
		bx::read(&reader, shaderCodeSize);

		const void* shaderControl = reader.getDataPtr();

		m_control.clear();
		m_control.resize(shaderControlSize);
		::memcpy(m_control.data(), shaderControl, shaderControlSize);

		bx::skip(&reader, shaderControlSize);
		const void* shaderCode = reader.getDataPtr();

		bx::skip(&reader, shaderCodeSize);

		/*
		* Shader code is not allowed to be in the last 1024 bytes of a memory pool,
		* additional padding is added to ensure that does not happen.
		*/

		m_codeMemoryPool.Init(
			nullptr,
			shaderCodeSize + 1024,
			NVN_MEMORY_POOL_FLAGS_CPU_UNCACHED_BIT | NVN_MEMORY_POOL_FLAGS_GPU_CACHED_BIT | NVN_MEMORY_POOL_FLAGS_SHADER_CODE_BIT,
			_device
		);

		ptrdiff_t codePoolOffset = m_codeMemoryPool.GetNewMemoryChunkOffset(shaderCodeSize, NVN_MEMORY_POOL_STORAGE_ALIGNMENT);
		m_code = static_cast<uint8_t*>(m_codeMemoryPool.GetMemory()) + codePoolOffset;
		m_codeSize = shaderCodeSize;
		::memcpy(m_code, shaderCode, m_codeSize);

		NVNbufferBuilder codeBufferBuilder;
		nvnBufferBuilderSetDefaults(&codeBufferBuilder);
		nvnBufferBuilderSetDevice(&codeBufferBuilder, _device);
		nvnBufferBuilderSetStorage(&codeBufferBuilder, m_codeMemoryPool.GetMemoryPool(), codePoolOffset, m_codeSize);

		nvnBufferInitialize(&m_codeBuffer, &codeBufferBuilder);

		m_shader.data = nvnBufferGetAddress(&m_codeBuffer);
		m_shader.control = m_control.data();

		bx::HashMurmur2A murmur;
		murmur.begin();
		murmur.add(hashIn);
		murmur.add(hashOut);
		murmur.add(m_code, shaderCodeSize);
		murmur.add(m_attrMask, sizeof(m_attrMask));
		m_hash = murmur.end();
	}

	void ProgramNVN::create(NVNdevice* _device, const ShaderNVN* _vsh, const ShaderNVN* _fsh)
	{
		BX_ASSERT(_vsh && _vsh->m_code, "Vertex shader doesn't exist.");

		m_Stages = 0;
		m_vsh = _vsh;
		m_fsh = _fsh;

		std::array<NVNshaderData, 2> shaderData;
		bool hasFrag = false;

		::memcpy(&m_predefined[0], _vsh->m_predefined, _vsh->m_numPredefined * sizeof(PredefinedUniform));
		m_numPredefined = _vsh->m_numPredefined;

		shaderData[0] = _vsh->m_shader;

		m_Stages |= NVNshaderStageBits::NVN_SHADER_STAGE_VERTEX_BIT;

		if (NULL != _fsh)
		{
			BX_ASSERT(NULL != _fsh->m_code, "Fragment shader doesn't exist.");
			hasFrag = true;

			m_Stages |= NVNshaderStageBits::NVN_SHADER_STAGE_FRAGMENT_BIT;

			m_fsh = _fsh;
			::memcpy(&m_predefined[m_numPredefined], _fsh->m_predefined, _fsh->m_numPredefined * sizeof(PredefinedUniform));
			m_numPredefined += _fsh->m_numPredefined;

			shaderData[1] = _fsh->m_shader;
		}
		else
		{
			m_Stages = NVNshaderStageBits::NVN_SHADER_STAGE_COMPUTE_BIT;
		}

		nvnProgramInitialize(&m_program, _device);

		if (!nvnProgramSetShaders(&m_program, hasFrag ? 2 : 1, &shaderData[0]))
		{
			BX_ASSERT(false, "Failed to set pre-compiled headers");
		}
	}

	//
	//
	//

	void VertexLayoutNVN::create(const VertexLayout& _vertexLayout)
	{
	}

	//
	//
	//

	void VertexBufferNVN::create(uint32_t _size, void* _data, VertexLayoutHandle _layoutHandle, uint16_t _flags)
	{
		BufferNVN::create(_size, _data, _flags, 0, BufferNVN::Usage::VertexBuffer);
		m_layoutHandle = _layoutHandle;
	}

	//
	//
	//

	void FrameBufferNVN::create(uint8_t _num, const Attachment* _attachment)
	{
		BX_ASSERT(_num <= BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS, "Invalid attachment count.");

		m_numAttachments = _num;
		memcpy(m_attachment, _attachment, _num * sizeof(Attachment));

		m_numTargets = 0;
		m_depthTarget = BGFX_INVALID_HANDLE;
	}
} }

#endif // BGFX_CONFIG_RENDERER_NVN

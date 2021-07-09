/********************************************************
*   (c) Mojang. All rights reserved                     *
*   (c) Microsoft. All rights reserved.                 *
*********************************************************/

#include "../bgfx_p.h"

#if BGFX_CONFIG_RENDERER_NVN

#include "resources.h"
#include <bimg/bimg.h>
#include <nvn/nvn.h>

namespace bgfx { namespace nvn
{
	struct TextureFormatInfo
	{
		NVNformat m_fmt;
		NVNformat m_fmtDsv;
		NVNformat m_fmtSrgb;
	};

	static const TextureFormatInfo s_textureFormat[] =
	{
		{ NVN_FORMAT_RGBA_DXT1,				NVN_FORMAT_NONE,			NVN_FORMAT_RGBA_DXT1_SRGB       }, // BC1
		{ NVN_FORMAT_RGBA_DXT3,				NVN_FORMAT_NONE,			NVN_FORMAT_RGBA_DXT3_SRGB       }, // BC2
		{ NVN_FORMAT_RGBA_DXT5,				NVN_FORMAT_NONE,			NVN_FORMAT_RGBA_DXT5_SRGB       }, // BC3
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // BC4
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // BC5
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // BC6H
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // BC7
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // ETC1
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // ETC2
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // ETC2A
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // ETC2A1
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // PTC12
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // PTC14
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // PTC12A
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // PTC14A
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // PTC22
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // PTC24
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // ATC
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // ATCE
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // ATCI
		{ NVN_FORMAT_RGBA_ASTC_4x4,			NVN_FORMAT_NONE,			NVN_FORMAT_RGBA_ASTC_4x4_SRGB	}, // ASTC4x4
		{ NVN_FORMAT_RGBA_ASTC_5x5,			NVN_FORMAT_NONE,			NVN_FORMAT_RGBA_ASTC_5x5_SRGB	}, // ASTC5x5
		{ NVN_FORMAT_RGBA_ASTC_6x6,			NVN_FORMAT_NONE,			NVN_FORMAT_RGBA_ASTC_6x6_SRGB	}, // ASTC6x6
		{ NVN_FORMAT_RGBA_ASTC_8x5,			NVN_FORMAT_NONE,			NVN_FORMAT_RGBA_ASTC_8x5_SRGB	}, // ASTC8x5
		{ NVN_FORMAT_RGBA_ASTC_8x6,			NVN_FORMAT_NONE,			NVN_FORMAT_RGBA_ASTC_8x6_SRGB	}, // ASTC8x6
		{ NVN_FORMAT_RGBA_ASTC_10x5,		NVN_FORMAT_NONE,			NVN_FORMAT_RGBA_ASTC_10x5_SRGB	}, // ASTC10x5
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // Unknown
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // R1
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // A8
		{ NVN_FORMAT_R8,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // R8
		{ NVN_FORMAT_R8I,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // R8I
		{ NVN_FORMAT_R8UI,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // R8U
		{ NVN_FORMAT_R8SN,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // R8S
		{ NVN_FORMAT_R16,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // R16
		{ NVN_FORMAT_R16I,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // R16I
		{ NVN_FORMAT_R16,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // R16U
		{ NVN_FORMAT_R16F,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // R16F
		{ NVN_FORMAT_R16SN,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // R16S
		{ NVN_FORMAT_R32I,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // R32I
		{ NVN_FORMAT_R32UI,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // R32U
		{ NVN_FORMAT_R32F,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // R32F
		{ NVN_FORMAT_RG8,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RG8
		{ NVN_FORMAT_RG8I,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RG8I
		{ NVN_FORMAT_RG8UI,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RG8U
		{ NVN_FORMAT_RG8SN,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RG8S
		{ NVN_FORMAT_RG16,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RG16
		{ NVN_FORMAT_RG16I,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RG16I
		{ NVN_FORMAT_RG16UI,				NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RG16U
		{ NVN_FORMAT_RG16F,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RG16F
		{ NVN_FORMAT_RG16SN,				NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RG16S
		{ NVN_FORMAT_RG32I,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RG32I
		{ NVN_FORMAT_RG32UI,				NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RG32U
		{ NVN_FORMAT_RG32F,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RG32F
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RGB8
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RGB8I
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RGB8U
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RGB8S
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RGB9E5F
		{ NVN_FORMAT_BGRA8,					NVN_FORMAT_NONE,			NVN_FORMAT_BGRA8_SRGB			}, // BGRA8
		{ NVN_FORMAT_RGBA8,					NVN_FORMAT_NONE,			NVN_FORMAT_RGBA8_SRGB			}, // RGBA8
		{ NVN_FORMAT_RGBA8I,				NVN_FORMAT_NONE,			NVN_FORMAT_RGBA8_SRGB			}, // RGBA8I
		{ NVN_FORMAT_RGBA8UI,				NVN_FORMAT_NONE,			NVN_FORMAT_RGBA8_SRGB			}, // RGBA8U
		{ NVN_FORMAT_RGBA8SN,				NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RGBA8S
		{ NVN_FORMAT_RGBA16,				NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RGBA16
		{ NVN_FORMAT_RGBA16I,				NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RGBA16I
		{ NVN_FORMAT_RGBA16UI,				NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RGBA16U
		{ NVN_FORMAT_RGBA16F,				NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RGBA16F
		{ NVN_FORMAT_RGBA16SN,				NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RGBA16S
		{ NVN_FORMAT_RGBA32I,				NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RGBA32I
		{ NVN_FORMAT_RGBA32UI,				NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RGBA32U
		{ NVN_FORMAT_RGBA32F,				NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RGBA32F
		{ NVN_FORMAT_BGR565,				NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // R5G6B5
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RGBA4
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RGB5A1
		{ NVN_FORMAT_RGB10A2,				NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RGB10A2
		{ NVN_FORMAT_R11G11B10F,			NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // RG11B10F
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // UnknownDepth
		{ NVN_FORMAT_R16,					NVN_FORMAT_DEPTH16,			NVN_FORMAT_NONE					}, // D16
		{ NVN_FORMAT_DEPTH24,				NVN_FORMAT_DEPTH24,			NVN_FORMAT_NONE					}, // D24
		{ NVN_FORMAT_DEPTH24_STENCIL8,		NVN_FORMAT_DEPTH24_STENCIL8,NVN_FORMAT_NONE					}, // D24S8
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE					}, // D32
		{ NVN_FORMAT_DEPTH32F,				NVN_FORMAT_DEPTH32F,        NVN_FORMAT_NONE					}, // D16F
		{ NVN_FORMAT_DEPTH32F,				NVN_FORMAT_DEPTH32F,        NVN_FORMAT_NONE					}, // D24F
		{ NVN_FORMAT_DEPTH32F,				NVN_FORMAT_DEPTH32F,        NVN_FORMAT_NONE					}, // D32F
		{ NVN_FORMAT_DEPTH24_STENCIL8,		NVN_FORMAT_DEPTH24_STENCIL8,NVN_FORMAT_NONE					}, // D0S8
	};

	static_assert(TextureFormat::Count == BX_COUNTOF(s_textureFormat), "");

	//
	//
	//

	void TextureNVN::create(NVNdevice* _device, NVNtextureBuilder& _builder)
	{
		BX_ASSERT(!m_created, "Texture should be destroyed first");

		nvnTextureBuilderSetDevice(&_builder, _device);
		size_t storageSize = nvnTextureBuilderGetStorageSize(&_builder);

		m_pool.Init(nullptr, storageSize, NVN_MEMORY_POOL_FLAGS_CPU_NO_ACCESS_BIT | NVN_MEMORY_POOL_FLAGS_GPU_CACHED_BIT | NVN_MEMORY_POOL_FLAGS_COMPRESSIBLE_BIT, _device);

		nvnTextureBuilderSetStorage(&_builder, m_pool.GetMemoryPool(), 0);

		BX_ASSERT(nvnTextureInitialize(&m_ptr, &_builder), "Texture creation failed");

		m_created = true;
	}

	void TextureNVN::create(NVNdevice* _device, const Memory* _mem, uint32_t _flags, uint8_t _skip)
	{
		bimg::ImageContainer imageContainer;

		if (bimg::imageParse(imageContainer, _mem->data, _mem->size))
		{
			uint8_t numMips = imageContainer.m_numMips;
			const uint8_t startLod = uint8_t(bx::uint32_min(_skip, numMips - 1));
			numMips -= startLod;
			const bimg::ImageBlockInfo& blockInfo = bimg::getBlockInfo(imageContainer.m_format);
			const uint32_t textureWidth = bx::uint32_max(blockInfo.blockWidth, imageContainer.m_width >> startLod);
			const uint32_t textureHeight = bx::uint32_max(blockInfo.blockHeight, imageContainer.m_height >> startLod);
			const uint16_t numLayers = imageContainer.m_numLayers;

			m_flags = _flags;
			m_width = textureWidth;
			m_height = textureHeight;
			m_depth = imageContainer.m_depth;
			m_requestedFormat = uint8_t(imageContainer.m_format);
			m_textureFormat = uint8_t(getViableTextureFormat(imageContainer));
			// const bool convert = m_textureFormat != m_requestedFormat;
			// const uint8_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat));

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
			//const uint32_t numSrd = numSides * numMips;

			uint32_t kk = 0;

			//const bool compressed = bimg::isCompressed(bimg::TextureFormat::Enum(m_textureFormat));
			//const bool swizzle = TextureFormat::BGRA8 == m_textureFormat && 0 != (m_flags&BGFX_TEXTURE_COMPUTE_WRITE);

			//const bool writeOnly = 0 != (m_flags&BGFX_TEXTURE_RT_WRITE_ONLY);
			//const bool computeWrite = 0 != (m_flags&BGFX_TEXTURE_COMPUTE_WRITE);
			const bool renderTarget = 0 != (m_flags & BGFX_TEXTURE_RT_MASK);
			const bool srgb = 0 != (m_flags & BGFX_TEXTURE_SRGB);
			//const bool blit = 0 != (m_flags&BGFX_TEXTURE_BLIT_DST);

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

			for (uint8_t side = 0; side < numSides; ++side)
			{
				for (uint8_t lod = 0; lod < numMips; ++lod)
				{
					bimg::ImageMip mip;
					if (bimg::imageGetRawData(imageContainer, side, lod + startLod, _mem->data, _mem->size, mip))
					{
						//BX_ASSERT(false, "TODO");
						/*if (convert)
						{
							const uint32_t pitch = bx::strideAlign(bx::max<uint32_t>(mip.m_width, 4)*bpp / 8, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);
							const uint32_t slice = bx::strideAlign(bx::max<uint32_t>(mip.m_height, 4)*pitch, D3D12_TEXTURE_DATA_PLACEMENT_ALIGNMENT);
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

							srd[kk].pData = temp;
							srd[kk].RowPitch = pitch;
							srd[kk].SlicePitch = slice;
						}
						else if (compressed)
						{
							const uint32_t pitch = bx::strideAlign((mip.m_width / blockInfo.blockWidth)*mip.m_blockSize, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);
							const uint32_t slice = bx::strideAlign((mip.m_height / blockInfo.blockHeight)*pitch, D3D12_TEXTURE_DATA_PLACEMENT_ALIGNMENT);
							const uint32_t size = slice * mip.m_depth;

							uint8_t* temp = (uint8_t*)BX_ALLOC(g_allocator, size);
							bimg::imageCopy(temp
								, mip.m_height / blockInfo.blockHeight
								, (mip.m_width / blockInfo.blockWidth)*mip.m_blockSize
								, mip.m_depth
								, mip.m_data
								, pitch
							);

							srd[kk].pData = temp;
							srd[kk].RowPitch = pitch;
							srd[kk].SlicePitch = slice;
						}
						else
						{
							const uint32_t pitch = bx::strideAlign(mip.m_width*mip.m_bpp / 8, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);
							const uint32_t slice = bx::strideAlign(mip.m_height*pitch, D3D12_TEXTURE_DATA_PLACEMENT_ALIGNMENT);

							uint8_t* temp = (uint8_t*)BX_ALLOC(g_allocator, slice*mip.m_depth);
							bimg::imageCopy(temp
								, mip.m_height
								, mip.m_width*mip.m_bpp / 8
								, mip.m_depth
								, mip.m_data
								, pitch
							);

							srd[kk].pData = temp;
							srd[kk].RowPitch = pitch;
							srd[kk].SlicePitch = slice;
						}*/

						++kk;
					}
				}
			}

			NVNtextureBuilder textureBuilder;
			nvnTextureBuilderSetDevice(&textureBuilder, _device);
			nvnTextureBuilderSetDefaults(&textureBuilder);

			NVNformat format = srgb ? s_textureFormat[m_textureFormat].m_fmtSrgb : s_textureFormat[m_textureFormat].m_fmt;

			if (bimg::isDepth(bimg::TextureFormat::Enum(m_textureFormat)))
			{
				BX_ASSERT(!srgb, "SRGB DepthBuffer ???");
				format = s_textureFormat[m_textureFormat].m_fmtDsv;
				// BX_ASSERT(false, "TODO");
				/*resourceDesc.Format = s_textureFormat[m_textureFormat].m_fmt;
				resourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
				state |= D3D12_RESOURCE_STATE_DEPTH_WRITE;
				state &= ~D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;

				clearValue = (D3D12_CLEAR_VALUE*)alloca(sizeof(D3D12_CLEAR_VALUE));
				clearValue->Format = s_textureFormat[m_textureFormat].m_fmtDsv;
				clearValue->DepthStencil.Depth = 1.0f;
				clearValue->DepthStencil.Stencil = 0;*/
			}
			else if (renderTarget)
			{
				BX_ASSERT(!srgb, "Can't have a SRGB RenderTarget");
				nvnTextureBuilderSetFlags(&textureBuilder, NVN_TEXTURE_FLAGS_DISPLAY_BIT | NVN_TEXTURE_FLAGS_COMPRESSIBLE_BIT);
			}

			nvnTextureBuilderSetFormat(&textureBuilder, format);

			/*const uint32_t msaaQuality = bx::uint32_satsub((m_flags&BGFX_TEXTURE_RT_MSAA_MASK) >> BGFX_TEXTURE_RT_MSAA_SHIFT, 1);
			const DXGI_SAMPLE_DESC& msaa = s_msaa[msaaQuality];

			bx::memSet(&m_srvd, 0, sizeof(m_srvd));
			m_srvd.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			m_srvd.Format = s_textureFormat[m_textureFormat].m_fmtSrv;
			DXGI_FORMAT format = s_textureFormat[m_textureFormat].m_fmt;
			if (swizzle)
			{
				format = srgb ? DXGI_FORMAT_RGBA8_UNORM_SRGB : DXGI_FORMAT_RGBA8_UNORM;
				m_srvd.Format = format;
			}
			else if (srgb)
			{
				format = s_textureFormat[m_textureFormat].m_fmtSrgb;
				m_srvd.Format = format;
				BX_WARN(format != DXGI_FORMAT_UNKNOWN, "sRGB not supported for texture format %d", m_textureFormat);
			}

			m_uavd.Format = m_srvd.Format;

			ID3D12Device* device = s_renderD3D12->m_device;
			ID3D12GraphicsCommandList* commandList = s_renderD3D12->m_commandList;

			D3D12_RESOURCE_DESC resourceDesc;
			resourceDesc.Alignment = 1 < msaa.Count ? D3D12_DEFAULT_MSAA_RESOURCE_PLACEMENT_ALIGNMENT : 0;
			resourceDesc.Width = textureWidth;
			resourceDesc.Height = textureHeight;
			resourceDesc.MipLevels = numMips;
			resourceDesc.Format = format;
			resourceDesc.SampleDesc = msaa;
			resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
			resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
			resourceDesc.DepthOrArraySize = numSides;
			D3D12_RESOURCE_STATES state = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;*/



			//D3D12_CLEAR_VALUE* clearValue = NULL;
			//if (bimg::isDepth(bimg::TextureFormat::Enum(m_textureFormat)))
			//{
			//	resourceDesc.Format = s_textureFormat[m_textureFormat].m_fmt;
			//	resourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
			//	state |= D3D12_RESOURCE_STATE_DEPTH_WRITE;
			//	state &= ~D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;

			//	clearValue = (D3D12_CLEAR_VALUE*)alloca(sizeof(D3D12_CLEAR_VALUE));
			//	clearValue->Format = s_textureFormat[m_textureFormat].m_fmtDsv;
			//	clearValue->DepthStencil.Depth = 1.0f;
			//	clearValue->DepthStencil.Stencil = 0;
			//}
			//else if (renderTarget)
			//{
			//	resourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
			//	state |= D3D12_RESOURCE_STATE_RENDER_TARGET;
			//	state &= ~D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;

			//	clearValue = (D3D12_CLEAR_VALUE*)alloca(sizeof(D3D12_CLEAR_VALUE));
			//	clearValue->Format = resourceDesc.Format;
			//	clearValue->Color[0] = 0.0f;
			//	clearValue->Color[1] = 0.0f;
			//	clearValue->Color[2] = 0.0f;
			//	clearValue->Color[3] = 0.0f;
			//}

			//if (writeOnly)
			//{
			//	resourceDesc.Flags |= D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;
			//	state &= ~D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
			//}

			//if (computeWrite)
			//{
			//	resourceDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
			//}

			//if (blit)
			//{
			//	state = D3D12_RESOURCE_STATE_COPY_DEST;
			//}

			//const bool directAccess = s_renderD3D12->m_directAccessSupport
			//	&& !renderTarget
			//	//				&& !readBack
			//	&& !blit
			//	&& !writeOnly
			//	;

			switch (m_type)
			{
			case Texture2D:
				nvnTextureBuilderSetSize2D(&textureBuilder, textureWidth, textureHeight);
				nvnTextureBuilderSetTarget(&textureBuilder, NVN_TEXTURE_TARGET_2D);
				break;
			case TextureCube:
				return;
				/*	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
					if (imageContainer.m_cubeMap)
					{
						if (1 < numLayers)
						{
							m_srvd.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBEARRAY;
							m_srvd.TextureCubeArray.MostDetailedMip = 0;
							m_srvd.TextureCubeArray.MipLevels = numMips;
							m_srvd.TextureCubeArray.ResourceMinLODClamp = 0.0f;
							m_srvd.TextureCubeArray.NumCubes = numLayers;
						}
						else
						{
							m_srvd.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
							m_srvd.TextureCube.MostDetailedMip = 0;
							m_srvd.TextureCube.MipLevels = numMips;
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
							m_srvd.Texture2DArray.MostDetailedMip = 0;
							m_srvd.Texture2DArray.MipLevels = numMips;
							m_srvd.Texture2DArray.ResourceMinLODClamp = 0.0f;
							m_srvd.Texture2DArray.ArraySize = numLayers;
						}
						else
						{
							m_srvd.ViewDimension = 1 < msaa.Count
								? D3D12_SRV_DIMENSION_TEXTURE2DMS
								: D3D12_SRV_DIMENSION_TEXTURE2D
								;
							m_srvd.Texture2D.MostDetailedMip = 0;
							m_srvd.Texture2D.MipLevels = numMips;
							m_srvd.Texture2D.ResourceMinLODClamp = 0.0f;
						}
					}

					if (1 < numLayers)
					{
						m_uavd.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2DARRAY;
						m_uavd.Texture2DArray.MipSlice = 0;
						m_uavd.Texture2DArray.PlaneSlice = 0;
					}
					else
					{
						m_uavd.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
						m_uavd.Texture2D.MipSlice = 0;
						m_uavd.Texture2D.PlaneSlice = 0;
					}

					if (TextureCube == m_type)
					{
						m_uavd.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2DARRAY;
						m_uavd.Texture2DArray.MipSlice = 0;
						m_uavd.Texture2DArray.ArraySize = 6;
					}

					break;*/

			case Texture3D:
				nvnTextureBuilderSetSize3D(&textureBuilder, textureWidth, textureHeight, m_depth);
				nvnTextureBuilderSetTarget(&textureBuilder, NVN_TEXTURE_TARGET_3D);
				// resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE3D;
				// resourceDesc.DepthOrArraySize = uint16_t(m_depth);
				// m_srvd.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
				// m_srvd.Texture3D.MostDetailedMip = 0;
				// m_srvd.Texture3D.MipLevels = numMips;
				// m_srvd.Texture3D.ResourceMinLODClamp = 0.0f;
				// 
				// m_uavd.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE3D;
				// m_uavd.Texture3D.MipSlice = 0;
				// m_uavd.Texture3D.FirstWSlice = 0;
				// m_uavd.Texture3D.WSize = 0;
				break;
			}

			create(_device, textureBuilder);

			/*m_ptr = createCommittedResource(device, HeapProperty::Texture, &resourceDesc, clearValue, renderTarget);

			if (directAccess)
			{
				DX_CHECK(m_ptr->Map(0, NULL, &m_directAccessPtr));
			}

			if (kk != 0)
			{
				uint64_t uploadBufferSize;
				device->GetCopyableFootprints(&resourceDesc, 0, numSrd, 0, NULL, NULL, NULL, &uploadBufferSize);

				ID3D12Resource* staging = createCommittedResource(s_renderD3D12->m_device, HeapProperty::Upload, uint32_t(uploadBufferSize));

				setState(commandList, D3D12_RESOURCE_STATE_COPY_DEST);

				uint64_t result = UpdateSubresources(commandList
					, m_ptr
					, staging
					, 0
					, 0
					, numSrd
					, srd
				);
				BX_ASSERT(0 != result, "Invalid size"); BX_UNUSED(result);
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
						BX_FREE(g_allocator, const_cast<void*>(srd[kk].pData));
						++kk;
					}
				}
			}*/
		}
	}

	void TextureNVN::destroy()
	{
		if (m_created)
		{
			nvnTextureFinalize(&m_ptr);

			m_handle = -1;

			m_created = false;
		}
	}

	void TextureNVN::update(NVNcommandBuffer*, uint8_t, uint8_t, const Rect&, uint16_t, uint16_t, uint16_t, const Memory*)
	{
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

	void SwapChainNVN::create(NVNnativeWindow _nativeWindow, NVNdevice* _device, const bgfx::Resolution& _size, const bgfx::TextureFormat::Enum _colorFormat, const bgfx::TextureFormat::Enum _depthFormat)
	{
		BX_ASSERT(!bimg::isDepth(bimg::TextureFormat::Enum(_colorFormat)), "Color shouldn't be a depth format");
		BX_ASSERT(bimg::isDepth(bimg::TextureFormat::Enum(_depthFormat)), "Depth should be a depth format");

		BX_ASSERT(!m_Created, "Should destroy first");

		nvnSyncInitialize(&m_WindowSync, _device);

		NVNwindowBuilder windowBuilder;

		nvnWindowBuilderSetDefaults(&windowBuilder);
		nvnWindowBuilderSetDevice(&windowBuilder, _device);
		nvnWindowBuilderSetNativeWindow(&windowBuilder, _nativeWindow);

		std::array<NVNtexture*, TextureCount> nvnColors;

		// BBI-TODO: (tstump 1) don't create depth buffers for each scan buffer, it's not needed

		for (int i = 0; i < TextureCount; i++) {
			{
				NVNtextureBuilder colorBuilder;
				nvnTextureBuilderSetDefaults(&colorBuilder);
				nvnTextureBuilderSetDevice(&colorBuilder, _device);
				nvnTextureBuilderSetFlags(&colorBuilder, NVN_TEXTURE_FLAGS_DISPLAY_BIT | NVN_TEXTURE_FLAGS_COMPRESSIBLE_BIT);
				nvnTextureBuilderSetTarget(&colorBuilder, NVN_TEXTURE_TARGET_2D);
				nvnTextureBuilderSetFormat(&colorBuilder, s_textureFormat[uint8_t(_colorFormat)].m_fmt);
				nvnTextureBuilderSetSize2D(&colorBuilder, _size.width, _size.height);

				m_ColorTextures[i].create(_device, colorBuilder);

				nvnColors[i] = &m_ColorTextures[i].m_ptr;
			}

			{
				NVNtextureBuilder depthBuilder;
				nvnTextureBuilderSetDefaults(&depthBuilder);
				nvnTextureBuilderSetDevice(&depthBuilder, _device);
				nvnTextureBuilderSetFlags(&depthBuilder, NVN_TEXTURE_FLAGS_COMPRESSIBLE_BIT);
				nvnTextureBuilderSetTarget(&depthBuilder, NVN_TEXTURE_TARGET_2D);
				nvnTextureBuilderSetFormat(&depthBuilder, s_textureFormat[uint8_t(_depthFormat)].m_fmtDsv);
				nvnTextureBuilderSetSize2D(&depthBuilder, _size.width, _size.height);

				m_DepthTextures[i].create(_device, depthBuilder);
			}
		}

		nvnWindowBuilderSetTextures(&windowBuilder, TextureCount, nvnColors.data());
		nvnWindowInitialize(&m_Window, &windowBuilder);

		m_Created = true;
	}

	void SwapChainNVN::destroy()
	{
		if (m_Created)
		{
			nvnWindowFinalize(&m_Window);

			for (int i = 0; i < TextureCount; i++)
			{
				m_ColorTextures[i].destroy();
				m_DepthTextures[i].destroy();
			}

			nvnSyncFinalize(&m_WindowSync);

			m_Created = false;
		}
	}

	BackBuffer SwapChainNVN::acquireNext()
	{
		BX_ASSERT(m_Created, "SwapChain wasn't created");
		BX_ASSERT(nvnWindowAcquireTexture(&m_Window, &m_WindowSync, &m_Current) == NVN_WINDOW_ACQUIRE_TEXTURE_RESULT_SUCCESS, "AcquireNext failed");

		nvnSyncWait(&m_WindowSync, NVN_WAIT_TIMEOUT_MAXIMUM);

		return get();
	}

	BackBuffer SwapChainNVN::get()
	{
		BX_ASSERT(m_Created, "SwapChain wasn't created");
		return BackBuffer{ &m_ColorTextures[m_Current], &m_DepthTextures[m_Current] };
	}

	void SwapChainNVN::present(NVNqueue* _queue)
	{
		BX_ASSERT(m_Created, "SwapChain wasn't created");
		nvnQueuePresentTexture(_queue, &m_Window, m_Current);
	}

	//
	//
	//

	void OutOfCommandBufferMemoryEventCallback(NVNcommandBuffer* cmdBuf, NVNcommandBufferMemoryEvent event, size_t minSize, void* callbackData);

	void CommandListNVN::init(NVNdevice* _device)
	{
		nvnCommandBufferInitialize(&m_cmd, _device);

		nvnCommandBufferSetMemoryCallback(&m_cmd, OutOfCommandBufferMemoryEventCallback);
	}

	void CommandListNVN::shutdown()
	{
		nvnCommandBufferFinalize(&m_cmd);
	}

	void CommandListNVN::begin(const char* name)
	{
		NN_PERF_BEGIN_MEASURE_NAME_GPU(&m_cmd, name);

		OutOfCommandBufferMemoryEventCallback(&m_cmd, NVNcommandBufferMemoryEvent::NVN_COMMAND_BUFFER_MEMORY_EVENT_OUT_OF_COMMAND_MEMORY, 512, nullptr);
		OutOfCommandBufferMemoryEventCallback(&m_cmd, NVNcommandBufferMemoryEvent::NVN_COMMAND_BUFFER_MEMORY_EVENT_OUT_OF_CONTROL_MEMORY, 512, nullptr);

		nvnCommandBufferBeginRecording(&m_cmd);

		_resetState();
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

	NVNcommandHandle CommandListNVN::_end()
	{
		NN_PERF_END_MEASURE_GPU(&m_cmd);

		return nvnCommandBufferEndRecording(&m_cmd);
	}

	void CommandListNVN::_resetState()
	{
		for (int i = 0; i < m_CurrentColor.size(); i++)
		{
			m_CurrentColor[i] = nullptr;
		}

		m_CurrentDepth = nullptr;

		m_PrimitiveTopology = NVNdrawPrimitive::NVN_DRAW_PRIMITIVE_TRIANGLES;

		//m_CurrentIndexBuffer = nullptr;
		m_CurrentIndexBufferIndexType = NVNindexType::NVN_INDEX_TYPE_UNSIGNED_SHORT;
		m_CurrentIndexBufferAddress = 0;

		//m_CurrentProgram = nullptr;

		//std::fill(m_VboBindings.begin(), m_VboBindings.end(), PipelineVboBindPoint{});
		//std::fill(m_UniformScratch.begin(), m_UniformScratch.end(), UniformScratchMemory{});
	}

	//
	//
	//

	CommandQueueNVN::CommandQueueNVN()
		: m_control(CommandListCount)
		/* : m_currentFence(0)
		, m_completedFence(0)
		, m_control(BX_COUNTOF(m_commandList))*/
	{
		// BX_STATIC_ASSERT(BX_COUNTOF(m_commandList) == BX_COUNTOF(m_release));
	}

	void CommandQueueNVN::init(NVNdevice* _device, SwapChainNVN* _swapChain)
	{
		m_Device = _device;
		m_SwapChain = _swapChain;

		{
			NVNqueueBuilder queueBuilder;
			nvnQueueBuilderSetDevice(&queueBuilder, m_Device);
			nvnQueueBuilderSetDefaults(&queueBuilder);
			nvnQueueBuilderSetComputeMemorySize(&queueBuilder, 0);

			BX_ASSERT(nvnQueueInitialize(&m_GfxQueue, &queueBuilder), "nvnQueueInitialize");
		}

		/*D3D12_COMMAND_QUEUE_DESC queueDesc;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		queueDesc.Priority = 0;
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.NodeMask = 1;
		DX_CHECK(_device->CreateCommandQueue(&queueDesc
			, IID_ID3D12CommandQueue
			, (void**)&m_commandQueue
		));

		m_completedFence = 0;
		m_currentFence = 0;
		DX_CHECK(_device->CreateFence(0
			, D3D12_FENCE_FLAG_NONE
			, IID_ID3D12Fence
			, (void**)&m_fence
		));
		*/

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

	CommandListNVN* CommandQueueNVN::alloc(CommandMemoryPool& commandMemoryPool, const char* name)
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
		// QueuePresentTexture
		CpuMeasureScope("PresentTexture");
		// nvnQueuePresentTexture
		// nvnQueueFenceSync(&m_GfxQueue, fence, NVN_SYNC_CONDITION_ALL_GPU_COMMANDS_COMPLETE, 0);
		nvnQueueFlush(&m_GfxQueue);
		//m_GfxQueue.Present(m_SwapChain, 1);
	}

	// void release(ID3D12Resource* _ptr) {}

	bool CommandQueueNVN::consume(const uint64_t _ms)
	{
		// nn::gfx::CommandBuffer& commandList = m_commandList[m_control.m_read];
		NVNsync& fence = m_fences[m_control.m_read];

		if (waitIsFenceSignaled(&fence, _ms))
		{
			/*CloseHandle(commandList.m_event);
			commandList.m_event = NULL;
			m_completedFence = m_fence->GetCompletedValue();
			BX_WARN(UINT64_MAX != m_completedFence, "D3D12: Device lost.");

			m_commandQueue->Wait(m_fence, m_completedFence);

			ResourceArray& ra = m_release[m_control.m_read];
			for (ResourceArray::iterator it = ra.begin(), itEnd = ra.end(); it != itEnd; ++it)
			{
				DX_RELEASE(*it, 0);
			}
			ra.clear();*/

			m_control.consume(1);

			return true;
		}

		return false;
	}
} }

#endif // BGFX_CONFIG_RENDERER_NVN

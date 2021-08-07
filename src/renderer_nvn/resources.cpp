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
		{ NVN_FORMAT_RGBA32UI, NVN_FORMAT_NONE, NVN_FORMAT_NONE					}, // RGBA32U
		{ NVN_FORMAT_RGBA32F,				NVN_FORMAT_NONE,			NVN_FORMAT_NONE }, // RGBA32F
		{ NVN_FORMAT_BGR565,				NVN_FORMAT_NONE,			NVN_FORMAT_NONE }, // R5G6B5
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE }, // RGBA4
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE }, // RGB5A1
		{ NVN_FORMAT_RGB10A2,				NVN_FORMAT_NONE,			NVN_FORMAT_NONE }, // RGB10A2
		{ NVN_FORMAT_R11G11B10F,			NVN_FORMAT_NONE,			NVN_FORMAT_NONE }, // RG11B10F
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE }, // UnknownDepth
		{ NVN_FORMAT_R16,					NVN_FORMAT_DEPTH16,			NVN_FORMAT_NONE }, // D16
		{ NVN_FORMAT_DEPTH24,				NVN_FORMAT_DEPTH24,			NVN_FORMAT_NONE }, // D24
		{ NVN_FORMAT_DEPTH24_STENCIL8,		NVN_FORMAT_DEPTH24_STENCIL8,NVN_FORMAT_NONE }, // D24S8
		{ NVN_FORMAT_NONE,					NVN_FORMAT_NONE,			NVN_FORMAT_NONE }, // D32
		{ NVN_FORMAT_DEPTH32F,				NVN_FORMAT_DEPTH32F,        NVN_FORMAT_NONE }, // D16F
		{ NVN_FORMAT_DEPTH32F,				NVN_FORMAT_DEPTH32F,        NVN_FORMAT_NONE }, // D24F
		{ NVN_FORMAT_DEPTH32F,				NVN_FORMAT_DEPTH32F,        NVN_FORMAT_NONE }, // D32F
		{ NVN_FORMAT_DEPTH24_STENCIL8,		NVN_FORMAT_DEPTH24_STENCIL8,NVN_FORMAT_NONE }, // D0S8
	};

	static_assert(TextureFormat::Count == BX_COUNTOF(s_textureFormat), "");

	//
	//
	//

	void CopyOperation::createBuffer(size_t _size, CopyOperation::Data* _data)
	{
		_data->m_size = _size;

		size_t poolSize = nn::util::align_up(_size, NVN_MEMORY_POOL_STORAGE_GRANULARITY);
		_data->m_mem = BX_ALIGNED_ALLOC(g_allocator, poolSize, NVN_MEMORY_POOL_STORAGE_ALIGNMENT);

		NVNmemoryPoolBuilder poolBuilder;
		nvnMemoryPoolBuilderSetDefaults(&poolBuilder);
		nvnMemoryPoolBuilderSetDevice(&poolBuilder, g_nvnDevice);
		nvnMemoryPoolBuilderSetFlags(&poolBuilder, NVN_MEMORY_POOL_FLAGS_CPU_UNCACHED_BIT | NVN_MEMORY_POOL_FLAGS_GPU_UNCACHED_BIT);
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

	void TextureNVN::create(NVNdevice* _device, const Memory* _mem, uint32_t _flags, uint8_t _skip, CopyOperation& _copyOp)
	{
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
			// const bool convert = m_textureFormat != m_requestedFormat;
			// const uint8_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(m_textureFormat));

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

			//const bool compressed = bimg::isCompressed(bimg::TextureFormat::Enum(m_textureFormat));
			const bool swizzle = TextureFormat::BGRA8 == m_textureFormat && 0 != (m_flags & BGFX_TEXTURE_COMPUTE_WRITE);

			//const bool writeOnly = 0 != (m_flags & BGFX_TEXTURE_RT_WRITE_ONLY);
			//const bool computeWrite = 0 != (m_flags & BGFX_TEXTURE_COMPUTE_WRITE);
			const bool renderTarget = 0 != (m_flags & BGFX_TEXTURE_RT_MASK);
			const bool srgb = 0 != (m_flags & BGFX_TEXTURE_SRGB);
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
			nvnTextureBuilderSetDevice(&textureBuilder, _device);
			nvnTextureBuilderSetDefaults(&textureBuilder);

			NVNformat format = srgb ? s_textureFormat[m_textureFormat].m_fmtSrgb : s_textureFormat[m_textureFormat].m_fmt;

			if (bimg::isDepth(bimg::TextureFormat::Enum(m_textureFormat)))
			{
				BX_ASSERT(!srgb, "SRGB DepthBuffer ???");
				format = s_textureFormat[m_textureFormat].m_fmtDsv;
			}
			else if (renderTarget)
			{
				BX_ASSERT(!srgb, "Can't have a SRGB RenderTarget");
				nvnTextureBuilderSetFlags(&textureBuilder, NVN_TEXTURE_FLAGS_DISPLAY_BIT | NVN_TEXTURE_FLAGS_COMPRESSIBLE_BIT);
			}

			nvnTextureBuilderSetFormat(&textureBuilder, format);

			switch (m_type)
			{
			case Texture2D:
				nvnTextureBuilderSetSize2D(&textureBuilder, textureWidth, textureHeight);
				nvnTextureBuilderSetTarget(&textureBuilder, NVN_TEXTURE_TARGET_2D);
				break;
			case TextureCube:
				nvnTextureBuilderSetSize3D(&textureBuilder, textureWidth, textureHeight, 6); // BBI-NOTE: (tstump) hopefully this is correct
				nvnTextureBuilderSetTarget(&textureBuilder, NVN_TEXTURE_TARGET_CUBEMAP);
				return;
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

			create(_device, textureBuilder);

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
			};

			ImageInfo* imageInfo = (ImageInfo*)alloca(numLayers * numMips * sizeof(ImageInfo));
			int numImageInfo = 0;

			const uint32_t alignment = 1;

			uint32_t bufferSize = 0;

			for (uint16_t layer = 0; layer < numLayers; ++layer)
			{
				for (uint8_t lod = 0; lod < numMips; ++lod)
				{
					bimg::ImageMip mip;
					if (bimg::imageGetRawData(imageContainer, layer, lod + startLod, _mem->data, _mem->size, mip))
					{
						const uint32_t pitch = bx::strideAlign(mip.m_width * mip.m_bpp / 8, alignment);
						const uint32_t slice = bx::strideAlign(mip.m_height * pitch, alignment);
						const uint32_t size = slice * mip.m_depth;

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

						bufferSize += nn::util::align_up(size, NVN_MEMORY_POOL_STORAGE_GRANULARITY); // make sure each subcopy is aligned
					}
				}
			}

			if (numImageInfo != 0)
			{
				_copyOp.m_data = (CopyOperation::Data*)BX_ALLOC(g_allocator, sizeof(CopyOperation::Data));
				_copyOp.createBuffer(bufferSize, _copyOp.m_data);
				_copyOp.m_ops.reserve(numImageInfo);

				uint8_t* dst = (uint8_t*)nvnBufferMap(&_copyOp.m_data->m_buffer);

				for (int i = 0; i < numImageInfo; ++i)
				{
					const ImageInfo& info = imageInfo[i];

					bimg::imageCopy(dst + info.m_offset, info.m_height, info.m_pitch, 1, info.m_data, info.m_pitch);

					CopyOperation::Op op;
					op.m_dstData = &m_ptr;
					op.m_offset = info.m_offset;
					op.m_memSize = info.m_size;

					nvnTextureViewSetDefaults(&op.m_dstView);
					nvnTextureViewSetLayers(&op.m_dstView, info.m_layer, 1);
					nvnTextureViewSetLevels(&op.m_dstView, info.m_mip, 1);

					op.m_dstRegion.xoffset = 0;
					op.m_dstRegion.yoffset = 0;
					op.m_dstRegion.zoffset = 0;
					op.m_dstRegion.width = info.m_width;
					op.m_dstRegion.height = info.m_height;
					op.m_dstRegion.depth = 1;

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

			m_handle = -1;

			m_created = false;
		}
	}

	void TextureNVN::update(NVNcommandBuffer* _commandList, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem)
	{
#if 0
		bool isTextureArray = false;

		CopyOperation copyOp;
		copyOp.m_data = (CopyOperation::Data*)BX_ALLOC(g_allocator, sizeof(CopyOperation::Data));

		CopyOperation::Op op;
		op.m_dstData = &m_ptr;
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
		if (nvnWindowAcquireTexture(&m_Window, &m_WindowSync, &m_Current) != NVN_WINDOW_ACQUIRE_TEXTURE_RESULT_SUCCESS)
		{
			BX_ASSERT(false, "AcquireNext failed");
		}

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

	//
	//
	//

	uint32_t ShaderUniformBuffer::computeHash(const std::vector<UniformReference>& _uniforms)
	{
		uint32_t size = (uint32_t)(_uniforms.size() * sizeof(UniformReference));
		return bx::hash<bx::HashMurmur2A>((void*)_uniforms.data(), size);
	}

	void ShaderUniformBuffer::create(uint32_t _size, std::vector<UniformReference>&& _uniforms)
	{
		m_uniforms = std::move(_uniforms);
		m_size = _size;

		for (const UniformReference& data : m_uniforms)
		{
			BX_UNUSED(data);
		}

		m_data = (uint8_t*)BX_ALLOC(g_allocator, m_size);
		memset(m_data, 0, m_size);

		m_buffer = BX_NEW(g_allocator, BufferNVN);
		m_buffer->create(m_size, nullptr, 0, 0, BufferNVN::Usage::UniformBuffer);

		m_gpuAddress = nvnBufferGetAddress(&m_buffer->m_buffer);
	}

	void ShaderUniformBuffer::destroy()
	{
		m_uniforms.clear();
		m_size = 0;
		BX_FREE(g_allocator, m_data);
		BX_DELETE(g_allocator, m_buffer);
		m_data = nullptr;
		m_buffer = nullptr;
		m_gpuAddress = 0;
	}

	void ShaderUniformBuffer::update(NVNcommandBuffer* _cmdBuf)
	{
		bool dirty = false;

		// resolve uniform data
		// if uniforms dirty, copy into m_data and issue update
		for (const UniformReference& uniformRef : m_uniforms)
		{
			BX_ASSERT(uniformRef.m_data != nullptr, "Invalid uniform src data.");
			memcpy(m_data + uniformRef.m_index, uniformRef.m_data, uniformRef.m_count);
			dirty = true;
		}

		if (dirty)
		{
			nvnCommandBufferUpdateUniformBuffer(_cmdBuf, m_gpuAddress, m_size, 0, m_size, m_data);
		}
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

					ShaderUniformBuffer::UniformReference u;
					u.m_index = regIndex; // actually byte offset
					u.m_count = regCount * num; // actually size in bytes

					PredefinedUniform::Enum predefined = nameToPredefinedUniformEnum(name);
					if (PredefinedUniform::Count != predefined)
					{
						m_predefined[m_numPredefined].m_loc = regIndex;
						m_predefined[m_numPredefined].m_count = regCount;
						m_predefined[m_numPredefined].m_type = uint8_t(predefined | fragmentBit);
						m_numPredefined++;

						u.m_predefined = predefined;
					}
					else
					{
						const UniformRegInfo* info = _uniformRegistry.find(name);
						BX_ASSERT(info != nullptr, "Unknown uniform: %s", name);
						u.m_handle = info->m_handle;
					}

					uniforms->push_back(u);
				}
			}
		};

		// BBI-TODO: (tstump) rework all of this:
		//  step 1: read all uniforms
		//  step 2: read "global" uniforms (ie: samplers)
		//  step 3: read "user" uniform blocks

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

			uint32_t uniformSize;
			bx::read(&reader, uniformSize);

			BX_ASSERT(uniformBlockIdx < std::numeric_limits<uint8_t>::max(), "Too many uniform blocks");

			std::vector<ShaderUniformBuffer::UniformReference> uniformRefs;
			readUniformBlock(static_cast<uint8_t>(uniformBlockIdx), &uniformRefs);

			// compute hash from uniformRefs
			// get cbuffer index for hash from cbuffer repository
			// set cbuffer index in m_constantBuffers

			uint32_t cbHash = ShaderUniformBuffer::computeHash(uniformRefs);
			BX_UNUSED(cbHash);

			uint32_t index = _uniformBuffers.find(cbHash);
			if (index == UniformBufferRegistry::InvalidEntry)
			{
				// add
				ShaderUniformBuffer cb;
				cb.create(uniformSize, std::move(uniformRefs));
				index = _uniformBuffers.add(cbHash, std::move(cb));
			}

			m_constantBuffers.push_back(index);
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
			// BBI-TODO: (tstump) in bgfx, is a program with a NULL fragment shader considered a compute shader?
			BX_TRACE("NULL fragment shader, is this a compute shader?");
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
} }

#endif // BGFX_CONFIG_RENDERER_NVN

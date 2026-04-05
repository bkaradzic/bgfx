/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_p.h"

namespace bgfx
{
	struct DescriptorTypeToId
	{
		DescriptorType::Enum type;
		uint16_t id;
	};

	static DescriptorTypeToId s_descriptorTypeToId[] =
	{
		// NOTICE:
		// DescriptorType must be in order how it appears in DescriptorType::Enum! id is
		// unique and should not be changed if new DescriptorTypes are added.
		{ DescriptorType::StorageBuffer, 0x0007 },
		{ DescriptorType::StorageImage,  0x0003 },
	};
	static_assert(BX_COUNTOF(s_descriptorTypeToId) == DescriptorType::Count);

	DescriptorType::Enum idToDescriptorType(uint16_t _id)
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_descriptorTypeToId); ++ii)
		{
			if (s_descriptorTypeToId[ii].id == _id)
			{
				return s_descriptorTypeToId[ii].type;
			}
		}

		return DescriptorType::Count;
	}

	uint16_t descriptorTypeToId(DescriptorType::Enum _type)
	{
		return s_descriptorTypeToId[_type].id;
	}

	struct TextureComponentTypeToId
	{
		TextureComponentType::Enum type;
		uint8_t id;
	};

	static TextureComponentTypeToId s_textureComponentTypeToId[] =
	{
		// see comment in s_descriptorTypeToId
		{ TextureComponentType::Float,             0x00 },
		{ TextureComponentType::Int,               0x01 },
		{ TextureComponentType::Uint,              0x02 },
		{ TextureComponentType::Depth,             0x03 },
		{ TextureComponentType::UnfilterableFloat, 0x04 },
	};
	static_assert(BX_COUNTOF(s_textureComponentTypeToId) == TextureComponentType::Count);

	TextureComponentType::Enum idToTextureComponentType(uint8_t _id)
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_textureComponentTypeToId); ++ii)
		{
			if (s_textureComponentTypeToId[ii].id == _id)
			{
				return s_textureComponentTypeToId[ii].type;
			}
		}

		return TextureComponentType::Count;
	}

	uint8_t textureComponentTypeToId(TextureComponentType::Enum _type)
	{
		return s_textureComponentTypeToId[_type].id;
	}

	struct TextureDimensionToId
	{
		TextureDimension::Enum dimension;
		uint8_t id;
	};

	static TextureDimensionToId s_textureDimensionToId[] =
	{
		// see comment in s_descriptorTypeToId
		{ TextureDimension::Dimension1D,        0x01 },
		{ TextureDimension::Dimension2D,        0x02 },
		{ TextureDimension::Dimension2DArray,   0x03 },
		{ TextureDimension::DimensionCube,      0x04 },
		{ TextureDimension::DimensionCubeArray, 0x05 },
		{ TextureDimension::Dimension3D,        0x06 },
	};
	static_assert(BX_COUNTOF(s_textureDimensionToId) == TextureDimension::Count);

	TextureDimension::Enum idToTextureDimension(uint8_t _id)
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_textureDimensionToId); ++ii)
		{
			if (s_textureDimensionToId[ii].id == _id)
			{
				return s_textureDimensionToId[ii].dimension;
			}
		}

		return TextureDimension::Count;
	}

	uint8_t textureDimensionToId(TextureDimension::Enum _dim)
	{
		return s_textureDimensionToId[_dim].id;
	}

} // namespace bgfx

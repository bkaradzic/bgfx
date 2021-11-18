/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_SHADER_H
#define BGFX_SHADER_H

#include <bx/readerwriter.h>

namespace bgfx
{
	struct DescriptorType
	{
		enum Enum
		{
			StorageBuffer,
			StorageImage,

			Count
		};
	};

	DescriptorType::Enum idToDescriptorType(uint16_t _id);
	uint16_t descriptorTypeToId(DescriptorType::Enum _type);

	struct TextureComponentType
	{
		enum Enum
		{
			Float,
			Int,
			Uint,
			Depth,
			UnfilterableFloat,

			Count
		};
	};

	TextureComponentType::Enum idToTextureComponentType(uint8_t _id);
	uint8_t textureComponentTypeToId(TextureComponentType::Enum _type);

	struct TextureDimension
	{
		enum Enum
		{
			Dimension1D,
			Dimension2D,
			Dimension2DArray,
			DimensionCube,
			DimensionCubeArray,
			Dimension3D,

			Count
		};
	};

	TextureDimension::Enum idToTextureDimension(uint8_t _id);
	uint8_t textureDimensionToId(TextureDimension::Enum _dim);

	///
	void disassemble(bx::WriterI* _writer, bx::ReaderSeekerI* _reader, bx::Error* _err = NULL);

	///
	void disassemble(bx::WriterI* _writer, const void* _data, uint32_t _size, bx::Error* _err = NULL);

} // namespace bgfx

#endif // BGFX_SHADER_H

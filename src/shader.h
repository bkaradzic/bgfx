/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_SHADER_H
#define BGFX_SHADER_H

#include <bx/readerwriter.h>

namespace bgfx
{
	static constexpr uint8_t kSpirvVertexBinding   = 0;
	static constexpr uint8_t kSpirvFragmentBinding = 1;
	static constexpr uint8_t kSpirvBindShift       = 2;
	static constexpr uint8_t kSpirvSamplerShift    = 16;

	static constexpr uint8_t kSpirvOldVertexBinding    = 0;
	static constexpr uint8_t kSpirvOldFragmentBinding  = 48;
	static constexpr uint8_t kSpirvOldFragmentShift    = 48;
	static constexpr uint8_t kSpirvOldBufferShift      = 16;
	static constexpr uint8_t kSpirvOldImageShift       = 32;
	static constexpr uint8_t kSpirvOldTextureShift     = 16;

	BX_ERROR_RESULT(kShaderInvalidHeader,      BX_MAKEFOURCC('S', 'H', 0, 1) );
	BX_ERROR_RESULT(kShaderInvalidInstruction, BX_MAKEFOURCC('S', 'H', 0, 2) );

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
			Dimension2DMS,
			Dimension2DMSArray,

			Count
		};
	};

	TextureDimension::Enum idToTextureDimension(uint8_t _id);
	uint8_t textureDimensionToId(TextureDimension::Enum _dim);

	struct FragDataType
	{
		enum Enum
		{
			None,
			Float,
			Int,
			Uint,

			Count
		};
	};

	static constexpr uint32_t kFragDataValid   = UINT32_C(0x80000000);
	static constexpr uint32_t kFragDataMaxNum  = 8;
	static constexpr uint32_t kFragDataNumBits = 2;

	inline uint32_t encodeFragData(uint32_t _idx, FragDataType::Enum _type)
	{
		return uint32_t(_type) << (_idx*kFragDataNumBits);
	}

	inline FragDataType::Enum getFragDataType(uint32_t _fragData, uint32_t _idx)
	{
		return FragDataType::Enum( (_fragData >> (_idx*kFragDataNumBits) ) & ( (1<<kFragDataNumBits)-1) );
	}

	inline uint8_t getFragDataMask(uint32_t _fragData)
	{
		uint8_t mask = 0;

		for (uint32_t ii = 0; ii < kFragDataMaxNum; ++ii)
		{
			mask |= FragDataType::None != getFragDataType(_fragData, ii) ? uint8_t(1<<ii) : 0;
		}

		return mask;
	}

	///
	void disassemble(bx::WriterI* _writer, bx::ReaderSeekerI* _reader, bx::Error* _err = NULL);

	///
	void disassemble(bx::WriterI* _writer, const void* _data, uint32_t _size, bx::Error* _err = NULL);

} // namespace bgfx

#endif // BGFX_SHADER_H

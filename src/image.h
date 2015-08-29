/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_IMAGE_H_HEADER_GUARD
#define BGFX_IMAGE_H_HEADER_GUARD

#include <stdint.h>

namespace bgfx
{
	struct ImageContainer
	{
		void* m_data;
		uint32_t m_size;
		uint32_t m_offset;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_depth;
		uint8_t m_format;
		uint8_t m_numMips;
		bool m_hasAlpha;
		bool m_cubeMap;
		bool m_ktx;
		bool m_srgb;
	};

	struct ImageMip
	{
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_blockSize;
		uint32_t m_size;
		uint8_t m_bpp;
		uint8_t m_format;
		bool m_hasAlpha;
		const uint8_t* m_data;
	};

	struct EncodingType
	{
		enum Enum
		{
			Unorm,
			Int,
			Uint,
			Float,
			Snorm,

			Count
		};
	};

	struct ImageBlockInfo
	{
		uint8_t bitsPerPixel;
		uint8_t blockWidth;
		uint8_t blockHeight;
		uint8_t blockSize;
		uint8_t minBlockX;
		uint8_t minBlockY;
		uint8_t depthBits;
		uint8_t stencilBits;
		uint8_t encoding;
	};

	///
	bool isCompressed(TextureFormat::Enum _format);

	///
	bool isColor(TextureFormat::Enum _format);

	///
	bool isDepth(TextureFormat::Enum _format);

	///
	uint8_t getBitsPerPixel(TextureFormat::Enum _format);

	///
	const ImageBlockInfo& getBlockInfo(TextureFormat::Enum _format);

	///
	const char* getName(TextureFormat::Enum _format);

	///
	void imageSolid(uint32_t _width, uint32_t _height, uint32_t _solid, void* _dst);

	///
	void imageCheckerboard(uint32_t _width, uint32_t _height, uint32_t _step, uint32_t _0, uint32_t _1, void* _dst);

	///
	void imageRgba8Downsample2x2(uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, void* _dst);

	///
	void imageSwizzleBgra8(uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, void* _dst);

	///
	void imageCopy(uint32_t _height, uint32_t _srcPitch, const void* _src, uint32_t _dstPitch, void* _dst);

	///
	void imageCopy(uint32_t _width, uint32_t _height, uint32_t _bpp, uint32_t _srcPitch, const void* _src, void* _dst);

	///
	void imageWriteTga(bx::WriterI* _writer, uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, bool _grayscale, bool _yflip);

	///
	bool imageParse(ImageContainer& _imageContainer, bx::ReaderSeekerI* _reader);

	///
	bool imageParse(ImageContainer& _imageContainer, const void* _data, uint32_t _size);

	///
	void imageDecodeToBgra8(uint8_t* _dst, const uint8_t* _src, uint32_t _width, uint32_t _height, uint32_t _pitch, uint8_t _type);

	///
	void imageDecodeToRgba8(uint8_t* _dst, const uint8_t* _src, uint32_t _width, uint32_t _height, uint32_t _pitch, uint8_t _type);

	///
	bool imageGetRawData(const ImageContainer& _dds, uint8_t _side, uint8_t _index, const void* _data, uint32_t _size, ImageMip& _mip);

} // namespace bgfx

#endif // BGFX_IMAGE_H_HEADER_GUARD

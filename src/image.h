/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
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
		uint8_t m_blockSize;
		uint8_t m_numMips;
		uint8_t m_bpp;
		bool m_hasAlpha;
		bool m_cubeMap;
		bool m_ktx;
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

	///
	bool isCompressed(TextureFormat::Enum _format);

	///
	bool isColor(TextureFormat::Enum _format);

	///
	bool isDepth(TextureFormat::Enum _format);

	///
	uint32_t getBitsPerPixel(TextureFormat::Enum _format);

	///
	void imageSolid(uint32_t _width, uint32_t _height, uint32_t _solid, void* _dst);

	///
	void imageCheckerboard(uint32_t _width, uint32_t _height, uint32_t _step, uint32_t _0, uint32_t _1, void* _dst);

	///
	void imageRgba8Downsample2x2(uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, void* _dst);

	///
	void imageSwizzleBgra8(uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, void* _dst);

	///
	void imageCopy(uint32_t _width, uint32_t _height, uint32_t _bpp, uint32_t _srcPitch, const void* _src, void* _dst);

	///
	void imageWriteTga(bx::WriterI* _writer, uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, bool _grayscale, bool _yflip);

	///
	bool imageParse(ImageContainer& _imageContainer, bx::ReaderSeekerI* _reader);

	///
	bool imageParse(ImageContainer& _imageContainer, const void* _data, uint32_t _size);

	///
	void imageDecodeToBgra8(uint8_t* _dst, const uint8_t* _src, uint32_t _width, uint32_t _height, uint32_t _srcPitch, uint8_t _type);

	///
	bool imageGetRawData(const ImageContainer& _dds, uint8_t _side, uint8_t _index, const void* _data, uint32_t _size, ImageMip& _mip);

} // namespace bgfx

#endif // BGFX_IMAGE_H_HEADER_GUARD

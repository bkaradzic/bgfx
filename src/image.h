/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <stdint.h>

namespace bgfx
{
	struct ImageContainer
	{
		TextureFormat::Enum m_type;
		uint32_t m_offset;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_depth;
		uint8_t m_blockSize;
		uint8_t m_numMips;
		uint8_t m_bpp;
		bool m_hasAlpha;
		bool m_cubeMap;
		bool m_ktx;
	};

	struct Mip
	{
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_blockSize;
		uint32_t m_size;
		uint8_t m_bpp;
		uint8_t m_type;
		bool m_hasAlpha;
		const uint8_t* m_data;

		void decode(uint8_t* _dst);
	};

	///
	uint32_t getBitsPerPixel(TextureFormat::Enum _format);

	///
	void imageSolid(uint32_t _width, uint32_t _height, uint32_t _solid, void* _dst);

	///
	void imageCheckerboard(uint32_t _width, uint32_t _height, uint32_t _step, uint32_t _0, uint32_t _1, void* _dst);

	///
	void imageRgba8Downsample2x2(uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src, void* _dst);

	///
	void imageSwizzleBgra8(uint32_t _width, uint32_t _height, const void* _src, void* _dst);

	///
	void imageWriteTga(bx::WriterI* _writer, uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, bool _grayscale, bool _yflip);

	///
	bool imageParse(ImageContainer& _imageContainer, bx::ReaderSeekerI* _reader);

	///
	bool imageParse(ImageContainer& _dds, const void* _data, uint32_t _size);

	///
	bool imageGetRawData(const ImageContainer& _dds, uint8_t _side, uint8_t _index, const void* _data, uint32_t _size, Mip& _mip);

} // namespace bgfx

#endif // __IMAGE_H__

/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_IMAGE_H_HEADER_GUARD
#define BGFX_IMAGE_H_HEADER_GUARD

#include <stdint.h>

namespace bgfx
{
	struct ImageContainer
	{
		void*    m_data;
		TextureFormat::Enum m_format;
		uint32_t m_size;
		uint32_t m_offset;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_depth;
		uint8_t  m_numMips;
		bool     m_hasAlpha;
		bool     m_cubeMap;
		bool     m_ktx;
		bool     m_ktxLE;
		bool     m_srgb;
	};

	struct ImageMip
	{
		TextureFormat::Enum m_format;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_blockSize;
		uint32_t m_size;
		uint8_t  m_bpp;
		bool     m_hasAlpha;
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

	/// Returns true if texture format is compressed.
	bool isCompressed(TextureFormat::Enum _format);

	/// Returns true if texture format is uncompressed.
	bool isColor(TextureFormat::Enum _format);

	/// Returns true if texture format is depth.
	bool isDepth(TextureFormat::Enum _format);

	/// Returns true if texture format is valid.
	bool isValid(TextureFormat::Enum _format);

	/// Returns bits per pixel.
	uint8_t getBitsPerPixel(TextureFormat::Enum _format);

	/// Returns texture block info.
	const ImageBlockInfo& getBlockInfo(TextureFormat::Enum _format);

	/// Converts format to string.
	const char* getName(TextureFormat::Enum _format);

	/// Converts string to format.
	TextureFormat::Enum getFormat(const char* _name);

	/// Returns number of mip-maps required for complete mip-map chain.
	uint8_t imageGetNumMips(TextureFormat::Enum _format, uint16_t _width, uint16_t _height, uint16_t _depth = 0);

	/// Returns image size.
	uint32_t imageGetSize(TextureFormat::Enum _format, uint16_t _width, uint16_t _height, uint16_t _depth = 0, bool _cubeMap = false, uint8_t _numMips = 0);

	///
	void imageSolid(uint32_t _width, uint32_t _height, uint32_t _solid, void* _dst);

	///
	void imageCheckerboard(uint32_t _width, uint32_t _height, uint32_t _step, uint32_t _0, uint32_t _1, void* _dst);

	///
	void imageRgba8Downsample2x2(uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src, void* _dst);

	///
	void imageRgba32fDownsample2x2NormalMap(uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src, void* _dst);

	///
	void imageSwizzleBgra8(uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src, void* _dst);

	///
	void imageCopy(uint32_t _height, uint32_t _srcPitch, const void* _src, uint32_t _dstPitch, void* _dst);

	///
	void imageCopy(uint32_t _width, uint32_t _height, uint32_t _bpp, uint32_t _pitch, const void* _src, void* _dst);

	///
	bool imageConvert(void* _dst, TextureFormat::Enum _dstFormat, const void* _src, TextureFormat::Enum _srcFormat, uint32_t _width, uint32_t _height);

	///
	const Memory* imageAlloc(ImageContainer& _imageContainer, TextureFormat::Enum _format, uint16_t _width, uint16_t _height, uint16_t _depth = 0, bool _cubeMap = false, bool _mips = false);

	///
	void imageFree(const Memory* _memory);

	///
	void imageWriteTga(bx::WriterI* _writer, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src, bool _grayscale, bool _yflip);

	///
	void imageWriteKtx(bx::WriterI* _writer, TextureFormat::Enum _format, bool _cubeMap, uint32_t _width, uint32_t _height, uint32_t _depth, uint8_t _numMips, const void* _src);

	///
	void imageWriteKtx(bx::WriterI* _writer, ImageContainer& _imageContainer, const void* _data, uint32_t _size);

	///
	bool imageParse(ImageContainer& _imageContainer, bx::ReaderSeekerI* _reader);

	///
	bool imageParse(ImageContainer& _imageContainer, const void* _data, uint32_t _size);

	///
	void imageDecodeToBgra8(void* _dst, const void* _src, uint32_t _width, uint32_t _height, uint32_t _pitch, TextureFormat::Enum _format);

	///
	void imageDecodeToRgba8(void* _dst, const void* _src, uint32_t _width, uint32_t _height, uint32_t _pitch, TextureFormat::Enum _format);

	///
	void imageDecodeToRgba32f(bx::AllocatorI* _allocator, void* _dst, const void* _src, uint32_t _width, uint32_t _height, uint32_t _pitch, TextureFormat::Enum _format);

	///
	bool imageGetRawData(const ImageContainer& _imageContainer, uint8_t _side, uint8_t _index, const void* _data, uint32_t _size, ImageMip& _mip);

} // namespace bgfx

#endif // BGFX_IMAGE_H_HEADER_GUARD

/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_IMAGE_H_HEADER_GUARD
#define BGFX_IMAGE_H_HEADER_GUARD

#include <bx/pixelformat.h>

namespace bgfx
{
	struct ImageContainer
	{
		bx::AllocatorI* m_allocator;
		void*           m_data;

		TextureFormat::Enum m_format;

		uint32_t m_size;
		uint32_t m_offset;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_depth;
		uint16_t m_numLayers;
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
		uint8_t rBits;
		uint8_t gBits;
		uint8_t bBits;
		uint8_t aBits;
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
	uint8_t imageGetNumMips(
		  TextureFormat::Enum _format
		, uint16_t _width
		, uint16_t _height
		, uint16_t _depth = 0
		);

	/// Returns image size.
	uint32_t imageGetSize(
		  TextureInfo* _info
		, uint16_t _width
		, uint16_t _height
		, uint16_t _depth
		, bool _cubeMap
		, bool _hasMips
		, uint16_t _numLayers
		, TextureFormat::Enum _format
		);

	///
	void imageSolid(void* _dst, uint32_t _width, uint32_t _height, uint32_t _solid);

	///
	void imageCheckerboard(void* _dst, uint32_t _width, uint32_t _height, uint32_t _step, uint32_t _0, uint32_t _1);

	///
	void imageRgba8Downsample2x2(void* _dst, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src);

	///
	void imageRgba32fToLinear(void* _dst, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src);

	///
	void imageRgba32fToGamma(void* _dst, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src);

	///
	void imageRgba32fLinearDownsample2x2(void* _dst, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src);

	///
	void imageRgba32fDownsample2x2NormalMap(void* _dst, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src);

	///
	void imageSwizzleBgra8(void* _dst, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src);

	///
	void imageCopy(void* _dst, uint32_t _height, uint32_t _srcPitch, const void* _src, uint32_t _dstPitch);

	///
	void imageCopy(void* _dst, uint32_t _width, uint32_t _height, uint32_t _bpp, uint32_t _pitch, const void* _src);

	///
	bool imageConvert(TextureFormat::Enum _dstFormat, TextureFormat::Enum _srcFormat);

	///
	void imageConvert(
		  void* _dst
		, uint32_t _bpp
		, bx::PackFn _pack
		, const void* _src
		, bx::UnpackFn _unpack
		, uint32_t _size
		);

	///
	void imageConvert(
		  void* _dst
		, uint32_t _dstBpp
		, bx::PackFn _pack
		, const void* _src
		, uint32_t _srcBpp
		, bx::UnpackFn _unpack
		, uint32_t _width
		, uint32_t _height
		, uint32_t _srcPitch
		);

	///
	bool imageConvert(
		  void* _dst
		, TextureFormat::Enum _dstFormat
		, const void* _src
		, TextureFormat::Enum _srcFormat
		, uint32_t _width
		, uint32_t _height
		);

	///
	ImageContainer* imageConvert(
		  bx::AllocatorI* _allocator
		, TextureFormat::Enum _dstFormat
		, const void* _src
		, uint32_t _size
		);

	///
	ImageContainer* imageAlloc(
		  bx::AllocatorI* _allocator
		, TextureFormat::Enum _format
		, uint16_t _width
		, uint16_t _height
		, uint16_t _depth
		, uint16_t _numLayers
		, bool _cubeMap
		, bool _hasMips
		, const void* _data = NULL
		);

	///
	void imageFree(ImageContainer* _imageContainer);

	///
	void imageWriteTga(
		  bx::WriterI* _writer
		, uint32_t _width
		, uint32_t _height
		, uint32_t _pitch
		, const void* _src
		, bool _grayscale
		, bool _yflip
		, bx::Error* _err = NULL
		);

	///
	void imageWriteKtx(
		  bx::WriterI* _writer
		, TextureFormat::Enum _format
		, bool _cubeMap
		, uint32_t _width
		, uint32_t _height
		, uint32_t _depth
		, uint8_t _numMips
		, const void* _src
		, bx::Error* _err = NULL
		);

	///
	void imageWriteKtx(
		  bx::WriterI* _writer
		, ImageContainer& _imageContainer
		, const void* _data
		, uint32_t _size
		, bx::Error* _err = NULL
		);

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
	bool imageGetRawData(const ImageContainer& _imageContainer, uint16_t _side, uint8_t _lod, const void* _data, uint32_t _size, ImageMip& _mip);

} // namespace bgfx

#endif // BGFX_IMAGE_H_HEADER_GUARD

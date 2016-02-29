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

	typedef void (*PackFn)(void*, const float*);
	typedef void (*UnpackFn)(float*, const void*);

	// R8
	void packR8(void* _dst, const float* _src);
	void unpackR8(float* _dst, const void* _src);

	// R8S
	void packR8S(void* _dst, const float* _src);
	void unpackR8S(float* _dst, const void* _src);

	// R8I
	void packR8I(void* _dst, const float* _src);
	void unpackR8I(float* _dst, const void* _src);

	// R8U
	void packR8U(void* _dst, const float* _src);
	void unpackR8U(float* _dst, const void* _src);

	// RG8
	void packRg8(void* _dst, const float* _src);
	void unpackRg8(float* _dst, const void* _src);

	// RG8S
	void packRg8S(void* _dst, const float* _src);
	void unpackRg8S(float* _dst, const void* _src);

	// RG8I
	void packRg8I(void* _dst, const float* _src);
	void unpackRg8I(float* _dst, const void* _src);

	// RG8U
	void packRg8U(void* _dst, const float* _src);
	void unpackRg8U(float* _dst, const void* _src);

	// RGB8
	void packRgb8(void* _dst, const float* _src);
	void unpackRgb8(float* _dst, const void* _src);

	// RGB8S
	void packRgb8S(void* _dst, const float* _src);
	void unpackRgb8S(float* _dst, const void* _src);

	// RGB8I
	void packRgb8I(void* _dst, const float* _src);
	void unpackRgb8I(float* _dst, const void* _src);

	// RGB8U
	void packRgb8U(void* _dst, const float* _src);
	void unpackRgb8U(float* _dst, const void* _src);

	// RGBA8
	void packRgba8(void* _dst, const float* _src);
	void unpackRgba8(float* _dst, const void* _src);

	// BGRA8
	void packBgra8(void* _dst, const float* _src);
	void unpackBgra8(float* _dst, const void* _src);

	// RGBA8S
	void packRgba8S(void* _dst, const float* _src);
	void unpackRgba8S(float* _dst, const void* _src);

	// RGBA8I
	void packRgba8I(void* _dst, const float* _src);
	void unpackRgba8I(float* _dst, const void* _src);

	// RGBA8U
	void packRgba8U(void* _dst, const float* _src);
	void unpackRgba8U(float* _dst, const void* _src);

	// R16
	void packR16(void* _dst, const float* _src);
	void unpackR16(float* _dst, const void* _src);

	// R16S
	void packR16S(void* _dst, const float* _src);
	void unpackR16S(float* _dst, const void* _src);

	// R16I
	void packR16I(void* _dst, const float* _src);
	void unpackR16I(float* _dst, const void* _src);

	// R16U
	void packR16U(void* _dst, const float* _src);
	void unpackR16U(float* _dst, const void* _src);

	// R16F
	void packR16F(void* _dst, const float* _src);
	void unpackR16F(float* _dst, const void* _src);

	// RG16
	void packRg16(void* _dst, const float* _src);
	void unpackRg16(float* _dst, const void* _src);

	// RG16S
	void packRg16S(void* _dst, const float* _src);
	void unpackRg16S(float* _dst, const void* _src);

	// RG16I
	void packRg16I(void* _dst, const float* _src);
	void unpackRg16I(float* _dst, const void* _src);

	// RG16U
	void packRg16U(void* _dst, const float* _src);
	void unpackRg16U(float* _dst, const void* _src);

	// RG16F
	void packRg16F(void* _dst, const float* _src);
	void unpackRg16F(float* _dst, const void* _src);

	// RGBA16
	void packRgba16(void* _dst, const float* _src);
	void unpackRgba16(float* _dst, const void* _src);

	// RGBA16S
	void packRgba16S(void* _dst, const float* _src);
	void unpackRgba16S(float* _dst, const void* _src);

	// RGBA16I
	void packRgba16I(void* _dst, const float* _src);
	void unpackRgba16I(float* _dst, const void* _src);

	// RGBA16U
	void packRgba16U(void* _dst, const float* _src);
	void unpackRgba16U(float* _dst, const void* _src);

	// RGBA16F
	void packRgba16F(void* _dst, const float* _src);
	void unpackRgba16F(float* _dst, const void* _src);

	// R32I
	void packR32I(void* _dst, const float* _src);
	void unpackR32I(float* _dst, const void* _src);

	// R32U
	void packR32U(void* _dst, const float* _src);
	void unpackR32U(float* _dst, const void* _src);

	// R32F
	void packR32F(void* _dst, const float* _src);
	void unpackR32F(float* _dst, const void* _src);

	// RG32I
	void packRg32I(void* _dst, const float* _src);
	void unpackRg32I(float* _dst, const void* _src);

	// RG32U
	void packRg32U(void* _dst, const float* _src);
	void unpackRg32U(float* _dst, const void* _src);

	// RGB9E5F
	void packRgb9E5F(void* _dst, const float* _src);
	void unpackRgb9E5F(float* _dst, const void* _src);

	// RGBA32I
	void packRgba32I(void* _dst, const float* _src);
	void unpackRgba32I(float* _dst, const void* _src);

	// RGBA32U
	void packRgba32U(void* _dst, const float* _src);
	void unpackRgba32U(float* _dst, const void* _src);

	// RGBA32F
	void packRgba32F(void* _dst, const float* _src);
	void unpackRgba32F(float* _dst, const void* _src);

	// R5G6B5
	void packR5G6B5(void* _dst, const float* _src);
	void unpackR5G6B5(float* _dst, const void* _src);

	// RGBA4
	void packRgba4(void* _dst, const float* _src);
	void unpackRgba4(float* _dst, const void* _src);

	// RGBA4
	void packBgra4(void* _dst, const float* _src);
	void unpackBgra4(float* _dst, const void* _src);

	// RGB5A1
	void packRgb5a1(void* _dst, const float* _src);
	void unpackRgb5a1(float* _dst, const void* _src);

	// BGR5A1
	void packBgr5a1(void* _dst, const float* _src);
	void unpackBgr5a1(float* _dst, const void* _src);

	// RGB10A2
	void packRgb10A2(void* _dst, const float* _src);
	void unpackRgb10A2(float* _dst, const void* _src);

	// R11G11B10F
	void packR11G11B10F(void* _dst, const float* _src);
	void unpackR11G11B10F(float* _dst, const void* _src);

	// RG32F
	void packRg32F(void* _dst, const float* _src);
	void unpackRg32F(float* _dst, const void* _src);

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
	bool imageConvert(TextureFormat::Enum _dstFormat, TextureFormat::Enum _srcFormat);

	///
	void imageConvert(void* _dst, uint32_t _bpp, PackFn _pack, const void* _src, UnpackFn _unpack, uint32_t _size);

	///
	void imageConvert(void* _dst, uint32_t _dstBpp, PackFn _pack, const void* _src, uint32_t _srcBpp, UnpackFn _unpack, uint32_t _width, uint32_t _height, uint32_t _srcPitch);

	///
	bool imageConvert(void* _dst, TextureFormat::Enum _dstFormat, const void* _src, TextureFormat::Enum _srcFormat, uint32_t _width, uint32_t _height);

	///
	const Memory* imageAlloc(ImageContainer& _imageContainer, TextureFormat::Enum _format, uint16_t _width, uint16_t _height, uint16_t _depth = 0, bool _cubeMap = false, bool _generateMips = false);

	///
	void imageFree(const Memory* _memory);

	///
	void imageWriteTga(bx::WriterI* _writer, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src, bool _grayscale, bool _yflip, bx::Error* _err = NULL);

	///
	void imageWriteKtx(bx::WriterI* _writer, TextureFormat::Enum _format, bool _cubeMap, uint32_t _width, uint32_t _height, uint32_t _depth, uint8_t _numMips, const void* _src, bx::Error* _err = NULL);

	///
	void imageWriteKtx(bx::WriterI* _writer, ImageContainer& _imageContainer, const void* _data, uint32_t _size, bx::Error* _err = NULL);

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

/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "entry/dbg.h"

#include <bgfx/bgfx.h>
#include <bx/allocator.h>
#include <bx/endian.h>
#include <bx/readerwriter.h>
#include "bgfx_utils.h"

BX_PRAGMA_DIAGNOSTIC_PUSH()
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wtype-limits")
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wunused-parameter")
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wunused-value")
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4100) // error C4100: '' : unreferenced formal parameter
#if BX_PLATFORM_EMSCRIPTEN
#	include <compat/ctype.h>
#endif // BX_PLATFORM_EMSCRIPTEN
#define MINIZ_NO_STDIO
#define TINYEXR_IMPLEMENTATION
#include <tinyexr/tinyexr.h>
BX_PRAGMA_DIAGNOSTIC_POP()

#define LODEPNG_NO_COMPILE_ENCODER
#define LODEPNG_NO_COMPILE_DISK
#define LODEPNG_NO_COMPILE_ANCILLARY_CHUNKS
#define LODEPNG_NO_COMPILE_ERROR_TEXT
#define LODEPNG_NO_COMPILE_ALLOCATORS
#define LODEPNG_NO_COMPILE_CPP
#include <lodepng/lodepng.h>

typedef unsigned char stbi_uc;
extern "C" int stbi_is_hdr_from_memory(stbi_uc const* _buffer, int _len);
extern "C" stbi_uc* stbi_load_from_memory(stbi_uc const* _buffer, int _len, int* _x, int* _y, int* _comp, int _req_comp);
extern "C" float* stbi_loadf_from_memory(stbi_uc const* _buffer, int _len, int* _x, int* _y, int* _comp, int _req_comp);
extern "C" void stbi_image_free(void* _ptr);
extern void lodepng_free(void* _ptr);

namespace bgfx
{
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
	ImageContainer* imageParseBgfx(bx::AllocatorI* _allocator, const void* _src, uint32_t _size);

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
		, const ImageContainer& _input
		);

} // namespace bgfx

namespace bgfx
{
	static ImageContainer* imageParseLodePng(bx::AllocatorI* _allocator, const void* _data, uint32_t _size)
	{
		static uint8_t pngMagic[] = { 0x89, 0x50, 0x4E, 0x47, 0x0d, 0x0a };

		if (0 != bx::memCmp(_data, pngMagic, sizeof(pngMagic) ) )
		{
			return NULL;
		}

		bgfx::TextureFormat::Enum format = bgfx::TextureFormat::RGBA8;
		uint32_t width  = 0;
		uint32_t height = 0;

		unsigned error;
		LodePNGState state;
		lodepng_state_init(&state);
		state.decoder.color_convert = 0;

		uint8_t* data = NULL;
		error = lodepng_decode(&data, &width, &height, &state, (uint8_t*)_data, _size);

		if (0 == error)
		{
			switch (state.info_raw.bitdepth)
			{
				case 8:
					switch (state.info_raw.colortype)
					{
						case LCT_GREY:
							format = bgfx::TextureFormat::R8;
							break;

						case LCT_GREY_ALPHA:
							format = bgfx::TextureFormat::RG8;
							break;

						case LCT_RGB:
							format = bgfx::TextureFormat::RGB8;
							break;

						case LCT_RGBA:
							format = bgfx::TextureFormat::RGBA8;
							break;

						case LCT_PALETTE:
							break;
					}
					break;

				case 16:
					switch (state.info_raw.colortype)
					{
						case LCT_GREY:
							for (uint32_t ii = 0, num = width*height; ii < num; ++ii)
							{
								uint16_t* rgba = (uint16_t*)data + ii;
								rgba[0] = bx::toHostEndian(rgba[0], false);
							}
							format = bgfx::TextureFormat::R16;
							break;

						case LCT_GREY_ALPHA:
							for (uint32_t ii = 0, num = width*height; ii < num; ++ii)
							{
								uint16_t* rgba = (uint16_t*)data + ii*2;
								rgba[0] = bx::toHostEndian(rgba[0], false);
								rgba[1] = bx::toHostEndian(rgba[1], false);
							}
							format = bgfx::TextureFormat::RG16;
							break;

						case LCT_RGBA:
							for (uint32_t ii = 0, num = width*height; ii < num; ++ii)
							{
								uint16_t* rgba = (uint16_t*)data + ii*4;
								rgba[0] = bx::toHostEndian(rgba[0], false);
								rgba[1] = bx::toHostEndian(rgba[1], false);
								rgba[2] = bx::toHostEndian(rgba[2], false);
								rgba[3] = bx::toHostEndian(rgba[3], false);
							}
							format = bgfx::TextureFormat::RGBA16;
							break;

						case LCT_RGB:
						case LCT_PALETTE:
							break;
					}
					break;

				default:
					break;
			}
		}

		lodepng_state_cleanup(&state);

		ImageContainer* output = imageAlloc(_allocator
			, format
			, uint16_t(width)
			, uint16_t(height)
			, 0
			, 1
			, false
			, false
			, data
			);
		lodepng_free(data);

		return output;
	}

	static ImageContainer* imageParseTinyExr(bx::AllocatorI* _allocator, const void* _data, uint32_t _size)
	{
		EXRVersion exrVersion;
		int result = ParseEXRVersionFromMemory(&exrVersion, (uint8_t*)_data, _size);
		if (TINYEXR_SUCCESS != result)
		{
			return NULL;
		}

		bgfx::TextureFormat::Enum format = bgfx::TextureFormat::RGBA8;
		uint32_t width  = 0;
		uint32_t height = 0;

		uint8_t* data = NULL;
		const char* err = NULL;
		EXRHeader exrHeader;
		result = ParseEXRHeaderFromMemory(&exrHeader, &exrVersion, (uint8_t*)_data, _size, &err);
		if (TINYEXR_SUCCESS == result)
		{
			EXRImage exrImage;
			InitEXRImage(&exrImage);

			result = LoadEXRImageFromMemory(&exrImage, &exrHeader, (uint8_t*)_data, _size, &err);
			if (TINYEXR_SUCCESS == result)
			{
				uint8_t idxR = UINT8_MAX;
				uint8_t idxG = UINT8_MAX;
				uint8_t idxB = UINT8_MAX;
				uint8_t idxA = UINT8_MAX;
				for (uint8_t ii = 0, num = uint8_t(exrHeader.num_channels); ii < num; ++ii)
				{
					const EXRChannelInfo& channel = exrHeader.channels[ii];
					if (UINT8_MAX == idxR
					&&  0 == bx::strncmp(channel.name, "R") )
					{
						idxR = ii;
					}
					else if (UINT8_MAX == idxG
					&&  0 == bx::strncmp(channel.name, "G") )
					{
						idxG = ii;
					}
					else if (UINT8_MAX == idxB
					&&  0 == bx::strncmp(channel.name, "B") )
					{
						idxB = ii;
					}
					else if (UINT8_MAX == idxA
					&&  0 == bx::strncmp(channel.name, "A") )
					{
						idxA = ii;
					}
				}

				if (UINT8_MAX != idxR)
				{
					const bool asFloat = exrHeader.pixel_types[idxR] == TINYEXR_PIXELTYPE_FLOAT;
					uint32_t srcBpp = 32;
					uint32_t dstBpp = asFloat ? 32 : 16;
					format = asFloat ? TextureFormat::R32F : TextureFormat::R16F;
					uint32_t stepR = 1;
					uint32_t stepG = 0;
					uint32_t stepB = 0;
					uint32_t stepA = 0;

					if (UINT8_MAX != idxG)
					{
						srcBpp += 32;
						dstBpp = asFloat ? 64 : 32;
						format = asFloat ? TextureFormat::RG32F : TextureFormat::RG16F;
						stepG  = 1;
					}

					if (UINT8_MAX != idxB)
					{
						srcBpp += 32;
						dstBpp = asFloat ? 128 : 64;
						format = asFloat ? TextureFormat::RGBA32F : TextureFormat::RGBA16F;
						stepB  = 1;
					}

					if (UINT8_MAX != idxA)
					{
						srcBpp += 32;
						dstBpp = asFloat ? 128 : 64;
						format = asFloat ? TextureFormat::RGBA32F : TextureFormat::RGBA16F;
						stepA  = 1;
					}

					data = (uint8_t*)BX_ALLOC(_allocator, exrImage.width * exrImage.height * dstBpp/8);

					const float  zero = 0.0f;
					const float* srcR = UINT8_MAX == idxR ? &zero : (const float*)(exrImage.images)[idxR];
					const float* srcG = UINT8_MAX == idxG ? &zero : (const float*)(exrImage.images)[idxG];
					const float* srcB = UINT8_MAX == idxB ? &zero : (const float*)(exrImage.images)[idxB];
					const float* srcA = UINT8_MAX == idxA ? &zero : (const float*)(exrImage.images)[idxA];

					const uint32_t bytesPerPixel = dstBpp/8;
					for (uint32_t ii = 0, num = exrImage.width * exrImage.height; ii < num; ++ii)
					{
						float rgba[4] =
						{
							*srcR,
							*srcG,
							*srcB,
							*srcA,
						};
						bx::memCopy(&data[ii * bytesPerPixel], rgba, bytesPerPixel);

						srcR += stepR;
						srcG += stepG;
						srcB += stepB;
						srcA += stepA;
					}
				}

				FreeEXRImage(&exrImage);
			}

			FreeEXRHeader(&exrHeader);
		}

		ImageContainer* output = imageAlloc(_allocator
			, format
			, uint16_t(width)
			, uint16_t(height)
			, 0
			, 1
			, false
			, false
			, data
			);
		BX_FREE(_allocator, data);

		return output;
	}

	static ImageContainer* imageParseStbImage(bx::AllocatorI* _allocator, const void* _data, uint32_t _size)
	{
		const int isHdr = stbi_is_hdr_from_memory((const uint8_t*)_data, (int)_size);

		void* data;
		uint32_t width  = 0;
		uint32_t height = 0;
		int comp = 0;
		if (isHdr) { data = stbi_loadf_from_memory((const uint8_t*)_data, (int)_size, (int*)&width, (int*)&height, &comp, 4); }
		else       { data = stbi_load_from_memory ((const uint8_t*)_data, (int)_size, (int*)&width, (int*)&height, &comp, 0); }

		if (NULL == data)
		{
			return NULL;
		}

		bgfx::TextureFormat::Enum format;
		if (isHdr)
		{
			format = bgfx::TextureFormat::RGBA32F;
		}
		else
		{
			if       (1 == comp)   { format = bgfx::TextureFormat::R8;    }
			else  if (2 == comp)   { format = bgfx::TextureFormat::RG8;   }
			else  if (3 == comp)   { format = bgfx::TextureFormat::RGB8;  }
			else/*if (4 == comp)*/ { format = bgfx::TextureFormat::RGBA8; }
		}

		ImageContainer* output = imageAlloc(_allocator
			, format
			, uint16_t(width)
			, uint16_t(height)
			, 0
			, 1
			, false
			, false
			, data
			);
		stbi_image_free(data);

		return output;
	}

	ImageContainer* imageParse(bx::AllocatorI* _allocator, const void* _data, uint32_t _size, TextureFormat::Enum _dstFormat)
	{
		ImageContainer* input = imageParseBgfx    (_allocator, _data, _size)        ;
		input = NULL == input ? imageParseLodePng (_allocator, _data, _size) : input;
		input = NULL == input ? imageParseTinyExr (_allocator, _data, _size) : input;
		input = NULL == input ? imageParseStbImage(_allocator, _data, _size) : input;

		if (NULL == input)
		{
			return NULL;
		}

		_dstFormat = TextureFormat::Count == _dstFormat
			? input->m_format
			: _dstFormat
			;

		if (_dstFormat == input->m_format)
		{
			return input;
		}

		ImageContainer* output = imageConvert(_allocator, _dstFormat, *input);
		imageFree(input);

		return output;
	}

} // namespace bgfx

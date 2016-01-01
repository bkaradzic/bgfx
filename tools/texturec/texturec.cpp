/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Just hacking DDS loading code in here.
#include "bgfx_p.h"

#include "image.h"
#include <libsquish/squish.h>
#include <etc1/etc1.h>
#include <nvtt/nvtt.h>
#include <pvrtc/PvrTcEncoder.h>
#include <tinyexr/tinyexr.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.c>

#if 0
#	define BX_TRACE(_format, ...) fprintf(stderr, "" _format "\n", ##__VA_ARGS__)
#endif // DEBUG

#include <bx/bx.h>
#include <bx/allocator.h>
#include <bx/commandline.h>
#include <bx/uint32_t.h>

namespace bgfx
{
	const Memory* alloc(uint32_t _size)
	{
		Memory* mem = (Memory*)::realloc(NULL, sizeof(Memory) + _size);
		mem->size = _size;
		mem->data = (uint8_t*)mem + sizeof(Memory);
		return mem;
	}

	const Memory* makeRef(const void* _data, uint32_t _size, ReleaseFn _releaseFn, void* _userData)
	{
		BX_UNUSED(_releaseFn, _userData);
		Memory* mem = (Memory*)::realloc(NULL, sizeof(Memory) );
		mem->size = _size;
		mem->data = (uint8_t*)_data;
		return mem;
	}

	void release(const Memory* _mem)
	{
		Memory* mem = const_cast<Memory*>(_mem);
		::free(mem);
	}

	void imageEncodeFromRgba8(uint8_t* _dst, const uint8_t* _src, uint32_t _width, uint32_t _height, uint8_t _format)
	{
		TextureFormat::Enum format = TextureFormat::Enum(_format);

		switch (format)
		{
		case TextureFormat::BC1:
		case TextureFormat::BC2:
		case TextureFormat::BC3:
		case TextureFormat::BC4:
		case TextureFormat::BC5:
			squish::CompressImage(_src, _width, _height, _dst
				, format == TextureFormat::BC2 ? squish::kDxt3
				: format == TextureFormat::BC3 ? squish::kDxt5
				: format == TextureFormat::BC4 ? squish::kBc4
				: format == TextureFormat::BC5 ? squish::kBc5
				:                                squish::kDxt1
				);
			break;

		case TextureFormat::BC6H:
			nvtt::compressBC6H(_src, _width, _height, 4, _dst);
			break;

		case TextureFormat::BC7:
			nvtt::compressBC7(_src, _width, _height, 4, _dst);
			break;

		case TextureFormat::ETC1:
			etc1_encode_image(_src, _width, _height, 4, _width*4, _dst);
			break;

		case TextureFormat::ETC2:
		case TextureFormat::ETC2A:
		case TextureFormat::ETC2A1:
		case TextureFormat::PTC12:
			break;

		case TextureFormat::PTC14:
			{
				using namespace Javelin;
				RgbBitmap bmp;
				bmp.width  = _width;
				bmp.height = _height;
				bmp.data   = const_cast<uint8_t*>(_src);
				PvrTcEncoder::EncodeRgb4Bpp(_dst, bmp);
				bmp.data = NULL;
			}
			break;

		case TextureFormat::PTC12A:
			break;

		case TextureFormat::PTC14A:
			{
				using namespace Javelin;
				RgbaBitmap bmp;
				bmp.width  = _width;
				bmp.height = _height;
				bmp.data   = const_cast<uint8_t*>(_src);
				PvrTcEncoder::EncodeRgba4Bpp(_dst, bmp);
				bmp.data = NULL;
			}
			break;

		case TextureFormat::PTC22:
		case TextureFormat::PTC24:
			break;

		case TextureFormat::BGRA8:
			imageSwizzleBgra8(_width, _height, _width*4, _src, _dst);
			break;

		case TextureFormat::RGBA8:
			memcpy(_dst, _src, _width*_height*4);
			break;

		default:
			break;
		}
	}

} // namespace bgfx

void help(const char* _error = NULL)
{
	if (NULL != _error)
	{
		fprintf(stderr, "Error:\n%s\n\n", _error);
	}

	fprintf(stderr
		, "texturec, bgfx texture compiler tool\n"
		  "Copyright 2011-2016 Branimir Karadzic. All rights reserved.\n"
		  "License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause\n\n"
		);

	fprintf(stderr
		, "Usage: texturec -f <in> -o <out> -t <format>\n"

		  "\n"
		  "Supported input file types:\n"
		  "    *.png                  Portable Network Graphics\n"
		  "    *.tga                  Targa\n"
		  "    *.dds                  Direct Draw Surface\n"
		  "    *.ktx                  Khronos Texture\n"
		  "    *.pvr                  PowerVR\n"

		  "\n"
		  "Options:\n"
		  "  -f <file path>           Input file path.\n"
		  "  -o <file path>           Output file path (file will be written in KTX format).\n"
		  "  -t <format>              Output format type (BC1/2/3/4/5, ETC1, PVR14, etc.).\n"
		  "  -m, --mips               Generate mip-maps.\n"

		  "\n"
		  "For additional information, see https://github.com/bkaradzic/bgfx\n"
		);
}

int main(int _argc, const char* _argv[])
{
	bx::CommandLine cmdLine(_argc, _argv);

	if (cmdLine.hasArg('h', "help") )
	{
		help();
		return EXIT_FAILURE;
	}

	const char* inputFileName = cmdLine.findOption('f');
	if (NULL == inputFileName)
	{
		help("Input file must be specified.");
		return EXIT_FAILURE;
	}

	const char* outputFileName = cmdLine.findOption('o');
	if (NULL == outputFileName)
	{
		help("Output file must be specified.");
		return EXIT_FAILURE;
	}

	bx::CrtFileReader reader;
	if (0 != bx::open(&reader, inputFileName) )
	{
		help("Failed to open input file.");
		return EXIT_FAILURE;
	}

	const bool  mips = cmdLine.hasArg('m', "mips");
	const char* type = cmdLine.findOption('t');
	bgfx::TextureFormat::Enum format = bgfx::TextureFormat::BGRA8;

	if (NULL != type)
	{
		format = bgfx::getFormat(type);

		if (!isValid(format) )
		{
			help("Invalid format specified.");
			return EXIT_FAILURE;
		}
	}

	uint32_t size = (uint32_t)bx::getSize(&reader);
	const bgfx::Memory* mem = bgfx::alloc(size);
	bx::read(&reader, mem->data, mem->size);
	bx::close(&reader);

	{
		using namespace bgfx;

		uint8_t* decodedImage = NULL;
		ImageContainer imageContainer;

		bool loaded = imageParse(imageContainer, mem->data, mem->size);
		if (!loaded)
		{
			int width  = 0;
			int height = 0;
			int comp   = 0;

			decodedImage = stbi_load_from_memory( (uint8_t*)mem->data, mem->size, &width, &height, &comp, 4);
			loaded = NULL != decodedImage;

			if (loaded)
			{
				release(mem);

				mem = makeRef(decodedImage, width*height*4);

				imageContainer.m_data     = mem->data;
				imageContainer.m_size     = mem->size;
				imageContainer.m_offset   = 0;
				imageContainer.m_width    = width;
				imageContainer.m_height   = height;
				imageContainer.m_depth    = 1;
				imageContainer.m_format   = bgfx::TextureFormat::RGBA8;
				imageContainer.m_numMips  = 1;
				imageContainer.m_hasAlpha = true;
				imageContainer.m_cubeMap  = false;
				imageContainer.m_ktx      = false;
				imageContainer.m_ktxLE    = false;
				imageContainer.m_srgb     = false;
			}
		}

		if (loaded)
		{
			bx::CrtAllocator allocator;
			const Memory* output = NULL;

			ImageMip mip;
			if (imageGetRawData(imageContainer, 0, 0, mem->data, mem->size, mip) )
			{
				uint32_t size = imageGetSize(TextureFormat::RGBA8, mip.m_width, mip.m_height);
				uint8_t* rgba = (uint8_t*)BX_ALLOC(&allocator, size);

				imageDecodeToRgba8(rgba
					, mip.m_data
					, mip.m_width
					, mip.m_height
					, mip.m_width*mip.m_bpp/8
					, mip.m_format
					);

				uint8_t numMips = mips
					? imageGetNumMips(format, mip.m_width, mip.m_height)
					: 1
					;
				imageContainer.m_size   = imageGetSize(format, mip.m_width, mip.m_height, 0, false, numMips);
				imageContainer.m_format = format;
				output = alloc(imageContainer.m_size);

				imageEncodeFromRgba8(output->data, rgba, mip.m_width, mip.m_height, format);

				for (uint8_t lod = 1; lod < numMips; ++lod)
				{
					ImageMip mip1;
					imageGetRawData(imageContainer, 0, lod, output->data, output->size, mip1);
					uint8_t* data = const_cast<uint8_t*>(mip1.m_data);

					uint32_t width  = bx::uint32_max(1, mip.m_width >>lod);
					uint32_t height = bx::uint32_max(1, mip.m_height>>lod);
					imageRgba8Downsample2x2(width, height, width*4, rgba, rgba);
					imageEncodeFromRgba8(data, rgba, mip.m_width, mip.m_height, format);
				}

				BX_FREE(&allocator, rgba);
			}

			if (NULL != output)
			{
				bx::CrtFileWriter writer;
				if (0 == bx::open(&writer, outputFileName) )
				{
					if (NULL != bx::stristr(outputFileName, ".ktx") )
					{
						imageWriteKtx(&writer, imageContainer, output->data, output->size);
					}

					bx::close(&writer);
				}

				release(output);
			}
		}

		release(mem);
	}

	return EXIT_SUCCESS;
}

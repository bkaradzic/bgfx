/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
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
				, format == TextureFormat::BC1 ? squish::kDxt1
				: format == TextureFormat::BC2 ? squish::kDxt3
				: format == TextureFormat::BC3 ? squish::kDxt5
				: format == TextureFormat::BC4 ? squish::kBc4
				:                                squish::kBc5
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
		  "Copyright 2011-2015 Branimir Karadzic. All rights reserved.\n"
		  "License: http://www.opensource.org/licenses/BSD-2-Clause\n\n"
		);
}

int main(int _argc, const char* _argv[])
{
	using namespace bgfx;

	bx::CommandLine cmdLine(_argc, _argv);

	if (cmdLine.hasArg('h', "help") )
	{
		help();
		return EXIT_FAILURE;
	}

	const char* inputFileName = cmdLine.findOption('i');
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
	TextureFormat::Enum format = TextureFormat::BGRA8;

	if (NULL != type)
	{
		if (0 == bx::stricmp(type, "bc1")
		||  0 == bx::stricmp(type, "dxt1") )
		{
			format = TextureFormat::BC1;
		}
		else if (0 == bx::stricmp(type, "bc2")
		||       0 == bx::stricmp(type, "dxt3") )
		{
			format = TextureFormat::BC2;
		}
		else if (0 == bx::stricmp(type, "bc3")
		||       0 == bx::stricmp(type, "dxt5") )
		{
			format = TextureFormat::BC3;
		}
		else if (0 == bx::stricmp(type, "bc4") )
		{
			format = TextureFormat::BC4;
		}
		else if (0 == bx::stricmp(type, "bc5") )
		{
			format = TextureFormat::BC5;
		}
		else if (0 == bx::stricmp(type, "etc1") )
		{
			format = TextureFormat::ETC1;
		}
		else if (0 == bx::stricmp(type, "bc6h") )
		{
			format = TextureFormat::BC6H;
		}
		else if (0 == bx::stricmp(type, "bc7") )
		{
			format = TextureFormat::BC7;
		}
		else if (0 == bx::stricmp(type, "ptc14") )
		{
			format = TextureFormat::PTC14;
		}
		else if (0 == bx::stricmp(type, "ptc14a") )
		{
			format = TextureFormat::PTC14A;
		}
	}

	uint32_t size = (uint32_t)bx::getSize(&reader);
	const Memory* mem = alloc(size);
	bx::read(&reader, mem->data, mem->size);
	bx::close(&reader);

	ImageContainer imageContainer;

	bool loaded = imageParse(imageContainer, mem->data, mem->size);
	if (!loaded)
	{

	}

	BX_UNUSED(mips);
	if (loaded)
	{
		bx::CrtAllocator allocator;
		uint8_t* output = NULL;

		ImageMip mip;
		if (imageGetRawData(imageContainer, 0, 0, mem->data, mem->size, mip) )
		{
			uint8_t* rgba = (uint8_t*)BX_ALLOC(&allocator, imageGetSize(TextureFormat::RGBA8, mip.m_width, mip.m_height) );

			imageDecodeToRgba8(rgba, mip.m_data, mip.m_width, mip.m_height, mip.m_width*mip.m_bpp/8, mip.m_format);

			output = (uint8_t*)BX_ALLOC(&allocator, imageGetSize(format, mip.m_width, mip.m_height) );

			imageContainer.m_format = format;
			imageEncodeFromRgba8(output, rgba, mip.m_width, mip.m_height, format);

			BX_FREE(&allocator, rgba);
		}

		if (NULL != output)
		{
			bx::CrtFileWriter writer;
			if (0 == bx::open(&writer, outputFileName) )
			{
				if (NULL != bx::stristr(outputFileName, ".ktx") )
				{
					imageWriteKtx(&writer, imageContainer, mem->data, mem->size);
				}

				bx::close(&writer);
			}

			BX_FREE(&allocator, output);
		}
	}

	release(mem);

	return EXIT_SUCCESS;
}

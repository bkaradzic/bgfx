/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Just hacking DDS loading code in here.
#include "bgfx_p.h"
using namespace bgfx;

#include "image.h"

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

	uint32_t size = (uint32_t)bx::getSize(&reader);
	const Memory* mem = alloc(size);
	bx::read(&reader, mem->data, mem->size);
	bx::close(&reader);

	ImageContainer imageContainer;

	if (imageParse(imageContainer, mem->data, mem->size) )
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
	}

#if 0
	if (imageParse(imageContainer, mem->data, mem->size) )
	{
		bool decompress = cmdLine.hasArg('d');

		if (decompress
		||  0 == imageContainer.m_format)
		{
			for (uint8_t side = 0, numSides = imageContainer.m_cubeMap ? 6 : 1; side < numSides; ++side)
			{
				uint32_t width  = imageContainer.m_width;
				uint32_t height = imageContainer.m_height;

				for (uint32_t lod = 0, num = imageContainer.m_numMips; lod < num; ++lod)
				{
					width  = bx::uint32_max(1, width);
					height = bx::uint32_max(1, height);

					ImageMip mip;
					if (imageGetRawData(imageContainer, side, lod, mem->data, mem->size, mip) )
					{
						uint32_t dstpitch = width*4;
						uint8_t* bits = (uint8_t*)malloc(dstpitch*height);

						if (width  != mip.m_width
						||  height != mip.m_height)
						{
							uint8_t* temp = (uint8_t*)realloc(NULL, mip.m_width*mip.m_height*4);
							imageDecodeToBgra8(temp, mip.m_data, mip.m_width, mip.m_height, mip.m_width*4, mip.m_format);
							uint32_t srcpitch = mip.m_width*4;

							for (uint32_t yy = 0; yy < height; ++yy)
							{
								uint8_t* src = &temp[yy*srcpitch];
								uint8_t* dst = &bits[yy*dstpitch];

								for (uint32_t xx = 0; xx < width; ++xx)
								{
									memcpy(dst, src, 4);
									dst += 4;
									src += 4;
								}
							}

							free(temp);
						}
						else
						{
							imageDecodeToBgra8(bits
								, mip.m_data
								, mip.m_width
								, mip.m_height
								, mip.m_width*4
								, mip.m_format
								);
						}

						char filePath[256];
						bx::snprintf(filePath, sizeof(filePath), "mip%d_%d.ktx", side, lod);

						bx::CrtFileWriter writer;
						if (0 == bx::open(&writer, filePath) )
						{
							if (NULL != bx::stristr(filePath, ".ktx") )
							{
								imageWriteKtx(&writer
									, TextureFormat::BGRA8
									, false
									, width
									, height
									, 0
									, 1
									, bits
									);
							}
							else
							{
								imageWriteTga(&writer, width, height, dstpitch, bits, false, false);
							}

							bx::close(&writer);
						}

						free(bits);
					}

					width >>= 1;
					height >>= 1;
				}
			}
		}
		else
		{
			for (uint32_t lod = 0, num = imageContainer.m_numMips; lod < num; ++lod)
			{
				ImageMip mip;
				if (imageGetRawData(imageContainer, 0, lod, mem->data, mem->size, mip) )
				{
					char filePath[256];
					bx::snprintf(filePath, sizeof(filePath), "mip%d.bin", lod);

					bx::CrtFileWriter writer;
					if (0 == bx::open(&writer, filePath) )
					{
						printf("mip%d, size %d\n", lod, mip.m_size);
						bx::write(&writer, mip.m_data, mip.m_size);
						bx::close(&writer);
					}
				}
			}
		}
	}
#endif // 0

	release(mem);

	return EXIT_SUCCESS;
}

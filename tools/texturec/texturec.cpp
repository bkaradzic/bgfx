/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Just hacking DDS loading code in here.
#include "bgfx_p.h"
using namespace bgfx;

#include "dds.h"

#if 0
#	define BX_TRACE(_format, ...) fprintf(stderr, "" _format "\n", ##__VA_ARGS__)
#endif // DEBUG

#include <bx/bx.h>
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

	void saveTga(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, bool _grayscale, bool _yflip)
	{
		FILE* file = fopen(_filePath, "wb");
		if ( NULL != file )
		{
			uint8_t type = _grayscale ? 3 : 2;
			uint8_t bpp = _grayscale ? 8 : 32;

			putc(0, file);
			putc(0, file);
			putc(type, file);
			putc(0, file);
			putc(0, file);
			putc(0, file);
			putc(0, file);
			putc(0, file);
			putc(0, file);
			putc(0, file);
			putc(0, file);
			putc(0, file);
			putc(_width&0xff, file);
			putc( (_width>>8)&0xff, file);
			putc(_height&0xff, file);
			putc( (_height>>8)&0xff, file);
			putc(bpp, file);
			putc(32, file);

			uint32_t dstPitch = _width*bpp/8;
			if (_yflip)
			{
				uint8_t* data = (uint8_t*)_src + dstPitch*_height - _srcPitch;
				for (uint32_t yy = 0; yy < _height; ++yy)
				{
					fwrite(data, dstPitch, 1, file);
					data -= _srcPitch;
				}
			}
			else
			{
				uint8_t* data = (uint8_t*)_src;
				for (uint32_t yy = 0; yy < _height; ++yy)
				{
					fwrite(data, dstPitch, 1, file);
					data += _srcPitch;
				}
			}

			fclose(file);
		}
	}
}

long int fsize(FILE* _file)
{
	long int pos = ftell(_file);
	fseek(_file, 0L, SEEK_END);
	long int size = ftell(_file);
	fseek(_file, pos, SEEK_SET);
	return size;
}

int main(int _argc, const char* _argv[])
{
	bx::CommandLine cmdLine(_argc, _argv);

	FILE* file = fopen(_argv[1], "rb");
	uint32_t size = fsize(file);
	const Memory* mem = alloc(size);
	size_t readSize = fread(mem->data, 1, size, file);
	BX_UNUSED(readSize);
	fclose(file);

	Dds dds;

	if (parseDds(dds, mem) )
	{
		bool decompress = cmdLine.hasArg('d');

		if (decompress
		||  0 == dds.m_type)
		{
			for (uint8_t side = 0, numSides = dds.m_cubeMap ? 6 : 1; side < numSides; ++side)
			{
				uint32_t width = dds.m_width;
				uint32_t height = dds.m_height;

				for (uint32_t lod = 0, num = dds.m_numMips; lod < num; ++lod)
				{
					width = bx::uint32_max(1, width);
					height = bx::uint32_max(1, height);

					Mip mip;
					if (getRawImageData(dds, side, lod, mem, mip) )
					{
						uint32_t dstpitch = width*4;
						uint8_t* bits = (uint8_t*)malloc(dstpitch*height);

						if (width != mip.m_width
						||  height != mip.m_height)
						{
							uint8_t* temp = (uint8_t*)realloc(NULL, mip.m_width*mip.m_height*4);
							mip.decode(temp);
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
							mip.decode(bits);
						}

						char filePath[256];
						bx::snprintf(filePath, sizeof(filePath), "mip%d_%d.tga", side, lod);

						saveTga(filePath, width, height, dstpitch, bits);
						free(bits);
					}

					width >>= 1;
					height >>= 1;
				}
			}
		}
		else
		{
			for (uint32_t lod = 0, num = dds.m_numMips; lod < num; ++lod)
			{
				Mip mip;
				if (getRawImageData(dds, 0, lod, mem, mip) )
				{
					char filePath[256];
					bx::snprintf(filePath, sizeof(filePath), "mip%d.bin", lod);
					file = fopen(filePath, "wb");
					fwrite(mip.m_data, 1, mip.m_size, file);
					fclose(file);
				}
			}
		}
	}

	return EXIT_SUCCESS;
}

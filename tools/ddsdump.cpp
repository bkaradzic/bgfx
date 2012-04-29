/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bgfx_p.h"
using namespace bgfx;

#include "dds.h"

#if 0
#	define BX_TRACE(_format, ...) fprintf(stderr, "" _format "\n", ##__VA_ARGS__)
#endif // DEBUG

#define BX_NAMESPACE 1
#include <bx/bx.h>
#include <bx/commandline.h>
#include <bx/uint32_t.h>

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
	CommandLine cmdLine(_argc, _argv);

	FILE* file = fopen(_argv[1], "rb");
	uint32_t size = fsize(file);
	const Memory* mem = bgfx::alloc(size);
	fread(mem->data, 1, size, file);
	fclose(file);

	Dds dds;

	if (parseDds(dds, mem) )
	{
		bool decompress = cmdLine.hasArg('d');

		if (decompress
		||  0 == dds.m_type)
		{
			uint32_t width = dds.m_width;
			uint32_t height = dds.m_height;

			for (uint32_t lod = 0, num = dds.m_numMips; lod < num; ++lod)
			{
				width = uint32_max(1, width);
				height = uint32_max(1, height);

				Mip mip;
				if (getRawImageData(dds, lod, mem, mip) )
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
					_snprintf(filePath, sizeof(filePath), "mip%d.tga", lod);

					bgfx::saveTga(filePath, width, height, dstpitch, bits);
					free(bits);
				}

				width >>= 1;
				height >>= 1;
			}
		}
		else
		{
			for (uint32_t lod = 0, num = dds.m_numMips; lod < num; ++lod)
			{
				Mip mip;
				if (getRawImageData(dds, lod, mem, mip) )
				{
					char filePath[256];
					_snprintf(filePath, sizeof(filePath), "mip%d.bin", lod);
					file = fopen(filePath, "wb");
					fwrite(mip.m_data, 1, mip.m_size, file);
					fclose(file);
				}
			}
		}
	}

	return EXIT_SUCCESS;
}

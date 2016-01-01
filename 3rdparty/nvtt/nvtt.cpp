/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "nvtt.h"

#include <string.h>
#include <bx/uint32_t.h>

#include "bc6h/zoh.h"
#include "bc7/avpcl.h"
#include "nvmath/vector.inl"

NVCORE_API int nvAbort(const char *, const char *, int , const char *, const char *, ...)
{
	abort();
	return 0;
}

namespace nvtt
{
	using namespace nv;

	void compressBC6H(const void* _input, uint32_t _width, uint32_t _height, uint32_t _stride, void* _output)
	{
		const uint8_t* src = (const uint8_t*)_input;
		char* dst = (char*)_output;

		for (uint32_t yy = 0; yy < _height; yy += 4)
		{
			for (uint32_t xx = 0; xx < _width; xx += 4)
			{
				const Vector4* rgba = (const Vector4*)&src[yy*_stride + xx*sizeof(float)*4];

				ZOH::Utils::FORMAT = ZOH::UNSIGNED_F16;
				ZOH::Tile zohTile(4, 4);

				memset(zohTile.data, 0, sizeof(zohTile.data) );
				memset(zohTile.importance_map, 0, sizeof(zohTile.importance_map) );

				for (uint32_t blockY = 0; blockY < 4; ++blockY)
				{
					for (uint32_t blockX = 0; blockX < 4; ++blockX)
					{
						Vector4 color = rgba[blockY*4 + blockX];
						uint16 rHalf = bx::halfFromFloat(color.x);
						uint16 gHalf = bx::halfFromFloat(color.y);
						uint16 bHalf = bx::halfFromFloat(color.z);
						zohTile.data[blockY][blockX].x = ZOH::Tile::half2float(rHalf);
						zohTile.data[blockY][blockX].y = ZOH::Tile::half2float(gHalf);
						zohTile.data[blockY][blockX].z = ZOH::Tile::half2float(bHalf);
						zohTile.importance_map[blockY][blockX] = 1.0f;
					}
				}

				ZOH::compress(zohTile, &dst[( (yy*_width) + xx)/4 * 16]);
			}
		}
	}

	void compressBC7(const void* _input, uint32_t _width, uint32_t _height, uint32_t _stride, void* _output)
	{
		const uint8_t* src = (const uint8_t*)_input;
		char* dst = (char*)_output;

		for (uint32_t yy = 0; yy < _height; yy += 4)
		{
			for (uint32_t xx = 0; xx < _width; xx += 4)
			{
				const Vector4* rgba = (const Vector4*)&src[yy*_stride + xx*sizeof(float)*4];

				AVPCL::mode_rgb     = false;
				AVPCL::flag_premult = false;
				AVPCL::flag_nonuniform     = false;
				AVPCL::flag_nonuniform_ati = false;

				AVPCL::Tile avpclTile(4, 4);
				memset(avpclTile.data, 0, sizeof(avpclTile.data) );
				for (uint32_t blockY = 0; blockY < 4; ++blockY)
				{
					for (uint32_t blockX = 0; blockX < 4; ++blockX)
					{
						Vector4 color = rgba[blockY*4 + blockX];
						avpclTile.data[blockY][blockX] = color * 255.0f;
						avpclTile.importance_map[blockY][blockX] = 1.0f;
					}
				}

				AVPCL::compress(avpclTile, &dst[( (yy*_width) + xx)/4 * 16]);
			}
		}
	}

} //namespace nvtt

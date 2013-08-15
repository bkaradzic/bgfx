/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bx/float4_t.h>

namespace bgfx
{
	static void imageSwizzleBGRA8Ref(uint8_t* _rgbaData, uint32_t _width, uint32_t _height) 
	{
		uint32_t dstpitch = _width*4;
		for (uint32_t yy = 0; yy < _height; ++yy)
		{
			uint8_t* dst = &_rgbaData[yy*dstpitch];

			for (uint32_t xx = 0; xx < _width; ++xx)
			{
				uint8_t tmp = dst[0];
				dst[0] = dst[2];
				dst[2] = tmp;
				dst += 4;
			}
		}
	}

	void imageSwizzleBGRA8(uint8_t* _rgbaData, uint32_t _width, uint32_t _height)
	{
		if (0 != (_width&0xf)
		||  _width < 16)
		{
			imageSwizzleBGRA8Ref(_rgbaData, _width, _height);
			return;
		}

		uint32_t dstpitch = _width*4;
		uint32_t num = dstpitch/16;

		using namespace bx;

		const float4_t mf0f0 = float4_isplat(0xff00ff00);
		const float4_t m0f0f = float4_isplat(0x00ff00ff);

		for (uint32_t yy = 0; yy < _height; ++yy)
		{
			uint8_t* ptr = &_rgbaData[yy*dstpitch];

			for (uint32_t xx = 0; xx < num; ++xx)
			{
				const float4_t tabgr = float4_ld(ptr);
				const float4_t t00ab = float4_srl(tabgr, 16);
				const float4_t tgr00 = float4_sll(tabgr, 16);
				const float4_t tgrab = float4_or(t00ab, tgr00);
				const float4_t ta0g0 = float4_and(tabgr, mf0f0);
				const float4_t t0g0b = float4_and(tgrab, m0f0f);
				const float4_t targb = float4_or(ta0g0, t0g0b);
				float4_st(ptr, targb);
				ptr += 16;
			}
		}
	}

} // namespace bgfx

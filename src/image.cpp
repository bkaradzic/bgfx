/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"
#include <bx/float4_t.h>

namespace bgfx
{
	static void imageSwizzleBGRA8Ref(uint8_t* _rgbaData, uint32_t _width, uint32_t _height) 
	{
		const uint32_t dstpitch = _width*4;
		uint8_t* ptr = _rgbaData;

		for (uint32_t xx = 0, num = _width*_height; xx < num; ++xx)
		{
			uint8_t tmp = ptr[0];
			ptr[0] = ptr[2];
			ptr[2] = tmp;
			ptr += 4;
		}
	}

	void imageSwizzleBGRA8(uint8_t* _rgbaData, uint32_t _width, uint32_t _height)
	{
		// Test can we do four 4-byte pixels at the time.
		if (0 != (_width&0x3)
		||  _width < 4)
		{
			BX_WARN(_width < 4, "Image swizzle is taking slow path. Image width must be multiple of 4 (width %d).", _width);
			imageSwizzleBGRA8Ref(_rgbaData, _width, _height);
			return;
		}

		const uint32_t dstpitch = _width*4;

		using namespace bx;

		const float4_t mf0f0 = float4_isplat(0xff00ff00);
		const float4_t m0f0f = float4_isplat(0x00ff00ff);
		uint8_t* ptr = _rgbaData;

		for (uint32_t xx = 0, num = dstpitch/16*_height; xx < num; ++xx)
		{
			const float4_t tabgr = float4_ld(ptr);
			const float4_t t00ab = float4_srl(tabgr, 16);
			const float4_t tgr00 = float4_sll(tabgr, 16);
			const float4_t tgrab = float4_or(t00ab, tgr00);
			const float4_t ta0g0 = float4_and(tabgr, mf0f0);
			const float4_t t0r0b = float4_and(tgrab, m0f0f);
			const float4_t targb = float4_or(ta0g0, t0r0b);
			float4_st(ptr, targb);
			ptr += 16;
		}
	}

} // namespace bgfx

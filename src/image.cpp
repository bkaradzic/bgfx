/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"
#include <bx/float4_t.h>

namespace bgfx
{
	void imageSolid(uint32_t _width, uint32_t _height, uint32_t _solid, void* _dst)
	{
		uint32_t* dst = (uint32_t*)_dst;
		for (uint32_t ii = 0, num = _width*_height; ii < num; ++ii)
		{
			*dst++ = _solid;
		}
	}

	void imageChessboard(uint32_t _width, uint32_t _height, uint32_t _step, uint32_t _0, uint32_t _1, void* _dst)
	{
		uint32_t* dst = (uint32_t*)_dst;
		for (uint32_t yy = 0; yy < _height; ++yy)
		{
			for (uint32_t xx = 0; xx < _width; ++xx)
			{
				uint32_t abgr = ( (xx/_step)&1) ^ ( (yy/_step)&1) ? _1 : _0;
				*dst++ = abgr;
			}
		}
	}

	void imageRgba8Downsample2x2Ref(uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src, void* _dst)
	{
		const uint32_t dstwidth  = _width/2;
		const uint32_t dstheight = _height/2;

		if (0 == dstwidth
		||  0 == dstheight)
		{
			return;
		}

		uint8_t* dst = (uint8_t*)_dst;
		const uint8_t* src = (const uint8_t*)_src;
		
		for (uint32_t yy = 0, ystep = _pitch*2; yy < dstheight; ++yy, src += ystep)
		{
			const uint8_t* rgba = src;
			for (uint32_t xx = 0; xx < dstwidth; ++xx, rgba += 8, dst += 4)
			{
				float rr = powf(rgba[       0], 2.2f);
				float gg = powf(rgba[       1], 2.2f);
				float bb = powf(rgba[       2], 2.2f);
				float aa =      rgba[       3];
				rr      += powf(rgba[       4], 2.2f);
				gg      += powf(rgba[       5], 2.2f);
				bb      += powf(rgba[       6], 2.2f);
				aa      +=      rgba[       7];
				rr      += powf(rgba[_pitch+0], 2.2f);
				gg      += powf(rgba[_pitch+1], 2.2f);
				bb      += powf(rgba[_pitch+2], 2.2f);
				aa      +=      rgba[_pitch+3];
				rr      += powf(rgba[_pitch+4], 2.2f);
				gg      += powf(rgba[_pitch+5], 2.2f);
				bb      += powf(rgba[_pitch+6], 2.2f);
				aa      +=      rgba[_pitch+7];

				rr *= 0.25f;
				gg *= 0.25f;
				bb *= 0.25f;
				aa *= 0.25f;
				rr = powf(rr, 1.0f/2.2f);
				gg = powf(gg, 1.0f/2.2f);
				bb = powf(bb, 1.0f/2.2f);
				aa =      aa;
				dst[0] = (uint8_t)rr;
				dst[1] = (uint8_t)gg;
				dst[2] = (uint8_t)bb;
				dst[3] = (uint8_t)aa;
			}
		}
	}

	void imageRgba8Downsample2x2(uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src, void* _dst)
	{
		const uint32_t dstwidth  = _width/2;
		const uint32_t dstheight = _height/2;

		if (0 == dstwidth
		||  0 == dstheight)
		{
			return;
		}

		uint8_t* dst = (uint8_t*)_dst;
		const uint8_t* src = (const uint8_t*)_src;

		using namespace bx;
		const float4_t unpack = float4_ld(1.0f, 1.0f/256.0f, 1.0f/65536.0f, 1.0f/16777216.0f);
		const float4_t pack   = float4_ld(1.0f, 256.0f*0.5f, 65536.0f, 16777216.0f*0.5f);
		const float4_t umask  = float4_ild(0xff, 0xff00, 0xff0000, 0xff000000);
		const float4_t pmask  = float4_ild(0xff, 0x7f80, 0xff0000, 0x7f800000);
		const float4_t wflip  = float4_ild(0, 0, 0, 0x80000000);
		const float4_t wadd   = float4_ld(0.0f, 0.0f, 0.0f, 32768.0f*65536.0f);
		const float4_t gamma  = float4_ld(1.0f/2.2f, 1.0f/2.2f, 1.0f/2.2f, 1.0f);
		const float4_t linear = float4_ld(2.2f, 2.2f, 2.2f, 1.0f);
		const float4_t quater = float4_splat(0.25f);

		for (uint32_t yy = 0, ystep = _pitch*2; yy < dstheight; ++yy, src += ystep)
		{
			const uint8_t* rgba = src;
			for (uint32_t xx = 0; xx < dstwidth; ++xx, rgba += 8, dst += 4)
			{
				const float4_t abgr0  = float4_splat(rgba);
				const float4_t abgr1  = float4_splat(rgba+4);
				const float4_t abgr2  = float4_splat(rgba+_pitch);
				const float4_t abgr3  = float4_splat(rgba+_pitch+4);

				const float4_t abgr0m = float4_and(abgr0, umask);
				const float4_t abgr1m = float4_and(abgr1, umask);
				const float4_t abgr2m = float4_and(abgr2, umask);
				const float4_t abgr3m = float4_and(abgr3, umask);
				const float4_t abgr0x = float4_xor(abgr0m, wflip);
				const float4_t abgr1x = float4_xor(abgr1m, wflip);
				const float4_t abgr2x = float4_xor(abgr2m, wflip);
				const float4_t abgr3x = float4_xor(abgr3m, wflip);
				const float4_t abgr0f = float4_itof(abgr0x);
				const float4_t abgr1f = float4_itof(abgr1x);
				const float4_t abgr2f = float4_itof(abgr2x);
				const float4_t abgr3f = float4_itof(abgr3x);
				const float4_t abgr0c = float4_add(abgr0f, wadd);
				const float4_t abgr1c = float4_add(abgr1f, wadd);
				const float4_t abgr2c = float4_add(abgr2f, wadd);
				const float4_t abgr3c = float4_add(abgr3f, wadd);
				const float4_t abgr0n = float4_mul(abgr0c, unpack);
				const float4_t abgr1n = float4_mul(abgr1c, unpack);
				const float4_t abgr2n = float4_mul(abgr2c, unpack);
				const float4_t abgr3n = float4_mul(abgr3c, unpack);

				const float4_t abgr0l = float4_pow(abgr0n, linear);
				const float4_t abgr1l = float4_pow(abgr1n, linear);
				const float4_t abgr2l = float4_pow(abgr2n, linear);
				const float4_t abgr3l = float4_pow(abgr3n, linear);

				const float4_t sum0   = float4_add(abgr0l, abgr1l);
				const float4_t sum1   = float4_add(abgr2l, abgr3l);
				const float4_t sum2   = float4_add(sum0, sum1);
				const float4_t avg0   = float4_mul(sum2, quater);
				const float4_t avg1   = float4_pow(avg0, gamma);

				const float4_t avg2   = float4_mul(avg1, pack);
				const float4_t ftoi0  = float4_ftoi(avg2);
				const float4_t ftoi1  = float4_and(ftoi0, pmask);
				const float4_t zwxy   = float4_swiz_zwxy(ftoi1);
				const float4_t tmp0   = float4_or(ftoi1, zwxy);
				const float4_t yyyy   = float4_swiz_yyyy(tmp0);
				const float4_t tmp1   = float4_iadd(yyyy, yyyy);
				const float4_t result = float4_or(tmp0, tmp1);

				float4_stx(dst, result);
			}
		}
	}

	static void imageSwizzleBgra8Ref(uint32_t _width, uint32_t _height, const void* _src, void* _dst)
	{
		const uint8_t* src = (uint8_t*) _src;
		uint8_t* dst = (uint8_t*)_dst;

		for (uint32_t xx = 0, num = _width*_height; xx < num; ++xx, src += 4, dst += 4)
		{
			uint8_t rr = src[0];
			uint8_t gg = src[1];
			uint8_t bb = src[2];
			uint8_t aa = src[3];
			dst[0] = bb;
			dst[1] = gg;
			dst[2] = rr;
			dst[3] = aa;
		}
	}

	void imageSwizzleBgra8(uint32_t _width, uint32_t _height, const void* _src, void* _dst)
	{
		// Test can we do four 4-byte pixels at the time.
		if (0 != (_width&0x3)
		||  _width < 4)
		{
			BX_WARN(_width < 4, "Image swizzle is taking slow path. Image width must be multiple of 4 (width %d).", _width);
			imageSwizzleBgra8Ref(_width, _height, _src, _dst);
			return;
		}

		const uint32_t dstpitch = _width*4;

		using namespace bx;

		const float4_t mf0f0 = float4_isplat(0xff00ff00);
		const float4_t m0f0f = float4_isplat(0x00ff00ff);
		const uint8_t* src = (uint8_t*) _src;
		uint8_t* dst = (uint8_t*)_dst;

		for (uint32_t xx = 0, num = dstpitch/16*_height; xx < num; ++xx, src += 16, dst += 16)
		{
			const float4_t tabgr = float4_ld(src);
			const float4_t t00ab = float4_srl(tabgr, 16);
			const float4_t tgr00 = float4_sll(tabgr, 16);
			const float4_t tgrab = float4_or(t00ab, tgr00);
			const float4_t ta0g0 = float4_and(tabgr, mf0f0);
			const float4_t t0r0b = float4_and(tgrab, m0f0f);
			const float4_t targb = float4_or(ta0g0, t0r0b);
			float4_st(dst, targb);
		}
	}

	void imageWriteTga(bx::WriterI* _writer, uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, bool _grayscale, bool _yflip)
	{
		uint8_t type = _grayscale ? 3 : 2;
		uint8_t bpp = _grayscale ? 8 : 32;

		uint8_t header[18] = {};
		header[2] = type;
		header[12] = _width&0xff;
		header[13] = (_width>>8)&0xff;
		header[14] = _height&0xff;
		header[15] = (_height>>8)&0xff;
		header[16] = bpp;
		header[17] = 32;

		bx::write(_writer, header, sizeof(header) );

		uint32_t dstPitch = _width*bpp/8;
		if (_yflip)
		{
			uint8_t* data = (uint8_t*)_src + _srcPitch*_height - _srcPitch;
			for (uint32_t yy = 0; yy < _height; ++yy)
			{
				bx::write(_writer, data, dstPitch);
				data -= _srcPitch;
			}
		}
		else if (_srcPitch == dstPitch)
		{
			bx::write(_writer, _src, _height*_srcPitch);
		}
		else
		{
			uint8_t* data = (uint8_t*)_src;
			for (uint32_t yy = 0; yy < _height; ++yy)
			{
				bx::write(_writer, data, dstPitch);
				data += _srcPitch;
			}
		}
	}

} // namespace bgfx

/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"
#include <bx/float4_t.h>
#include <math.h> // powf, sqrtf

#include "image.h"

namespace bgfx
{
	static const uint32_t s_bitsPerPixel[TextureFormat::Count] =
	{
		4,  // BC1
		8,  // BC2
		8,  // BC3
		4,  // BC4
		8,  // BC5
		4,  // ETC1
		4,  // ETC2
		4,  // ETC2A
		4,  // ETC2A1
		2,  // PTC12
		4,  // PTC14
		2,  // PTC12A
		4,  // PTC14A
		2,  // PTC22
		4,  // PTC24
		0,  // Unknown
		8,  // L8
		32, // BGRA8
		64, // RGBA16
		64, // RGBA16F
		16, // R5G6B5
		16, // RGBA4
		16, // RGB5A1
		32, // RGB10A2
		0,  // UnknownDepth
		16, // D16
		24, // D24
		32, // D24S8
		32, // D32
		16, // D16F
		24, // D24F
		32, // D32F
		8,  // D0S8
	};

	bool isCompressed(TextureFormat::Enum _format)
	{
		return _format < TextureFormat::Unknown;
	}

	bool isColor(TextureFormat::Enum _format)
	{
		return _format > TextureFormat::Unknown
			&& _format < TextureFormat::UnknownDepth
			;
	}

	bool isDepth(TextureFormat::Enum _format)
	{
		return _format > TextureFormat::UnknownDepth
			&& _format < TextureFormat::Count
			;
	}

	uint32_t getBitsPerPixel(TextureFormat::Enum _format)
	{
		return s_bitsPerPixel[_format];
	}

	void imageSolid(uint32_t _width, uint32_t _height, uint32_t _solid, void* _dst)
	{
		uint32_t* dst = (uint32_t*)_dst;
		for (uint32_t ii = 0, num = _width*_height; ii < num; ++ii)
		{
			*dst++ = _solid;
		}
	}

	void imageCheckerboard(uint32_t _width, uint32_t _height, uint32_t _step, uint32_t _0, uint32_t _1, void* _dst)
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

	void imageRgba8Downsample2x2Ref(uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, void* _dst)
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
		
		for (uint32_t yy = 0, ystep = _srcPitch*2; yy < dstheight; ++yy, src += ystep)
		{
			const uint8_t* rgba = src;
			for (uint32_t xx = 0; xx < dstwidth; ++xx, rgba += 8, dst += 4)
			{
				float rr = powf(rgba[          0], 2.2f);
				float gg = powf(rgba[          1], 2.2f);
				float bb = powf(rgba[          2], 2.2f);
				float aa =      rgba[          3];
				rr      += powf(rgba[          4], 2.2f);
				gg      += powf(rgba[          5], 2.2f);
				bb      += powf(rgba[          6], 2.2f);
				aa      +=      rgba[          7];
				rr      += powf(rgba[_srcPitch+0], 2.2f);
				gg      += powf(rgba[_srcPitch+1], 2.2f);
				bb      += powf(rgba[_srcPitch+2], 2.2f);
				aa      +=      rgba[_srcPitch+3];
				rr      += powf(rgba[_srcPitch+4], 2.2f);
				gg      += powf(rgba[_srcPitch+5], 2.2f);
				bb      += powf(rgba[_srcPitch+6], 2.2f);
				aa      +=      rgba[_srcPitch+7];

				rr *= 0.25f;
				gg *= 0.25f;
				bb *= 0.25f;
				aa *= 0.25f;
				rr = powf(rr, 1.0f/2.2f);
				gg = powf(gg, 1.0f/2.2f);
				bb = powf(bb, 1.0f/2.2f);
				dst[0] = (uint8_t)rr;
				dst[1] = (uint8_t)gg;
				dst[2] = (uint8_t)bb;
				dst[3] = (uint8_t)aa;
			}
		}
	}

	void imageRgba8Downsample2x2(uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, void* _dst)
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

		for (uint32_t yy = 0, ystep = _srcPitch*2; yy < dstheight; ++yy, src += ystep)
		{
			const uint8_t* rgba = src;
			for (uint32_t xx = 0; xx < dstwidth; ++xx, rgba += 8, dst += 4)
			{
				const float4_t abgr0  = float4_splat(rgba);
				const float4_t abgr1  = float4_splat(rgba+4);
				const float4_t abgr2  = float4_splat(rgba+_srcPitch);
				const float4_t abgr3  = float4_splat(rgba+_srcPitch+4);

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

	void imageSwizzleBgra8Ref(uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, void* _dst)
	{
		const uint8_t* src = (uint8_t*) _src;
		const uint8_t* next = src + _srcPitch;
		uint8_t* dst = (uint8_t*)_dst;

		for (uint32_t yy = 0; yy < _height; ++yy, src = next, next += _srcPitch)
		{
			for (uint32_t xx = 0; xx < _width; ++xx, src += 4, dst += 4)
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
	}

	void imageSwizzleBgra8(uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, void* _dst)
	{
		// Test can we do four 4-byte pixels at the time.
		if (0 != (_width&0x3)
		||  _width < 4
		||  !bx::isPtrAligned(_src, 16)
		||  !bx::isPtrAligned(_dst, 16) )
		{
			BX_WARN(false, "Image swizzle is taking slow path.");
			BX_WARN(bx::isPtrAligned(_src, 16), "Source %p is not 16-byte aligned.", _src);
			BX_WARN(bx::isPtrAligned(_dst, 16), "Destination %p is not 16-byte aligned.", _dst);
			BX_WARN(_width < 4, "Image width must be multiple of 4 (width %d).", _width);
			imageSwizzleBgra8Ref(_width, _height, _srcPitch, _src, _dst);
			return;
		}

		using namespace bx;

		const float4_t mf0f0 = float4_isplat(0xff00ff00);
		const float4_t m0f0f = float4_isplat(0x00ff00ff);
		const uint8_t* src = (uint8_t*) _src;
		const uint8_t* next = src + _srcPitch;
		uint8_t* dst = (uint8_t*)_dst;

		const uint32_t width = _width/4;

		for (uint32_t yy = 0; yy < _height; ++yy, src = next, next += _srcPitch)
		{
			for (uint32_t xx = 0; xx < width; ++xx, src += 16, dst += 16)
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
	}

	void imageCopy(uint32_t _width, uint32_t _height, uint32_t _bpp, uint32_t _srcPitch, const void* _src, void* _dst)
	{
		const uint32_t pitch = _width*_bpp/8;
		const uint8_t* src = (uint8_t*) _src;
		const uint8_t* next = src + _srcPitch;
		uint8_t* dst = (uint8_t*)_dst;

		for (uint32_t yy = 0; yy < _height; ++yy, src = next, next += _srcPitch)
		{
			memcpy(dst, src, pitch);
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

	uint32_t bitRangeConvert(uint32_t _in, uint32_t _from, uint32_t _to)
	{
		using namespace bx;
		uint32_t tmp0   = uint32_sll(1, _to);
		uint32_t tmp1   = uint32_sll(1, _from);
		uint32_t tmp2   = uint32_dec(tmp0);
		uint32_t tmp3   = uint32_dec(tmp1);
		uint32_t tmp4   = uint32_mul(_in, tmp2);
		uint32_t tmp5   = uint32_add(tmp3, tmp4);
		uint32_t tmp6   = uint32_srl(tmp5, _from);
		uint32_t tmp7   = uint32_add(tmp5, tmp6);
		uint32_t result = uint32_srl(tmp7, _from);

		return result;
	}

	void decodeBlockDxt(uint8_t _dst[16*4], const uint8_t _src[8])
	{
		uint8_t colors[4*3];

		uint32_t c0 = _src[0] | (_src[1] << 8);
		colors[0] = bitRangeConvert( (c0>> 0)&0x1f, 5, 8);
		colors[1] = bitRangeConvert( (c0>> 5)&0x3f, 6, 8);
		colors[2] = bitRangeConvert( (c0>>11)&0x1f, 5, 8);

		uint32_t c1 = _src[2] | (_src[3] << 8);
		colors[3] = bitRangeConvert( (c1>> 0)&0x1f, 5, 8);
		colors[4] = bitRangeConvert( (c1>> 5)&0x3f, 6, 8);
		colors[5] = bitRangeConvert( (c1>>11)&0x1f, 5, 8);

		colors[6] = (2*colors[0] + colors[3]) / 3;
		colors[7] = (2*colors[1] + colors[4]) / 3;
		colors[8] = (2*colors[2] + colors[5]) / 3;

		colors[ 9] = (colors[0] + 2*colors[3]) / 3;
		colors[10] = (colors[1] + 2*colors[4]) / 3;
		colors[11] = (colors[2] + 2*colors[5]) / 3;

		for (uint32_t ii = 0, next = 8*4; ii < 16*4; ii += 4, next += 2)
		{
			int idx = ( (_src[next>>3] >> (next & 7) ) & 3) * 3;
			_dst[ii+0] = colors[idx+0];
			_dst[ii+1] = colors[idx+1];
			_dst[ii+2] = colors[idx+2];
		}
	}

	void decodeBlockDxt1(uint8_t _dst[16*4], const uint8_t _src[8])
	{
		uint8_t colors[4*4];

		uint32_t c0 = _src[0] | (_src[1] << 8);
		colors[0] = bitRangeConvert( (c0>> 0)&0x1f, 5, 8);
		colors[1] = bitRangeConvert( (c0>> 5)&0x3f, 6, 8);
		colors[2] = bitRangeConvert( (c0>>11)&0x1f, 5, 8);
		colors[3] = 255;

		uint32_t c1 = _src[2] | (_src[3] << 8);
		colors[4] = bitRangeConvert( (c1>> 0)&0x1f, 5, 8);
		colors[5] = bitRangeConvert( (c1>> 5)&0x3f, 6, 8);
		colors[6] = bitRangeConvert( (c1>>11)&0x1f, 5, 8);
		colors[7] = 255;

		if (c0 > c1)
		{
			colors[ 8] = (2*colors[0] + colors[4]) / 3;
			colors[ 9] = (2*colors[1] + colors[5]) / 3;
			colors[10] = (2*colors[2] + colors[6]) / 3;
			colors[11] = 255;

			colors[12] = (colors[0] + 2*colors[4]) / 3;
			colors[13] = (colors[1] + 2*colors[5]) / 3;
			colors[14] = (colors[2] + 2*colors[6]) / 3;
			colors[15] = 255;
		}
		else
		{
			colors[ 8] = (colors[0] + colors[4]) / 2;
			colors[ 9] = (colors[1] + colors[5]) / 2;
			colors[10] = (colors[2] + colors[6]) / 2;
			colors[11] = 255;
			
			colors[12] = 0;
			colors[13] = 0;
			colors[14] = 0;
			colors[15] = 0;
		}

		for (uint32_t ii = 0, next = 8*4; ii < 16*4; ii += 4, next += 2)
		{
			int idx = ( (_src[next>>3] >> (next & 7) ) & 3) * 4;
			_dst[ii+0] = colors[idx+0];
			_dst[ii+1] = colors[idx+1];
			_dst[ii+2] = colors[idx+2];
			_dst[ii+3] = colors[idx+3];
		}
	}

	void decodeBlockDxt23A(uint8_t _dst[16*4], const uint8_t _src[8])
	{
		for (uint32_t ii = 0, next = 0; ii < 16*4; ii += 4, next += 4)
		{
			uint32_t c0 = (_src[next>>3] >> (next&7) ) & 0xf;
			_dst[ii] = bitRangeConvert(c0, 4, 8);
		}
	}

	void decodeBlockDxt45A(uint8_t _dst[16*4], const uint8_t _src[8])
	{
		uint8_t alpha[8];
		alpha[0] = _src[0];
		alpha[1] = _src[1];

		if (alpha[0] > alpha[1])
		{
			alpha[2] = (6*alpha[0] + 1*alpha[1]) / 7;
			alpha[3] = (5*alpha[0] + 2*alpha[1]) / 7;
			alpha[4] = (4*alpha[0] + 3*alpha[1]) / 7;
			alpha[5] = (3*alpha[0] + 4*alpha[1]) / 7;
			alpha[6] = (2*alpha[0] + 5*alpha[1]) / 7;
			alpha[7] = (1*alpha[0] + 6*alpha[1]) / 7;
		}
		else
		{
			alpha[2] = (4*alpha[0] + 1*alpha[1]) / 5;
			alpha[3] = (3*alpha[0] + 2*alpha[1]) / 5;
			alpha[4] = (2*alpha[0] + 3*alpha[1]) / 5;
			alpha[5] = (1*alpha[0] + 4*alpha[1]) / 5;
			alpha[6] = 0;
			alpha[7] = 255;
		}

		uint32_t idx0 = _src[2];
		uint32_t idx1 = _src[5];
		idx0 |= uint32_t(_src[3])<<8;
		idx1 |= uint32_t(_src[6])<<8;
		idx0 |= uint32_t(_src[4])<<16;
		idx1 |= uint32_t(_src[7])<<16;
		for (uint32_t ii = 0; ii < 8*4; ii += 4)
		{
			_dst[ii]    = alpha[idx0&7];
			_dst[ii+32] = alpha[idx1&7];
			idx0 >>= 3;
			idx1 >>= 3;
		}
	}

	static const int32_t s_etc1Mod[8][4] =
	{
		{  2,   8,  -2,   -8},
		{  5,  17,  -5,  -17},
		{  9,  29,  -9,  -29},
		{ 13,  42, -13,  -42},
		{ 18,  60, -18,  -60},
		{ 24,  80, -24,  -80},
		{ 33, 106, -33, -106},
		{ 47, 183, -47, -183},
	};

	static const uint8_t s_etc2Mod[8] = { 3, 6, 11, 16, 23, 32, 41, 64 };

	uint8_t uint8_sat(int32_t _a)
	{
		using namespace bx;
		const uint32_t min    = uint32_imin(_a, 255);
		const uint32_t result = uint32_imax(min, 0);
		return (uint8_t)result;
	}

	uint8_t uint8_satadd(int32_t _a, int32_t _b)
	{
		const int32_t add = _a + _b;
		return uint8_sat(add);
	}

	void decodeBlockEtc2ModeT(uint8_t _dst[16*4], const uint8_t _src[8])
	{
		uint8_t rgb[16];

		// 0       1       2       3       4       5       6       7
		// 7654321076543210765432107654321076543210765432107654321076543210
		// ...rr.rrggggbbbbrrrrggggbbbbDDD.mmmmmmmmmmmmmmmmllllllllllllllll
		//    ^            ^           ^   ^               ^
		//    +-- c0       +-- c1      |   +-- msb         +-- lsb
		//                             +-- dist

		rgb[ 0] = ( (_src[0] >> 1) & 0xc)
			    | (_src[0] & 0x3)
			    ;
		rgb[ 1] = _src[1] >> 4;
		rgb[ 2] = _src[1] & 0xf;

		rgb[ 8] = _src[2] >> 4;
		rgb[ 9] = _src[2] & 0xf;
		rgb[10] = _src[3] >> 4;

		rgb[ 0] = bitRangeConvert(rgb[ 0], 4, 8);
		rgb[ 1] = bitRangeConvert(rgb[ 1], 4, 8);
		rgb[ 2] = bitRangeConvert(rgb[ 2], 4, 8);
		rgb[ 8] = bitRangeConvert(rgb[ 8], 4, 8);
		rgb[ 9] = bitRangeConvert(rgb[ 9], 4, 8);
		rgb[10] = bitRangeConvert(rgb[10], 4, 8);

		uint8_t dist = (_src[3] >> 1) & 0x7;
		int32_t mod = s_etc2Mod[dist];

		rgb[ 4] = uint8_satadd(rgb[ 8],  mod);
		rgb[ 5] = uint8_satadd(rgb[ 9],  mod);
		rgb[ 6] = uint8_satadd(rgb[10],  mod);

		rgb[12] = uint8_satadd(rgb[ 8], -mod);
		rgb[13] = uint8_satadd(rgb[ 9], -mod);
		rgb[14] = uint8_satadd(rgb[10], -mod);

		uint32_t indexMsb = (_src[4]<<8) | _src[5];
		uint32_t indexLsb = (_src[6]<<8) | _src[7];

		for (uint32_t ii = 0; ii < 16; ++ii)
		{
			const uint32_t idx  = (ii&0xc) | ( (ii & 0x3)<<4);
			const uint32_t lsbi = indexLsb & 1;
			const uint32_t msbi = (indexMsb & 1)<<1;
			const uint32_t pal  = (lsbi | msbi)<<2;

			_dst[idx + 0] = rgb[pal+2];
			_dst[idx + 1] = rgb[pal+1];
			_dst[idx + 2] = rgb[pal+0];
			_dst[idx + 3] = 255;

			indexLsb >>= 1;
			indexMsb >>= 1;
		}
	}

	void decodeBlockEtc2ModeH(uint8_t _dst[16*4], const uint8_t _src[8])
	{
		uint8_t rgb[16];

		// 0       1       2       3       4       5       6       7
		// 7654321076543210765432107654321076543210765432107654321076543210
		// .rrrrggg...gb.bbbrrrrggggbbbbDD.mmmmmmmmmmmmmmmmllllllllllllllll
		//  ^               ^           ^  ^               ^
		//  +-- c0          +-- c1      |  +-- msb         +-- lsb
		//                              +-- dist

		rgb[ 0] = (_src[0] >> 3) & 0xf;
		rgb[ 1] = ( (_src[0] << 1) & 0xe)
				| ( (_src[1] >> 4) & 0x1)
				;
		rgb[ 2] = (_src[1] & 0x8)
				| ( (_src[1] << 1) & 0x6)
				| (_src[2] >> 7)
				;

		rgb[ 8] = (_src[2] >> 3) & 0xf;
		rgb[ 9] = ( (_src[2] << 1) & 0xe)
				| (_src[3] >> 7)
				;
		rgb[10] = (_src[2] >> 3) & 0xf;

		rgb[ 0] = bitRangeConvert(rgb[ 0], 4, 8);
		rgb[ 1] = bitRangeConvert(rgb[ 1], 4, 8);
		rgb[ 2] = bitRangeConvert(rgb[ 2], 4, 8);
		rgb[ 8] = bitRangeConvert(rgb[ 8], 4, 8);
		rgb[ 9] = bitRangeConvert(rgb[ 9], 4, 8);
		rgb[10] = bitRangeConvert(rgb[10], 4, 8);

		uint32_t col0 = uint32_t(rgb[0]<<16) | uint32_t(rgb[1]<<8) | uint32_t(rgb[ 2]);
		uint32_t col1 = uint32_t(rgb[8]<<16) | uint32_t(rgb[9]<<8) | uint32_t(rgb[10]);
		uint8_t dist = (_src[3] & 0x6) | (col0 >= col1);
		int32_t mod = s_etc2Mod[dist];

		rgb[ 4] = uint8_satadd(rgb[ 0], -mod);
		rgb[ 5] = uint8_satadd(rgb[ 1], -mod);
		rgb[ 6] = uint8_satadd(rgb[ 2], -mod);

		rgb[ 0] = uint8_satadd(rgb[ 0],  mod);
		rgb[ 1] = uint8_satadd(rgb[ 1],  mod);
		rgb[ 2] = uint8_satadd(rgb[ 2],  mod);

		rgb[12] = uint8_satadd(rgb[ 8], -mod);
		rgb[13] = uint8_satadd(rgb[ 9], -mod);
		rgb[14] = uint8_satadd(rgb[10], -mod);

		rgb[ 8] = uint8_satadd(rgb[ 8],  mod);
		rgb[ 9] = uint8_satadd(rgb[ 9],  mod);
		rgb[10] = uint8_satadd(rgb[10],  mod);

		uint32_t indexMsb = (_src[4]<<8) | _src[5];
		uint32_t indexLsb = (_src[6]<<8) | _src[7];

		for (uint32_t ii = 0; ii < 16; ++ii)
		{
			const uint32_t idx  = (ii&0xc) | ( (ii & 0x3)<<4);
			const uint32_t lsbi = indexLsb & 1;
			const uint32_t msbi = (indexMsb & 1)<<1;
			const uint32_t pal  = (lsbi | msbi)<<2;

			_dst[idx + 0] = rgb[pal+2];
			_dst[idx + 1] = rgb[pal+1];
			_dst[idx + 2] = rgb[pal+0];
			_dst[idx + 3] = 255;

			indexLsb >>= 1;
			indexMsb >>= 1;
		}
	}

	void decodeBlockEtc2ModePlanar(uint8_t _dst[16*4], const uint8_t _src[8])
	{
		// 0       1       2       3       4       5       6       7
		// 7654321076543210765432107654321076543210765432107654321076543210
		// .rrrrrrg.ggggggb...bb.bbbrrrrr.rgggggggbbbbbbrrrrrrgggggggbbbbbb
		//  ^                       ^                   ^
		//  +-- c0                  +-- cH              +-- cV

		uint8_t c0[3];
		uint8_t cH[3];
		uint8_t cV[3];

		c0[0] = (_src[0] >> 1) & 0x3f;
		c0[1] = ( (_src[0] & 1) << 6) 
			  | ( (_src[1] >> 1) & 0x3f)
			  ;
		c0[2] = ( (_src[1] & 1) << 5)
			  | ( (_src[2] & 0x18) )
			  | ( (_src[2] << 1) & 6)
			  | ( (_src[3] >> 7) )
			  ;

		cH[0] = ( (_src[3] >> 1) & 0x3e)
			  | (_src[3] & 1)
			  ;
		cH[1] = _src[4] >> 1;
		cH[2] = ( (_src[4] & 1) << 5)
			  | (_src[5] >> 3)
			  ;

		cV[0] = ( (_src[5] & 0x7) << 3)
			  | (_src[6] >> 5)
			  ;
		cV[1] = ( (_src[6] & 0x1f) << 2)
			  | (_src[7] >> 5)
			  ;
		cV[2] = _src[7] & 0x3f;

		c0[0] = bitRangeConvert(c0[0], 6, 8);
		c0[1] = bitRangeConvert(c0[1], 7, 8);
		c0[2] = bitRangeConvert(c0[2], 6, 8);

		cH[0] = bitRangeConvert(cH[0], 6, 8);
		cH[1] = bitRangeConvert(cH[1], 7, 8);
		cH[2] = bitRangeConvert(cH[2], 6, 8);

		cV[0] = bitRangeConvert(cV[0], 6, 8);
		cV[1] = bitRangeConvert(cV[1], 7, 8);
		cV[2] = bitRangeConvert(cV[2], 6, 8);

		int16_t dy[3];
		dy[0] = cV[0] - c0[0];
		dy[1] = cV[1] - c0[1];
		dy[2] = cV[2] - c0[2];

		int16_t sx[3];
		sx[0] = int16_t(c0[0])<<2;
		sx[1] = int16_t(c0[1])<<2;
		sx[2] = int16_t(c0[2])<<2;

		int16_t ex[3];
		ex[0] = int16_t(cH[0])<<2;
		ex[1] = int16_t(cH[1])<<2;
		ex[2] = int16_t(cH[2])<<2;

		for (int32_t vv = 0; vv < 4; ++vv)
		{
			int16_t dx[3];
			dx[0] = (ex[0] - sx[0])>>2;
			dx[1] = (ex[1] - sx[1])>>2;
			dx[2] = (ex[2] - sx[2])>>2;

			for (int32_t hh = 0; hh < 4; ++hh)
			{
				const uint32_t idx  = (vv<<4) + (hh<<2);

				_dst[idx + 0] = uint8_sat( (sx[2] + dx[2]*hh)>>2);
				_dst[idx + 1] = uint8_sat( (sx[1] + dx[1]*hh)>>2);
				_dst[idx + 2] = uint8_sat( (sx[0] + dx[0]*hh)>>2);
				_dst[idx + 3] = 255;
			}

			sx[0] += dy[0];
			sx[1] += dy[1];
			sx[2] += dy[2];

			ex[0] += dy[0];
			ex[1] += dy[1];
			ex[2] += dy[2];
		}
	}

	void decodeBlockEtc12(uint8_t _dst[16*4], const uint8_t _src[8])
	{
		bool flipBit = 0 != (_src[3] & 0x1);
		bool diffBit = 0 != (_src[3] & 0x2);

		uint8_t rgb[8];

		if (diffBit)
		{
			rgb[0]  = _src[0] >> 3;
			rgb[1]  = _src[1] >> 3;
			rgb[2]  = _src[2] >> 3;

			int8_t diff[3];
			diff[0] = int8_t( (_src[0] & 0x7)<<5)>>5;
			diff[1] = int8_t( (_src[1] & 0x7)<<5)>>5;
			diff[2] = int8_t( (_src[2] & 0x7)<<5)>>5;

			int8_t rr = rgb[0] + diff[0];
			int8_t gg = rgb[1] + diff[1];
			int8_t bb = rgb[2] + diff[2];

			// Etc2 3-modes
			if (rr < 0 || rr > 31)
			{
				decodeBlockEtc2ModeT(_dst, _src);
				return;
			}
			if (gg < 0 || gg > 31)
			{
				decodeBlockEtc2ModeH(_dst, _src);
				return;
			}
			if (bb < 0 || bb > 31)
			{
				decodeBlockEtc2ModePlanar(_dst, _src);
				return;
			}

			// Etc1
			rgb[0] = bitRangeConvert(rgb[0], 5, 8);
			rgb[1] = bitRangeConvert(rgb[1], 5, 8);
			rgb[2] = bitRangeConvert(rgb[2], 5, 8);
			rgb[4] = bitRangeConvert(rr, 5, 8);
			rgb[5] = bitRangeConvert(gg, 5, 8);
			rgb[6] = bitRangeConvert(bb, 5, 8);
		}
		else
		{
			rgb[0] = _src[0] >> 4;
			rgb[1] = _src[1] >> 4;
			rgb[2] = _src[2] >> 4;

			rgb[4] = _src[0] & 0xf;
			rgb[5] = _src[1] & 0xf;
			rgb[6] = _src[2] & 0xf;

			rgb[0] = bitRangeConvert(rgb[0], 4, 8);
			rgb[1] = bitRangeConvert(rgb[1], 4, 8);
			rgb[2] = bitRangeConvert(rgb[2], 4, 8);
			rgb[4] = bitRangeConvert(rgb[4], 4, 8);
			rgb[5] = bitRangeConvert(rgb[5], 4, 8);
			rgb[6] = bitRangeConvert(rgb[6], 4, 8);
		}

		uint32_t table[2];
		table[0] = (_src[3] >> 5) & 0x7;
		table[1] = (_src[3] >> 2) & 0x7;

		uint32_t indexMsb = (_src[4]<<8) | _src[5];
		uint32_t indexLsb = (_src[6]<<8) | _src[7];

		if (flipBit)
		{
			for (uint32_t ii = 0; ii < 16; ++ii)
			{
				const uint32_t block = (ii>>1)&1;
				const uint32_t color = block<<2;
				const uint32_t idx   = (ii&0xc) | ( (ii & 0x3)<<4);
				const uint32_t lsbi  = indexLsb & 1;
				const uint32_t msbi  = (indexMsb & 1)<<1;
				const  int32_t mod   = s_etc1Mod[table[block] ][lsbi | msbi];

				_dst[idx + 0] = uint8_satadd(rgb[color+2], mod);
				_dst[idx + 1] = uint8_satadd(rgb[color+1], mod);
				_dst[idx + 2] = uint8_satadd(rgb[color+0], mod);
				_dst[idx + 3] = 255;

				indexLsb >>= 1;
				indexMsb >>= 1;
			}
		}
		else
		{
			for (uint32_t ii = 0; ii < 16; ++ii)
			{
				const uint32_t block = ii>>3;
				const uint32_t color = block<<2;
				const uint32_t idx   = (ii&0xc) | ( (ii & 0x3)<<4);
				const uint32_t lsbi  = indexLsb & 1;
				const uint32_t msbi  = (indexMsb & 1)<<1;
				const  int32_t mod   = s_etc1Mod[table[block] ][lsbi | msbi];

				_dst[idx + 0] = uint8_satadd(rgb[color+2], mod);
				_dst[idx + 1] = uint8_satadd(rgb[color+1], mod);
				_dst[idx + 2] = uint8_satadd(rgb[color+0], mod);
				_dst[idx + 3] = 255;

				indexLsb >>= 1;
				indexMsb >>= 1;
			}
		}
	}

// DDS
#define DDS_MAGIC             BX_MAKEFOURCC('D', 'D', 'S', ' ')
#define DDS_HEADER_SIZE       124
#define DDS_IMAGE_DATA_OFFSET (DDS_HEADER_SIZE + 4)

#define DDS_DXT1 BX_MAKEFOURCC('D', 'X', 'T', '1')
#define DDS_DXT2 BX_MAKEFOURCC('D', 'X', 'T', '2')
#define DDS_DXT3 BX_MAKEFOURCC('D', 'X', 'T', '3')
#define DDS_DXT4 BX_MAKEFOURCC('D', 'X', 'T', '4')
#define DDS_DXT5 BX_MAKEFOURCC('D', 'X', 'T', '5')
#define DDS_ATI1 BX_MAKEFOURCC('A', 'T', 'I', '1')
#define DDS_BC4U BX_MAKEFOURCC('B', 'C', '4', 'U')
#define DDS_ATI2 BX_MAKEFOURCC('A', 'T', 'I', '2')
#define DDS_BC5U BX_MAKEFOURCC('B', 'C', '5', 'U')

#define D3DFMT_A16B16G16R16  36
#define D3DFMT_A16B16G16R16F 113

#define DDSD_CAPS                   0x00000001
#define DDSD_HEIGHT                 0x00000002
#define DDSD_WIDTH                  0x00000004
#define DDSD_PITCH                  0x00000008
#define DDSD_PIXELFORMAT            0x00001000
#define DDSD_MIPMAPCOUNT            0x00020000
#define DDSD_LINEARSIZE             0x00080000
#define DDSD_DEPTH                  0x00800000

#define DDPF_ALPHAPIXELS            0x00000001
#define DDPF_ALPHA                  0x00000002
#define DDPF_FOURCC                 0x00000004
#define DDPF_INDEXED                0x00000020
#define DDPF_RGB                    0x00000040
#define DDPF_YUV                    0x00000200
#define DDPF_LUMINANCE              0x00020000

#define DDSCAPS_COMPLEX             0x00000008
#define DDSCAPS_TEXTURE             0x00001000
#define DDSCAPS_MIPMAP              0x00400000

#define DDSCAPS2_CUBEMAP            0x00000200
#define DDSCAPS2_CUBEMAP_POSITIVEX  0x00000400
#define DDSCAPS2_CUBEMAP_NEGATIVEX  0x00000800
#define DDSCAPS2_CUBEMAP_POSITIVEY  0x00001000
#define DDSCAPS2_CUBEMAP_NEGATIVEY  0x00002000
#define DDSCAPS2_CUBEMAP_POSITIVEZ  0x00004000
#define DDSCAPS2_CUBEMAP_NEGATIVEZ  0x00008000

#define DDS_CUBEMAP_ALLFACES (DDSCAPS2_CUBEMAP_POSITIVEX|DDSCAPS2_CUBEMAP_NEGATIVEX \
							 |DDSCAPS2_CUBEMAP_POSITIVEY|DDSCAPS2_CUBEMAP_NEGATIVEY \
							 |DDSCAPS2_CUBEMAP_POSITIVEZ|DDSCAPS2_CUBEMAP_NEGATIVEZ)

#define DDSCAPS2_VOLUME             0x00200000

	static struct TranslateDdsFormat
	{
		uint32_t m_format;
		TextureFormat::Enum m_textureFormat;

	} s_translateDdsFormat[] =
	{
		{ DDS_DXT1,                  TextureFormat::BC1     },
		{ DDS_DXT2,                  TextureFormat::BC2     },
		{ DDS_DXT3,                  TextureFormat::BC2     },
		{ DDS_DXT4,                  TextureFormat::BC3     },
		{ DDS_DXT5,                  TextureFormat::BC3     },
		{ DDS_ATI1,                  TextureFormat::BC4     },
		{ DDS_BC4U,                  TextureFormat::BC4     },
		{ DDS_ATI2,                  TextureFormat::BC5     },
		{ DDS_BC5U,                  TextureFormat::BC5     },
		{ D3DFMT_A16B16G16R16,       TextureFormat::RGBA16  },
		{ D3DFMT_A16B16G16R16F,      TextureFormat::RGBA16F },
		{ DDPF_RGB|DDPF_ALPHAPIXELS, TextureFormat::BGRA8   },
		{ DDPF_INDEXED,              TextureFormat::L8      },
		{ DDPF_LUMINANCE,            TextureFormat::L8      },
		{ DDPF_ALPHA,                TextureFormat::L8      },
	};

	bool imageParseDds(ImageContainer& _imageContainer, bx::ReaderSeekerI* _reader)
	{
		uint32_t headerSize;
		bx::read(_reader, headerSize);

		if (headerSize < DDS_HEADER_SIZE)
		{
			return false;
		}

		uint32_t flags;
		bx::read(_reader, flags);

		if ( (flags & (DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH|DDSD_PIXELFORMAT) ) != (DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH|DDSD_PIXELFORMAT) )
		{
			return false;
		}

		uint32_t height;
		bx::read(_reader, height);

		uint32_t width;
		bx::read(_reader, width);

		uint32_t pitch;
		bx::read(_reader, pitch);

		uint32_t depth;
		bx::read(_reader, depth);

		uint32_t mips;
		bx::read(_reader, mips);

		bx::skip(_reader, 44); // reserved
		bx::skip(_reader, 4); // pixel format size

		uint32_t pixelFlags;
		bx::read(_reader, pixelFlags);

		uint32_t fourcc;
		bx::read(_reader, fourcc);

		uint32_t rgbCount;
		bx::read(_reader, rgbCount);

		uint32_t rbitmask;
		bx::read(_reader, rbitmask);

		uint32_t gbitmask;
		bx::read(_reader, gbitmask);

		uint32_t bbitmask;
		bx::read(_reader, bbitmask);

		uint32_t abitmask;
		bx::read(_reader, abitmask);

		uint32_t caps[4];
		bx::read(_reader, caps);

		if ( (caps[0] & DDSCAPS_TEXTURE) == 0)
		{
			return false;
		}

		bool cubeMap = 0 != (caps[1] & DDSCAPS2_CUBEMAP);
		if (cubeMap)
		{
			if ( (caps[1] & DDS_CUBEMAP_ALLFACES) != DDS_CUBEMAP_ALLFACES)
			{
				// parital cube map is not supported.
				return false;
			}
		}

		bx::skip(_reader, 4); // reserved

		uint8_t bpp = 0;
		uint8_t blockSize = 1;
		TextureFormat::Enum format = TextureFormat::Unknown;
		bool hasAlpha = pixelFlags & DDPF_ALPHAPIXELS;

		uint32_t ddsFormat = pixelFlags & DDPF_FOURCC ? fourcc : pixelFlags;
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_translateDdsFormat); ++ii)
		{
			if (s_translateDdsFormat[ii].m_format == ddsFormat)
			{
				format = s_translateDdsFormat[ii].m_textureFormat;
				break;
			}
		}

		bpp = getBitsPerPixel(format);
		blockSize = format < TextureFormat::Unknown ? 4*4 : 1;
		blockSize = blockSize*bpp/8;

		_imageContainer.m_data = NULL;
		_imageContainer.m_size = 0;
		_imageContainer.m_offset = DDS_IMAGE_DATA_OFFSET;
		_imageContainer.m_width = width;
		_imageContainer.m_height = height;
		_imageContainer.m_depth = depth;
		_imageContainer.m_format = format;
		_imageContainer.m_blockSize = blockSize;
		_imageContainer.m_numMips = (caps[0] & DDSCAPS_MIPMAP) ? mips : 1;
		_imageContainer.m_bpp = bpp;
		_imageContainer.m_hasAlpha = hasAlpha;
		_imageContainer.m_cubeMap = cubeMap;
		_imageContainer.m_ktx = false;

		return TextureFormat::Unknown != format;
	}

// KTX
#define KTX_MAGIC       BX_MAKEFOURCC(0xAB, 'K', 'T', 'X')
#define KTX_HEADER_SIZE 64

#define KTX_ETC1_RGB8_OES                             0x8D64
#define KTX_COMPRESSED_R11_EAC                        0x9270
#define KTX_COMPRESSED_SIGNED_R11_EAC                 0x9271
#define KTX_COMPRESSED_RG11_EAC                       0x9272
#define KTX_COMPRESSED_SIGNED_RG11_EAC                0x9273
#define KTX_COMPRESSED_RGB8_ETC2                      0x9274
#define KTX_COMPRESSED_SRGB8_ETC2                     0x9275
#define KTX_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2  0x9276
#define KTX_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#define KTX_COMPRESSED_RGBA8_ETC2_EAC                 0x9278
#define KTX_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC          0x9279
#define KTX_COMPRESSED_RGB_PVRTC_4BPPV1_IMG           0x8C00
#define KTX_COMPRESSED_RGB_PVRTC_2BPPV1_IMG           0x8C01
#define KTX_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG          0x8C02
#define KTX_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG          0x8C03
#define KTX_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG          0x9137
#define KTX_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG          0x9138
#define KTX_COMPRESSED_RGBA_S3TC_DXT1_EXT             0x83F1
#define KTX_COMPRESSED_RGBA_S3TC_DXT3_EXT             0x83F2
#define KTX_COMPRESSED_RGBA_S3TC_DXT5_EXT             0x83F3
#define KTX_COMPRESSED_LUMINANCE_LATC1_EXT            0x8C70
#define KTX_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT      0x8C72
#define KTX_RGBA16                                    0x805B
#define KTX_RGBA16F                                   0x881A

	static struct TranslateKtxFormat
	{
		uint32_t m_format;
		TextureFormat::Enum m_textureFormat;

	} s_translateKtxFormat[] =
	{
		{ KTX_COMPRESSED_RGBA_S3TC_DXT1_EXT,             TextureFormat::BC1     },
		{ KTX_COMPRESSED_RGBA_S3TC_DXT3_EXT,             TextureFormat::BC2     },
		{ KTX_COMPRESSED_RGBA_S3TC_DXT5_EXT,             TextureFormat::BC3     },
		{ KTX_COMPRESSED_LUMINANCE_LATC1_EXT,            TextureFormat::BC4     },
		{ KTX_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT,      TextureFormat::BC5     },
		{ KTX_ETC1_RGB8_OES,                             TextureFormat::ETC1    },
		{ KTX_COMPRESSED_RGB8_ETC2,                      TextureFormat::ETC2    },
		{ KTX_COMPRESSED_RGBA8_ETC2_EAC,                 TextureFormat::ETC2A   },
		{ KTX_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2,  TextureFormat::ETC2A1  },
		{ KTX_COMPRESSED_RGB_PVRTC_2BPPV1_IMG,           TextureFormat::PTC12   },
		{ KTX_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG,          TextureFormat::PTC12A  },
		{ KTX_COMPRESSED_RGB_PVRTC_4BPPV1_IMG,           TextureFormat::PTC14   },
		{ KTX_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG,          TextureFormat::PTC14A  },
		{ KTX_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG,          TextureFormat::PTC22   },
		{ KTX_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG,          TextureFormat::PTC24   },
		{ KTX_RGBA16,                                    TextureFormat::RGBA16  },
		{ KTX_RGBA16F,                                   TextureFormat::RGBA16F },
		{ KTX_COMPRESSED_R11_EAC,                        TextureFormat::Unknown },
		{ KTX_COMPRESSED_SIGNED_R11_EAC,                 TextureFormat::Unknown },
		{ KTX_COMPRESSED_RG11_EAC,                       TextureFormat::Unknown },
		{ KTX_COMPRESSED_SIGNED_RG11_EAC,                TextureFormat::Unknown },
		{ KTX_COMPRESSED_SRGB8_ETC2,                     TextureFormat::Unknown },
		{ KTX_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2, TextureFormat::Unknown },
		{ KTX_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC,          TextureFormat::Unknown },
	};

	bool imageParseKtx(ImageContainer& _imageContainer, bx::ReaderSeekerI* _reader)
	{
		uint8_t identifier[8];
		bx::read(_reader, identifier);

		if (identifier[1] != '1'
		&&  identifier[2] != '1')
		{
			return false;
		}

		uint32_t endianness;
		bx::read(_reader, endianness);

		bool fromLittleEndian = 0x04030201 == endianness;

		uint32_t glType;
		bx::readHE(_reader, glType, fromLittleEndian);

		uint32_t glTypeSize;
		bx::readHE(_reader, glTypeSize, fromLittleEndian);

		uint32_t glFormat;
		bx::readHE(_reader, glFormat, fromLittleEndian);

		uint32_t glInternalFormat;
		bx::readHE(_reader, glInternalFormat, fromLittleEndian);

		uint32_t glBaseInternalFormat;
		bx::readHE(_reader, glBaseInternalFormat, fromLittleEndian);

		uint32_t width;
		bx::readHE(_reader, width, fromLittleEndian);

		uint32_t height;
		bx::readHE(_reader, height, fromLittleEndian);

		uint32_t depth;
		bx::readHE(_reader, depth, fromLittleEndian);

		uint32_t numberOfArrayElements;
		bx::readHE(_reader, numberOfArrayElements, fromLittleEndian);

		uint32_t numFaces;
		bx::readHE(_reader, numFaces, fromLittleEndian);

		uint32_t numMips;
		bx::readHE(_reader, numMips, fromLittleEndian);

		uint32_t metaDataSize;
		bx::readHE(_reader, metaDataSize, fromLittleEndian);

		// skip meta garbage...
		int64_t offset = bx::skip(_reader, metaDataSize);

		uint8_t bpp = 0;
		uint8_t blockSize = 1;
		TextureFormat::Enum format = TextureFormat::Unknown;
		bool hasAlpha = false;

		for (uint32_t ii = 0; ii < BX_COUNTOF(s_translateKtxFormat); ++ii)
		{
			if (s_translateKtxFormat[ii].m_format == glInternalFormat)
			{
				format = s_translateKtxFormat[ii].m_textureFormat;
				break;
			}
		}

		bpp = getBitsPerPixel(format);
		blockSize = format < TextureFormat::Unknown ? 4*4 : 1;
		blockSize = blockSize*bpp/8;

		_imageContainer.m_data = NULL;
		_imageContainer.m_size = 0;
		_imageContainer.m_offset = (uint32_t)offset;
		_imageContainer.m_width = width;
		_imageContainer.m_height = height;
		_imageContainer.m_depth = depth;
		_imageContainer.m_format = format;
		_imageContainer.m_blockSize = blockSize;
		_imageContainer.m_numMips = numMips;
		_imageContainer.m_bpp = bpp;
		_imageContainer.m_hasAlpha = hasAlpha;
		_imageContainer.m_cubeMap = numFaces > 1;
		_imageContainer.m_ktx = true;

		return TextureFormat::Unknown != format;
	}

// PVR3
#define PVR3_MAKE8CC(_a, _b, _c, _d, _e, _f, _g, _h) (uint64_t(BX_MAKEFOURCC(_a, _b, _c, _d) ) | (uint64_t(BX_MAKEFOURCC(_e, _f, _g, _h) )<<32) )

#define PVR3_MAGIC            BX_MAKEFOURCC('P', 'V', 'R', 3)
#define PVR3_HEADER_SIZE      52

#define PVR3_PVRTC1_2BPP_RGB  0
#define PVR3_PVRTC1_2BPP_RGBA 1
#define PVR3_PVRTC1_4BPP_RGB  2
#define PVR3_PVRTC1_4BPP_RGBA 3
#define PVR3_PVRTC2_2BPP_RGBA 4
#define PVR3_PVRTC2_4BPP_RGBA 5
#define PVR3_ETC1             6
#define PVR3_DXT1             7
#define PVR3_DXT2             8
#define PVR3_DXT3             9
#define PVR3_DXT4             10
#define PVR3_DXT5             11
#define PVR3_BC4              12
#define PVR3_BC5              13
#define PVR3_RGBA16           PVR3_MAKE8CC('r', 'g', 'b', 'a', 16, 16, 16, 16)

#define PVR3_CHANNEL_TYPE_ANY   UINT32_MAX
#define PVR3_CHANNEL_TYPE_FLOAT UINT32_C(12)

	static struct TranslatePvr3Format
	{
		uint64_t m_format;
		uint32_t m_channelTypeMask;
		TextureFormat::Enum m_textureFormat;

	} s_translatePvr3Format[] =
	{
		{ PVR3_PVRTC1_2BPP_RGB,  PVR3_CHANNEL_TYPE_ANY,   TextureFormat::PTC12   },
		{ PVR3_PVRTC1_2BPP_RGBA, PVR3_CHANNEL_TYPE_ANY,   TextureFormat::PTC12A  },
		{ PVR3_PVRTC1_4BPP_RGB,  PVR3_CHANNEL_TYPE_ANY,   TextureFormat::PTC14   },
		{ PVR3_PVRTC1_4BPP_RGBA, PVR3_CHANNEL_TYPE_ANY,   TextureFormat::PTC14A  },
		{ PVR3_PVRTC2_2BPP_RGBA, PVR3_CHANNEL_TYPE_ANY,   TextureFormat::PTC22   },
		{ PVR3_PVRTC2_4BPP_RGBA, PVR3_CHANNEL_TYPE_ANY,   TextureFormat::PTC24   },
		{ PVR3_ETC1,             PVR3_CHANNEL_TYPE_ANY,   TextureFormat::ETC1    },
		{ PVR3_DXT1,             PVR3_CHANNEL_TYPE_ANY,   TextureFormat::BC1     },
		{ PVR3_DXT2,             PVR3_CHANNEL_TYPE_ANY,   TextureFormat::BC2     },
		{ PVR3_DXT3,             PVR3_CHANNEL_TYPE_ANY,   TextureFormat::BC2     },
		{ PVR3_DXT4,             PVR3_CHANNEL_TYPE_ANY,   TextureFormat::BC3     },
		{ PVR3_DXT5,             PVR3_CHANNEL_TYPE_ANY,   TextureFormat::BC3     },
		{ PVR3_BC4,              PVR3_CHANNEL_TYPE_ANY,   TextureFormat::BC4     },
		{ PVR3_BC5,              PVR3_CHANNEL_TYPE_ANY,   TextureFormat::BC5     },
		{ PVR3_RGBA16,           PVR3_CHANNEL_TYPE_FLOAT, TextureFormat::RGBA16F },
		{ PVR3_RGBA16,           PVR3_CHANNEL_TYPE_ANY,   TextureFormat::RGBA16  },
	};

	bool imageParsePvr3(ImageContainer& _imageContainer, bx::ReaderSeekerI* _reader)
	{
		uint32_t flags;
		bx::read(_reader, flags);

		uint64_t pixelFormat;
		bx::read(_reader, pixelFormat);

		uint32_t colorSpace;
		bx::read(_reader, colorSpace); // 0 - linearRGB, 1 - sRGB

		uint32_t channelType;
		bx::read(_reader, channelType);

		uint32_t height;
		bx::read(_reader, height);

		uint32_t width;
		bx::read(_reader, width);

		uint32_t depth;
		bx::read(_reader, depth);

		uint32_t numSurfaces;
		bx::read(_reader, numSurfaces);

		uint32_t numFaces;
		bx::read(_reader, numFaces);

		uint32_t numMips;
		bx::read(_reader, numMips);

		uint32_t metaDataSize;
		bx::read(_reader, metaDataSize);

		// skip meta garbage...
		int64_t offset = bx::skip(_reader, metaDataSize);

		uint8_t bpp = 0;
		uint8_t blockSize = 1;
		TextureFormat::Enum format = TextureFormat::Unknown;
		bool hasAlpha = false;

		for (uint32_t ii = 0; ii < BX_COUNTOF(s_translatePvr3Format); ++ii)
		{
			if (s_translatePvr3Format[ii].m_format == pixelFormat
			&&  channelType == (s_translatePvr3Format[ii].m_channelTypeMask & channelType) )
			{
				format = s_translatePvr3Format[ii].m_textureFormat;
				break;
			}
		}

		bpp = getBitsPerPixel(format);
		blockSize = format < TextureFormat::Unknown ? 4*4 : 1;
		blockSize = blockSize*bpp/8;

		_imageContainer.m_data = NULL;
		_imageContainer.m_size = 0;
		_imageContainer.m_offset = (uint32_t)offset;
		_imageContainer.m_width = width;
		_imageContainer.m_height = height;
		_imageContainer.m_depth = depth;
		_imageContainer.m_format = format;
		_imageContainer.m_blockSize = blockSize;
		_imageContainer.m_numMips = numMips;
		_imageContainer.m_bpp = bpp;
		_imageContainer.m_hasAlpha = hasAlpha;
		_imageContainer.m_cubeMap = numFaces > 1;
		_imageContainer.m_ktx = false;

		return TextureFormat::Unknown != format;
	}

	bool imageParse(ImageContainer& _imageContainer, bx::ReaderSeekerI* _reader)
	{
		uint32_t magic;
		bx::read(_reader, magic);

		if (DDS_MAGIC == magic)
		{
			return imageParseDds(_imageContainer, _reader);
		}
		else if (KTX_MAGIC == magic)
		{
			return imageParseKtx(_imageContainer, _reader);
		}
		else if (PVR3_MAGIC == magic)
		{
			return imageParsePvr3(_imageContainer, _reader);
		}
		else if (BGFX_CHUNK_MAGIC_TEX == magic)
		{
			TextureCreate tc;
			bx::read(_reader, tc);

			uint32_t bpp = getBitsPerPixel(TextureFormat::Enum(tc.m_format) );
			uint32_t blockSize = tc.m_format < TextureFormat::Unknown ? 4*4 : 1;
			blockSize = blockSize*bpp/8;

			_imageContainer.m_format = tc.m_format;
			_imageContainer.m_offset = UINT32_MAX;
			if (NULL == tc.m_mem)
			{
				_imageContainer.m_data = NULL;
				_imageContainer.m_size = 0;
			}
			else
			{
				_imageContainer.m_data = tc.m_mem->data;
				_imageContainer.m_size = tc.m_mem->size;
			}
			_imageContainer.m_width = tc.m_width;
			_imageContainer.m_height = tc.m_height;
			_imageContainer.m_depth = tc.m_depth;
			_imageContainer.m_blockSize = blockSize;
			_imageContainer.m_numMips = tc.m_numMips;
			_imageContainer.m_bpp = getBitsPerPixel(TextureFormat::Enum(tc.m_format) );
			_imageContainer.m_hasAlpha = false;
			_imageContainer.m_cubeMap = tc.m_cubeMap;
			_imageContainer.m_ktx = false;

			return true;
		}

		return false;
	}

	bool imageParse(ImageContainer& _imageContainer, const void* _data, uint32_t _size)
	{
		bx::MemoryReader reader(_data, _size);
		return imageParse(_imageContainer, &reader);
	}

	void imageDecodeToBgra8(uint8_t* _dst, const uint8_t* _src, uint32_t _width, uint32_t _height, uint32_t _pitch, uint8_t _type)
	{
		const uint8_t* src = _src;

		uint32_t width  = _width/4;
		uint32_t height = _height/4;

		uint8_t temp[16*4];

		switch (_type)
		{
		case TextureFormat::BC1:
			for (uint32_t yy = 0; yy < height; ++yy)
			{
				for (uint32_t xx = 0; xx < width; ++xx)
				{
					decodeBlockDxt1(temp, src);
					src += 8;

					uint8_t* dst = &_dst[(yy*_pitch+xx*4)*4];
					memcpy(&dst[0*_pitch], &temp[ 0], 16);
					memcpy(&dst[1*_pitch], &temp[16], 16);
					memcpy(&dst[2*_pitch], &temp[32], 16);
					memcpy(&dst[3*_pitch], &temp[48], 16);
				}
			}
			break;

		case TextureFormat::BC2:
			for (uint32_t yy = 0; yy < height; ++yy)
			{
				for (uint32_t xx = 0; xx < width; ++xx)
				{
					decodeBlockDxt23A(temp+3, src);
					src += 8;
					decodeBlockDxt(temp, src);
					src += 8;

					uint8_t* dst = &_dst[(yy*_pitch+xx*4)*4];
					memcpy(&dst[0*_pitch], &temp[ 0], 16);
					memcpy(&dst[1*_pitch], &temp[16], 16);
					memcpy(&dst[2*_pitch], &temp[32], 16);
					memcpy(&dst[3*_pitch], &temp[48], 16);
				}
			}
			break;

		case TextureFormat::BC3:
			for (uint32_t yy = 0; yy < height; ++yy)
			{
				for (uint32_t xx = 0; xx < width; ++xx)
				{
					decodeBlockDxt45A(temp+3, src);
					src += 8;
					decodeBlockDxt(temp, src);
					src += 8;

					uint8_t* dst = &_dst[(yy*_pitch+xx*4)*4];
					memcpy(&dst[0*_pitch], &temp[ 0], 16);
					memcpy(&dst[1*_pitch], &temp[16], 16);
					memcpy(&dst[2*_pitch], &temp[32], 16);
					memcpy(&dst[3*_pitch], &temp[48], 16);
				}
			}
			break;

		case TextureFormat::BC4:
			for (uint32_t yy = 0; yy < height; ++yy)
			{
				for (uint32_t xx = 0; xx < width; ++xx)
				{
					decodeBlockDxt45A(temp, src);
					src += 8;

					uint8_t* dst = &_dst[(yy*_pitch+xx*4)*4];
					memcpy(&dst[0*_pitch], &temp[ 0], 16);
					memcpy(&dst[1*_pitch], &temp[16], 16);
					memcpy(&dst[2*_pitch], &temp[32], 16);
					memcpy(&dst[3*_pitch], &temp[48], 16);
				}
			}
			break;

		case TextureFormat::BC5:
			for (uint32_t yy = 0; yy < height; ++yy)
			{
				for (uint32_t xx = 0; xx < width; ++xx)
				{
					decodeBlockDxt45A(temp+1, src);
					src += 8;
					decodeBlockDxt45A(temp+2, src);
					src += 8;

					for (uint32_t ii = 0; ii < 16; ++ii)
					{
						float nx = temp[ii*4+2]*2.0f/255.0f - 1.0f;
						float ny = temp[ii*4+1]*2.0f/255.0f - 1.0f;
						float nz = sqrtf(1.0f - nx*nx - ny*ny);
						temp[ii*4+0] = uint8_t( (nz + 1.0f)*255.0f/2.0f);
						temp[ii*4+3] = 0;
					}

					uint8_t* dst = &_dst[(yy*_pitch+xx*4)*4];
					memcpy(&dst[0*_pitch], &temp[ 0], 16);
					memcpy(&dst[1*_pitch], &temp[16], 16);
					memcpy(&dst[2*_pitch], &temp[32], 16);
					memcpy(&dst[3*_pitch], &temp[48], 16);
				}
			}
			break;

		case TextureFormat::ETC1:
		case TextureFormat::ETC2:
			for (uint32_t yy = 0; yy < height; ++yy)
			{
				for (uint32_t xx = 0; xx < width; ++xx)
				{
					decodeBlockEtc12(temp, src);
					src += 8;

					uint8_t* dst = &_dst[(yy*_pitch+xx*4)*4];
					memcpy(&dst[0*_pitch], &temp[ 0], 16);
					memcpy(&dst[1*_pitch], &temp[16], 16);
					memcpy(&dst[2*_pitch], &temp[32], 16);
					memcpy(&dst[3*_pitch], &temp[48], 16);
				}
			}
			break;

		case TextureFormat::ETC2A:
			BX_WARN(false, "ETC2A decoder is not implemented.");
			imageCheckerboard(_width, _height, 16, UINT32_C(0xff000000), UINT32_C(0xff00ff00), _dst);
			break;

		case TextureFormat::ETC2A1:
			BX_WARN(false, "ETC2A1 decoder is not implemented.");
			imageCheckerboard(_width, _height, 16, UINT32_C(0xff000000), UINT32_C(0xffff0000), _dst);
			break;

		case TextureFormat::PTC12:
			BX_WARN(false, "PTC12 decoder is not implemented.");
			imageCheckerboard(_width, _height, 16, UINT32_C(0xff000000), UINT32_C(0xffff00ff), _dst);
			break;

		case TextureFormat::PTC12A:
			BX_WARN(false, "PTC12A decoder is not implemented.");
			imageCheckerboard(_width, _height, 16, UINT32_C(0xff000000), UINT32_C(0xffffff00), _dst);
			break;

		case TextureFormat::PTC14:
			BX_WARN(false, "PTC14 decoder is not implemented.");
			imageCheckerboard(_width, _height, 16, UINT32_C(0xff000000), UINT32_C(0xff00ffff), _dst);
			break;

		case TextureFormat::PTC14A:
			BX_WARN(false, "PTC14A decoder is not implemented.");
			imageCheckerboard(_width, _height, 16, UINT32_C(0xffff0000), UINT32_C(0xff0000ff), _dst);
			break;

		case TextureFormat::PTC22:
			BX_WARN(false, "PTC22 decoder is not implemented.");
			imageCheckerboard(_width, _height, 16, UINT32_C(0xff00ff00), UINT32_C(0xff0000ff), _dst);
			break;

		case TextureFormat::PTC24:
			BX_WARN(false, "PTC24 decoder is not implemented.");
			imageCheckerboard(_width, _height, 16, UINT32_C(0xff000000), UINT32_C(0xffffffff), _dst);
			break;

		default:
			// Decompression not implemented... Make ugly red-yellow checkerboard texture.
			imageCheckerboard(_width, _height, 16, UINT32_C(0xffff0000), UINT32_C(0xffffff00), _dst);
			break;
		}
	}

	bool imageGetRawData(const ImageContainer& _imageContainer, uint8_t _side, uint8_t _lod, const void* _data, uint32_t _size, ImageMip& _mip)
	{
		const uint32_t blockSize = _imageContainer.m_blockSize;
		uint32_t offset = _imageContainer.m_offset;
		const uint8_t bpp = _imageContainer.m_bpp;
		TextureFormat::Enum type = TextureFormat::Enum(_imageContainer.m_format);
		bool hasAlpha = _imageContainer.m_hasAlpha;

		if (UINT32_MAX == _imageContainer.m_offset)
		{
			if (NULL == _imageContainer.m_data)
			{
				return false;
			}

			offset = 0;
			_data = _imageContainer.m_data;
			_size = _imageContainer.m_size;
		}

		for (uint8_t side = 0, numSides = _imageContainer.m_cubeMap ? 6 : 1; side < numSides; ++side)
		{
			uint32_t width  = _imageContainer.m_width;
			uint32_t height = _imageContainer.m_height;
			uint32_t depth  = _imageContainer.m_depth;

			for (uint8_t lod = 0, num = _imageContainer.m_numMips; lod < num; ++lod)
			{
				// skip imageSize in KTX format.
				offset += _imageContainer.m_ktx ? sizeof(uint32_t) : 0;

				width  = bx::uint32_max(1, width);
				height = bx::uint32_max(1, height);
				depth  = bx::uint32_max(1, depth);

				uint32_t size = width*height*depth*blockSize;
				if (TextureFormat::Unknown > type)
				{
					width  = bx::uint32_max(1, (width + 3)>>2);
					height = bx::uint32_max(1, (height + 3)>>2);
					size   = width*height*depth*blockSize;

					width  <<= 2;
					height <<= 2;
				}

				if (side == _side
				&&  lod == _lod)
				{
					_mip.m_width = width;
					_mip.m_height = height;
					_mip.m_blockSize = blockSize;
					_mip.m_size = size;
					_mip.m_data = (const uint8_t*)_data + offset;
					_mip.m_bpp = bpp;
					_mip.m_format = type;
					_mip.m_hasAlpha = hasAlpha;
					return true;
				}

				offset += size;

				BX_CHECK(offset <= _size, "Reading past size of data buffer! (offset %d, size %d)", offset, _size);
				BX_UNUSED(_size);

				width  >>= 1;
				height >>= 1;
				depth  >>= 1;
			}
		}

		return false;
	}

} // namespace bgfx

/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"
#include <bx/float4_t.h>
#include <math.h> // powf, sqrtf

#include "image.h"

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

#define PKM_MAGIC       BX_MAKEFOURCC('P', 'K', 'M', 0)
#define PKM_HEADER_SIZE 16

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

	void imageSwizzleBgra8Ref(uint32_t _width, uint32_t _height, const void* _src, void* _dst)
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
		||  _width < 4
		||  !bx::isPtrAligned(_src, 16)
		||  !bx::isPtrAligned(_dst, 16) )
		{
			BX_WARN(false, "Image swizzle is taking slow path.");
			BX_WARN(bx::isPtrAligned(_src, 16), "Source %p is not 16-byte aligned.", _src);
			BX_WARN(bx::isPtrAligned(_dst, 16), "Destination %p is not 16-byte aligned.", _dst);
			BX_WARN(_width < 4, "Image width must be multiple of 4 (width %d).", _width);
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

	static const int32_t s_mod[8][4] =
	{
		{  2,   8,  -2,   -8},
		{ 15,  17, -15,  -17},
		{  9,  29,  -9,  -29},
		{ 13,  42, -13,  -42},
		{ 18,  60, -18,  -60},
		{ 24,  80, -24,  -80},
		{ 33, 106, -33, -106},
		{ 47, 183, -47, -183},
	};

	int8_t uint8_add2c(int32_t _a, int32_t _b)
	{
		return _b & 0x4
			? _a - ( (~_b + 1) & 0x7)
			: _a + _b
			;
	}

	int8_t uint8_satadd(int32_t _a, int32_t _b)
	{
		using namespace bx;
		const  int32_t add    = _a + _b;
		const uint32_t min    = uint32_min(add, 255);
		const uint32_t result = uint32_max(min, 0);
		return result;
	}

	void decodeBlockEtc1(uint8_t _dst[16*4], const uint8_t _src[8])
	{
		bool flipBit = 0 != (_src[3] & 0x1);
		bool diffBit = 0 != (_src[3] & 0x2);

		uint8_t rgb[8];

		if (diffBit)
		{
			rgb[0]  = _src[0] >> 3;
			rgb[1]  = _src[1] >> 3;
			rgb[2]  = _src[2] >> 3;

			uint8_t diff[3];
			diff[0] = _src[0] & 0x07;
			diff[1] = _src[1] & 0x07;
			diff[2] = _src[2] & 0x07;

			rgb[4] = uint8_add2c(rgb[0], diff[0]);
			rgb[5] = uint8_add2c(rgb[1], diff[1]);
			rgb[6] = uint8_add2c(rgb[2], diff[2]);

			rgb[0] = bitRangeConvert(rgb[0], 5, 8);
			rgb[1] = bitRangeConvert(rgb[1], 5, 8);
			rgb[2] = bitRangeConvert(rgb[2], 5, 8);
			rgb[4] = bitRangeConvert(rgb[4], 5, 8);
			rgb[5] = bitRangeConvert(rgb[5], 5, 8);
			rgb[6] = bitRangeConvert(rgb[6], 5, 8);
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

		uint32_t indexBits = 0
						| (_src[4]<<24)
						| (_src[5]<<16)
						| (_src[6]<< 8)
						| (_src[7]    )
						;

		if (flipBit)
		{
			for (uint32_t ii = 0; ii < 16; ++ii)
			{
				const uint32_t block = (ii>>1)&1;
				const uint32_t color = block<<2;
				const uint32_t idx   = (ii&0xc) | ( (ii & 0x3)<<4);
				const uint32_t lsbi  = (indexBits >> ii) & 1;
				const uint32_t msbi  = (indexBits >> (16 + ii) ) & 1;
				const  int32_t mod   = s_mod[table[block] ][lsbi + msbi*2];

				_dst[idx + 0] = uint8_satadd(rgb[color+2], mod);
				_dst[idx + 1] = uint8_satadd(rgb[color+1], mod);
				_dst[idx + 2] = uint8_satadd(rgb[color+0], mod);
			}
		}
		else
		{
			for (uint32_t ii = 0; ii < 16; ++ii)
			{
				const uint32_t block = ii>>3;
				const uint32_t color = block<<2;
				const uint32_t idx   = (ii&0xc) | ( (ii & 0x3)<<4);
				const uint32_t lsbi  = (indexBits >> ii) & 1;
				const uint32_t msbi  = (indexBits >> (16 + ii) ) & 1;
				const  int32_t mod   = s_mod[table[block] ][lsbi + msbi*2];

				_dst[idx + 0] = uint8_satadd(rgb[color+2], mod);
				_dst[idx + 1] = uint8_satadd(rgb[color+1], mod);
				_dst[idx + 2] = uint8_satadd(rgb[color+0], mod);
			}
		}
	}

	void Mip::decode(uint8_t* _dst)
	{
		const uint8_t* src = m_data;

		if (TextureFormat::Unknown > m_type)
		{
			uint32_t width = m_width/4;
			uint32_t height = m_height/4;
			uint32_t pitch = m_width*4;

			uint8_t temp[16*4];

			switch (m_type)
			{
			case TextureFormat::BC1:
				for (uint32_t yy = 0; yy < height; ++yy)
				{
					for (uint32_t xx = 0; xx < width; ++xx)
					{
						decodeBlockDxt1(temp, src);
						src += 8;

						uint8_t* dst = &_dst[(yy*pitch+xx*4)*4];
						memcpy(&dst[0*pitch], &temp[ 0], 16);
						memcpy(&dst[1*pitch], &temp[16], 16);
						memcpy(&dst[2*pitch], &temp[32], 16);
						memcpy(&dst[3*pitch], &temp[48], 16);
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

						uint8_t* dst = &_dst[(yy*pitch+xx*4)*4];
						memcpy(&dst[0*pitch], &temp[ 0], 16);
						memcpy(&dst[1*pitch], &temp[16], 16);
						memcpy(&dst[2*pitch], &temp[32], 16);
						memcpy(&dst[3*pitch], &temp[48], 16);
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

						uint8_t* dst = &_dst[(yy*pitch+xx*4)*4];
						memcpy(&dst[0*pitch], &temp[ 0], 16);
						memcpy(&dst[1*pitch], &temp[16], 16);
						memcpy(&dst[2*pitch], &temp[32], 16);
						memcpy(&dst[3*pitch], &temp[48], 16);
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

						uint8_t* dst = &_dst[(yy*pitch+xx*4)*4];
						memcpy(&dst[0*pitch], &temp[ 0], 16);
						memcpy(&dst[1*pitch], &temp[16], 16);
						memcpy(&dst[2*pitch], &temp[32], 16);
						memcpy(&dst[3*pitch], &temp[48], 16);
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

						uint8_t* dst = &_dst[(yy*pitch+xx*4)*4];
						memcpy(&dst[0*pitch], &temp[ 0], 16);
						memcpy(&dst[1*pitch], &temp[16], 16);
						memcpy(&dst[2*pitch], &temp[32], 16);
						memcpy(&dst[3*pitch], &temp[48], 16);
					}
				}
				break;

			case TextureFormat::ETC1:
				for (uint32_t yy = 0; yy < height; ++yy)
				{
					for (uint32_t xx = 0; xx < width; ++xx)
					{
						decodeBlockEtc1(temp, src);
						src += 8;

						uint8_t* dst = &_dst[(yy*pitch+xx*4)*4];
						memcpy(&dst[0*pitch], &temp[ 0], 16);
						memcpy(&dst[1*pitch], &temp[16], 16);
						memcpy(&dst[2*pitch], &temp[32], 16);
						memcpy(&dst[3*pitch], &temp[48], 16);
					}
				}
				break;
			}
		}
		else
		{
			uint32_t width = m_width;
			uint32_t height = m_height;

			if (m_bpp == 8
			||  m_bpp == 32
			||  m_bpp == 64)
			{
				uint32_t pitch = m_width*m_bpp/8;
				memcpy(_dst, src, pitch*height);
			}
			else
			{
				uint32_t pitch = m_width*4;
				for (uint32_t yy = 0; yy < height; ++yy)
				{
					uint8_t* dst = &_dst[yy*pitch];

					for (uint32_t xx = 0; xx < width; ++xx)
					{
						memcpy(dst, src, 3);
						dst[3] = 255;
						dst += 4;
						src += 3;
					}
				}
			}
		}
	}

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
		TextureFormat::Enum type = TextureFormat::Unknown;
		bool hasAlpha = pixelFlags & DDPF_ALPHAPIXELS;

		if (pixelFlags & DDPF_FOURCC)
		{
			switch (fourcc)
			{
			case DDS_DXT1:
				type = TextureFormat::BC1;
				bpp = 4;
				blockSize = 4*4*bpp/8;
				break;

			case DDS_DXT2:
			case DDS_DXT3:
				type = TextureFormat::BC2;
				bpp = 8;
				blockSize = 4*4*bpp/8;
				break;

			case DDS_DXT4:
			case DDS_DXT5:
				type = TextureFormat::BC3;
				bpp = 8;
				blockSize = 4*4*bpp/8;
				break;

			case DDS_ATI1:
			case DDS_BC4U:
				type = TextureFormat::BC4;
				bpp = 4;
				blockSize = 4*4*bpp/8;
				break;

			case DDS_ATI2:
			case DDS_BC5U:
				type = TextureFormat::BC5;
				bpp = 8;
				blockSize = 4*4*bpp/8;
				break;

			case D3DFMT_A16B16G16R16:
				type = TextureFormat::RGBA16;
				blockSize = 8;
				bpp = 64;
				break;

			case D3DFMT_A16B16G16R16F:
				type = TextureFormat::RGBA16F;
				blockSize = 8;
				bpp = 64;
				break;
			}
		}
		else
		{
			switch (pixelFlags)
			{
			case DDPF_RGB:
				type = TextureFormat::BGRX8;
				blockSize = 3;
				bpp = 24;
				break;

			case DDPF_RGB|DDPF_ALPHAPIXELS:
				type = TextureFormat::BGRA8;
				blockSize = 4;
				bpp = 32;
				break;

			case DDPF_INDEXED:
			case DDPF_LUMINANCE:
			case DDPF_ALPHA:
				type = TextureFormat::L8;
				bpp = 8;
				break;

	// 			type = TextureFormat::A8;
	// 			bpp = 1;
	// 			break;

			default:
				bpp = 0;
				break;
			}
		}

		_imageContainer.m_type = type;
		_imageContainer.m_offset = DDS_IMAGE_DATA_OFFSET;
		_imageContainer.m_width = width;
		_imageContainer.m_height = height;
		_imageContainer.m_depth = depth;
		_imageContainer.m_blockSize = blockSize;
		_imageContainer.m_numMips = (caps[0] & DDSCAPS_MIPMAP) ? mips : 1;
		_imageContainer.m_bpp = bpp;
		_imageContainer.m_hasAlpha = hasAlpha;
		_imageContainer.m_cubeMap = cubeMap;
		_imageContainer.m_ktx = false;

		return TextureFormat::Unknown != type;
	}

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

		uint32_t pixelWidth;
		bx::readHE(_reader, pixelWidth, fromLittleEndian);

		uint32_t pixelHeight;
		bx::readHE(_reader, pixelHeight, fromLittleEndian);

		uint32_t pixelDepth;
		bx::readHE(_reader, pixelDepth, fromLittleEndian);

		uint32_t numberOfArrayElements;
		bx::readHE(_reader, numberOfArrayElements, fromLittleEndian);

		uint32_t numberOfFaces;
		bx::readHE(_reader, numberOfFaces, fromLittleEndian);

		uint32_t numberOfMipmapLevels;
		bx::readHE(_reader, numberOfMipmapLevels, fromLittleEndian);

		uint32_t bytesOfKeyValueData;
		bx::readHE(_reader, bytesOfKeyValueData, fromLittleEndian);

		// skip meta garbage...
		int64_t offset = bx::skip(_reader, bytesOfKeyValueData);

		uint8_t bpp = 0;
		uint8_t blockSize = 1;
		TextureFormat::Enum type = TextureFormat::Unknown;
		bool hasAlpha = false;

		switch (glInternalFormat)
		{
		case KTX_ETC1_RGB8_OES:
			type = TextureFormat::ETC1;
			bpp = 4;
			blockSize = 4*4*bpp/8;
			break;

		case KTX_COMPRESSED_R11_EAC:
		case KTX_COMPRESSED_SIGNED_R11_EAC:
		case KTX_COMPRESSED_RG11_EAC:
		case KTX_COMPRESSED_SIGNED_RG11_EAC:
		case KTX_COMPRESSED_RGB8_ETC2:
		case KTX_COMPRESSED_SRGB8_ETC2:
		case KTX_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2:
		case KTX_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2:
		case KTX_COMPRESSED_RGBA8_ETC2_EAC:
		case KTX_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC:
		case KTX_COMPRESSED_RGB_PVRTC_4BPPV1_IMG:
		case KTX_COMPRESSED_RGB_PVRTC_2BPPV1_IMG:
		case KTX_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG:
		case KTX_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG:
		default:
			break;
		}

		_imageContainer.m_type = type;
		_imageContainer.m_offset = (uint32_t)offset;
		_imageContainer.m_width = pixelWidth;
		_imageContainer.m_height = pixelHeight;
		_imageContainer.m_depth = pixelDepth;
		_imageContainer.m_blockSize = blockSize;
		_imageContainer.m_numMips = numberOfMipmapLevels;
		_imageContainer.m_bpp = bpp;
		_imageContainer.m_hasAlpha = hasAlpha;
		_imageContainer.m_cubeMap = numberOfFaces > 1;
		_imageContainer.m_ktx = true;

		return TextureFormat::Unknown != type;
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

		return false;
	}

	bool imageParse(ImageContainer& _imageContainer, const void* _data, uint32_t _size)
	{
		bx::MemoryReader reader(_data, _size);
		return imageParse(_imageContainer, &reader);
	}

	bool imageGetRawData(const ImageContainer& _imageContainer, uint8_t _side, uint8_t _lod, const void* _data, uint32_t _size, Mip& _mip)
	{
		const uint32_t blockSize = _imageContainer.m_blockSize;
		uint32_t offset = _imageContainer.m_offset;
		const uint8_t bpp = _imageContainer.m_bpp;
		TextureFormat::Enum type = _imageContainer.m_type;
		bool hasAlpha = _imageContainer.m_hasAlpha;

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
					_mip.m_type = type;
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

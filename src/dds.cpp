/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"
#include "dds.h"

namespace bgfx
{

#define DDS_MAGIC MAKEFOURCC('D','D','S',' ')
#define DDS_HEADER_SIZE 124
#define DDS_IMAGE_DATA_OFFSET (DDS_HEADER_SIZE + 4)

#define DDS_DXT1 MAKEFOURCC('D', 'X', 'T', '1')
#define DDS_DXT2 MAKEFOURCC('D', 'X', 'T', '2')
#define DDS_DXT3 MAKEFOURCC('D', 'X', 'T', '3')
#define DDS_DXT4 MAKEFOURCC('D', 'X', 'T', '4')
#define DDS_DXT5 MAKEFOURCC('D', 'X', 'T', '5')

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
#define DDSCAPS2_VOLUME             0x00200000

bool isDds(const Memory* _mem)
{
	StreamRead stream(_mem->data, _mem->size);

	uint32_t magic;
	stream.read(magic);

	return DDS_MAGIC == magic;
}

uint32_t bitRangeConvert(uint32_t _in, uint32_t _from, uint32_t _to)
{
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
		int idx = ( (_src[next>>3] >> (next & 7)) & 3) * 3;
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
		int idx = ( (_src[next>>3] >> (next & 7)) & 3) * 4;
		_dst[ii+0] = colors[idx+0];
		_dst[ii+1] = colors[idx+1];
		_dst[ii+2] = colors[idx+2];
		_dst[ii+3] = colors[idx+3];
	}
}

void decodeBlockDxt23A(uint8_t _dst[16*4], const uint8_t _src[8])
{
	for (uint32_t ii = 3, next = 0; ii < 16*4; ii += 4, next += 4)
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

	for (uint32_t ii = 3, next = 8*2; ii < 16*4; ii += 4, ++next)
	{
		uint32_t bit = (_src[next>>3] >> (next&7) ) & 1;
		uint32_t idx = bit;
		++next;

		bit = (_src[next>>3] >> (next&7) ) & 1;
		idx += bit << 1;
		++next;

		bit = (_src[next>>3] >> (next&7) ) & 1;
		idx += bit << 2;

		_dst[ii] = alpha[idx & 7];
	}
}

uint32_t Mip::getDecodedSize() const
{
	return m_width*m_height*4;
}

void Mip::decode(uint8_t* _dst)
{
	const uint8_t* src = m_data;

	if (0 != m_type)
	{
		uint32_t width = m_width/4;
		uint32_t height = m_height/4;
		uint32_t pitch = m_width*4;

		uint8_t temp[16*4];

		switch (m_type)
		{
		case 1:
			for (uint32_t yy = 0; yy < height; ++yy)
			{
				for (uint32_t xx = 0; xx < width; ++xx)
				{
					decodeBlockDxt1(temp, src);
					src += 8;

					uint8_t* dst = &_dst[(yy*pitch+xx*4)*4];
					memcpy(dst, temp, 16);
					memcpy(&dst[pitch], &temp[16], 16);
					memcpy(&dst[2*pitch], &temp[32], 16);
					memcpy(&dst[3*pitch], &temp[48], 16);
				}
			}
			break;

		case 2:
			for (uint32_t yy = 0; yy < height; ++yy)
			{
				for (uint32_t xx = 0; xx < width; ++xx)
				{
					decodeBlockDxt23A(temp, src);
					src += 8;
					decodeBlockDxt(temp, src);
					src += 8;

					uint8_t* dst = &_dst[(yy*pitch+xx*4)*4];
					memcpy(dst, temp, 16);
					memcpy(&dst[pitch], &temp[16], 16);
					memcpy(&dst[2*pitch], &temp[32], 16);
					memcpy(&dst[3*pitch], &temp[48], 16);
				}
			}
			break;

		case 3:
			for (uint32_t yy = 0; yy < height; ++yy)
			{
				for (uint32_t xx = 0; xx < width; ++xx)
				{
					decodeBlockDxt45A(temp, src);
					src += 8;
					decodeBlockDxt(temp, src);
					src += 8;

					uint8_t* dst = &_dst[(yy*pitch+xx*4)*4];
					memcpy(dst, temp, 16);
					memcpy(&dst[pitch], &temp[16], 16);
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

		if (m_bpp == 1
		||  m_bpp == 4)
		{
			uint32_t pitch = m_width*m_bpp;
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

bool parseDds(Dds& _dds, const Memory* _mem)
{
	StreamRead stream(_mem->data, _mem->size);

	uint32_t magic;
	stream.read(magic);

	if (DDS_MAGIC != magic)
	{
		return false;
	}

	uint32_t headerSize;
	stream.read(headerSize);

	if (headerSize < DDS_HEADER_SIZE)
	{
		return false;
	}

	uint32_t flags;
	stream.read(flags);

	if ( (flags & (DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH|DDSD_PIXELFORMAT) ) != (DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH|DDSD_PIXELFORMAT) )
	{
		return false;
	}

	uint32_t height;
	stream.read(height);

	uint32_t width;
	stream.read(width);

	uint32_t pitch;
	stream.read(pitch);

	uint32_t depth;
	stream.read(depth);

	uint32_t mips;
	stream.read(mips);

	stream.skip(44); // reserved

	stream.skip(4); // pixel format size

	uint32_t pixelFlags;
	stream.read(pixelFlags);

	uint32_t fourcc;
	stream.read(fourcc);

	uint32_t rgbCount;
	stream.read(rgbCount);

	uint32_t rbitmask;
	stream.read(rbitmask);

	uint32_t gbitmask;
	stream.read(gbitmask);

	uint32_t bbitmask;
	stream.read(bbitmask);

	uint32_t abitmask;
	stream.read(abitmask);

	uint32_t caps[4];
	stream.read(caps);

	if ( (caps[0] & DDSCAPS_TEXTURE) == 0)
	{
		return false;
	}

	stream.skip(4); // reserved

	uint8_t bpp = 1;
	uint8_t blockSize = 1;
	uint8_t type = 0;
	bool hasAlpha = pixelFlags & DDPF_ALPHAPIXELS;

	if (pixelFlags & DDPF_FOURCC)
	{
		switch (fourcc)
		{
		case DDS_DXT1:
			type = 1;
			blockSize = 8;
			break;

		case DDS_DXT2:
		case DDS_DXT3:
			type = 2;
			blockSize = 16;
			break;

		case DDS_DXT4:
		case DDS_DXT5:
			type = 3;
			blockSize = 16;
			break;
		}
	}
	else
	{
		switch (pixelFlags)
		{
		case DDPF_RGB:
			blockSize *= 3;
			bpp = 3;
			break;

		case DDPF_RGB|DDPF_ALPHAPIXELS:
			blockSize *= 4;
			bpp = 4;
			break;

		case DDPF_LUMINANCE:
		case DDPF_INDEXED:
		case DDPF_ALPHA:
			bpp = 1;
			break;

		default:
			bpp = 0;
			break;
		}
	}

	_dds.m_width = width;
	_dds.m_height = height;
	_dds.m_depth = depth;
	_dds.m_blockSize = blockSize;
	_dds.m_numMips = (caps[0] & DDSCAPS_MIPMAP) ? mips : 1;
	_dds.m_bpp = bpp;
	_dds.m_type = type;
	_dds.m_hasAlpha = hasAlpha;

	return true;
}

bool getRawImageData(const Dds& _dds, uint8_t _index, const Memory* _mem, Mip& _mip)
{
	uint32_t width = _dds.m_width;
	uint32_t height = _dds.m_height;
	uint32_t blockSize = _dds.m_blockSize;
	uint32_t offset = DDS_IMAGE_DATA_OFFSET;
	uint8_t bpp = _dds.m_bpp;
	uint8_t type = _dds.m_type;
	bool hasAlpha = _dds.m_hasAlpha;

	for (uint8_t ii = 0, num = _dds.m_numMips; ii < num; ++ii)
	{
		width = uint32_max(1, width);
		height = uint32_max(1, height);

		uint32_t size = width*height*blockSize;
		if (0 != type)
		{
			width = uint32_max(1, (width + 3)>>2);
			height = uint32_max(1, (height + 3)>>2);
			size = width*height*blockSize;

			width <<= 2;
			height <<= 2;
		}

		if (ii == _index)
		{
			_mip.m_width = width;
			_mip.m_height = height;
			_mip.m_blockSize = blockSize;
			_mip.m_size = size;
			_mip.m_data = _mem->data + offset;
			_mip.m_bpp = bpp;
			_mip.m_type = type;
			_mip.m_hasAlpha = hasAlpha;
			return true;
		}

		offset += size;

		width >>= 1;
		height >>= 1;
	}

	return false;
}

} // namespace bgfx

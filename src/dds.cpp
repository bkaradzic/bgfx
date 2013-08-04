/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <math.h> // sqrtf

#include "bgfx_p.h"
#include "dds.h"

namespace bgfx
{

#define DDS_MAGIC BX_MAKEFOURCC('D','D','S',' ')
#define DDS_HEADER_SIZE 124
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

bool isDds(const Memory* _mem)
{
	bx::MemoryReader reader(_mem->data, _mem->size);

	uint32_t magic;
	bx::read(&reader, magic);

	return DDS_MAGIC == magic;
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

uint32_t Mip::getDecodedSize() const
{
	return m_width*m_height*4;
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

bool parseDds(Dds& _dds, const Memory* _mem)
{
	bx::MemoryReader reader(_mem->data, _mem->size);

	uint32_t magic;
	bx::read(&reader, magic);

	if (DDS_MAGIC != magic)
	{
		return false;
	}

	uint32_t headerSize;
	bx::read(&reader, headerSize);

	if (headerSize < DDS_HEADER_SIZE)
	{
		return false;
	}

	uint32_t flags;
	bx::read(&reader, flags);

	if ( (flags & (DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH|DDSD_PIXELFORMAT) ) != (DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH|DDSD_PIXELFORMAT) )
	{
		return false;
	}

	uint32_t height;
	bx::read(&reader, height);

	uint32_t width;
	bx::read(&reader, width);

	uint32_t pitch;
	bx::read(&reader, pitch);

	uint32_t depth;
	bx::read(&reader, depth);

	uint32_t mips;
	bx::read(&reader, mips);

	bx::skip(&reader, 44); // reserved
	bx::skip(&reader, 4); // pixel format size

	uint32_t pixelFlags;
	bx::read(&reader, pixelFlags);

	uint32_t fourcc;
	bx::read(&reader, fourcc);

	uint32_t rgbCount;
	bx::read(&reader, rgbCount);

	uint32_t rbitmask;
	bx::read(&reader, rbitmask);

	uint32_t gbitmask;
	bx::read(&reader, gbitmask);

	uint32_t bbitmask;
	bx::read(&reader, bbitmask);

	uint32_t abitmask;
	bx::read(&reader, abitmask);

	uint32_t caps[4];
	bx::read(&reader, caps);

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

	bx::skip(&reader, 4); // reserved

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

	_dds.m_type = type;
	_dds.m_width = width;
	_dds.m_height = height;
	_dds.m_depth = depth;
	_dds.m_blockSize = blockSize;
	_dds.m_numMips = (caps[0] & DDSCAPS_MIPMAP) ? mips : 1;
	_dds.m_bpp = bpp;
	_dds.m_hasAlpha = hasAlpha;
	_dds.m_cubeMap = cubeMap;

	return true;
}

bool getRawImageData(const Dds& _dds, uint8_t _side, uint8_t _lod, const Memory* _mem, Mip& _mip)
{
	uint32_t blockSize = _dds.m_blockSize;
	uint32_t offset = DDS_IMAGE_DATA_OFFSET;
	uint8_t bpp = _dds.m_bpp;
	TextureFormat::Enum type = _dds.m_type;
	bool hasAlpha = _dds.m_hasAlpha;

	for (uint8_t side = 0, numSides = _dds.m_cubeMap ? 6 : 1; side < numSides; ++side)
	{
		uint32_t width = _dds.m_width;
		uint32_t height = _dds.m_height;
		uint32_t depth = _dds.m_depth;

		for (uint8_t lod = 0, num = _dds.m_numMips; lod < num; ++lod)
		{
			width = bx::uint32_max(1, width);
			height = bx::uint32_max(1, height);
			depth = bx::uint32_max(1, depth);

			uint32_t size = width*height*depth*blockSize;
			if (TextureFormat::Unknown > type)
			{
				width = bx::uint32_max(1, (width + 3)>>2);
				height = bx::uint32_max(1, (height + 3)>>2);
				size = width*height*depth*blockSize;

				width <<= 2;
				height <<= 2;
			}

			if (side == _side
			&&  lod == _lod)
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
			depth >>= 1;
		}
	}

	return false;
}

} // namespace bgfx

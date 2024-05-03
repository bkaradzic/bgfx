/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef RECTPACK_H_HEADER_GUARD
#define RECTPACK_H_HEADER_GUARD

#include <bx/uint32_t.h>

struct Pack2D
{
	uint16_t m_x;
	uint16_t m_y;
	uint16_t m_width;
	uint16_t m_height;
};

struct PackCube
{
	Pack2D m_rect;
	uint8_t m_side;
};

template <uint16_t numBlocks>
class RectPackCubeT;

template <uint16_t numBlocks>
class RectPack2DT
{
public:
	RectPack2DT(uint16_t _width, uint16_t _height)
	{
		reset(_width, _height);
	}

	void reset(uint16_t _width, uint16_t _height)
	{
		m_bw = _width/64;
		m_bh = _height/numBlocks;
		bx::memSet(m_mem, 0xff, sizeof(m_mem) );
	}

	bool find(uint16_t _width, uint16_t _height, Pack2D& _pack)
	{
		uint16_t width  = bx::min<uint16_t>(64, (_width  + m_bw - 1) / m_bw);
		uint16_t height = bx::min<uint16_t>(numBlocks, (_height + m_bh - 1) / m_bh);
		uint16_t numx = 64-width;
		uint16_t numy = numBlocks-height;

		const uint64_t scan = width == 64 ? UINT64_MAX : (UINT64_C(1)<<width)-1;

		for (uint16_t starty = 0; starty <= numy; ++starty)
		{
			uint64_t mem = m_mem[starty];
			uint16_t ntz = (uint16_t)bx::uint64_cnttz(mem);
			uint64_t mask = scan<<ntz;

			for (uint16_t xx = ntz; xx <= numx; ++xx, mask <<= 1)
			{
				uint16_t yy = starty;
				if ( (mem&mask) == mask)
				{
					uint16_t endy = starty + height;
					while (yy < endy && (m_mem[yy]&mask) == mask)
					{
						++yy;
					}

					if (yy == endy)
					{
						uint64_t cmask = ~mask;
						for (yy = starty; yy < endy; ++yy)
						{
							m_mem[yy] &= cmask;
						}

						_pack.m_x = xx * m_bw;
						_pack.m_y = starty * m_bh;
						_pack.m_width = width * m_bw;
						_pack.m_height = height * m_bh;
						return true;
					}
				}
			}
		}

		return false;
	}

	void clear(const Pack2D& _pack)
	{
		uint16_t startx = bx::min<uint16_t>(63, _pack.m_x / m_bw);
		uint16_t starty = bx::min<uint16_t>(numBlocks-1, _pack.m_y / m_bh);
		uint16_t endx   = bx::min<uint16_t>(64, (_pack.m_width + m_bw - 1) / m_bw + startx);
		uint16_t endy   = bx::min<uint16_t>(numBlocks, (_pack.m_height + m_bh - 1) / m_bh + starty);
		uint16_t width  = endx - startx;

		const uint64_t mask = (width == 64 ? UINT64_MAX : (UINT64_C(1)<<width)-1 )<<startx;

		for (uint16_t yy = starty; yy < endy; ++yy)
		{
			m_mem[yy] |= mask;
		}
	}

private:
	friend class RectPackCubeT<numBlocks>;

	RectPack2DT()
	{
	}

	uint64_t m_mem[numBlocks];
	uint16_t m_bw;
	uint16_t m_bh;
};

template <uint16_t numBlocks>
class RectPackCubeT
{
public:
	RectPackCubeT(uint16_t _side)
	{
		reset(_side);
	}

	void reset(uint16_t _side)
	{
		for (uint8_t ii = 0; ii < 6; ++ii)
		{
			m_mru[ii] = ii;
			m_ra[ii].reset(_side, _side);
		}
	}

	bool find(uint16_t _width, uint16_t _height, PackCube& _pack)
	{
		bool found = false;
		for (uint32_t ii = 0; ii < 6; ++ii)
		{
			uint8_t side = m_mru[ii];
			found = m_ra[side].find(_width, _height, _pack.m_rect);

			if (found)
			{
				_pack.m_side = side;
				m_mru[ii] = m_mru[0];
				m_mru[0] = side;
				return true;
			}
		}

		return false;
	}

	void clear(const PackCube& _pack)
	{
		uint8_t side = _pack.m_side;

		uint32_t ii = 0;
		for (; ii < 6 && m_mru[ii] != side; ++ii) {};

		m_mru[ii] = m_mru[0];
		m_mru[0] = side;

		m_ra[side].clear(_pack.m_rect);
	}

private:
	RectPackCubeT();

	RectPack2DT<numBlocks> m_ra[6];
	uint8_t m_mru[6];
};

#endif // RECTPACK_H_HEADER_GUARD

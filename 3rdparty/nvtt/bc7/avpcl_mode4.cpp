/*
Copyright 2007 nVidia, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 

You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 

See the License for the specific language governing permissions and limitations under the License.
*/

// Thanks to Jacob Munkberg (jacob@cs.lth.se) for the shortcut of using SVD to do the equivalent of principal components analysis

// x10000 2r 1i 555x2 6x2 2bi 3bi

#include "bits.h"
#include "tile.h"
#include "avpcl.h"
#include "nvcore/debug.h"
#include "nvmath/vector.inl"
#include "nvmath/matrix.inl"
#include "nvmath/fitting.h"
#include "avpcl_utils.h"
#include "endpts.h"
#include <string.h>
#include <float.h>

using namespace nv;
using namespace AVPCL;

// there are 2 index arrays. INDEXMODE selects between the arrays being 2 & 3 bits or 3 & 2 bits
// array 0 is always the RGB array and array 1 is always the A array
#define	NINDEXARRAYS	2
#define	INDEXARRAY_RGB	0
#define INDEXARRAY_A	1
#define INDEXARRAY_2BITS(indexmode)	((indexmode == INDEXMODE_ALPHA_IS_2BITS) ? INDEXARRAY_A : INDEXARRAY_RGB)
#define INDEXARRAY_3BITS(indexmode)	((indexmode == INDEXMODE_ALPHA_IS_3BITS) ? INDEXARRAY_A : INDEXARRAY_RGB)

#define NINDICES3	8
#define	INDEXBITS3	3
#define	HIGH_INDEXBIT3	(1<<(INDEXBITS3-1))
#define	DENOM3		(NINDICES3-1)
#define	BIAS3		(DENOM3/2)

#define NINDICES2	4
#define	INDEXBITS2	2
#define	HIGH_INDEXBIT2	(1<<(INDEXBITS2-1))
#define	DENOM2		(NINDICES2-1)
#define	BIAS2		(DENOM2/2)

#define	NINDICES_RGB(indexmode)		((indexmode == INDEXMODE_ALPHA_IS_2BITS) ? NINDICES3 : NINDICES2)
#define	INDEXBITS_RGB(indexmode)	((indexmode == INDEXMODE_ALPHA_IS_2BITS) ? INDEXBITS3 : INDEXBITS2)
#define	HIGH_INDEXBIT_RGB(indexmode)((indexmode == INDEXMODE_ALPHA_IS_2BITS) ? HIGH_INDEXBIT3 : HIGH_INDEXBIT2)
#define	DENOM_RGB(indexmode)		((indexmode == INDEXMODE_ALPHA_IS_2BITS) ? DENOM3 : DENOM2)
#define	BIAS_RGB(indexmode)			((indexmode == INDEXMODE_ALPHA_IS_2BITS) ? BIAS3 : BIAS2)

#define	NINDICES_A(indexmode)		((indexmode == INDEXMODE_ALPHA_IS_2BITS) ? NINDICES2 : NINDICES3)
#define	INDEXBITS_A(indexmode)		((indexmode == INDEXMODE_ALPHA_IS_2BITS) ? INDEXBITS2 : INDEXBITS3)
#define	HIGH_INDEXBIT_A(indexmode)	((indexmode == INDEXMODE_ALPHA_IS_2BITS) ? HIGH_INDEXBIT2 : HIGH_INDEXBIT3)
#define	DENOM_A(indexmode)			((indexmode == INDEXMODE_ALPHA_IS_2BITS) ? DENOM2 : DENOM3)
#define	BIAS_A(indexmode)			((indexmode == INDEXMODE_ALPHA_IS_2BITS) ? BIAS2 : BIAS3)

#define	NSHAPES	1

static int shapes[NSHAPES] =
{
	0x0000,
};

#define	REGION(x,y,shapeindex)	((shapes[shapeindex]&(1<<(15-(x)-4*(y))))!=0)

#define NREGIONS	1			// keep the region stuff in just in case...

// encoded index compression location: region 0 is always at 0,0.

#define	NBITSIZES	2			// one endpoint pair

struct ChanBits
{
	int nbitsizes[NBITSIZES];	// bitsizes for one channel
};

struct Pattern
{
	ChanBits chan[NCHANNELS_RGBA];//  bit patterns used per channel
	int transform_mode;		// x0 means alpha channel not transformed, x1 otherwise. 0x rgb not transformed, 1x otherwise.
	int mode;				// associated mode value
	int modebits;			// number of mode bits
	const char *encoding;			// verilog description of encoding for this mode
};

#define	TRANSFORM_MODE_ALPHA	1
#define	TRANSFORM_MODE_RGB	2

#define	NPATTERNS 1

static Pattern patterns[NPATTERNS] =
{
	// red		green		blue		alpha	xfm	mode  mb encoding
	5,5,		5,5,		5,5,		6,6,	0x0, 0x10, 5, "",
};

struct RegionPrec
{
	int	endpt_a_prec[NCHANNELS_RGBA];
	int endpt_b_prec[NCHANNELS_RGBA];
};

struct PatternPrec
{
	RegionPrec region_precs[NREGIONS];
};

// this is the precision for each channel and region
// NOTE: this MUST match the corresponding data in "patterns" above -- WARNING: there is NO nvAssert to check this!
static PatternPrec pattern_precs[NPATTERNS] =
{
	5,5,5,6,	5,5,5,6,
};


// return # of bits needed to store n. handle signed or unsigned cases properly
static int nbits(int n, bool issigned)
{
	int nb;
	if (n==0)
		return 0;	// no bits needed for 0, signed or not
	else if (n > 0)
	{
		for (nb=0; n; ++nb, n>>=1) ;
		return nb + (issigned?1:0);
	}
	else
	{
		nvAssert (issigned);
		for (nb=0; n<-1; ++nb, n>>=1) ;
		return nb + 1;
	}
}

#define	R_0	ep[0].A[i]
#define	R_1 ep[0].B[i]

static void transform_forward(int transform_mode, IntEndptsRGBA ep[NREGIONS])
{
	int i;

	if (transform_mode & TRANSFORM_MODE_RGB)
		for (i=CHANNEL_R; i<CHANNEL_A; ++i)
			R_1 -= R_0;
	if (transform_mode & TRANSFORM_MODE_ALPHA)
	{
		i = CHANNEL_A;
		R_1 -= R_0;
	}
}

static void transform_inverse(int transform_mode, IntEndptsRGBA ep[NREGIONS])
{
	int i;

	if (transform_mode & TRANSFORM_MODE_RGB)
		for (i=CHANNEL_R; i<CHANNEL_A; ++i)
			R_1 += R_0;
	if (transform_mode & TRANSFORM_MODE_ALPHA)
	{
		i = CHANNEL_A;
		R_1 += R_0;
	}
}

static void quantize_endpts(const FltEndpts endpts[NREGIONS], const PatternPrec &pattern_prec, IntEndptsRGBA q_endpts[NREGIONS])
{
	for (int region = 0; region < NREGIONS; ++region)
	{
		q_endpts[region].A[0] = Utils::quantize(endpts[region].A.x, pattern_prec.region_precs[region].endpt_a_prec[0]);
		q_endpts[region].A[1] = Utils::quantize(endpts[region].A.y, pattern_prec.region_precs[region].endpt_a_prec[1]);
		q_endpts[region].A[2] = Utils::quantize(endpts[region].A.z, pattern_prec.region_precs[region].endpt_a_prec[2]);
		q_endpts[region].A[3] = Utils::quantize(endpts[region].A.w, pattern_prec.region_precs[region].endpt_a_prec[3]);

		q_endpts[region].B[0] = Utils::quantize(endpts[region].B.x, pattern_prec.region_precs[region].endpt_b_prec[0]);
		q_endpts[region].B[1] = Utils::quantize(endpts[region].B.y, pattern_prec.region_precs[region].endpt_b_prec[1]);
		q_endpts[region].B[2] = Utils::quantize(endpts[region].B.z, pattern_prec.region_precs[region].endpt_b_prec[2]);
		q_endpts[region].B[3] = Utils::quantize(endpts[region].B.w, pattern_prec.region_precs[region].endpt_b_prec[3]);
	}
}

// swap endpoints as needed to ensure that the indices at index_one and index_two have a 0 high-order bit
// index_two is 0 at x=0 y=0 and 15 at x=3 y=3 so y = (index >> 2) & 3 and x = index & 3
static void swap_indices(int shapeindex, int indexmode, IntEndptsRGBA endpts[NREGIONS], int indices[NINDEXARRAYS][Tile::TILE_H][Tile::TILE_W])
{
	int index_positions[NREGIONS];

	index_positions[0] = 0;			// since WLOG we have the high bit of the shapes at 0

	for (int region = 0; region < NREGIONS; ++region)
	{
		int x = index_positions[region] & 3;
		int y = (index_positions[region] >> 2) & 3;
		nvAssert(REGION(x,y,shapeindex) == region);		// double check the table

		// swap RGB
		if (indices[INDEXARRAY_RGB][y][x] & HIGH_INDEXBIT_RGB(indexmode))
		{
			// high bit is set, swap the endpts and indices for this region
			int t;
			for (int i=CHANNEL_R; i<=CHANNEL_B; ++i) { t = endpts[region].A[i]; endpts[region].A[i] = endpts[region].B[i]; endpts[region].B[i] = t; }

			for (int y = 0; y < Tile::TILE_H; y++)
			for (int x = 0; x < Tile::TILE_W; x++)
				if (REGION(x,y,shapeindex) == region)
					indices[INDEXARRAY_RGB][y][x] = NINDICES_RGB(indexmode) - 1 - indices[INDEXARRAY_RGB][y][x];
		}

		// swap A
		if (indices[INDEXARRAY_A][y][x] & HIGH_INDEXBIT_A(indexmode))
		{
			// high bit is set, swap the endpts and indices for this region
			int t;
			for (int i=CHANNEL_A; i<=CHANNEL_A; ++i) { t = endpts[region].A[i]; endpts[region].A[i] = endpts[region].B[i]; endpts[region].B[i] = t; }

			for (int y = 0; y < Tile::TILE_H; y++)
			for (int x = 0; x < Tile::TILE_W; x++)
				if (REGION(x,y,shapeindex) == region)
					indices[INDEXARRAY_A][y][x] = NINDICES_A(indexmode) - 1 - indices[INDEXARRAY_A][y][x];
		}
	}
}

static bool endpts_fit(IntEndptsRGBA endpts[NREGIONS], const Pattern &p)
{
	return true;
}

static void write_header(const IntEndptsRGBA endpts[NREGIONS], int shapeindex, const Pattern &p, int rotatemode, int indexmode, Bits &out)
{
	// ignore shapeindex
	out.write(p.mode, p.modebits);
	out.write(rotatemode, ROTATEMODE_BITS);
	out.write(indexmode, INDEXMODE_BITS);
	for (int i=0; i<NREGIONS; ++i)
		for (int j=0; j<NCHANNELS_RGBA; ++j)
		{
			out.write(endpts[i].A[j], p.chan[j].nbitsizes[0]);
			out.write(endpts[i].B[j], p.chan[j].nbitsizes[1]);
		}
	nvAssert (out.getptr() == 50);
}

static void read_header(Bits &in, IntEndptsRGBA endpts[NREGIONS], int &shapeindex, int &rotatemode, int &indexmode, Pattern &p, int &pat_index)
{
	int mode = AVPCL::getmode(in);

	pat_index = 0;

	nvAssert (pat_index >= 0 && pat_index < NPATTERNS);
	nvAssert (in.getptr() == patterns[pat_index].modebits);

	p = patterns[pat_index];

	shapeindex = 0;		// we don't have any

	rotatemode = in.read(ROTATEMODE_BITS);
	indexmode = in.read(INDEXMODE_BITS);
	for (int i=0; i<NREGIONS; ++i)
		for (int j=0; j<NCHANNELS_RGBA; ++j)
		{
			endpts[i].A[j] = in.read(p.chan[j].nbitsizes[0]);
			endpts[i].B[j] = in.read(p.chan[j].nbitsizes[1]);
		}
	nvAssert (in.getptr() == 50);
}

static void write_indices(const int indices[NINDEXARRAYS][Tile::TILE_H][Tile::TILE_W], int shapeindex, int indexmode, Bits &out)
{
	// the indices we shorten is always index 0

	// do the 2 bit indices first
	nvAssert ((indices[INDEXARRAY_2BITS(indexmode)][0][0] & HIGH_INDEXBIT2) == 0);
	for (int i = 0; i < Tile::TILE_TOTAL; ++i)
		out.write(indices[INDEXARRAY_2BITS(indexmode)][i>>2][i&3], INDEXBITS2 - (i==0?1:0));	// write i..[1:0] or i..[0]

	// then the 3 bit indices
	nvAssert ((indices[INDEXARRAY_3BITS(indexmode)][0][0] & HIGH_INDEXBIT3) == 0);
	for (int i = 0; i < Tile::TILE_TOTAL; ++i)
		out.write(indices[INDEXARRAY_3BITS(indexmode)][i>>2][i&3], INDEXBITS3 - (i==0?1:0));	// write i..[2:0] or i..[1:0]
}

static void read_indices(Bits &in, int shapeindex, int indexmode, int indices[NINDEXARRAYS][Tile::TILE_H][Tile::TILE_W])
{
	// the indices we shorten is always index 0

	// do the 2 bit indices first
	for (int i = 0; i < Tile::TILE_TOTAL; ++i)
		indices[INDEXARRAY_2BITS(indexmode)][i>>2][i&3] = in.read(INDEXBITS2 - (i==0?1:0));		// read i..[1:0] or i..[0]

	// then the 3 bit indices
	for (int i = 0; i < Tile::TILE_TOTAL; ++i)
		indices[INDEXARRAY_3BITS(indexmode)][i>>2][i&3] = in.read(INDEXBITS3 - (i==0?1:0));		// read i..[1:0] or i..[0]
}

static void emit_block(const IntEndptsRGBA endpts[NREGIONS], int shapeindex, const Pattern &p, const int indices[NINDEXARRAYS][Tile::TILE_H][Tile::TILE_W], int rotatemode, int indexmode, char *block)
{
	Bits out(block, AVPCL::BITSIZE);

	write_header(endpts, shapeindex, p, rotatemode, indexmode, out);

	write_indices(indices, shapeindex, indexmode, out);

	nvAssert(out.getptr() == AVPCL::BITSIZE);
}

static void generate_palette_quantized_rgb_a(const IntEndptsRGBA &endpts, const RegionPrec &region_prec, int indexmode, Vector3 palette_rgb[NINDICES3], float palette_a[NINDICES3])
{
	// scale endpoints for RGB
	int a, b;

	a = Utils::unquantize(endpts.A[0], region_prec.endpt_a_prec[0]); 
	b = Utils::unquantize(endpts.B[0], region_prec.endpt_b_prec[0]);

	// interpolate R
	for (int i = 0; i < NINDICES_RGB(indexmode); ++i)
		palette_rgb[i].x = float(Utils::lerp(a, b, i, BIAS_RGB(indexmode), DENOM_RGB(indexmode)));

	a = Utils::unquantize(endpts.A[1], region_prec.endpt_a_prec[1]); 
	b = Utils::unquantize(endpts.B[1], region_prec.endpt_b_prec[1]);

	// interpolate G
	for (int i = 0; i < NINDICES_RGB(indexmode); ++i)
		palette_rgb[i].y = float(Utils::lerp(a, b, i, BIAS_RGB(indexmode), DENOM_RGB(indexmode)));

	a = Utils::unquantize(endpts.A[2], region_prec.endpt_a_prec[2]); 
	b = Utils::unquantize(endpts.B[2], region_prec.endpt_b_prec[2]);

	// interpolate B
	for (int i = 0; i < NINDICES_RGB(indexmode); ++i)
		palette_rgb[i].z = float(Utils::lerp(a, b, i, BIAS_RGB(indexmode), DENOM_RGB(indexmode)));

	a = Utils::unquantize(endpts.A[3], region_prec.endpt_a_prec[3]); 
	b = Utils::unquantize(endpts.B[3], region_prec.endpt_b_prec[3]);

	// interpolate A
	for (int i = 0; i < NINDICES_A(indexmode); ++i)
		palette_a[i] = float(Utils::lerp(a, b, i, BIAS_A(indexmode), DENOM_A(indexmode)));

}

static void sign_extend(Pattern &p, IntEndptsRGBA endpts[NREGIONS])
{
	for (int i=0; i<NCHANNELS_RGBA; ++i)
	{
		if (p.transform_mode)
		{
			// endpts[0].A[i] = SIGN_EXTEND(endpts[0].B[i], p.chan[i].nbitsizes[0]);	// always positive here
			endpts[0].B[i] = SIGN_EXTEND(endpts[0].B[i], p.chan[i].nbitsizes[0]);
			endpts[1].A[i] = SIGN_EXTEND(endpts[1].A[i], p.chan[i].nbitsizes[1]);
			endpts[1].B[i] = SIGN_EXTEND(endpts[1].B[i], p.chan[i].nbitsizes[1]);
		}
	}
}

static void rotate_tile(const Tile &in, int rotatemode, Tile &out)
{
	out.size_x = in.size_x;
	out.size_y = in.size_y;

	for (int y=0; y<in.size_y; ++y)
	for (int x=0; x<in.size_x; ++x)
	{
		float t;
		out.data[y][x] = in.data[y][x];

		switch(rotatemode)
		{
		case ROTATEMODE_RGBA_RGBA: break;
		case ROTATEMODE_RGBA_AGBR: t = (out.data[y][x]).x; (out.data[y][x]).x = (out.data[y][x]).w; (out.data[y][x]).w = t; break;
		case ROTATEMODE_RGBA_RABG: t = (out.data[y][x]).y; (out.data[y][x]).y = (out.data[y][x]).w; (out.data[y][x]).w = t; break;
		case ROTATEMODE_RGBA_RGAB: t = (out.data[y][x]).z; (out.data[y][x]).z = (out.data[y][x]).w; (out.data[y][x]).w = t; break;
		default: nvUnreachable();
		}
	}
}

void AVPCL::decompress_mode4(const char *block, Tile &t)
{
	Bits in(block, AVPCL::BITSIZE);

	Pattern p;
	IntEndptsRGBA endpts[NREGIONS];
	int shapeindex, pat_index, rotatemode, indexmode;

	read_header(in, endpts, shapeindex, rotatemode, indexmode, p, pat_index);
	
	sign_extend(p, endpts);

	if (p.transform_mode)
		transform_inverse(p.transform_mode, endpts);

	Vector3 palette_rgb[NREGIONS][NINDICES3];	// could be nindices2
	float palette_a[NREGIONS][NINDICES3];	// could be nindices2

	for (int region = 0; region < NREGIONS; ++region)
		generate_palette_quantized_rgb_a(endpts[region], pattern_precs[pat_index].region_precs[region], indexmode, &palette_rgb[region][0], &palette_a[region][0]);

	int indices[NINDEXARRAYS][Tile::TILE_H][Tile::TILE_W];

	read_indices(in, shapeindex, indexmode, indices);

	nvAssert(in.getptr() == AVPCL::BITSIZE);

	Tile temp(t.size_x, t.size_y);

	// lookup
	for (int y = 0; y < Tile::TILE_H; y++)
	for (int x = 0; x < Tile::TILE_W; x++)
		temp.data[y][x] = Vector4(palette_rgb[REGION(x,y,shapeindex)][indices[INDEXARRAY_RGB][y][x]], palette_a[REGION(x,y,shapeindex)][indices[INDEXARRAY_A][y][x]]);

	rotate_tile(temp, rotatemode, t);
}

// given a collection of colors and quantized endpoints, generate a palette, choose best entries, and return a single toterr
// we already have a candidate mapping when we call this function, thus an error. take an early exit if the accumulated error so far
// exceeds what we already have
static float map_colors(const Vector4 colors[], const float importance[], int np, int rotatemode, int indexmode, const IntEndptsRGBA &endpts, const RegionPrec &region_prec, float current_besterr, int indices[NINDEXARRAYS][Tile::TILE_TOTAL])
{
	Vector3 palette_rgb[NINDICES3];	// could be nindices2
	float palette_a[NINDICES3];	// could be nindices2
	float toterr = 0;

	generate_palette_quantized_rgb_a(endpts, region_prec, indexmode, &palette_rgb[0], &palette_a[0]);

	Vector3 rgb;
	float a;

	for (int i = 0; i < np; ++i)
	{
		float err, besterr;
		float palette_alpha = 0, tile_alpha = 0;

		if(AVPCL::flag_premult)
				tile_alpha = (rotatemode == ROTATEMODE_RGBA_AGBR) ? (colors[i]).x :
							 (rotatemode == ROTATEMODE_RGBA_RABG) ? (colors[i]).y :
							 (rotatemode == ROTATEMODE_RGBA_RGAB) ? (colors[i]).z : (colors[i]).w;

		rgb.x = (colors[i]).x;
		rgb.y = (colors[i]).y;
		rgb.z = (colors[i]).z;
		a = (colors[i]).w;

		// compute the two indices separately
		// if we're doing premultiplied alpha, we need to choose first the index that
		// determines the alpha value, and then do the other index

		if (rotatemode == ROTATEMODE_RGBA_RGBA)
		{
			// do A index first as it has the alpha
			besterr = FLT_MAX;
			for (int j = 0; j < NINDICES_A(indexmode) && besterr > 0; ++j)
			{
				err = Utils::metric1(a, palette_a[j], rotatemode);

				if (err > besterr)	// error increased, so we're done searching
					break;
				if (err < besterr)
				{
					besterr = err;
					palette_alpha = palette_a[j];
					indices[INDEXARRAY_A][i] = j;
				}
			}
			toterr += besterr;		// squared-error norms are additive since we don't do the square root

			// do RGB index
			besterr = FLT_MAX;
			for (int j = 0; j < NINDICES_RGB(indexmode) && besterr > 0; ++j)
			{
				err = !AVPCL::flag_premult ? Utils::metric3(rgb, palette_rgb[j], rotatemode) :
											 Utils::metric3premult_alphaout(rgb, tile_alpha, palette_rgb[j], palette_alpha);

				if (err > besterr)	// error increased, so we're done searching
					break;
				if (err < besterr)
				{
					besterr = err;
					indices[INDEXARRAY_RGB][i] = j;
				}
			}
			toterr += besterr;
			if (toterr > current_besterr)
			{
				// fill out bogus index values so it's initialized at least
				for (int k = i; k < np; ++k)
				{
					indices[INDEXARRAY_RGB][k] = -1;
					indices[INDEXARRAY_A][k] = -1;
				}
				return FLT_MAX;
			}
		}
		else
		{
			// do RGB index
			besterr = FLT_MAX;
			int bestindex;
			for (int j = 0; j < NINDICES_RGB(indexmode) && besterr > 0; ++j)
			{
				err = !AVPCL::flag_premult ? Utils::metric3(rgb, palette_rgb[j], rotatemode) :
											 Utils::metric3premult_alphain(rgb, palette_rgb[j], rotatemode);

				if (err > besterr)	// error increased, so we're done searching
					break;
				if (err < besterr)
				{
					besterr = err;
					bestindex = j;
					indices[INDEXARRAY_RGB][i] = j;
				}
			}
			palette_alpha = (rotatemode == ROTATEMODE_RGBA_AGBR) ? (palette_rgb[bestindex]).x :
							(rotatemode == ROTATEMODE_RGBA_RABG) ? (palette_rgb[bestindex]).y :
							(rotatemode == ROTATEMODE_RGBA_RGAB) ? (palette_rgb[bestindex]).z : nvCheckMacro(0);
			toterr += besterr;

			// do A index
			besterr = FLT_MAX;
			for (int j = 0; j < NINDICES_A(indexmode) && besterr > 0; ++j)
			{
				err = !AVPCL::flag_premult ? Utils::metric1(a, palette_a[j], rotatemode) :
											 Utils::metric1premult(a, tile_alpha, palette_a[j], palette_alpha, rotatemode);

				if (err > besterr)	// error increased, so we're done searching
					break;
				if (err < besterr)
				{
					besterr = err;
					indices[INDEXARRAY_A][i] = j;
				}
			}
			toterr += besterr;		// squared-error norms are additive since we don't do the square root
			if (toterr > current_besterr)
			{
				// fill out bogus index values so it's initialized at least
				for (int k = i; k < np; ++k)
				{
					indices[INDEXARRAY_RGB][k] = -1;
					indices[INDEXARRAY_A][k] = -1;
				}
				return FLT_MAX;
			}
		}
	}
	return toterr;
}

// assign indices given a tile, shape, and quantized endpoints, return toterr for each region
static void assign_indices(const Tile &tile, int shapeindex, int rotatemode, int indexmode, IntEndptsRGBA endpts[NREGIONS], const PatternPrec &pattern_prec, 
						   int indices[NINDEXARRAYS][Tile::TILE_H][Tile::TILE_W], float toterr[NREGIONS])
{
	Vector3 palette_rgb[NREGIONS][NINDICES3];	// could be nindices2
	float palette_a[NREGIONS][NINDICES3];	// could be nindices2

	for (int region = 0; region < NREGIONS; ++region)
	{
		generate_palette_quantized_rgb_a(endpts[region], pattern_prec.region_precs[region], indexmode, &palette_rgb[region][0], &palette_a[region][0]);
		toterr[region] = 0;
	}

	Vector3 rgb;
	float a;

	for (int y = 0; y < tile.size_y; y++)
	for (int x = 0; x < tile.size_x; x++)
	{
		int region = REGION(x,y,shapeindex);
		float err, besterr;
		float palette_alpha = 0, tile_alpha = 0;

		rgb.x = (tile.data[y][x]).x;
		rgb.y = (tile.data[y][x]).y;
		rgb.z = (tile.data[y][x]).z;
		a = (tile.data[y][x]).w;

		if(AVPCL::flag_premult)
				tile_alpha = (rotatemode == ROTATEMODE_RGBA_AGBR) ? (tile.data[y][x]).x :
							 (rotatemode == ROTATEMODE_RGBA_RABG) ? (tile.data[y][x]).y :
							 (rotatemode == ROTATEMODE_RGBA_RGAB) ? (tile.data[y][x]).z : (tile.data[y][x]).w;

		// compute the two indices separately
		// if we're doing premultiplied alpha, we need to choose first the index that
		// determines the alpha value, and then do the other index

		if (rotatemode == ROTATEMODE_RGBA_RGBA)
		{
			// do A index first as it has the alpha
			besterr = FLT_MAX;
			for (int i = 0; i < NINDICES_A(indexmode) && besterr > 0; ++i)
			{
				err = Utils::metric1(a, palette_a[region][i], rotatemode);

				if (err > besterr)	// error increased, so we're done searching
					break;
				if (err < besterr)
				{
					besterr = err;
					indices[INDEXARRAY_A][y][x] = i;
					palette_alpha = palette_a[region][i];
				}
			}
			toterr[region] += besterr;		// squared-error norms are additive since we don't do the square root

			// do RGB index
			besterr = FLT_MAX;
			for (int i = 0; i < NINDICES_RGB(indexmode) && besterr > 0; ++i)
			{
				err = !AVPCL::flag_premult ? Utils::metric3(rgb, palette_rgb[region][i], rotatemode) :
											 Utils::metric3premult_alphaout(rgb, tile_alpha, palette_rgb[region][i], palette_alpha);

				if (err > besterr)	// error increased, so we're done searching
					break;
				if (err < besterr)
				{
					besterr = err;
					indices[INDEXARRAY_RGB][y][x] = i;
				}
			}
			toterr[region] += besterr;
		}
		else
		{
			// do RGB index first as it has the alpha
			besterr = FLT_MAX;
			int bestindex;
			for (int i = 0; i < NINDICES_RGB(indexmode) && besterr > 0; ++i)
			{
				err = !AVPCL::flag_premult ? Utils::metric3(rgb, palette_rgb[region][i], rotatemode) :
											 Utils::metric3premult_alphain(rgb, palette_rgb[region][i], rotatemode);

				if (err > besterr)	// error increased, so we're done searching
					break;
				if (err < besterr)
				{
					besterr = err;
					indices[INDEXARRAY_RGB][y][x] = i;
					bestindex = i;
				}
			}
			palette_alpha = (rotatemode == ROTATEMODE_RGBA_AGBR) ? (palette_rgb[region][bestindex]).x :
							(rotatemode == ROTATEMODE_RGBA_RABG) ? (palette_rgb[region][bestindex]).y :
							(rotatemode == ROTATEMODE_RGBA_RGAB) ? (palette_rgb[region][bestindex]).z : nvCheckMacro(0);
			toterr[region] += besterr;

			// do A index
			besterr = FLT_MAX;
			for (int i = 0; i < NINDICES_A(indexmode) && besterr > 0; ++i)
			{
				err = !AVPCL::flag_premult ? Utils::metric1(a, palette_a[region][i], rotatemode) :
											 Utils::metric1premult(a, tile_alpha, palette_a[region][i], palette_alpha, rotatemode);

				if (err > besterr)	// error increased, so we're done searching
					break;
				if (err < besterr)
				{
					besterr = err;
					indices[INDEXARRAY_A][y][x] = i;
				}
			}
			toterr[region] += besterr;		// squared-error norms are additive since we don't do the square root
		}
	}
}

// note: indices are valid only if the value returned is less than old_err; otherwise they contain -1's
// this function returns either old_err or a value smaller (if it was successful in improving the error)
static float perturb_one(const Vector4 colors[], const float importance[], int np, int rotatemode, int indexmode, int ch, const RegionPrec &region_prec, const IntEndptsRGBA &old_endpts, IntEndptsRGBA &new_endpts, 
						  float old_err, int do_b, int indices[NINDEXARRAYS][Tile::TILE_TOTAL])
{
	// we have the old endpoints: old_endpts
	// we have the perturbed endpoints: new_endpts
	// we have the temporary endpoints: temp_endpts

	IntEndptsRGBA temp_endpts;
	float min_err = old_err;		// start with the best current error
	int beststep;
	int temp_indices[NINDEXARRAYS][Tile::TILE_TOTAL];

	for (int j=0; j<NINDEXARRAYS; ++j)
	for (int i=0; i<np; ++i)
		indices[j][i] = -1;

	// copy real endpoints so we can perturb them
	temp_endpts = new_endpts = old_endpts;

	int prec = do_b ? region_prec.endpt_b_prec[ch] : region_prec.endpt_a_prec[ch];

	// do a logarithmic search for the best error for this endpoint (which)
	for (int step = 1 << (prec-1); step; step >>= 1)
	{
		bool improved = false;
		for (int sign = -1; sign <= 1; sign += 2)
		{
			if (do_b == 0)
			{
				temp_endpts.A[ch] = new_endpts.A[ch] + sign * step;
				if (temp_endpts.A[ch] < 0 || temp_endpts.A[ch] >= (1 << prec))
					continue;
			}
			else
			{
				temp_endpts.B[ch] = new_endpts.B[ch] + sign * step;
				if (temp_endpts.B[ch] < 0 || temp_endpts.B[ch] >= (1 << prec))
					continue;
			}

            float err = map_colors(colors, importance, np, rotatemode, indexmode, temp_endpts, region_prec, min_err, temp_indices);

			if (err < min_err)
			{
				improved = true;
				min_err = err;
				beststep = sign * step;
				for (int j=0; j<NINDEXARRAYS; ++j)
				for (int i=0; i<np; ++i)
					indices[j][i] = temp_indices[j][i];
			}
		}
		// if this was an improvement, move the endpoint and continue search from there
		if (improved)
		{
			if (do_b == 0)
				new_endpts.A[ch] += beststep;
			else
				new_endpts.B[ch] += beststep;
		}
	}
	return min_err;
}

// the larger the error the more time it is worth spending on an exhaustive search.
// perturb the endpoints at least -3 to 3.
// if err > 5000 perturb endpoints 50% of precision
// if err > 1000 25%
// if err > 200 12.5%
// if err > 40  6.25%
// for np = 16 -- adjust error thresholds as a function of np
// always ensure endpoint ordering is preserved (no need to overlap the scan)
static float exhaustive(const Vector4 colors[], const float importance[], int np, int rotatemode, int indexmode, int ch, const RegionPrec &region_prec, float orig_err, IntEndptsRGBA &opt_endpts, int indices[NINDEXARRAYS][Tile::TILE_TOTAL])
{
	IntEndptsRGBA temp_endpts;
	float best_err = orig_err;
	int aprec = region_prec.endpt_a_prec[ch];
	int bprec = region_prec.endpt_b_prec[ch];
	int good_indices[NINDEXARRAYS][Tile::TILE_TOTAL];
	int temp_indices[NINDEXARRAYS][Tile::TILE_TOTAL];

	for (int j=0; j<NINDEXARRAYS; ++j)
	for (int i=0; i<np; ++i)
		indices[j][i] = -1;

	float thr_scale = (float)np / (float)Tile::TILE_TOTAL;

	if (orig_err == 0) return orig_err;

	int adelta = 0, bdelta = 0;
	if (orig_err > 5000.0*thr_scale)		{ adelta = (1 << aprec)/2; bdelta = (1 << bprec)/2; }
	else if (orig_err > 1000.0*thr_scale)	{ adelta = (1 << aprec)/4; bdelta = (1 << bprec)/4; }
	else if (orig_err > 200.0*thr_scale)	{ adelta = (1 << aprec)/8; bdelta = (1 << bprec)/8; }
	else if (orig_err > 40.0*thr_scale)		{ adelta = (1 << aprec)/16; bdelta = (1 << bprec)/16; }
	adelta = max(adelta, 3);
	bdelta = max(bdelta, 3);

#ifdef	DISABLE_EXHAUSTIVE
	adelta = bdelta = 3;
#endif

	temp_endpts = opt_endpts;

	// ok figure out the range of A and B
	int alow = max(0, opt_endpts.A[ch] - adelta);
	int ahigh = min((1<<aprec)-1, opt_endpts.A[ch] + adelta);
	int blow = max(0, opt_endpts.B[ch] - bdelta);
	int bhigh = min((1<<bprec)-1, opt_endpts.B[ch] + bdelta);

	// now there's no need to swap the ordering of A and B
	bool a_le_b = opt_endpts.A[ch] <= opt_endpts.B[ch];

	int amin, bmin;

	if (opt_endpts.A[ch] <= opt_endpts.B[ch])
	{
		// keep a <= b
		for (int a = alow; a <= ahigh; ++a)
		for (int b = max(a, blow); b < bhigh; ++b)
		{
			temp_endpts.A[ch] = a;
			temp_endpts.B[ch] = b;
		
            float err = map_colors(colors, importance, np, rotatemode, indexmode, temp_endpts, region_prec, best_err, temp_indices);
			if (err < best_err) 
			{ 
				amin = a; 
				bmin = b; 
				best_err = err;
				for (int j=0; j<NINDEXARRAYS; ++j)
				for (int i=0; i<np; ++i)
					good_indices[j][i] = temp_indices[j][i];
			}
		}
	}
	else
	{
		// keep b <= a
		for (int b = blow; b < bhigh; ++b)
		for (int a = max(b, alow); a <= ahigh; ++a)
		{
			temp_endpts.A[ch] = a;
			temp_endpts.B[ch] = b;
		
            float err = map_colors(colors, importance, np, rotatemode, indexmode, temp_endpts, region_prec, best_err, temp_indices);
			if (err < best_err) 
			{ 
				amin = a; 
				bmin = b; 
				best_err = err;
				for (int j=0; j<NINDEXARRAYS; ++j)
				for (int i=0; i<np; ++i)
					good_indices[j][i] = temp_indices[j][i];
			}
		}
	}
	if (best_err < orig_err)
	{
		opt_endpts.A[ch] = amin;
		opt_endpts.B[ch] = bmin;
		orig_err = best_err;
		for (int j=0; j<NINDEXARRAYS; ++j)
		for (int i=0; i<np; ++i)
			indices[j][i] = good_indices[j][i];
	}

	return best_err;
}

static float optimize_one(const Vector4 colors[], const float importance[], int np, int rotatemode, int indexmode, float orig_err, const IntEndptsRGBA &orig_endpts, const RegionPrec &region_prec, IntEndptsRGBA &opt_endpts)
{
	float opt_err = orig_err;

	opt_endpts = orig_endpts;

	/*
		err0 = perturb(rgb0, delta0)
		err1 = perturb(rgb1, delta1)
		if (err0 < err1)
			if (err0 >= initial_error) break
			rgb0 += delta0
			next = 1
		else
			if (err1 >= initial_error) break
			rgb1 += delta1
			next = 0
		initial_err = map()
		for (;;)
			err = perturb(next ? rgb1:rgb0, delta)
			if (err >= initial_err) break
			next? rgb1 : rgb0 += delta
			initial_err = err
	*/
	IntEndptsRGBA new_a, new_b;
	IntEndptsRGBA new_endpt;
	int do_b;
	int orig_indices[NINDEXARRAYS][Tile::TILE_TOTAL];
	int new_indices[NINDEXARRAYS][Tile::TILE_TOTAL];
	int temp_indices0[NINDEXARRAYS][Tile::TILE_TOTAL];
	int temp_indices1[NINDEXARRAYS][Tile::TILE_TOTAL];

	// now optimize each channel separately
	for (int ch = 0; ch < NCHANNELS_RGBA; ++ch)
	{
		// figure out which endpoint when perturbed gives the most improvement and start there
		// if we just alternate, we can easily end up in a local minima
		float err0 = perturb_one(colors, importance, np, rotatemode, indexmode, ch, region_prec, opt_endpts, new_a, opt_err, 0, temp_indices0);	// perturb endpt A
        float err1 = perturb_one(colors, importance, np, rotatemode, indexmode, ch, region_prec, opt_endpts, new_b, opt_err, 1, temp_indices1);	// perturb endpt B

		if (err0 < err1)
		{
			if (err0 >= opt_err)
				continue;

			for (int j=0; j<NINDEXARRAYS; ++j)
			for (int i=0; i<np; ++i)
			{
				new_indices[j][i] = orig_indices[j][i] = temp_indices0[j][i];
				nvAssert (orig_indices[j][i] != -1);
			}

			opt_endpts.A[ch] = new_a.A[ch];
			opt_err = err0;
			do_b = 1;		// do B next
		}
		else
		{
			if (err1 >= opt_err)
				continue;

			for (int j=0; j<NINDEXARRAYS; ++j)
			for (int i=0; i<np; ++i)
			{
				new_indices[j][i] = orig_indices[j][i] = temp_indices1[j][i];
				nvAssert (orig_indices[j][i] != -1);
			}

			opt_endpts.B[ch] = new_b.B[ch];
			opt_err = err1;
			do_b = 0;		// do A next
		}
		
		// now alternate endpoints and keep trying until there is no improvement
		for (;;)
		{
            float err = perturb_one(colors, importance, np, rotatemode, indexmode, ch, region_prec, opt_endpts, new_endpt, opt_err, do_b, temp_indices0);
			if (err >= opt_err)
				break;

			for (int j=0; j<NINDEXARRAYS; ++j)
			for (int i=0; i<np; ++i)
			{
				new_indices[j][i] = temp_indices0[j][i];
				nvAssert (orig_indices[j][i] != -1);
			}

			if (do_b == 0)
				opt_endpts.A[ch] = new_endpt.A[ch];
			else
				opt_endpts.B[ch] = new_endpt.B[ch];
			opt_err = err;
			do_b = 1 - do_b;	// now move the other endpoint
		}

		// see if the indices have changed
		int i;
		for (i=0; i<np; ++i)
			if (orig_indices[INDEXARRAY_RGB][i] != new_indices[INDEXARRAY_RGB][i] || orig_indices[INDEXARRAY_A][i] != new_indices[INDEXARRAY_A][i])
				break;

		if (i<np)
			ch = -1;	// start over
	}

	// finally, do a small exhaustive search around what we think is the global minima to be sure
	bool first = true;
	for (int ch = 0; ch < NCHANNELS_RGBA; ++ch)
	{
        float new_err = exhaustive(colors, importance, np, rotatemode, indexmode, ch, region_prec, opt_err, opt_endpts, temp_indices0);

		if (new_err < opt_err)
		{
			opt_err = new_err;

			if (first)
			{
				for (int j=0; j<NINDEXARRAYS; ++j)
				for (int i=0; i<np; ++i)
				{
					orig_indices[j][i] = temp_indices0[j][i];
					nvAssert (orig_indices[j][i] != -1);
				}
				first = false;
			}
			else
			{
				// see if the indices have changed
				int i;
				for (i=0; i<np; ++i)
					if (orig_indices[INDEXARRAY_RGB][i] != temp_indices0[INDEXARRAY_RGB][i] || orig_indices[INDEXARRAY_A][i] != temp_indices0[INDEXARRAY_A][i])
						break;

				if (i<np)
				{
					ch = -1;	// start over
					first = true;
				}
			}
		}
	}

	return opt_err;
}

static void optimize_endpts(const Tile &tile, int shapeindex, int rotatemode, int indexmode, const float orig_err[NREGIONS], 
							const IntEndptsRGBA orig_endpts[NREGIONS], const PatternPrec &pattern_prec, float opt_err[NREGIONS], IntEndptsRGBA opt_endpts[NREGIONS])
{
	Vector4 pixels[Tile::TILE_TOTAL];
    float importance[Tile::TILE_TOTAL];
	IntEndptsRGBA temp_in, temp_out;

	for (int region=0; region<NREGIONS; ++region)
	{
		// collect the pixels in the region
		int np = 0;

        for (int y = 0; y < tile.size_y; y++) {
            for (int x = 0; x < tile.size_x; x++) {
                if (REGION(x, y, shapeindex) == region) {
                    pixels[np] = tile.data[y][x];
                    importance[np] = tile.importance_map[y][x];
                    np++;
                }
            }
        }

		opt_endpts[region] = temp_in = orig_endpts[region];
		opt_err[region] = orig_err[region];

		float best_err = orig_err[region];

		// make sure we have a valid error for temp_in
		// we didn't change temp_in, so orig_err[region] is still valid
		float temp_in_err = orig_err[region];

		// now try to optimize these endpoints
        float temp_out_err = optimize_one(pixels, importance, np, rotatemode, indexmode, temp_in_err, temp_in, pattern_prec.region_precs[region], temp_out);

		// if we find an improvement, update the best so far and correct the output endpoints and errors
		if (temp_out_err < best_err)
		{
			best_err = temp_out_err;
			opt_err[region] = temp_out_err;
			opt_endpts[region] = temp_out;
		}
	}
}

/* optimization algorithm
	for each pattern
		convert endpoints using pattern precision
		assign indices and get initial error
		compress indices (and possibly reorder endpoints)
		transform endpoints
		if transformed endpoints fit pattern
			get original endpoints back
			optimize endpoints, get new endpoints, new indices, and new error // new error will almost always be better
			compress new indices
			transform new endpoints
			if new endpoints fit pattern AND if error is improved
				emit compressed block with new data
			else
				emit compressed block with original data // to try to preserve maximum endpoint precision
*/

static float refine(const Tile &tile, int shapeindex_best, int rotatemode, int indexmode, const FltEndpts endpts[NREGIONS], char *block)
{
	float orig_err[NREGIONS], opt_err[NREGIONS], orig_toterr, opt_toterr, expected_opt_err[NREGIONS];
	IntEndptsRGBA orig_endpts[NREGIONS], opt_endpts[NREGIONS];
	int orig_indices[NINDEXARRAYS][Tile::TILE_H][Tile::TILE_W], opt_indices[NINDEXARRAYS][Tile::TILE_H][Tile::TILE_W];

	for (int sp = 0; sp < NPATTERNS; ++sp)
	{
		quantize_endpts(endpts, pattern_precs[sp], orig_endpts);

		assign_indices(tile, shapeindex_best, rotatemode, indexmode, orig_endpts, pattern_precs[sp], orig_indices, orig_err);
		swap_indices(shapeindex_best, indexmode, orig_endpts, orig_indices);

		if (patterns[sp].transform_mode)
			transform_forward(patterns[sp].transform_mode, orig_endpts);

		// apply a heuristic here -- we check if the endpoints fit before we try to optimize them.
		// the assumption made is that if they don't fit now, they won't fit after optimizing.
		if (endpts_fit(orig_endpts, patterns[sp]))
		{
			if (patterns[sp].transform_mode)
				transform_inverse(patterns[sp].transform_mode, orig_endpts);

			optimize_endpts(tile, shapeindex_best, rotatemode, indexmode, orig_err, orig_endpts, pattern_precs[sp], expected_opt_err, opt_endpts);

			assign_indices(tile, shapeindex_best, rotatemode, indexmode, opt_endpts, pattern_precs[sp], opt_indices, opt_err);
			// (nreed) Commented out asserts because they go off all the time...not sure why
			//for (int i=0; i<NREGIONS; ++i)
			//	nvAssert(expected_opt_err[i] == opt_err[i]);
			swap_indices(shapeindex_best, indexmode, opt_endpts, opt_indices);

			if (patterns[sp].transform_mode)
				transform_forward(patterns[sp].transform_mode, opt_endpts);

			orig_toterr = opt_toterr = 0;
			for (int i=0; i < NREGIONS; ++i) { orig_toterr += orig_err[i]; opt_toterr += opt_err[i]; }
			if (endpts_fit(opt_endpts, patterns[sp]) && opt_toterr < orig_toterr)
			{
				emit_block(opt_endpts, shapeindex_best, patterns[sp], opt_indices, rotatemode, indexmode, block);
				return opt_toterr;
			}
			else
			{
				// either it stopped fitting when we optimized it, or there was no improvement
				// so go back to the unoptimized endpoints which we know will fit
				if (patterns[sp].transform_mode)
					transform_forward(patterns[sp].transform_mode, orig_endpts);
				emit_block(orig_endpts, shapeindex_best, patterns[sp], orig_indices, rotatemode, indexmode, block);
				return orig_toterr;
			}
		}
	}
	nvAssert(false); //throw "No candidate found, should never happen (mode avpcl 4).";
	return FLT_MAX;
}

static void clamp(Vector4 &v)
{
	if (v.x < 0.0f) v.x = 0.0f;
	if (v.x > 255.0f) v.x = 255.0f;
	if (v.y < 0.0f) v.y = 0.0f;
	if (v.y > 255.0f) v.y = 255.0f;
	if (v.z < 0.0f) v.z = 0.0f;
	if (v.z > 255.0f) v.z = 255.0f;
	if (v.w < 0.0f) v.w = 0.0f;
	if (v.w > 255.0f) v.w = 255.0f;
}

// compute initial endpoints for the "RGB" portion and the "A" portion. 
// Note these channels may have been rotated.
static void rough(const Tile &tile, int shapeindex, FltEndpts endpts[NREGIONS])
{
	for (int region=0; region<NREGIONS; ++region)
	{
		int np = 0;
		Vector3 colors[Tile::TILE_TOTAL];
		float alphas[Tile::TILE_TOTAL];
		Vector4 mean(0,0,0,0);

		for (int y = 0; y < tile.size_y; y++)
		for (int x = 0; x < tile.size_x; x++)
			if (REGION(x,y,shapeindex) == region)
			{
				colors[np] = tile.data[y][x].xyz();
				alphas[np] = tile.data[y][x].w;
				mean += tile.data[y][x];
				++np;
			}

		// handle simple cases	
		if (np == 0)
		{
			Vector4 zero(0,0,0,255.0f);
			endpts[region].A = zero;
			endpts[region].B = zero;
			continue;
		}
		else if (np == 1)
		{
			endpts[region].A = Vector4(colors[0], alphas[0]);
			endpts[region].B = Vector4(colors[0], alphas[0]);
			continue;
		}
		else if (np == 2)
		{
			endpts[region].A = Vector4(colors[0], alphas[0]);
			endpts[region].B = Vector4(colors[1], alphas[1]);
			continue;
		}

		mean /= float(np);

		Vector3 direction = Fit::computePrincipalComponent_EigenSolver(np, colors);

		// project each pixel value along the principal direction
		float minp = FLT_MAX, maxp = -FLT_MAX;
		float mina = FLT_MAX, maxa = -FLT_MAX;
		for (int i = 0; i < np; i++) 
		{
			float dp = dot(colors[i]-mean.xyz(), direction);
			if (dp < minp) minp = dp;
			if (dp > maxp) maxp = dp;

			dp = alphas[i] - mean.w;
			if (dp < mina) mina = dp;
			if (dp > maxa) maxa = dp;
		}

		// choose as endpoints 2 points along the principal direction that span the projections of all of the pixel values
		endpts[region].A = mean + Vector4(minp*direction, mina);
		endpts[region].B = mean + Vector4(maxp*direction, maxa);

		// clamp endpoints
		// the argument for clamping is that the actual endpoints need to be clamped and thus we need to choose the best
		// shape based on endpoints being clamped
		clamp(endpts[region].A);
		clamp(endpts[region].B);
	}
}

float AVPCL::compress_mode4(const Tile &t, char *block)
{
	FltEndpts endpts[NREGIONS];
	char tempblock[AVPCL::BLOCKSIZE];
	float msebest = FLT_MAX;
	int shape = 0;
	Tile t1;

	// try all rotations. refine tries the 2 different indexings.
	for (int r = 0; r < NROTATEMODES && msebest > 0; ++r)
	{
		rotate_tile(t, r, t1);
		rough(t1, shape, endpts);
		for (int i = 0; i < NINDEXMODES && msebest > 0; ++i)
		{
			float mse = refine(t1, shape, r, i, endpts, tempblock);
			if (mse < msebest)
			{
				memcpy(block, tempblock, sizeof(tempblock));
				msebest = mse;
			}
		}
	}
	return msebest;
}

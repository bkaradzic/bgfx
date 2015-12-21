/*
Copyright 2007 nVidia, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 

You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 

See the License for the specific language governing permissions and limitations under the License.
*/

// Thanks to Jacob Munkberg (jacob@cs.lth.se) for the shortcut of using SVD to do the equivalent of principal components analysis

// x1000000 7777.1x2 4bi

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

#define	NLSBMODES	4		// number of different lsb modes per region. since we have two .1 per region, that can have 4 values

#define NINDICES	16
#define	INDEXBITS	4
#define	HIGH_INDEXBIT	(1<<(INDEXBITS-1))
#define	DENOM		(NINDICES-1)
#define	BIAS		(DENOM/2)

#define	NSHAPES	1

static int shapes[NSHAPES] =
{
	0x0000,
};

#define	REGION(x,y,shapeindex)	((shapes[shapeindex]&(1<<(15-(x)-4*(y))))!=0)

#define	NREGIONS	1

#define	NBITSIZES	(NREGIONS*2)
#define	ABITINDEX(region)	(2*(region)+0)
#define	BBITINDEX(region)	(2*(region)+1)

struct ChanBits
{
	int nbitsizes[NBITSIZES];	// bitsizes for one channel
};

struct Pattern
{
	ChanBits chan[NCHANNELS_RGBA];//  bit patterns used per channel
	int mode;				// associated mode value
	int modebits;			// number of mode bits
	const char *encoding;			// verilog description of encoding for this mode
};

#define	NPATTERNS 1

static Pattern patterns[NPATTERNS] =
{
	// red	green	blue	alpha	mode  mb verilog
	7,7,	7,7,	7,7,	7,7,	0x40, 7, "",
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
	7,7,7,7,	7,7,7,7,
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

/*
we're using this table to assign lsbs
abgr	>=2	correct
0000	0	0
0001	0	0
0010	0	0
0011	1	x1
0100	0	0
0101	1	x1
0110	1	x1
0111	1	1
1000	0	0
1001	1	x0
1010	1	x0
1011	1	1
1100	1	x0
1101	1	1
1110	1	1
1111	1	1

we need 8 0's and 8 1's. the x's can be either 0 or 1 as long as you get 8/8.
I choose to assign the lsbs so that the rgb channels are as good as possible.
*/

// 8888 ->7777.1, use the "correct" column above to assign the lsb
static void compress_one(const IntEndptsRGBA& endpts, IntEndptsRGBA_2& compr_endpts)
{
	int onescnt;

	onescnt = 0;
	for (int j=0; j<NCHANNELS_RGBA; ++j)
	{
		// ignore the alpha channel in the count
		onescnt += (j==CHANNEL_A) ? 0 : (endpts.A[j] & 1);
		compr_endpts.A[j] = endpts.A[j] >> 1;
		nvAssert (compr_endpts.A[j] < 128);
	}
	compr_endpts.a_lsb = onescnt >= 2;

	onescnt = 0;
	for (int j=0; j<NCHANNELS_RGBA; ++j)
	{
		onescnt += (j==CHANNEL_A) ? 0 : (endpts.B[j] & 1);
		compr_endpts.B[j] = endpts.B[j] >> 1;
		nvAssert (compr_endpts.B[j] < 128);
	}
	compr_endpts.b_lsb = onescnt >= 2;
}

static void uncompress_one(const IntEndptsRGBA_2& compr_endpts, IntEndptsRGBA& endpts)
{
	for (int j=0; j<NCHANNELS_RGBA; ++j)
	{
		endpts.A[j] = (compr_endpts.A[j] << 1) | compr_endpts.a_lsb;
		endpts.B[j] = (compr_endpts.B[j] << 1) | compr_endpts.b_lsb;
	}
}

static void uncompress_endpoints(const IntEndptsRGBA_2 compr_endpts[NREGIONS], IntEndptsRGBA endpts[NREGIONS])
{
	for (int i=0; i<NREGIONS; ++i)
		uncompress_one(compr_endpts[i], endpts[i]);
}

static void compress_endpoints(const IntEndptsRGBA endpts[NREGIONS], IntEndptsRGBA_2 compr_endpts[NREGIONS])
{
	for (int i=0; i<NREGIONS; ++i)
		compress_one(endpts[i], compr_endpts[i]);
}



static void quantize_endpts(const FltEndpts endpts[NREGIONS], const PatternPrec &pattern_prec, IntEndptsRGBA_2 q_endpts[NREGIONS])
{
	IntEndptsRGBA full_endpts[NREGIONS];

	for (int region = 0; region < NREGIONS; ++region)
	{
		full_endpts[region].A[0] = Utils::quantize(endpts[region].A.x, pattern_prec.region_precs[region].endpt_a_prec[0]+1);	// +1 since we are in uncompressed space
		full_endpts[region].A[1] = Utils::quantize(endpts[region].A.y, pattern_prec.region_precs[region].endpt_a_prec[1]+1);
		full_endpts[region].A[2] = Utils::quantize(endpts[region].A.z, pattern_prec.region_precs[region].endpt_a_prec[2]+1);
		full_endpts[region].A[3] = Utils::quantize(endpts[region].A.w, pattern_prec.region_precs[region].endpt_a_prec[3]+1);

		full_endpts[region].B[0] = Utils::quantize(endpts[region].B.x, pattern_prec.region_precs[region].endpt_b_prec[0]+1);
		full_endpts[region].B[1] = Utils::quantize(endpts[region].B.y, pattern_prec.region_precs[region].endpt_b_prec[1]+1);
		full_endpts[region].B[2] = Utils::quantize(endpts[region].B.z, pattern_prec.region_precs[region].endpt_b_prec[2]+1);
		full_endpts[region].B[3] = Utils::quantize(endpts[region].B.w, pattern_prec.region_precs[region].endpt_b_prec[3]+1);

		compress_one(full_endpts[region], q_endpts[region]);
	}
}

// swap endpoints as needed to ensure that the indices at index_one and index_two have a 0 high-order bit
// index_two is 0 at x=0 y=0 and 15 at x=3 y=3 so y = (index >> 2) & 3 and x = index & 3
static void swap_indices(IntEndptsRGBA_2 endpts[NREGIONS], int indices[Tile::TILE_H][Tile::TILE_W], int shapeindex)
{
	int index_positions[NREGIONS];

	index_positions[0] = 0;			// since WLOG we have the high bit of the shapes at 0

	for (int region = 0; region < NREGIONS; ++region)
	{
		int x = index_positions[region] & 3;
		int y = (index_positions[region] >> 2) & 3;
		nvAssert(REGION(x,y,shapeindex) == region);		// double check the table
		if (indices[y][x] & HIGH_INDEXBIT)
		{
			// high bit is set, swap the endpts and indices for this region
			int t;
			for (int i=0; i<NCHANNELS_RGBA; ++i) 
			{
				t = endpts[region].A[i]; endpts[region].A[i] = endpts[region].B[i]; endpts[region].B[i] = t;
			}
			t = endpts[region].a_lsb; endpts[region].a_lsb = endpts[region].b_lsb; endpts[region].b_lsb = t;

			for (int y = 0; y < Tile::TILE_H; y++)
			for (int x = 0; x < Tile::TILE_W; x++)
				if (REGION(x,y,shapeindex) == region)
					indices[y][x] = NINDICES - 1 - indices[y][x];
		}
	}
}

static bool endpts_fit(IntEndptsRGBA_2 endpts[NREGIONS], const Pattern &p)
{
	return true;
}

static void write_header(const IntEndptsRGBA_2 endpts[NREGIONS], int shapeindex, const Pattern &p, Bits &out)
{
	out.write(p.mode, p.modebits);

	for (int j=0; j<NCHANNELS_RGBA; ++j)
		for (int i=0; i<NREGIONS; ++i)
		{
			out.write(endpts[i].A[j], p.chan[j].nbitsizes[ABITINDEX(i)]);
			out.write(endpts[i].B[j], p.chan[j].nbitsizes[BBITINDEX(i)]);
		}

	for (int i=0; i<NREGIONS; ++i)
	{
		out.write(endpts[i].a_lsb, 1);
		out.write(endpts[i].b_lsb, 1);
	}

	nvAssert (out.getptr() == 65);
}

static void read_header(Bits &in, IntEndptsRGBA_2 endpts[NREGIONS], int &shapeindex, Pattern &p, int &pat_index)
{
	int mode = AVPCL::getmode(in);

	pat_index = 0;

	nvAssert (pat_index >= 0 && pat_index < NPATTERNS);
	nvAssert (in.getptr() == patterns[pat_index].modebits);

	p = patterns[pat_index];

	shapeindex = 0;		// we don't have any

	for (int j=0; j<NCHANNELS_RGBA; ++j)
		for (int i=0; i<NREGIONS; ++i)
		{
			endpts[i].A[j] = in.read(p.chan[j].nbitsizes[ABITINDEX(i)]);
			endpts[i].B[j] = in.read(p.chan[j].nbitsizes[BBITINDEX(i)]);
		}
	
	for (int i=0; i<NREGIONS; ++i)
	{
		endpts[i].a_lsb  = in.read(1);
		endpts[i].b_lsb  = in.read(1);
	}

	nvAssert (in.getptr() == 65);
}

static void write_indices(const int indices[Tile::TILE_H][Tile::TILE_W], int shapeindex, Bits &out)
{
	nvAssert ((indices[0][0] & HIGH_INDEXBIT) == 0);

	// the index we shorten is always index 0
	for (int i = 0; i < Tile::TILE_TOTAL; ++i)
	{
		if (i==0)
			out.write(indices[i>>2][i&3], INDEXBITS-1);	// write i..[2:0]
		else
			out.write(indices[i>>2][i&3], INDEXBITS);	// write i..[3:0]
	}

}

static void read_indices(Bits &in, int shapeindex, int indices[Tile::TILE_H][Tile::TILE_W])
{
	// the index we shorten is always index 0
	for (int i = 0; i < Tile::TILE_TOTAL; ++i)
	{
		if (i==0)
			indices[i>>2][i&3] = in.read(INDEXBITS-1);	// read i..[1:0]
		else
			indices[i>>2][i&3] = in.read(INDEXBITS);	// read i..[2:0]
	}
}

static void emit_block(const IntEndptsRGBA_2 endpts[NREGIONS], int shapeindex, const Pattern &p, const int indices[Tile::TILE_H][Tile::TILE_W], char *block)
{
	Bits out(block, AVPCL::BITSIZE);

	write_header(endpts, shapeindex, p, out);

	write_indices(indices, shapeindex, out);

	nvAssert(out.getptr() == AVPCL::BITSIZE);
}

static void generate_palette_quantized(const IntEndptsRGBA_2 &endpts_2, const RegionPrec &region_prec, Vector4 palette[NINDICES])
{
	IntEndptsRGBA endpts;

	uncompress_one(endpts_2, endpts);

	// scale endpoints
	int a, b;			// really need a IntVec4...

	a = Utils::unquantize(endpts.A[0], region_prec.endpt_a_prec[0]+1);	// +1 since we are in uncompressed space 
	b = Utils::unquantize(endpts.B[0], region_prec.endpt_b_prec[0]+1);

	// interpolate
	for (int i = 0; i < NINDICES; ++i)
		palette[i].x = float(Utils::lerp(a, b, i, BIAS, DENOM));

	a = Utils::unquantize(endpts.A[1], region_prec.endpt_a_prec[1]+1); 
	b = Utils::unquantize(endpts.B[1], region_prec.endpt_b_prec[1]+1);

	// interpolate
	for (int i = 0; i < NINDICES; ++i)
		palette[i].y = float(Utils::lerp(a, b, i, BIAS, DENOM));

	a = Utils::unquantize(endpts.A[2], region_prec.endpt_a_prec[2]+1); 
	b = Utils::unquantize(endpts.B[2], region_prec.endpt_b_prec[2]+1);

	// interpolate
	for (int i = 0; i < NINDICES; ++i)
		palette[i].z = float(Utils::lerp(a, b, i, BIAS, DENOM));

	a = Utils::unquantize(endpts.A[3], region_prec.endpt_a_prec[3]+1); 
	b = Utils::unquantize(endpts.B[3], region_prec.endpt_b_prec[3]+1);

	// interpolate
	for (int i = 0; i < NINDICES; ++i)
		palette[i].w = float(Utils::lerp(a, b, i, BIAS, DENOM));
}

void AVPCL::decompress_mode6(const char *block, Tile &t)
{
	Bits in(block, AVPCL::BITSIZE);

	Pattern p;
	IntEndptsRGBA_2 endpts[NREGIONS];
	int shapeindex, pat_index;

	read_header(in, endpts, shapeindex, p, pat_index);
	
	Vector4 palette[NREGIONS][NINDICES];
	for (int r = 0; r < NREGIONS; ++r)
		generate_palette_quantized(endpts[r], pattern_precs[pat_index].region_precs[r], &palette[r][0]);

	int indices[Tile::TILE_H][Tile::TILE_W];

	read_indices(in, shapeindex, indices);

	nvAssert(in.getptr() == AVPCL::BITSIZE);

	// lookup
	for (int y = 0; y < Tile::TILE_H; y++)
	for (int x = 0; x < Tile::TILE_W; x++)
		t.data[y][x] = palette[REGION(x,y,shapeindex)][indices[y][x]];
}

// given a collection of colors and quantized endpoints, generate a palette, choose best entries, and return a single toterr
static float map_colors(const Vector4 colors[], const float importance[], int np, const IntEndptsRGBA_2 &endpts, const RegionPrec &region_prec, float current_err, int indices[Tile::TILE_TOTAL])
{
	Vector4 palette[NINDICES];
	float toterr = 0;
	Vector4 err;

	generate_palette_quantized(endpts, region_prec, palette);

	for (int i = 0; i < np; ++i)
	{
		float err, besterr = FLT_MAX;

		for (int j = 0; j < NINDICES && besterr > 0; ++j)
		{
			err = !AVPCL::flag_premult ? Utils::metric4(colors[i], palette[j]) :
									     Utils::metric4premult(colors[i], palette[j]) ;

			if (err > besterr)	// error increased, so we're done searching
				break;
			if (err < besterr)
			{
				besterr = err;
				indices[i] = j;
			}
		}
		toterr += besterr;

		// check for early exit
		if (toterr > current_err)
		{
			// fill out bogus index values so it's initialized at least
			for (int k = i; k < np; ++k)
				indices[k] = -1;

			return FLT_MAX;
		}
	}
	return toterr;
}

// assign indices given a tile, shape, and quantized endpoints, return toterr for each region
static void assign_indices(const Tile &tile, int shapeindex, IntEndptsRGBA_2 endpts[NREGIONS], const PatternPrec &pattern_prec, 
						   int indices[Tile::TILE_H][Tile::TILE_W], float toterr[NREGIONS])
{
	// build list of possibles
	Vector4 palette[NREGIONS][NINDICES];

	for (int region = 0; region < NREGIONS; ++region)
	{
		generate_palette_quantized(endpts[region], pattern_prec.region_precs[region], &palette[region][0]);
		toterr[region] = 0;
	}

	Vector4 err;

	for (int y = 0; y < tile.size_y; y++)
	for (int x = 0; x < tile.size_x; x++)
	{
		int region = REGION(x,y,shapeindex);
		float err, besterr = FLT_MAX;

		for (int i = 0; i < NINDICES && besterr > 0; ++i)
		{
			err = !AVPCL::flag_premult ? Utils::metric4(tile.data[y][x], palette[region][i]) :
										 Utils::metric4premult(tile.data[y][x], palette[region][i]) ;

			if (err > besterr)	// error increased, so we're done searching
				break;
			if (err < besterr)
			{
				besterr = err;
				indices[y][x] = i;
			}
		}
		toterr[region] += besterr;
	}
}

// note: indices are valid only if the value returned is less than old_err; otherwise they contain -1's
// this function returns either old_err or a value smaller (if it was successful in improving the error)
static float perturb_one(const Vector4 colors[], const float importance[], int np, int ch, const RegionPrec &region_prec, const IntEndptsRGBA_2 &old_endpts, IntEndptsRGBA_2 &new_endpts,
						  float old_err, int do_b, int indices[Tile::TILE_TOTAL])
{
	// we have the old endpoints: old_endpts
	// we have the perturbed endpoints: new_endpts
	// we have the temporary endpoints: temp_endpts

	IntEndptsRGBA_2 temp_endpts;
	float min_err = old_err;		// start with the best current error
	int beststep;
	int temp_indices[Tile::TILE_TOTAL];

	for (int i=0; i<np; ++i)
		indices[i] = -1;

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

            float err = map_colors(colors, importance, np, temp_endpts, region_prec, min_err, temp_indices);

			if (err < min_err)
			{
				improved = true;
				min_err = err;
				beststep = sign * step;
				for (int i=0; i<np; ++i)
					indices[i] = temp_indices[i];
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
// if orig_err returned from this is less than its input value, then indices[] will contain valid indices
static float exhaustive(const Vector4 colors[], const float importance[], int np, int ch, const RegionPrec &region_prec, float orig_err, IntEndptsRGBA_2 &opt_endpts, int indices[Tile::TILE_TOTAL])
{
	IntEndptsRGBA_2 temp_endpts;
	float best_err = orig_err;
	int aprec = region_prec.endpt_a_prec[ch];
	int bprec = region_prec.endpt_b_prec[ch];
	int good_indices[Tile::TILE_TOTAL];
	int temp_indices[Tile::TILE_TOTAL];

	for (int i=0; i<np; ++i)
		indices[i] = -1;

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
		
            float err = map_colors(colors, importance, np, temp_endpts, region_prec, best_err, temp_indices);
			if (err < best_err) 
			{ 
				amin = a; 
				bmin = b; 
				best_err = err;
				for (int i=0; i<np; ++i)
					good_indices[i] = temp_indices[i];
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
		
            float err = map_colors(colors, importance, np, temp_endpts, region_prec, best_err, temp_indices);
			if (err < best_err) 
			{ 
				amin = a; 
				bmin = b; 
				best_err = err; 
				for (int i=0; i<np; ++i)
					good_indices[i] = temp_indices[i];
			}
		}
	}
	if (best_err < orig_err)
	{
		opt_endpts.A[ch] = amin;
		opt_endpts.B[ch] = bmin;
		orig_err = best_err;
		// if we actually improved, update the indices
		for (int i=0; i<np; ++i)
			indices[i] = good_indices[i];
	}
	return best_err;
}

static float optimize_one(const Vector4 colors[], const float importance[], int np, float orig_err, const IntEndptsRGBA_2 &orig_endpts, const RegionPrec &region_prec, IntEndptsRGBA_2 &opt_endpts)
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
	IntEndptsRGBA_2 new_a, new_b;
	IntEndptsRGBA_2 new_endpt;
	int do_b;
	int orig_indices[Tile::TILE_TOTAL];
	int new_indices[Tile::TILE_TOTAL];
	int temp_indices0[Tile::TILE_TOTAL];
	int temp_indices1[Tile::TILE_TOTAL];

	// now optimize each channel separately
	// for the first error improvement, we save the indices. then, for any later improvement, we compare the indices
	// if they differ, we restart the loop (which then falls back to looking for a first improvement.)
	for (int ch = 0; ch < NCHANNELS_RGBA; ++ch)
	{
		// figure out which endpoint when perturbed gives the most improvement and start there
		// if we just alternate, we can easily end up in a local minima
        float err0 = perturb_one(colors, importance, np, ch, region_prec, opt_endpts, new_a, opt_err, 0, temp_indices0);	// perturb endpt A
        float err1 = perturb_one(colors, importance, np, ch, region_prec, opt_endpts, new_b, opt_err, 1, temp_indices1);	// perturb endpt B

		if (err0 < err1)
		{
			if (err0 >= opt_err)
				continue;

			for (int i=0; i<np; ++i)
			{
				new_indices[i] = orig_indices[i] = temp_indices0[i];
				nvAssert (orig_indices[i] != -1);
			}

			opt_endpts.A[ch] = new_a.A[ch];
			opt_err = err0;
			do_b = 1;		// do B next
		}
		else
		{
			if (err1 >= opt_err)
				continue;

			for (int i=0; i<np; ++i)
			{
				new_indices[i] = orig_indices[i] = temp_indices1[i];
				nvAssert (orig_indices[i] != -1);
			}

			opt_endpts.B[ch] = new_b.B[ch];
			opt_err = err1;
			do_b = 0;		// do A next
		}
		
		// now alternate endpoints and keep trying until there is no improvement
		for (;;)
		{
            float err = perturb_one(colors, importance, np, ch, region_prec, opt_endpts, new_endpt, opt_err, do_b, temp_indices0);
			if (err >= opt_err)
				break;

			for (int i=0; i<np; ++i)
			{
				new_indices[i] = temp_indices0[i];
				nvAssert (new_indices[i] != -1);
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
			if (orig_indices[i] != new_indices[i])
				break;

		if (i<np)
			ch = -1;	// start over
	}

	// finally, do a small exhaustive search around what we think is the global minima to be sure
	// note this is independent of the above search, so we don't care about the indices from the above
	// we don't care about the above because if they differ, so what? we've already started at ch=0
	bool first = true;
	for (int ch = 0; ch < NCHANNELS_RGBA; ++ch)
	{
        float new_err = exhaustive(colors, importance, np, ch, region_prec, opt_err, opt_endpts, temp_indices0);

		if (new_err < opt_err)
		{
			opt_err = new_err;

			if (first)
			{
				for (int i=0; i<np; ++i)
				{
					orig_indices[i] = temp_indices0[i];
					nvAssert (orig_indices[i] != -1);
				}
				first = false;
			}
			else
			{
				// see if the indices have changed
				int i;
				for (i=0; i<np; ++i)
					if (orig_indices[i] != temp_indices0[i])
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

static void optimize_endpts(const Tile &tile, int shapeindex, const float orig_err[NREGIONS], 
							IntEndptsRGBA_2 orig_endpts[NREGIONS], const PatternPrec &pattern_prec, float opt_err[NREGIONS], IntEndptsRGBA_2 opt_endpts[NREGIONS])
{
	Vector4 pixels[Tile::TILE_TOTAL];
    float importance[Tile::TILE_TOTAL];
	IntEndptsRGBA_2 temp_in, temp_out;
	int temp_indices[Tile::TILE_TOTAL];

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

		// try all lsb modes as we search for better endpoints
		for (int lsbmode=0; lsbmode<NLSBMODES; ++lsbmode)
		{
			temp_in.a_lsb = lsbmode & 1;
			temp_in.b_lsb = (lsbmode >> 1) & 1;

			// make sure we have a valid error for temp_in
			// we use FLT_MAX here because we want an accurate temp_in_err, no shortcuts
			// (mapcolors will compute a mapping but will stop if the error exceeds the value passed in the FLT_MAX position)
            float temp_in_err = map_colors(pixels, importance, np, temp_in, pattern_prec.region_precs[region], FLT_MAX, temp_indices);

			// now try to optimize these endpoints
            float temp_out_err = optimize_one(pixels, importance, np, temp_in_err, temp_in, pattern_prec.region_precs[region], temp_out);

			// if we find an improvement, update the best so far and correct the output endpoints and errors
			if (temp_out_err < best_err)
			{
				best_err = temp_out_err;
				opt_err[region] = temp_out_err;
				opt_endpts[region] = temp_out;
			}
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

     simplify the above given that there is no transform now and that endpoints will always fit
*/

static float refine(const Tile &tile, int shapeindex_best, const FltEndpts endpts[NREGIONS], char *block)
{
	float orig_err[NREGIONS], opt_err[NREGIONS], orig_toterr, opt_toterr, expected_opt_err[NREGIONS];
	IntEndptsRGBA_2 orig_endpts[NREGIONS], opt_endpts[NREGIONS];
	int orig_indices[Tile::TILE_H][Tile::TILE_W], opt_indices[Tile::TILE_H][Tile::TILE_W];

	for (int sp = 0; sp < NPATTERNS; ++sp)
	{
		quantize_endpts(endpts, pattern_precs[sp], orig_endpts);
		assign_indices(tile, shapeindex_best, orig_endpts, pattern_precs[sp], orig_indices, orig_err);
		swap_indices(orig_endpts, orig_indices, shapeindex_best);

		optimize_endpts(tile, shapeindex_best, orig_err, orig_endpts, pattern_precs[sp], expected_opt_err, opt_endpts);

		assign_indices(tile, shapeindex_best, opt_endpts, pattern_precs[sp], opt_indices, opt_err);
		// (nreed) Commented out asserts because they go off all the time...not sure why
		//for (int i=0; i<NREGIONS; ++i)
		//	nvAssert(expected_opt_err[i] == opt_err[i]);
		swap_indices(opt_endpts, opt_indices, shapeindex_best);

		orig_toterr = opt_toterr = 0;
		for (int i=0; i < NREGIONS; ++i) { orig_toterr += orig_err[i]; opt_toterr += opt_err[i]; }
		//nvAssert(opt_toterr <= orig_toterr);

		if (opt_toterr < orig_toterr)
		{
			emit_block(opt_endpts, shapeindex_best, patterns[sp], opt_indices, block);
			return opt_toterr;
		}
		else
		{
			emit_block(orig_endpts, shapeindex_best, patterns[sp], orig_indices, block);
			return orig_toterr;
		}
	}
	nvAssert(false); //throw "No candidate found, should never happen (mode avpcl 6).";
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

static void generate_palette_unquantized(const FltEndpts endpts[NREGIONS], Vector4 palette[NREGIONS][NINDICES])
{
	for (int region = 0; region < NREGIONS; ++region)
	for (int i = 0; i < NINDICES; ++i)
		palette[region][i] = Utils::lerp(endpts[region].A, endpts[region].B, i, 0, DENOM);
}

// generate a palette from unquantized endpoints, then pick best palette color for all pixels in each region, return toterr for all regions combined
static float map_colors(const Tile &tile, int shapeindex, const FltEndpts endpts[NREGIONS])
{
	// build list of possibles
	Vector4 palette[NREGIONS][NINDICES];

	generate_palette_unquantized(endpts, palette);

	float toterr = 0;
	Vector4 err;

	for (int y = 0; y < tile.size_y; y++)
	for (int x = 0; x < tile.size_x; x++)
	{
		int region = REGION(x,y,shapeindex);
		float err, besterr;

		besterr = Utils::metric4(tile.data[y][x], palette[region][0]);

		for (int i = 1; i < NINDICES && besterr > 0; ++i)
		{
			err = Utils::metric4(tile.data[y][x], palette[region][i]);

			if (err > besterr)	// error increased, so we're done searching. this works for most norms.
				break;
			if (err < besterr)
				besterr = err;
		}
		toterr += besterr;
	}
	return toterr;
}

static float rough(const Tile &tile, int shapeindex, FltEndpts endpts[NREGIONS])
{
	for (int region=0; region<NREGIONS; ++region)
	{
		int np = 0;
		Vector4 colors[Tile::TILE_TOTAL];
		Vector4 mean(0,0,0,0);

		for (int y = 0; y < tile.size_y; y++)
		for (int x = 0; x < tile.size_x; x++)
			if (REGION(x,y,shapeindex) == region)
			{
				colors[np] = tile.data[y][x];
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
			endpts[region].A = colors[0];
			endpts[region].B = colors[0];
			continue;
		}
		else if (np == 2)
		{
			endpts[region].A = colors[0];
			endpts[region].B = colors[1];
			continue;
		}

		mean /= float(np);

		Vector4 direction = Fit::computePrincipalComponent_EigenSolver(np, colors);

		// project each pixel value along the principal direction
		float minp = FLT_MAX, maxp = -FLT_MAX;
		for (int i = 0; i < np; i++) 
		{
			float dp = dot(colors[i]-mean, direction);
			if (dp < minp) minp = dp;
			if (dp > maxp) maxp = dp;
		}

		// choose as endpoints 2 points along the principal direction that span the projections of all of the pixel values
		endpts[region].A = mean + minp*direction;
		endpts[region].B = mean + maxp*direction;

		// clamp endpoints
		// the argument for clamping is that the actual endpoints need to be clamped and thus we need to choose the best
		// shape based on endpoints being clamped
		clamp(endpts[region].A);
		clamp(endpts[region].B);
	}

	return map_colors(tile, shapeindex, endpts);
}

static void swap(float *list1, int *list2, int i, int j)
{
	float t = list1[i]; list1[i] = list1[j]; list1[j] = t;
	int t1 = list2[i]; list2[i] = list2[j]; list2[j] = t1;
}

float AVPCL::compress_mode6(const Tile &t, char *block)
{
	// number of rough cases to look at. reasonable values of this are 1, NSHAPES/4, and NSHAPES
	// NSHAPES/4 gets nearly all the cases; you can increase that a bit (say by 3 or 4) if you really want to squeeze the last bit out
	const int NITEMS=1;

	// pick the best NITEMS shapes and refine these.
	struct {
		FltEndpts endpts[NREGIONS];
	} all[NSHAPES];
	float roughmse[NSHAPES];
	int index[NSHAPES];
	char tempblock[AVPCL::BLOCKSIZE];
	float msebest = FLT_MAX;

	for (int i=0; i<NSHAPES; ++i)
	{
		roughmse[i] = rough(t, i, &all[i].endpts[0]);
		index[i] = i;
	}

	// bubble sort -- only need to bubble up the first NITEMS items
	for (int i=0; i<NITEMS; ++i)
	for (int j=i+1; j<NSHAPES; ++j)
		if (roughmse[i] > roughmse[j])
			swap(roughmse, index, i, j);

	for (int i=0; i<NITEMS && msebest>0; ++i)
	{
		int shape = index[i];
		float mse = refine(t, shape, &all[shape].endpts[0], tempblock);
		if (mse < msebest)
		{
			memcpy(block, tempblock, sizeof(tempblock));
			msebest = mse;
		}
	}
	return msebest;
}


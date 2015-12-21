/*
Copyright 2007 nVidia, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 

You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 

See the License for the specific language governing permissions and limitations under the License.
*/

// two regions zoh compress/decompress code
// Thanks to Jacob Munkberg (jacob@cs.lth.se) for the shortcut of using SVD to do the equivalent of principal components analysis

/* optimization algorithm

	get initial float endpoints
	convert endpoints using 16 bit precision, transform, and get bit delta. choose likely endpoint compression candidates.
		note that there will be 1 or 2 candidates; 2 will be chosen when the delta values are close to the max possible.
	for each EC candidate in order from max precision to smaller precision
		convert endpoints using the appropriate precision.
		optimize the endpoints and minimize square error. save the error and index assignments. apply index compression as well.
			(thus the endpoints and indices are in final form.)
		transform and get bit delta.
		if the bit delta fits, exit
	if we ended up with no candidates somehow, choose the tail set of EC candidates and retry. this should happen hardly ever.
		add a state variable to nvDebugCheck we only do this once.
	convert to bit stream.
	return the error.

	Global optimization
		order all tiles based on their errors
		do something special for high-error tiles
			the goal here is to try to avoid tiling artifacts. but I think this is a research problem. let's just generate an error image...

	display an image that shows partitioning and precision selected for each tile
*/

#include "bits.h"
#include "tile.h"
#include "zoh.h"
#include "zoh_utils.h"

#include "nvmath/fitting.h"
#include "nvmath/vector.inl"

#include <string.h> // strlen
#include <float.h> // FLT_MAX

using namespace nv;
using namespace ZOH;

#define NINDICES	8
#define	INDEXBITS	3
#define	HIGH_INDEXBIT	(1<<(INDEXBITS-1))
#define	DENOM		(NINDICES-1)

// WORK: determine optimal traversal pattern to search for best shape -- what does the error curve look like?
// i.e. can we search shapes in a particular order so we can see the global error minima easily and
// stop without having to touch all shapes?

#include "shapes_two.h"
// use only the first 32 available shapes
#undef NSHAPES
#undef SHAPEBITS
#define NSHAPES 32
#define SHAPEBITS 5

#define	POS_TO_X(pos)	((pos)&3)
#define	POS_TO_Y(pos)	(((pos)>>2)&3)

#define	NDELTA	4

struct Chanpat
{
    int prec[NDELTA];		// precision pattern for one channel
};

struct Pattern
{
    Chanpat chan[NCHANNELS];    // allow different bit patterns per channel -- but we still want constant precision per channel
    int transformed;            // if 0, deltas are unsigned and no transform; otherwise, signed and transformed
    int mode;                   // associated mode value
    int modebits;               // number of mode bits
    const char *encoding;       // verilog description of encoding for this mode
};

#define MAXMODEBITS	5
#define	MAXMODES (1<<MAXMODEBITS)

#define	NPATTERNS 10

static const Pattern patterns[NPATTERNS] =
{
    11,5,5,5,	11,4,4,4,	11,4,4,4,	1,	0x02, 5, "d[4:0],bz[3],rz[4:0],bz[2],ry[4:0],by[3:0],bz[1],bw[10],bx[3:0],gz[3:0],bz[0],gw[10],gx[3:0],gy[3:0],rw[10],rx[4:0],bw[9:0],gw[9:0],rw[9:0],m[4:0]",
    11,4,4,4,	11,5,5,5,	11,4,4,4,	1,	0x06, 5, "d[4:0],bz[3],gy[4],rz[3:0],bz[2],bz[0],ry[3:0],by[3:0],bz[1],bw[10],bx[3:0],gz[3:0],gw[10],gx[4:0],gy[3:0],gz[4],rw[10],rx[3:0],bw[9:0],gw[9:0],rw[9:0],m[4:0]",
    11,4,4,4,	11,4,4,4,	11,5,5,5,	1,	0x0a, 5, "d[4:0],bz[3],bz[4],rz[3:0],bz[2:1],ry[3:0],by[3:0],bw[10],bx[4:0],gz[3:0],bz[0],gw[10],gx[3:0],gy[3:0],by[4],rw[10],rx[3:0],bw[9:0],gw[9:0],rw[9:0],m[4:0]",
    10,5,5,5,	10,5,5,5,	10,5,5,5,	1,	0x00, 2, "d[4:0],bz[3],rz[4:0],bz[2],ry[4:0],by[3:0],bz[1],bx[4:0],gz[3:0],bz[0],gx[4:0],gy[3:0],gz[4],rx[4:0],bw[9:0],gw[9:0],rw[9:0],bz[4],by[4],gy[4],m[1:0]",
    9,5,5,5,	9,5,5,5,	9,5,5,5,	1,	0x0e, 5, "d[4:0],bz[3],rz[4:0],bz[2],ry[4:0],by[3:0],bz[1],bx[4:0],gz[3:0],bz[0],gx[4:0],gy[3:0],gz[4],rx[4:0],bz[4],bw[8:0],gy[4],gw[8:0],by[4],rw[8:0],m[4:0]",
    8,6,6,6,	8,5,5,5,	8,5,5,5,	1,	0x12, 5, "d[4:0],rz[5:0],ry[5:0],by[3:0],bz[1],bx[4:0],gz[3:0],bz[0],gx[4:0],gy[3:0],rx[5:0],bz[4:3],bw[7:0],gy[4],bz[2],gw[7:0],by[4],gz[4],rw[7:0],m[4:0]",
    8,5,5,5,	8,6,6,6,	8,5,5,5,	1,	0x16, 5, "d[4:0],bz[3],rz[4:0],bz[2],ry[4:0],by[3:0],bz[1],bx[4:0],gz[3:0],gx[5:0],gy[3:0],gz[4],rx[4:0],bz[4],gz[5],bw[7:0],gy[4],gy[5],gw[7:0],by[4],bz[0],rw[7:0],m[4:0]",
    8,5,5,5,	8,5,5,5,	8,6,6,6,	1,	0x1a, 5, "d[4:0],bz[3],rz[4:0],bz[2],ry[4:0],by[3:0],bx[5:0],gz[3:0],bz[0],gx[4:0],gy[3:0],gz[4],rx[4:0],bz[4],bz[5],bw[7:0],gy[4],by[5],gw[7:0],by[4],bz[1],rw[7:0],m[4:0]",
    7,6,6,6,	7,6,6,6,	7,6,6,6,	1,	0x01, 2, "d[4:0],rz[5:0],ry[5:0],by[3:0],bx[5:0],gz[3:0],gx[5:0],gy[3:0],rx[5:0],bz[4],bz[5],bz[3],bw[6:0],gy[4],bz[2],by[5],gw[6:0],by[4],bz[1:0],rw[6:0],gz[5:4],gy[5],m[1:0]",
    6,6,6,6,	6,6,6,6,	6,6,6,6,	0,	0x1e, 5, "d[4:0],rz[5:0],ry[5:0],by[3:0],bx[5:0],gz[3:0],gx[5:0],gy[3:0],rx[5:0],bz[4],bz[5],bz[3],gz[5],bw[5:0],gy[4],bz[2],by[5],gy[5],gw[5:0],by[4],bz[1:0],gz[4],rw[5:0],m[4:0]",
};

// mapping of mode to the corresponding index in pattern
// UNUSED ZOH MODES are 0x13, 0x17, 0x1b, 0x1f -- return -2 for these
static const int mode_to_pat[MAXMODES] = {	
    3,	// 0x00
    8,	// 0x01
    0,	// 0x02
    -1,-1,-1,
    1,	// 0x06
    -1,-1,-1,
    2,	// 0x0a
    -1,-1,-1,
    4,	// 0x0e
    -1,-1,-1,
    5,	// 0x12
    -2,-1,-1,
    6,	// 0x16
    -2,-1,-1,
    7,	// 0x1a
    -2,-1,-1,
    9,	// 0x1e
    -2
};

#define	R_0(ep)	(ep)[0].A[i]
#define	R_1(ep)	(ep)[0].B[i]
#define	R_2(ep)	(ep)[1].A[i]
#define	R_3(ep)	(ep)[1].B[i]
#define	MASK(n)	((1<<(n))-1)

// compress endpoints
static void compress_endpts(const IntEndpts in[NREGIONS_TWO], ComprEndpts out[NREGIONS_TWO], const Pattern &p)
{
    if (p.transformed)
    {
        for (int i=0; i<NCHANNELS; ++i)
        {
            R_0(out) = R_0(in) & MASK(p.chan[i].prec[0]);
            R_1(out) = (R_1(in) - R_0(in)) & MASK(p.chan[i].prec[1]);
            R_2(out) = (R_2(in) - R_0(in)) & MASK(p.chan[i].prec[2]);
            R_3(out) = (R_3(in) - R_0(in)) & MASK(p.chan[i].prec[3]);
        }
    }
    else
    {
        for (int i=0; i<NCHANNELS; ++i)
        {
            R_0(out) = R_0(in) & MASK(p.chan[i].prec[0]);
            R_1(out) = R_1(in) & MASK(p.chan[i].prec[1]);
            R_2(out) = R_2(in) & MASK(p.chan[i].prec[2]);
            R_3(out) = R_3(in) & MASK(p.chan[i].prec[3]);
        }
    }
}

// decompress endpoints
static void decompress_endpts(const ComprEndpts in[NREGIONS_TWO], IntEndpts out[NREGIONS_TWO], const Pattern &p)
{
    bool issigned = Utils::FORMAT == SIGNED_F16;

    if (p.transformed)
    {
        for (int i=0; i<NCHANNELS; ++i)
        {
            R_0(out) = issigned ? SIGN_EXTEND(R_0(in),p.chan[i].prec[0]) : R_0(in);
            int t;
            t = SIGN_EXTEND(R_1(in), p.chan[i].prec[1]);
            t = (t + R_0(in)) & MASK(p.chan[i].prec[0]);
            R_1(out) = issigned ? SIGN_EXTEND(t,p.chan[i].prec[0]) : t;
            t = SIGN_EXTEND(R_2(in), p.chan[i].prec[2]);
            t = (t + R_0(in)) & MASK(p.chan[i].prec[0]);
            R_2(out) = issigned ? SIGN_EXTEND(t,p.chan[i].prec[0]) : t;
            t = SIGN_EXTEND(R_3(in), p.chan[i].prec[3]);
            t = (t + R_0(in)) & MASK(p.chan[i].prec[0]);
            R_3(out) = issigned ? SIGN_EXTEND(t,p.chan[i].prec[0]) : t;
        }
    }
    else
    {
        for (int i=0; i<NCHANNELS; ++i)
        {
            R_0(out) = issigned ? SIGN_EXTEND(R_0(in),p.chan[i].prec[0]) : R_0(in);
            R_1(out) = issigned ? SIGN_EXTEND(R_1(in),p.chan[i].prec[1]) : R_1(in);
            R_2(out) = issigned ? SIGN_EXTEND(R_2(in),p.chan[i].prec[2]) : R_2(in);
            R_3(out) = issigned ? SIGN_EXTEND(R_3(in),p.chan[i].prec[3]) : R_3(in);
        }
    }
}

static void quantize_endpts(const FltEndpts endpts[NREGIONS_TWO], int prec, IntEndpts q_endpts[NREGIONS_TWO])
{
    for (int region = 0; region < NREGIONS_TWO; ++region)
    {
        q_endpts[region].A[0] = Utils::quantize(endpts[region].A.x, prec);
        q_endpts[region].A[1] = Utils::quantize(endpts[region].A.y, prec);
        q_endpts[region].A[2] = Utils::quantize(endpts[region].A.z, prec);
        q_endpts[region].B[0] = Utils::quantize(endpts[region].B.x, prec);
        q_endpts[region].B[1] = Utils::quantize(endpts[region].B.y, prec);
        q_endpts[region].B[2] = Utils::quantize(endpts[region].B.z, prec);
    }
}

// swap endpoints as needed to ensure that the indices at index_positions have a 0 high-order bit
static void swap_indices(IntEndpts endpts[NREGIONS_TWO], int indices[Tile::TILE_H][Tile::TILE_W], int shapeindex)
{
    for (int region = 0; region < NREGIONS_TWO; ++region)
    {
        int position = SHAPEINDEX_TO_COMPRESSED_INDICES(shapeindex,region);

        int x = POS_TO_X(position);
        int y = POS_TO_Y(position);
        nvDebugCheck(REGION(x,y,shapeindex) == region);		// double check the table
        if (indices[y][x] & HIGH_INDEXBIT)
        {
            // high bit is set, swap the endpts and indices for this region
            int t;
            for (int i=0; i<NCHANNELS; ++i)
            {
                t = endpts[region].A[i]; endpts[region].A[i] = endpts[region].B[i]; endpts[region].B[i] = t;
            }

            for (int y = 0; y < Tile::TILE_H; y++)
                for (int x = 0; x < Tile::TILE_W; x++)
                    if (REGION(x,y,shapeindex) == region)
                        indices[y][x] = NINDICES - 1 - indices[y][x];
        }
    }
}

// endpoints fit only if the compression was lossless
static bool endpts_fit(const IntEndpts orig[NREGIONS_TWO], const ComprEndpts compressed[NREGIONS_TWO], const Pattern &p)
{
    IntEndpts uncompressed[NREGIONS_TWO];

    decompress_endpts(compressed, uncompressed, p);

    for (int j=0; j<NREGIONS_TWO; ++j)
    {
	for (int i=0; i<NCHANNELS; ++i)
	{
            if (orig[j].A[i] != uncompressed[j].A[i]) return false;
            if (orig[j].B[i] != uncompressed[j].B[i]) return false;
        }
    }
    return true;
}

static void write_header(const ComprEndpts endpts[NREGIONS_TWO], int shapeindex, const Pattern &p, Bits &out)
{
    // interpret the verilog backwards and process it
    int m = p.mode;
    int d = shapeindex;
    int rw = endpts[0].A[0], rx = endpts[0].B[0], ry = endpts[1].A[0], rz = endpts[1].B[0];
    int gw = endpts[0].A[1], gx = endpts[0].B[1], gy = endpts[1].A[1], gz = endpts[1].B[1];
    int bw = endpts[0].A[2], bx = endpts[0].B[2], by = endpts[1].A[2], bz = endpts[1].B[2];
    int ptr = int(strlen(p.encoding));
    while (ptr)
    {
        Field field;
        int endbit, len;

		// !!!UNDONE: get rid of string parsing!!!
        Utils::parse(p.encoding, ptr, field, endbit, len);
        switch(field)
        {
        case FIELD_M:	out.write( m >> endbit, len); break;
        case FIELD_D:	out.write( d >> endbit, len); break;
        case FIELD_RW:	out.write(rw >> endbit, len); break;
        case FIELD_RX:	out.write(rx >> endbit, len); break;
        case FIELD_RY:	out.write(ry >> endbit, len); break;
        case FIELD_RZ:	out.write(rz >> endbit, len); break;
        case FIELD_GW:	out.write(gw >> endbit, len); break;
        case FIELD_GX:	out.write(gx >> endbit, len); break;
        case FIELD_GY:	out.write(gy >> endbit, len); break;
        case FIELD_GZ:	out.write(gz >> endbit, len); break;
        case FIELD_BW:	out.write(bw >> endbit, len); break;
        case FIELD_BX:	out.write(bx >> endbit, len); break;
        case FIELD_BY:	out.write(by >> endbit, len); break;
        case FIELD_BZ:	out.write(bz >> endbit, len); break;
        default: nvUnreachable();
        }
    }
}

static bool read_header(Bits &in, ComprEndpts endpts[NREGIONS_TWO], int &shapeindex, Pattern &p)
{
    // reading isn't quite symmetric with writing -- we don't know the encoding until we decode the mode
    int mode = in.read(2);
    if (mode != 0x00 && mode != 0x01)
        mode = (in.read(3) << 2) | mode;

    int pat_index = mode_to_pat[mode];

    if (pat_index == -2)
        return false;		// reserved mode found

    nvDebugCheck (pat_index >= 0 && pat_index < NPATTERNS);
    nvDebugCheck (in.getptr() == patterns[pat_index].modebits);

    p = patterns[pat_index];

    int d;
    int rw, rx, ry, rz;
    int gw, gx, gy, gz;
    int bw, bx, by, bz;

    d = 0;
    rw = rx = ry = rz = 0;
    gw = gx = gy = gz = 0;
    bw = bx = by = bz = 0;

    int ptr = int(strlen(p.encoding));

    while (ptr)
    {
        Field field;
        int endbit, len;

		// !!!UNDONE: get rid of string parsing!!!
        Utils::parse(p.encoding, ptr, field, endbit, len);

        switch(field)
        {
        case FIELD_M:	break;	// already processed so ignore
        case FIELD_D:	 d |= in.read(len) << endbit; break;
        case FIELD_RW:	rw |= in.read(len) << endbit; break;
        case FIELD_RX:	rx |= in.read(len) << endbit; break;
        case FIELD_RY:	ry |= in.read(len) << endbit; break;
        case FIELD_RZ:	rz |= in.read(len) << endbit; break;
        case FIELD_GW:	gw |= in.read(len) << endbit; break;
        case FIELD_GX:	gx |= in.read(len) << endbit; break;
        case FIELD_GY:	gy |= in.read(len) << endbit; break;
        case FIELD_GZ:	gz |= in.read(len) << endbit; break;
        case FIELD_BW:	bw |= in.read(len) << endbit; break;
        case FIELD_BX:	bx |= in.read(len) << endbit; break;
        case FIELD_BY:	by |= in.read(len) << endbit; break;
        case FIELD_BZ:	bz |= in.read(len) << endbit; break;
        default: nvUnreachable();
        }
    }

    nvDebugCheck (in.getptr() == 128 - 46);

    shapeindex = d;
    endpts[0].A[0] = rw; endpts[0].B[0] = rx; endpts[1].A[0] = ry; endpts[1].B[0] = rz;
    endpts[0].A[1] = gw; endpts[0].B[1] = gx; endpts[1].A[1] = gy; endpts[1].B[1] = gz;
    endpts[0].A[2] = bw; endpts[0].B[2] = bx; endpts[1].A[2] = by; endpts[1].B[2] = bz;

    return true;
}

static void write_indices(const int indices[Tile::TILE_H][Tile::TILE_W], int shapeindex, Bits &out)
{
    int positions[NREGIONS_TWO];

    for (int r = 0; r < NREGIONS_TWO; ++r)
        positions[r] = SHAPEINDEX_TO_COMPRESSED_INDICES(shapeindex,r);

    for (int pos = 0; pos < Tile::TILE_TOTAL; ++pos)
    {
        int x = POS_TO_X(pos);
        int y = POS_TO_Y(pos);

        bool match = false;

        for (int r = 0; r < NREGIONS_TWO; ++r)
            if (positions[r] == pos) { match = true; break; }

        out.write(indices[y][x], INDEXBITS - (match ? 1 : 0));
    }
}

static void emit_block(const ComprEndpts compr_endpts[NREGIONS_TWO], int shapeindex, const Pattern &p, const int indices[Tile::TILE_H][Tile::TILE_W], char *block)
{
    Bits out(block, ZOH::BITSIZE);

    write_header(compr_endpts, shapeindex, p, out);

    write_indices(indices, shapeindex, out);

    nvDebugCheck(out.getptr() == ZOH::BITSIZE);
}

static void generate_palette_quantized(const IntEndpts &endpts, int prec, Vector3 palette[NINDICES])
{
    // scale endpoints
    int a, b;			// really need a IntVector3...

    a = Utils::unquantize(endpts.A[0], prec);
    b = Utils::unquantize(endpts.B[0], prec);

    // interpolate
    for (int i = 0; i < NINDICES; ++i)
        palette[i].x = float(Utils::finish_unquantize(Utils::lerp(a, b, i, DENOM), prec));

    a = Utils::unquantize(endpts.A[1], prec);
    b = Utils::unquantize(endpts.B[1], prec);

    // interpolate
    for (int i = 0; i < NINDICES; ++i)
        palette[i].y = float(Utils::finish_unquantize(Utils::lerp(a, b, i, DENOM), prec));

    a = Utils::unquantize(endpts.A[2], prec);
    b = Utils::unquantize(endpts.B[2], prec);

    // interpolate
    for (int i = 0; i < NINDICES; ++i)
        palette[i].z = float(Utils::finish_unquantize(Utils::lerp(a, b, i, DENOM), prec));
}

static void read_indices(Bits &in, int shapeindex, int indices[Tile::TILE_H][Tile::TILE_W])
{
    int positions[NREGIONS_TWO];

    for (int r = 0; r < NREGIONS_TWO; ++r)
        positions[r] = SHAPEINDEX_TO_COMPRESSED_INDICES(shapeindex,r);

    for (int pos = 0; pos < Tile::TILE_TOTAL; ++pos)
    {
        int x = POS_TO_X(pos);
        int y = POS_TO_Y(pos);

        bool match = false;

        for (int r = 0; r < NREGIONS_TWO; ++r)
            if (positions[r] == pos) { match = true; break; }

        indices[y][x]= in.read(INDEXBITS - (match ? 1 : 0));
    }
}

void ZOH::decompresstwo(const char *block, Tile &t)
{
    Bits in(block, ZOH::BITSIZE);

    Pattern p;
    IntEndpts endpts[NREGIONS_TWO];
    ComprEndpts compr_endpts[NREGIONS_TWO];
    int shapeindex;

    if (!read_header(in, compr_endpts, shapeindex, p))
    {
        // reserved mode, return all zeroes
        for (int y = 0; y < Tile::TILE_H; y++)
            for (int x = 0; x < Tile::TILE_W; x++)
                t.data[y][x] = Vector3(0.0f);

        return;
    }

    decompress_endpts(compr_endpts, endpts, p);

    Vector3 palette[NREGIONS_TWO][NINDICES];
    for (int r = 0; r < NREGIONS_TWO; ++r)
        generate_palette_quantized(endpts[r], p.chan[0].prec[0], &palette[r][0]);

    int indices[Tile::TILE_H][Tile::TILE_W];

    read_indices(in, shapeindex, indices);

    nvDebugCheck(in.getptr() == ZOH::BITSIZE);

    // lookup
    for (int y = 0; y < Tile::TILE_H; y++)
	for (int x = 0; x < Tile::TILE_W; x++)
        t.data[y][x] = palette[REGION(x,y,shapeindex)][indices[y][x]];
}

// given a collection of colors and quantized endpoints, generate a palette, choose best entries, and return a single toterr
static float map_colors(const Vector3 colors[], const float importance[], int np, const IntEndpts &endpts, int prec)
{
    Vector3 palette[NINDICES];
    float toterr = 0;
    Vector3 err;

    generate_palette_quantized(endpts, prec, palette);

    for (int i = 0; i < np; ++i)
    {
        float err, besterr;

        besterr = Utils::norm(colors[i], palette[0]) * importance[i];

        for (int j = 1; j < NINDICES && besterr > 0; ++j)
        {
            err = Utils::norm(colors[i], palette[j]) * importance[i];

            if (err > besterr)	// error increased, so we're done searching
                break;
            if (err < besterr)
                besterr = err;
        }
        toterr += besterr;
    }
    return toterr;
}

// assign indices given a tile, shape, and quantized endpoints, return toterr for each region
static void assign_indices(const Tile &tile, int shapeindex, IntEndpts endpts[NREGIONS_TWO], int prec, 
                           int indices[Tile::TILE_H][Tile::TILE_W], float toterr[NREGIONS_TWO])
{
    // build list of possibles
    Vector3 palette[NREGIONS_TWO][NINDICES];

    for (int region = 0; region < NREGIONS_TWO; ++region)
    {
        generate_palette_quantized(endpts[region], prec, &palette[region][0]);
        toterr[region] = 0;
    }

    Vector3 err;

    for (int y = 0; y < tile.size_y; y++)
	for (int x = 0; x < tile.size_x; x++)
	{
        int region = REGION(x,y,shapeindex);
        float err, besterr;

        besterr = Utils::norm(tile.data[y][x], palette[region][0]);
        indices[y][x] = 0;

        for (int i = 1; i < NINDICES && besterr > 0; ++i)
        {
            err = Utils::norm(tile.data[y][x], palette[region][i]);

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

static float perturb_one(const Vector3 colors[], const float importance[], int np, int ch, int prec, const IntEndpts &old_endpts, IntEndpts &new_endpts,
                          float old_err, int do_b)
{
    // we have the old endpoints: old_endpts
    // we have the perturbed endpoints: new_endpts
    // we have the temporary endpoints: temp_endpts

    IntEndpts temp_endpts;
    float min_err = old_err;		// start with the best current error
    int beststep;

    // copy real endpoints so we can perturb them
    for (int i=0; i<NCHANNELS; ++i) { temp_endpts.A[i] = new_endpts.A[i] = old_endpts.A[i]; temp_endpts.B[i] = new_endpts.B[i] = old_endpts.B[i]; }

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

            float err = map_colors(colors, importance, np, temp_endpts, prec);

            if (err < min_err)
            {
                improved = true;
                min_err = err;
                beststep = sign * step;
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

static void optimize_one(const Vector3 colors[], const float importance[], int np, float orig_err, const IntEndpts &orig_endpts, int prec, IntEndpts &opt_endpts)
{
    float opt_err = orig_err;
    for (int ch = 0; ch < NCHANNELS; ++ch)
    {
        opt_endpts.A[ch] = orig_endpts.A[ch];
        opt_endpts.B[ch] = orig_endpts.B[ch];
    }
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
    IntEndpts new_a, new_b;
    IntEndpts new_endpt;
    int do_b;

    // now optimize each channel separately
    for (int ch = 0; ch < NCHANNELS; ++ch)
    {
        // figure out which endpoint when perturbed gives the most improvement and start there
        // if we just alternate, we can easily end up in a local minima
        float err0 = perturb_one(colors, importance, np, ch, prec, opt_endpts, new_a, opt_err, 0);	// perturb endpt A
        float err1 = perturb_one(colors, importance, np, ch, prec, opt_endpts, new_b, opt_err, 1);	// perturb endpt B

        if (err0 < err1)
        {
            if (err0 >= opt_err)
                continue;

            opt_endpts.A[ch] = new_a.A[ch];
            opt_err = err0;
            do_b = 1;		// do B next
        }
        else
        {
            if (err1 >= opt_err)
                continue;
            opt_endpts.B[ch] = new_b.B[ch];
            opt_err = err1;
            do_b = 0;		// do A next
        }

        // now alternate endpoints and keep trying until there is no improvement
        for (;;)
        {
            float err = perturb_one(colors, importance, np, ch, prec, opt_endpts, new_endpt, opt_err, do_b);
            if (err >= opt_err)
                break;
            if (do_b == 0)
                opt_endpts.A[ch] = new_endpt.A[ch];
            else
                opt_endpts.B[ch] = new_endpt.B[ch];
            opt_err = err;
            do_b = 1 - do_b;	// now move the other endpoint
        }
    }
}

static void optimize_endpts(const Tile &tile, int shapeindex, const float orig_err[NREGIONS_TWO], 
                            const IntEndpts orig_endpts[NREGIONS_TWO], int prec, IntEndpts opt_endpts[NREGIONS_TWO])
{
    Vector3 pixels[Tile::TILE_TOTAL];
    float importance[Tile::TILE_TOTAL];
    float err = 0;

    for (int region=0; region<NREGIONS_TWO; ++region)
    {
        // collect the pixels in the region
        int np = 0;

        for (int y = 0; y < tile.size_y; y++)
            for (int x = 0; x < tile.size_x; x++)
                if (REGION(x,y,shapeindex) == region)
                {
            pixels[np] = tile.data[y][x];
            importance[np] = tile.importance_map[y][x];
            ++np;
        }

        optimize_one(pixels, importance, np, orig_err[region], orig_endpts[region], prec, opt_endpts[region]);
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

float ZOH::refinetwo(const Tile &tile, int shapeindex_best, const FltEndpts endpts[NREGIONS_TWO], char *block)
{
    float orig_err[NREGIONS_TWO], opt_err[NREGIONS_TWO], orig_toterr, opt_toterr;
    IntEndpts orig_endpts[NREGIONS_TWO], opt_endpts[NREGIONS_TWO];
    ComprEndpts compr_orig[NREGIONS_TWO], compr_opt[NREGIONS_TWO];
    int orig_indices[Tile::TILE_H][Tile::TILE_W], opt_indices[Tile::TILE_H][Tile::TILE_W];

    for (int sp = 0; sp < NPATTERNS; ++sp)
    {
        // precisions for all channels need to be the same
        for (int i=1; i<NCHANNELS; ++i) nvDebugCheck (patterns[sp].chan[0].prec[0] == patterns[sp].chan[i].prec[0]);

        quantize_endpts(endpts, patterns[sp].chan[0].prec[0], orig_endpts);
        assign_indices(tile, shapeindex_best, orig_endpts, patterns[sp].chan[0].prec[0], orig_indices, orig_err);
        swap_indices(orig_endpts, orig_indices, shapeindex_best);
        compress_endpts(orig_endpts, compr_orig, patterns[sp]);
        if (endpts_fit(orig_endpts, compr_orig, patterns[sp]))
        {
            optimize_endpts(tile, shapeindex_best, orig_err, orig_endpts, patterns[sp].chan[0].prec[0], opt_endpts);
            assign_indices(tile, shapeindex_best, opt_endpts, patterns[sp].chan[0].prec[0], opt_indices, opt_err);
            swap_indices(opt_endpts, opt_indices, shapeindex_best);
            compress_endpts(opt_endpts, compr_opt, patterns[sp]);
            orig_toterr = opt_toterr = 0;
            for (int i=0; i < NREGIONS_TWO; ++i) { orig_toterr += orig_err[i]; opt_toterr += opt_err[i]; }
            if (endpts_fit(opt_endpts, compr_opt, patterns[sp]) && opt_toterr < orig_toterr)
            {
                emit_block(compr_opt, shapeindex_best, patterns[sp], opt_indices, block);
                return opt_toterr;
            }
            else
            {
                // either it stopped fitting when we optimized it, or there was no improvement
                // so go back to the unoptimized endpoints which we know will fit
                emit_block(compr_orig, shapeindex_best, patterns[sp], orig_indices, block);
                return orig_toterr;
            }
        }
    }
    nvAssert(false); //throw "No candidate found, should never happen (refinetwo.)";
	return FLT_MAX;
}

static void generate_palette_unquantized(const FltEndpts endpts[NREGIONS_TWO], Vector3 palette[NREGIONS_TWO][NINDICES])
{
    for (int region = 0; region < NREGIONS_TWO; ++region)
	for (int i = 0; i < NINDICES; ++i)
            palette[region][i] = Utils::lerp(endpts[region].A, endpts[region].B, i, DENOM);
}

// generate a palette from unquantized endpoints, then pick best palette color for all pixels in each region, return toterr for all regions combined
static float map_colors(const Tile &tile, int shapeindex, const FltEndpts endpts[NREGIONS_TWO])
{
    // build list of possibles
    Vector3 palette[NREGIONS_TWO][NINDICES];

    generate_palette_unquantized(endpts, palette);

    float toterr = 0;
    Vector3 err;

    for (int y = 0; y < tile.size_y; y++)
	for (int x = 0; x < tile.size_x; x++)
	{
        int region = REGION(x,y,shapeindex);
        float err, besterr;

        besterr = Utils::norm(tile.data[y][x], palette[region][0]) * tile.importance_map[y][x];

        for (int i = 1; i < NINDICES && besterr > 0; ++i)
        {
            err = Utils::norm(tile.data[y][x], palette[region][i]) * tile.importance_map[y][x];

            if (err > besterr)	// error increased, so we're done searching
                break;
            if (err < besterr)
                besterr = err;
        }
        toterr += besterr;
    }
    return toterr;
}

float ZOH::roughtwo(const Tile &tile, int shapeindex, FltEndpts endpts[NREGIONS_TWO])
{
    for (int region=0; region<NREGIONS_TWO; ++region)
    {
        int np = 0;
        Vector3 colors[Tile::TILE_TOTAL];
        Vector3 mean(0,0,0);

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
            Vector3 zero(0,0,0);
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

        Vector3 direction = Fit::computePrincipalComponent_EigenSolver(np, colors);

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
        Utils::clamp(endpts[region].A);
        Utils::clamp(endpts[region].B);
    }

    return map_colors(tile, shapeindex, endpts);
}

float ZOH::compresstwo(const Tile &t, char *block)
{
    int shapeindex_best = 0;
    FltEndpts endptsbest[NREGIONS_TWO], tempendpts[NREGIONS_TWO];
    float msebest = FLT_MAX;

    /*
    collect the mse values that are within 5% of the best values
    optimize each one and choose the best
    */
    // hack for now -- just use the best value WORK
    for (int i=0; i<NSHAPES && msebest>0.0; ++i)
    {
        float mse = roughtwo(t, i, tempendpts);
        if (mse < msebest)
        {
            msebest = mse;
            shapeindex_best = i;
            memcpy(endptsbest, tempendpts, sizeof(endptsbest));
        }

    }
    return refinetwo(t, shapeindex_best, endptsbest, block);
}


/*
Copyright 2007 nVidia, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 

You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 

See the License for the specific language governing permissions and limitations under the License.
*/

// one region zoh compress/decompress code
// Thanks to Jacob Munkberg (jacob@cs.lth.se) for the shortcut of using SVD to do the equivalent of principal components analysis

#include "bits.h"
#include "tile.h"
#include "zoh.h"
#include "zoh_utils.h"

#include "nvmath/Vector.inl"
#include "nvmath/Fitting.h"

#include <string.h> // strlen
#include <float.h> // FLT_MAX

using namespace nv;
using namespace ZOH;

#define NINDICES	16
#define	INDEXBITS	4
#define	HIGH_INDEXBIT	(1<<(INDEXBITS-1))
#define	DENOM		(NINDICES-1)

#define	NSHAPES	1

static const int shapes[NSHAPES] =
{
    0x0000
};	// only 1 shape

#define	REGION(x,y,shapeindex)	((shapes[shapeindex]&(1<<(15-(x)-4*(y))))!=0)

#define	POS_TO_X(pos)	((pos)&3)
#define	POS_TO_Y(pos)	(((pos)>>2)&3)

#define	NDELTA	2

struct Chanpat
{
    int prec[NDELTA];		// precision pattern for one channel
};

struct Pattern
{
    Chanpat chan[NCHANNELS];// allow different bit patterns per channel -- but we still want constant precision per channel
    int transformed;		// if 0, deltas are unsigned and no transform; otherwise, signed and transformed
    int mode;				// associated mode value
    int modebits;			// number of mode bits
    const char *encoding;	// verilog description of encoding for this mode
};

#define MAXMODEBITS	5
#define	MAXMODES (1<<MAXMODEBITS)

#define	NPATTERNS 4

static const Pattern patterns[NPATTERNS] =
{
    16,4,  16,4,  16,4,   1, 0x0f, 5, "bw[10],bw[11],bw[12],bw[13],bw[14],bw[15],bx[3:0],gw[10],gw[11],gw[12],gw[13],gw[14],gw[15],gx[3:0],rw[10],rw[11],rw[12],rw[13],rw[14],rw[15],rx[3:0],bw[9:0],gw[9:0],rw[9:0],m[4:0]",
    12,8,  12,8,  12,8,   1, 0x0b, 5, "bw[10],bw[11],bx[7:0],gw[10],gw[11],gx[7:0],rw[10],rw[11],rx[7:0],bw[9:0],gw[9:0],rw[9:0],m[4:0]",
    11,9,  11,9,  11,9,   1, 0x07, 5, "bw[10],bx[8:0],gw[10],gx[8:0],rw[10],rx[8:0],bw[9:0],gw[9:0],rw[9:0],m[4:0]",
    10,10, 10,10, 10,10,  0, 0x03, 5, "bx[9:0],gx[9:0],rx[9:0],bw[9:0],gw[9:0],rw[9:0],m[4:0]",
};

// mapping of mode to the corresponding index in pattern
static const int mode_to_pat[MAXMODES] = {
    -1,-1,-1,
    3,	// 0x03
    -1,-1,-1,
    2,	// 0x07
    -1,-1,-1,
    1,	// 0x0b
    -1,-1,-1,
    0,	// 0x0f
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
};

#define	R_0(ep)	(ep)[0].A[i]
#define	R_1(ep)	(ep)[0].B[i]
#define	MASK(n)	((1<<(n))-1)

// compress endpoints
static void compress_endpts(const IntEndpts in[NREGIONS_ONE], ComprEndpts out[NREGIONS_ONE], const Pattern &p)
{
    if (p.transformed)
    {
        for (int i=0; i<NCHANNELS; ++i)
        {
            R_0(out) = R_0(in) & MASK(p.chan[i].prec[0]);
            R_1(out) = (R_1(in) - R_0(in)) & MASK(p.chan[i].prec[1]);
        }
    }
    else
    {
        for (int i=0; i<NCHANNELS; ++i)
        {
            R_0(out) = R_0(in) & MASK(p.chan[i].prec[0]);
            R_1(out) = R_1(in) & MASK(p.chan[i].prec[1]);
        }
    }
}

// decompress endpoints
static void decompress_endpts(const ComprEndpts in[NREGIONS_ONE], IntEndpts out[NREGIONS_ONE], const Pattern &p)
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
        }
    }
    else
    {
        for (int i=0; i<NCHANNELS; ++i)
        {
            R_0(out) = issigned ? SIGN_EXTEND(R_0(in),p.chan[i].prec[0]) : R_0(in);
            R_1(out) = issigned ? SIGN_EXTEND(R_1(in),p.chan[i].prec[1]) : R_1(in);
        }
    }
}

static void quantize_endpts(const FltEndpts endpts[NREGIONS_ONE], int prec, IntEndpts q_endpts[NREGIONS_ONE])
{
    for (int region = 0; region < NREGIONS_ONE; ++region)
    {
        q_endpts[region].A[0] = Utils::quantize(endpts[region].A.x, prec);
        q_endpts[region].A[1] = Utils::quantize(endpts[region].A.y, prec);
        q_endpts[region].A[2] = Utils::quantize(endpts[region].A.z, prec);
        q_endpts[region].B[0] = Utils::quantize(endpts[region].B.x, prec);
        q_endpts[region].B[1] = Utils::quantize(endpts[region].B.y, prec);
        q_endpts[region].B[2] = Utils::quantize(endpts[region].B.z, prec);
    }
}

// swap endpoints as needed to ensure that the indices at index_one and index_one have a 0 high-order bit
// index_one is 0 at x=0 y=0 and 15 at x=3 y=3 so y = (index >> 2) & 3 and x = index & 3
static void swap_indices(IntEndpts endpts[NREGIONS_ONE], int indices[Tile::TILE_H][Tile::TILE_W], int shapeindex)
{
    int index_positions[NREGIONS_ONE];

    index_positions[0] = 0;			// since WLOG we have the high bit of the shapes at 0

    for (int region = 0; region < NREGIONS_ONE; ++region)
    {
        int x = index_positions[region] & 3;
        int y = (index_positions[region] >> 2) & 3;
        nvDebugCheck(REGION(x,y,shapeindex) == region);		// double check the table
        if (indices[y][x] & HIGH_INDEXBIT)
        {
            // high bit is set, swap the endpts and indices for this region
            int t;
            for (int i=0; i<NCHANNELS; ++i) { t = endpts[region].A[i]; endpts[region].A[i] = endpts[region].B[i]; endpts[region].B[i] = t; }

            for (int y = 0; y < Tile::TILE_H; y++)
                for (int x = 0; x < Tile::TILE_W; x++)
                    if (REGION(x,y,shapeindex) == region)
                        indices[y][x] = NINDICES - 1 - indices[y][x];
        }
    }
}

// endpoints fit only if the compression was lossless
static bool endpts_fit(const IntEndpts orig[NREGIONS_ONE], const ComprEndpts compressed[NREGIONS_ONE], const Pattern &p)
{
    IntEndpts uncompressed[NREGIONS_ONE];

    decompress_endpts(compressed, uncompressed, p);

    for (int j=0; j<NREGIONS_ONE; ++j)
	for (int i=0; i<NCHANNELS; ++i)
	{
        if (orig[j].A[i] != uncompressed[j].A[i]) return false;
        if (orig[j].B[i] != uncompressed[j].B[i]) return false;
    }
    return true;
}

static void write_header(const ComprEndpts endpts[NREGIONS_ONE], const Pattern &p, Bits &out)
{
    // interpret the verilog backwards and process it
    int m = p.mode;
    int rw = endpts[0].A[0], rx = endpts[0].B[0];
    int gw = endpts[0].A[1], gx = endpts[0].B[1];
    int bw = endpts[0].A[2], bx = endpts[0].B[2];
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
        case FIELD_RW:	out.write(rw >> endbit, len); break;
        case FIELD_RX:	out.write(rx >> endbit, len); break;
        case FIELD_GW:	out.write(gw >> endbit, len); break;
        case FIELD_GX:	out.write(gx >> endbit, len); break;
        case FIELD_BW:	out.write(bw >> endbit, len); break;
        case FIELD_BX:	out.write(bx >> endbit, len); break;

        case FIELD_D:
        case FIELD_RY:
        case FIELD_RZ:
        case FIELD_GY:
        case FIELD_GZ:
        case FIELD_BY:
        case FIELD_BZ:
        default: nvUnreachable();
        }
    }
}

static void read_header(Bits &in, ComprEndpts endpts[NREGIONS_ONE], Pattern &p)
{
    // reading isn't quite symmetric with writing -- we don't know the encoding until we decode the mode
    int mode = in.read(2);
    if (mode != 0x00 && mode != 0x01)
        mode = (in.read(3) << 2) | mode;

    int pat_index = mode_to_pat[mode];

    nvDebugCheck (pat_index >= 0 && pat_index < NPATTERNS);
    nvDebugCheck (in.getptr() == patterns[pat_index].modebits);

    p = patterns[pat_index];

    int d;
    int rw, rx;
    int gw, gx;
    int bw, bx;

    d = 0;
    rw = rx = 0;
    gw = gx = 0;
    bw = bx = 0;

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
        case FIELD_RW:	rw |= in.read(len) << endbit; break;
        case FIELD_RX:	rx |= in.read(len) << endbit; break;
        case FIELD_GW:	gw |= in.read(len) << endbit; break;
        case FIELD_GX:	gx |= in.read(len) << endbit; break;
        case FIELD_BW:	bw |= in.read(len) << endbit; break;
        case FIELD_BX:	bx |= in.read(len) << endbit; break;

        case FIELD_D:
        case FIELD_RY:
        case FIELD_RZ:
        case FIELD_GY:
        case FIELD_GZ:
        case FIELD_BY:
        case FIELD_BZ:
        default: nvUnreachable();
        }
    }

    nvDebugCheck (in.getptr() == 128 - 63);

    endpts[0].A[0] = rw; endpts[0].B[0] = rx;
    endpts[0].A[1] = gw; endpts[0].B[1] = gx;
    endpts[0].A[2] = bw; endpts[0].B[2] = bx;
}

// compress index 0
static void write_indices(const int indices[Tile::TILE_H][Tile::TILE_W], int shapeindex, Bits &out)
{
    for (int pos = 0; pos < Tile::TILE_TOTAL; ++pos)
    {
        int x = POS_TO_X(pos);
        int y = POS_TO_Y(pos);

        out.write(indices[y][x], INDEXBITS - ((pos == 0) ? 1 : 0));
    }
}

static void emit_block(const ComprEndpts endpts[NREGIONS_ONE], int shapeindex, const Pattern &p, const int indices[Tile::TILE_H][Tile::TILE_W], char *block)
{
    Bits out(block, ZOH::BITSIZE);

    write_header(endpts, p, out);

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

// position 0 was compressed
static void read_indices(Bits &in, int shapeindex, int indices[Tile::TILE_H][Tile::TILE_W])
{
    for (int pos = 0; pos < Tile::TILE_TOTAL; ++pos)
    {
        int x = POS_TO_X(pos);
        int y = POS_TO_Y(pos);

        indices[y][x]= in.read(INDEXBITS - ((pos == 0) ? 1 : 0));
    }
}

void ZOH::decompressone(const char *block, Tile &t)
{
    Bits in(block, ZOH::BITSIZE);

    Pattern p;
    IntEndpts endpts[NREGIONS_ONE];
    ComprEndpts compr_endpts[NREGIONS_ONE];

    read_header(in, compr_endpts, p);
    int shapeindex = 0;		// only one shape

    decompress_endpts(compr_endpts, endpts, p);

    Vector3 palette[NREGIONS_ONE][NINDICES];
    for (int r = 0; r < NREGIONS_ONE; ++r)
        generate_palette_quantized(endpts[r], p.chan[0].prec[0], &palette[r][0]);

    // read indices
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
static void assign_indices(const Tile &tile, int shapeindex, IntEndpts endpts[NREGIONS_ONE], int prec, 
                           int indices[Tile::TILE_H][Tile::TILE_W], float toterr[NREGIONS_ONE])
{
    // build list of possibles
    Vector3 palette[NREGIONS_ONE][NINDICES];

    for (int region = 0; region < NREGIONS_ONE; ++region)
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

static void optimize_endpts(const Tile &tile, int shapeindex, const float orig_err[NREGIONS_ONE], 
                            const IntEndpts orig_endpts[NREGIONS_ONE], int prec, IntEndpts opt_endpts[NREGIONS_ONE])
{
    Vector3 pixels[Tile::TILE_TOTAL];
    float importance[Tile::TILE_TOTAL];
    float err = 0;

    for (int region=0; region<NREGIONS_ONE; ++region)
    {
        // collect the pixels in the region
        int np = 0;

        for (int y = 0; y < tile.size_y; y++) {
            for (int x = 0; x < tile.size_x; x++) {
                if (REGION(x, y, shapeindex) == region) {
                    pixels[np] = tile.data[y][x];
                    importance[np] = tile.importance_map[y][x];
                    ++np;
                }
            }
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

float ZOH::refineone(const Tile &tile, int shapeindex_best, const FltEndpts endpts[NREGIONS_ONE], char *block)
{
    float orig_err[NREGIONS_ONE], opt_err[NREGIONS_ONE], orig_toterr, opt_toterr;
    IntEndpts orig_endpts[NREGIONS_ONE], opt_endpts[NREGIONS_ONE];
    ComprEndpts compr_orig[NREGIONS_ONE], compr_opt[NREGIONS_ONE];
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
            for (int i=0; i < NREGIONS_ONE; ++i) { orig_toterr += orig_err[i]; opt_toterr += opt_err[i]; }

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

	nvAssert (false); // "No candidate found, should never happen (refineone.)";
	return FLT_MAX;
}

static void generate_palette_unquantized(const FltEndpts endpts[NREGIONS_ONE], Vector3 palette[NREGIONS_ONE][NINDICES])
{
    for (int region = 0; region < NREGIONS_ONE; ++region)
	for (int i = 0; i < NINDICES; ++i)
            palette[region][i] = Utils::lerp(endpts[region].A, endpts[region].B, i, DENOM);
}

// generate a palette from unquantized endpoints, then pick best palette color for all pixels in each region, return toterr for all regions combined
static float map_colors(const Tile &tile, int shapeindex, const FltEndpts endpts[NREGIONS_ONE])
{
    // build list of possibles
    Vector3 palette[NREGIONS_ONE][NINDICES];

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

float ZOH::roughone(const Tile &tile, int shapeindex, FltEndpts endpts[NREGIONS_ONE])
{
    for (int region=0; region<NREGIONS_ONE; ++region)
    {
        int np = 0;
        Vector3 colors[Tile::TILE_TOTAL];
        Vector3 mean(0,0,0);

        for (int y = 0; y < tile.size_y; y++) {
            for (int x = 0; x < tile.size_x; x++) {
                if (REGION(x,y,shapeindex) == region)
                {
                    colors[np] = tile.data[y][x];
                    mean += tile.data[y][x];
                    ++np;
                }
            }
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

float ZOH::compressone(const Tile &t, char *block)
{
    int shapeindex_best = 0;
    FltEndpts endptsbest[NREGIONS_ONE], tempendpts[NREGIONS_ONE];
    float msebest = FLT_MAX;

    /*
		collect the mse values that are within 5% of the best values
		optimize each one and choose the best
	*/
    // hack for now -- just use the best value WORK
    for (int i=0; i<NSHAPES && msebest>0.0; ++i)
    {
        float mse = roughone(t, i, tempendpts);
        if (mse < msebest)
        {
            msebest = mse;
            shapeindex_best = i;
            memcpy(endptsbest, tempendpts, sizeof(endptsbest));
        }

    }
    return refineone(t, shapeindex_best, endptsbest, block);
}

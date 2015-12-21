/*
Copyright 2007 nVidia, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 

You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 

See the License for the specific language governing permissions and limitations under the License.
*/

// the avpcl compressor and decompressor

#include "tile.h"
#include "avpcl.h"
#include "nvcore/debug.h"
#include "nvmath/vector.inl"
#include <string.h>
#include <float.h>

using namespace nv;
using namespace AVPCL;

// global flags
bool AVPCL::flag_premult = false;
bool AVPCL::flag_nonuniform = false;
bool AVPCL::flag_nonuniform_ati = false;

// global mode
bool AVPCL::mode_rgb = false;		// true if image had constant alpha = 255

void AVPCL::compress(const Tile &t, char *block)
{
	char tempblock[AVPCL::BLOCKSIZE];
	float msebest = FLT_MAX;

	float mse_mode0 = AVPCL::compress_mode0(t, tempblock);		if(mse_mode0 < msebest) { msebest = mse_mode0; memcpy(block, tempblock, AVPCL::BLOCKSIZE); }
	float mse_mode1 = AVPCL::compress_mode1(t, tempblock);		if(mse_mode1 < msebest) { msebest = mse_mode1; memcpy(block, tempblock, AVPCL::BLOCKSIZE); }
	float mse_mode2 = AVPCL::compress_mode2(t, tempblock);		if(mse_mode2 < msebest) { msebest = mse_mode2; memcpy(block, tempblock, AVPCL::BLOCKSIZE); }
	float mse_mode3 = AVPCL::compress_mode3(t, tempblock);		if(mse_mode3 < msebest) { msebest = mse_mode3; memcpy(block, tempblock, AVPCL::BLOCKSIZE); }
	float mse_mode4 = AVPCL::compress_mode4(t, tempblock);		if(mse_mode4 < msebest) { msebest = mse_mode4; memcpy(block, tempblock, AVPCL::BLOCKSIZE); }
	float mse_mode5 = AVPCL::compress_mode5(t, tempblock);		if(mse_mode5 < msebest) { msebest = mse_mode5; memcpy(block, tempblock, AVPCL::BLOCKSIZE); }
	float mse_mode6 = AVPCL::compress_mode6(t, tempblock);		if(mse_mode6 < msebest) { msebest = mse_mode6; memcpy(block, tempblock, AVPCL::BLOCKSIZE); }
	float mse_mode7 = AVPCL::compress_mode7(t, tempblock);		if(mse_mode7 < msebest) { msebest = mse_mode7; memcpy(block, tempblock, AVPCL::BLOCKSIZE); }
		
	/*if (errfile)
	{
		float errs[21];
		int nerrs = 8;
		errs[0] = mse_mode0; 
		errs[1] = mse_mode1; 
		errs[2] = mse_mode2; 
		errs[3] = mse_mode3; 
		errs[4] = mse_mode4; 
		errs[5] = mse_mode5; 
		errs[6] = mse_mode6; 
		errs[7] = mse_mode7;
		if (fwrite(errs, sizeof(float), nerrs, errfile) != nerrs)
			throw "Write error on error file";
	}*/
}

/*
static int getbit(char *b, int start)
{
	if (start < 0 || start >= 128) return 0; // out of range

	int ix = start >> 3;
	return (b[ix] & (1 << (start & 7))) != 0;
}

static int getbits(char *b, int start, int len)
{
	int out = 0;
	for (int i=0; i<len; ++i)
		out |= getbit(b, start+i) << i;
	return out;
}

static void setbit(char *b, int start, int bit)
{
	if (start < 0 || start >= 128) return; // out of range

	int ix = start >> 3;

	if (bit & 1)
		b[ix] |= (1 << (start & 7));
	else
		b[ix] &= ~(1 << (start & 7));
}

static void setbits(char *b, int start, int len, int bits)
{
	for (int i=0; i<len; ++i)
		setbit(b, start+i, bits >> i);
}
*/

void AVPCL::decompress(const char *cblock, Tile &t)
{
	char block[AVPCL::BLOCKSIZE];
	memcpy(block, cblock, AVPCL::BLOCKSIZE);

	switch(getmode(block))
	{
	case 0:	AVPCL::decompress_mode0(block, t);	break;
	case 1:	AVPCL::decompress_mode1(block, t);	break;
	case 2:	AVPCL::decompress_mode2(block, t);	break;
	case 3:	AVPCL::decompress_mode3(block, t);	break;
	case 4:	AVPCL::decompress_mode4(block, t);	break;
	case 5:	AVPCL::decompress_mode5(block, t);	break;
	case 6:	AVPCL::decompress_mode6(block, t);	break;
	case 7:	AVPCL::decompress_mode7(block, t);	break;
	case 8: // return a black tile if you get a reserved mode
		for (int y=0; y<Tile::TILE_H; ++y)
			for (int x=0; x<Tile::TILE_W; ++x)
				t.data[y][x].set(0, 0, 0, 0);
		break;
	default: nvUnreachable();
	}
}

/*
void AVPCL::compress(string inf, string avpclf, string errf)
{
	Array2D<RGBA> pixels;
	int w, h;
	char block[AVPCL::BLOCKSIZE];

	Targa::read(inf, pixels, w, h);
	FILE *avpclfile = fopen(avpclf.c_str(), "wb");
	if (avpclfile == NULL) throw "Unable to open .avpcl file for write";
	FILE *errfile = NULL;
	if (errf != "")
	{
		errfile = fopen(errf.c_str(), "wb");
		if (errfile == NULL) throw "Unable to open error file for write";
	}

	// Look at alpha channel and override the premult flag if alpha is constant (but only if premult is set)
	if (AVPCL::flag_premult)
	{
		if (AVPCL::mode_rgb)
		{
			AVPCL::flag_premult = false;
			cout << endl << "NOTE: Source image alpha is constant 255, turning off premultiplied-alpha error metric." << endl << endl;
		}
	}

	// stuff for progress bar O.o
	int ntiles = ((h+Tile::TILE_H-1)/Tile::TILE_H)*((w+Tile::TILE_W-1)/Tile::TILE_W);
	int tilecnt = 0;
	clock_t start, prev, cur;

	start = prev = clock();

	// convert to tiles and compress each tile
	for (int y=0; y<h; y+=Tile::TILE_H)
	{
		int ysize = min(Tile::TILE_H, h-y);
		for (int x=0; x<w; x+=Tile::TILE_W)
		{
			if ((tilecnt%100) == 0) { cur = clock(); printf("Progress %d of %d, %5.2f seconds per 100 tiles\r", tilecnt, ntiles, float(cur-prev)/CLOCKS_PER_SEC); fflush(stdout); prev = cur; }

			int xsize = min(Tile::TILE_W, w-x);
			Tile t(xsize, ysize);

			t.insert(pixels, x, y);

			AVPCL::compress(t, block, errfile);
			if (fwrite(block, sizeof(char), AVPCL::BLOCKSIZE, avpclfile) != AVPCL::BLOCKSIZE)
				throw "File error on write";

			// progress bar
			++tilecnt;
		}
	}

	cur = clock();
	printf("\nTotal time to compress: %.2f seconds\n\n", float(cur-start)/CLOCKS_PER_SEC);		// advance to next line finally

	if (fclose(avpclfile)) throw "Close failed on .avpcl file";
	if (errfile && fclose(errfile)) throw "Close failed on error file";
}

static int str2int(std::string s) 
{
	int thing;
	std::stringstream str (stringstream::in | stringstream::out);
	str << s;
	str >> thing;
	return thing;
}

// avpcl file name is ...-w-h-RGB[A].avpcl, extract width and height
static void extract(string avpclf, int &w, int &h, bool &mode_rgb)
{
	size_t n = avpclf.rfind('.', avpclf.length()-1);
	size_t n1 = avpclf.rfind('-', n-1);
	size_t n2 = avpclf.rfind('-', n1-1);
	size_t n3 = avpclf.rfind('-', n2-1);
	//	...-wwww-hhhh-RGB[A].avpcl
	//     ^    ^    ^      ^
	//     n3   n2   n1     n n3<n2<n1<n
	string width = avpclf.substr(n3+1, n2-n3-1);
	w = str2int(width);
	string height = avpclf.substr(n2+1, n1-n2-1);
	h = str2int(height);
	string mode = avpclf.substr(n1+1, n-n1-1);
	mode_rgb = mode == "RGB";
}

static int modehist[8];

static void stats(char block[AVPCL::BLOCKSIZE])
{
	int m = AVPCL::getmode(block);
	modehist[m]++;
}

static void printstats()
{
	printf("\nMode histogram: "); for (int i=0; i<8; ++i) { printf("%d,", modehist[i]); }
	printf("\n");
}

void AVPCL::decompress(string avpclf, string outf)
{
	Array2D<RGBA> pixels;
	int w, h;
	char block[AVPCL::BLOCKSIZE];

	extract(avpclf, w, h, AVPCL::mode_rgb);
	FILE *avpclfile = fopen(avpclf.c_str(), "rb");
	if (avpclfile == NULL) throw "Unable to open .avpcl file for read";
	pixels.resizeErase(h, w);

	// convert to tiles and decompress each tile
	for (int y=0; y<h; y+=Tile::TILE_H)
	{
		int ysize = min(Tile::TILE_H, h-y);
		for (int x=0; x<w; x+=Tile::TILE_W)
		{
			int xsize = min(Tile::TILE_W, w-x);
			Tile t(xsize, ysize);

			if (fread(block, sizeof(char), AVPCL::BLOCKSIZE, avpclfile) != AVPCL::BLOCKSIZE)
				throw "File error on read";

			stats(block);	// collect statistics
		
			AVPCL::decompress(block, t);

			t.extract(pixels, x, y);
		}
	}
	if (fclose(avpclfile)) throw "Close failed on .avpcl file";

	Targa::write(outf, pixels, w, h);

	printstats();	// print statistics
}
*/

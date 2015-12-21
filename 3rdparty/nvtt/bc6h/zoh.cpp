/*
Copyright 2007 nVidia, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 

You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 

See the License for the specific language governing permissions and limitations under the License.
*/

// the zoh compressor and decompressor

#include "tile.h"
#include "zoh.h"

#include <string.h> // memcpy

using namespace ZOH;


bool ZOH::isone(const char *block)
{
	char code = block[0] & 0x1F;

	return (code == 0x03 || code == 0x07 || code == 0x0b || code == 0x0f);
}

void ZOH::compress(const Tile &t, char *block)
{
	char oneblock[ZOH::BLOCKSIZE], twoblock[ZOH::BLOCKSIZE];

	float mseone = ZOH::compressone(t, oneblock);
	float msetwo = ZOH::compresstwo(t, twoblock);

	if (mseone <= msetwo)
		memcpy(block, oneblock, ZOH::BLOCKSIZE);
	else
		memcpy(block, twoblock, ZOH::BLOCKSIZE);
}

void ZOH::decompress(const char *block, Tile &t)
{
	if (ZOH::isone(block))
		ZOH::decompressone(block, t);
	else
		ZOH::decompresstwo(block, t);
}

/*
void ZOH::compress(string inf, string zohf)
{
	Array2D<Rgba> pixels;
	int w, h;
	char block[ZOH::BLOCKSIZE];

	Exr::readRgba(inf, pixels, w, h);
	FILE *zohfile = fopen(zohf.c_str(), "wb");
	if (zohfile == NULL) throw "Unable to open .zoh file for write";

	// stuff for progress bar O.o
	int ntiles = ((h+Tile::TILE_H-1)/Tile::TILE_H)*((w+Tile::TILE_W-1)/Tile::TILE_W);
	int tilecnt = 0;
	int ndots = 25;
	int dotcnt = 0;
	printf("Progress [");
	for (int i=0; i<ndots;++i) printf(" ");
	printf("]\rProgress ["); fflush(stdout);

	// convert to tiles and compress each tile
	for (int y=0; y<h; y+=Tile::TILE_H)
	{
		int ysize = min(Tile::TILE_H, h-y);
		for (int x=0; x<w; x+=Tile::TILE_W)
		{
			int xsize = min(Tile::TILE_W, w-x);
			Tile t(xsize, ysize);

			t.insert(pixels, x, y);

			ZOH::compress(t, block);
			if (fwrite(block, sizeof(char), ZOH::BLOCKSIZE, zohfile) != ZOH::BLOCKSIZE)
				throw "File error on write";

			// progress bar
			++tilecnt;
			if (tilecnt > (ntiles * dotcnt)/ndots) { printf("."); fflush(stdout); ++dotcnt; }
		}
	}

	printf("]\n");		// advance to next line finally

	if (fclose(zohfile)) throw "Close failed on .zoh file";
}

static int str2int(std::string s)
{
	int thing;
	std::stringstream str (stringstream::in | stringstream::out);
	str << s;
	str >> thing;
	return thing;
}

// zoh file name is ...-w-h.zoh, extract width and height
static void extract(string zohf, int &w, int &h)
{
	size_t n = zohf.rfind('.', zohf.length()-1);
	size_t n1 = zohf.rfind('-', n-1);
	size_t n2 = zohf.rfind('-', n1-1);
	string width = zohf.substr(n2+1, n1-n2-1);
	w = str2int(width);
	string height = zohf.substr(n1+1, n-n1-1);
	h = str2int(height);
}

static int mode_to_prec[] = {
	10,7,11,10,
	10,7,11,11,
	10,7,11,12,
	10,7,9,16,
	10,7,8,-1,
	10,7,8,-1,
	10,7,8,-1,
	10,7,6,-1,
};

static int shapeindexhist[32], modehist[32], prechistone[16], prechisttwo[16], oneregion, tworegions;

static void stats(char block[ZOH::BLOCKSIZE])
{
	char mode = block[0] & 0x1F; if ((mode & 0x3) == 0) mode = 0; if ((mode & 0x3) == 1) mode = 1; modehist[mode]++;
	int prec = mode_to_prec[mode];
	nvAssert (prec != -1);
	if (!ZOH::isone(block))
	{
		tworegions++;
		prechisttwo[prec]++;
		int shapeindex = ((block[0] & 0xe0) >> 5) | ((block[1] & 0x3) << 3);
		shapeindexhist[shapeindex]++;
	}
	else
	{
		oneregion++;
		prechistone[prec]++;
	}
}

static void printstats()
{
	printf("\nPrecision histogram 10b to 16b one region: "); for (int i=10; i<=16; ++i) printf("%d,", prechistone[i]);
	printf("\nPrecision histogram 6b to 11b two regions: "); for (int i=6; i<=11; ++i) printf("%d,", prechisttwo[i]);
	printf("\nMode histogram: "); for (int i=0; i<32; ++i) printf("%d,", modehist[i]);
	printf("\nShape index histogram: "); for (int i=0; i<32; ++i) printf("%d,", shapeindexhist[i]);
	printf("\nOne region %5.2f%%  Two regions %5.2f%%", 100.0*oneregion/float(oneregion+tworegions), 100.0*tworegions/float(oneregion+tworegions));
	printf("\n");
}

void ZOH::decompress(string zohf, string outf)
{
	Array2D<Rgba> pixels;
	int w, h;
	char block[ZOH::BLOCKSIZE];

	extract(zohf, w, h);
	FILE *zohfile = fopen(zohf.c_str(), "rb");
	if (zohfile == NULL) throw "Unable to open .zoh file for read";
	pixels.resizeErase(h, w);

	// convert to tiles and decompress each tile
	for (int y=0; y<h; y+=Tile::TILE_H)
	{
		int ysize = min(Tile::TILE_H, h-y);
		for (int x=0; x<w; x+=Tile::TILE_W)
		{
			int xsize = min(Tile::TILE_W, w-x);
			Tile t(xsize, ysize);

			if (fread(block, sizeof(char), ZOH::BLOCKSIZE, zohfile) != ZOH::BLOCKSIZE)
				throw "File error on read";

			stats(block);	// collect statistics

			ZOH::decompress(block, t);

			t.extract(pixels, x, y);
		}
	}
	if (fclose(zohfile)) throw "Close failed on .zoh file";
	Exr::writeRgba(outf, pixels, w, h);

#ifndef EXTERNAL_RELEASE
	printstats();	// print statistics
#endif
}
*/

/*
Copyright 2007 nVidia, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 

You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 

See the License for the specific language governing permissions and limitations under the License.
*/

#ifndef _AVPCL_H
#define _AVPCL_H

#include "tile.h"
#include "bits.h"

#define	DISABLE_EXHAUSTIVE	1	// define this if you don't want to spend a lot of time on exhaustive compression
#define	USE_ZOH_INTERP		1	// use zoh interpolator, otherwise use exact avpcl interpolators
#define	USE_ZOH_INTERP_ROUNDED 1	// use the rounded versions!

namespace AVPCL {

static const int NREGIONS_TWO	= 2;
static const int NREGIONS_THREE	= 3;

static const int BLOCKSIZE=16;
static const int BITSIZE=128;

// global flags
extern bool flag_premult;
extern bool flag_nonuniform;
extern bool flag_nonuniform_ati;

// global mode
extern bool mode_rgb;		// true if image had constant alpha = 255

void compress(const Tile &t, char *block);
void decompress(const char *block, Tile &t);

float compress_mode0(const Tile &t, char *block);
void decompress_mode0(const char *block, Tile &t);

float compress_mode1(const Tile &t, char *block);
void decompress_mode1(const char *block, Tile &t);

float compress_mode2(const Tile &t, char *block);
void decompress_mode2(const char *block, Tile &t);

float compress_mode3(const Tile &t, char *block);
void decompress_mode3(const char *block, Tile &t);

float compress_mode4(const Tile &t, char *block);
void decompress_mode4(const char *block, Tile &t);

float compress_mode5(const Tile &t, char *block);
void decompress_mode5(const char *block, Tile &t);

float compress_mode6(const Tile &t, char *block);
void decompress_mode6(const char *block, Tile &t);

float compress_mode7(const Tile &t, char *block);
void decompress_mode7(const char *block, Tile &t);

inline int getmode(Bits &in)
{
	int mode = 0;

	if (in.read(1))			mode = 0;
	else if (in.read(1))	mode = 1;
	else if (in.read(1))	mode = 2;
	else if (in.read(1))	mode = 3;
	else if (in.read(1))	mode = 4;
	else if (in.read(1))	mode = 5;
	else if (in.read(1))	mode = 6;
	else if (in.read(1))	mode = 7;
	else mode = 8;	// reserved
	return mode;
}
inline int getmode(const char *block)
{
	int bits = block[0], mode = 0;

	if (bits & 1) mode = 0;
	else if ((bits&3) == 2) mode = 1;
	else if ((bits&7) == 4) mode = 2;
	else if ((bits & 0xF) == 8) mode = 3;
	else if ((bits & 0x1F) == 16) mode = 4;
	else if ((bits & 0x3F) == 32) mode = 5;
	else if ((bits & 0x7F) == 64) mode = 6;
	else if ((bits & 0xFF) == 128) mode = 7;
	else mode = 8;	// reserved
	return mode;
}

}

#endif

/*
Copyright 2007 nVidia, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 

You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 

See the License for the specific language governing permissions and limitations under the License.
*/
#pragma once
#ifndef _ZOH_H
#define _ZOH_H

#include "tile.h"

namespace ZOH {

// UNUSED ZOH MODES are 0x13, 0x17, 0x1b, 0x1f

static const int NREGIONS_TWO	= 2;
static const int NREGIONS_ONE	= 1;
static const int NCHANNELS		= 3;

struct FltEndpts
{
    nv::Vector3 A;
    nv::Vector3 B;
};

struct IntEndpts
{
	int A[NCHANNELS];
	int B[NCHANNELS];
};

struct ComprEndpts
{
	uint A[NCHANNELS];
	uint B[NCHANNELS];
};

static const int BLOCKSIZE=16;
static const int BITSIZE=128;

void compress(const Tile &t, char *block);
void decompress(const char *block, Tile &t);

float compressone(const Tile &t, char *block);
float compresstwo(const Tile &t, char *block);
void decompressone(const char *block, Tile &t);
void decompresstwo(const char *block, Tile &t);

float refinetwo(const Tile &tile, int shapeindex_best, const FltEndpts endpts[NREGIONS_TWO], char *block);
float roughtwo(const Tile &tile, int shape, FltEndpts endpts[NREGIONS_TWO]);

float refineone(const Tile &tile, int shapeindex_best, const FltEndpts endpts[NREGIONS_ONE], char *block);
float roughone(const Tile &tile, int shape, FltEndpts endpts[NREGIONS_ONE]);

bool isone(const char *block);

}

#endif // _ZOH_H

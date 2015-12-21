/*
Copyright 2007 nVidia, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 

You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 

See the License for the specific language governing permissions and limitations under the License.
*/
#ifndef _ZOH_TILE_H
#define _ZOH_TILE_H

#include "zoh_utils.h"
#include "nvmath/vector.h"
#include <math.h>

namespace ZOH {

//#define	USE_IMPORTANCE_MAP	1		// define this if you want to increase importance of some pixels in tile
class Tile
{
public:
	// NOTE: this returns the appropriately-clamped BIT PATTERN of the half as an INTEGRAL float value
	static float half2float(uint16 h)
	{
		return (float) Utils::ushort_to_format(h);
	}
	// NOTE: this is the inverse of the above operation
	static uint16 float2half(float f)
	{
		return Utils::format_to_ushort((int)f);
	}

	// look for adjacent pixels that are identical. if there are enough of them, increase their importance
	void generate_importance_map()
	{
		// initialize
		for (int y=0; y<size_y; ++y)
		for (int x=0; x<size_x; ++x)
		{
			// my importance is increased if I am identical to any of my 4-neighbors
			importance_map[y][x] = match_4_neighbor(x,y) ? 5.0f : 1.0f;
		}
	}
	bool is_equal(int x, int y, int xn, int yn)
	{
		if (xn < 0 || xn >= size_x || yn < 0 || yn >= size_y)
			return false;
		return( (data[y][x].x == data[yn][xn].x) &&
				(data[y][x].y == data[yn][xn].y) &&
				(data[y][x].z == data[yn][xn].z) );
	}

#ifdef USE_IMPORTANCE_MAP
	bool match_4_neighbor(int x, int y)
	{
		return is_equal(x,y,x-1,y) || is_equal(x,y,x+1,y) || is_equal(x,y,x,y-1) || is_equal(x,y,x,y+1);
	}
#else
	bool match_4_neighbor(int, int)
	{
		return false;
	}
#endif

	Tile() {};
	~Tile(){};
	Tile(int xs, int ys) {size_x = xs; size_y = ys;}

	static const int TILE_H = 4;
	static const int TILE_W = 4;
	static const int TILE_TOTAL = TILE_H * TILE_W;
    nv::Vector3 data[TILE_H][TILE_W];
	float importance_map[TILE_H][TILE_W];
	int	size_x, size_y;			// actual size of tile
};

}

#endif // _ZOH_TILE_H

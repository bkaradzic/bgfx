/*
Copyright 2007 nVidia, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 

You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 

See the License for the specific language governing permissions and limitations under the License.
*/

#ifndef _AVPCL_TILE_H
#define _AVPCL_TILE_H

#include "nvmath/vector.h"
#include <math.h>
#include "avpcl_utils.h"

namespace AVPCL {

// extract a tile of pixels from an array

class Tile
{
public:
	static const int TILE_H = 4;
	static const int TILE_W = 4;
	static const int TILE_TOTAL = TILE_H * TILE_W;
	nv::Vector4 data[TILE_H][TILE_W];
    float importance_map[TILE_H][TILE_W];
	int	size_x, size_y;			// actual size of tile

	Tile() {};
	~Tile(){};
	Tile(int xs, int ys) {size_x = xs; size_y = ys;}
};

}

#endif

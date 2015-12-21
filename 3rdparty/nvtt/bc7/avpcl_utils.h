/*
Copyright 2007 nVidia, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 

You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 

See the License for the specific language governing permissions and limitations under the License.
*/

// utility class holding common routines
#ifndef _AVPCL_UTILS_H
#define _AVPCL_UTILS_H

#include "nvmath/Vector.h"

namespace AVPCL {

inline int SIGN_EXTEND(int x, int nb) { return ((((x)&(1<<((nb)-1)))?((~0)<<(nb)):0)|(x)); }

static const int INDEXMODE_BITS				= 1;		// 2 different index modes
static const int NINDEXMODES				= (1<<(INDEXMODE_BITS));
static const int INDEXMODE_ALPHA_IS_3BITS	= 0;
static const int INDEXMODE_ALPHA_IS_2BITS	= 1;

static const int ROTATEMODE_BITS		= 2;		// 4 different rotate modes
static const int NROTATEMODES			= (1<<(ROTATEMODE_BITS));
static const int ROTATEMODE_RGBA_RGBA	= 0;
static const int ROTATEMODE_RGBA_AGBR	= 1;
static const int ROTATEMODE_RGBA_RABG	= 2;
static const int ROTATEMODE_RGBA_RGAB	= 3;

class Utils
{
public:
	// error metrics
	static float metric4(nv::Vector4::Arg a, nv::Vector4::Arg b);
	static float metric3(nv::Vector3::Arg a, nv::Vector3::Arg b, int rotatemode);
	static float metric1(float a, float b, int rotatemode);

	static float metric4premult(nv::Vector4::Arg rgba0, nv::Vector4::Arg rgba1);
	static float metric3premult_alphaout(nv::Vector3::Arg rgb0, float a0, nv::Vector3::Arg rgb1, float a1);
	static float metric3premult_alphain(nv::Vector3::Arg rgb0, nv::Vector3::Arg rgb1, int rotatemode);
	static float metric1premult(float rgb0, float a0, float rgb1, float a1, int rotatemode);

	static float premult(float r, float a);

	// quantization and unquantization
	static int unquantize(int q, int prec);
	static int quantize(float value, int prec);

	// lerping
	static int lerp(int a, int b, int i, int bias, int denom);
	static nv::Vector4 lerp(nv::Vector4::Arg a, nv::Vector4::Arg b, int i, int bias, int denom);
};

}

#endif
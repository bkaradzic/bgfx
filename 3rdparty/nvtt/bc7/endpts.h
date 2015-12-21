/*
Copyright 2007 nVidia, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 

You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 

See the License for the specific language governing permissions and limitations under the License.
*/

#ifndef _AVPCL_ENDPTS_H
#define _AVPCL_ENDPTS_H

// endpoint definitions and routines to search through endpoint space

#include "nvmath/Vector.h"

namespace AVPCL {

static const int NCHANNELS_RGB	= 3;
static const int NCHANNELS_RGBA	= 4;
static const int CHANNEL_R		= 0;
static const int CHANNEL_G		= 1;
static const int CHANNEL_B		= 2;
static const int CHANNEL_A		= 3;

struct FltEndpts
{
	nv::Vector4	A;
	nv::Vector4	B;
};

struct IntEndptsRGB
{
	int		A[NCHANNELS_RGB];
	int		B[NCHANNELS_RGB];
};

struct IntEndptsRGB_1
{
	int		A[NCHANNELS_RGB];
	int		B[NCHANNELS_RGB];
	int		lsb;				// shared lsb for A and B
};

struct IntEndptsRGB_2
{
	int		A[NCHANNELS_RGB];
	int		B[NCHANNELS_RGB];
	int		a_lsb;				// lsb for A
	int		b_lsb;				// lsb for B
};


struct IntEndptsRGBA
{
	int		A[NCHANNELS_RGBA];
	int		B[NCHANNELS_RGBA];
};

struct IntEndptsRGBA_2
{
	int		A[NCHANNELS_RGBA];
	int		B[NCHANNELS_RGBA];
	int		a_lsb;				// lsb for A
	int		b_lsb;				// lsb for B
};

struct IntEndptsRGBA_2a
{
	int		A[NCHANNELS_RGBA];
	int		B[NCHANNELS_RGBA];
	int		a_lsb;				// lsb for RGB channels of A
	int		b_lsb;				// lsb for RGB channels of A
};

}

#endif

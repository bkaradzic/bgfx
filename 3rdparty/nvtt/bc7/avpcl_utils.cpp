/*
Copyright 2007 nVidia, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 

You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 

See the License for the specific language governing permissions and limitations under the License.
*/

// Utility and common routines

#include "avpcl_utils.h"
#include "avpcl.h"
#include "nvmath/vector.inl"
#include <math.h>

using namespace nv;
using namespace AVPCL;

static const int denom7_weights[] = {0, 9, 18, 27, 37, 46, 55, 64};										// divided by 64
static const int denom15_weights[] = {0, 4, 9, 13, 17, 21, 26, 30, 34, 38, 43, 47, 51, 55, 60, 64};		// divided by 64

int Utils::lerp(int a, int b, int i, int bias, int denom)
{
#ifdef	USE_ZOH_INTERP
	nvAssert (denom == 3 || denom == 7 || denom == 15);
	nvAssert (i >= 0 && i <= denom);
	nvAssert (bias >= 0 && bias <= denom/2);
	nvAssert (a >= 0 && b >= 0);

	int round = 0;
#ifdef	USE_ZOH_INTERP_ROUNDED
	round = 32;
#endif

	switch (denom)
	{
	case 3:	denom *= 5; i *= 5;	// fall through to case 15
	case 15:return (a*denom15_weights[denom-i] + b*denom15_weights[i] + round) >> 6;
	case 7:	return (a*denom7_weights[denom-i] + b*denom7_weights[i] + round) >> 6;
	default: nvUnreachable(); return 0;
	}
#else
	return (((a)*((denom)-i)+(b)*(i)+(bias))/(denom));		// simple exact interpolation
#endif
}

Vector4 Utils::lerp(Vector4::Arg a, Vector4::Arg b, int i, int bias, int denom)
{
#ifdef	USE_ZOH_INTERP
	nvAssert (denom == 3 || denom == 7 || denom == 15);
	nvAssert (i >= 0 && i <= denom);
	nvAssert (bias >= 0 && bias <= denom/2);
//	nvAssert (a >= 0 && b >= 0);

	// no need to bias these as this is an exact division

	switch (denom)
	{
	case 3:	denom *= 5; i *= 5;	// fall through to case 15
	case 15:return (a*float(denom15_weights[denom-i]) + b*float(denom15_weights[i])) / 64.0f;
	case 7:	return (a*float(denom7_weights[denom-i]) + b*float(denom7_weights[i])) / 64.0f;
	default: nvUnreachable(); return Vector4(0);
	}
#else
	return (((a)*((denom)-i)+(b)*(i)+(bias))/(denom));		// simple exact interpolation
#endif
}


int Utils::unquantize(int q, int prec)
{
	int unq;

	nvAssert (prec > 3);	// we only want to do one replicate

#ifdef USE_ZOH_QUANT
	if (prec >= 8)
		unq = q;
	else if (q == 0) 
		unq = 0;
	else if (q == ((1<<prec)-1)) 
		unq = 255;
	else
		unq = (q * 256 + 128) >> prec;
#else
	// avpcl unquantizer -- bit replicate
	unq = (q << (8-prec)) | (q >> (2*prec-8));
#endif

	return unq;
}

// quantize to the best value -- i.e., minimize unquantize error
int Utils::quantize(float value, int prec)
{
	int q, unq;

	nvAssert (prec > 3);	// we only want to do one replicate

	unq = (int)floor(value + 0.5f);
	nvAssert (unq <= 255);

#ifdef USE_ZOH_QUANT
	q = (prec >= 8) ? unq : (unq << prec) / 256;
#else
	// avpcl quantizer -- scale properly for best possible bit-replicated result
	q = (unq * ((1<<prec)-1) + 127)/255;
#endif

	nvAssert (q >= 0 && q < (1 << prec));

	return q;
}

float Utils::metric4(Vector4::Arg a, Vector4::Arg b)
{
	Vector4 err = a - b;

	// if nonuniform, select weights and weigh away
	if (AVPCL::flag_nonuniform || AVPCL::flag_nonuniform_ati)
	{
		float rwt, gwt, bwt;
		if (AVPCL::flag_nonuniform)
		{
			rwt = 0.299f; gwt = 0.587f; bwt = 0.114f;
		}
		else /*if (AVPCL::flag_nonuniform_ati)*/
		{
			rwt = 0.3086f; gwt = 0.6094f; bwt = 0.0820f;
		}

		// weigh the components
		err.x *= rwt;
		err.y *= gwt;
		err.z *= bwt;
	}

	return lengthSquared(err);
}

// WORK -- implement rotatemode for the below -- that changes where the rwt, gwt, and bwt's go.
float Utils::metric3(Vector3::Arg a, Vector3::Arg b, int rotatemode)
{
	Vector3 err = a - b;

	// if nonuniform, select weights and weigh away
	if (AVPCL::flag_nonuniform || AVPCL::flag_nonuniform_ati)
	{
		float rwt, gwt, bwt;
		if (AVPCL::flag_nonuniform)
		{
			rwt = 0.299f; gwt = 0.587f; bwt = 0.114f;
		}
		else if (AVPCL::flag_nonuniform_ati)
		{
			rwt = 0.3086f; gwt = 0.6094f; bwt = 0.0820f;
		}

		// adjust weights based on rotatemode
		switch(rotatemode)
		{
		case ROTATEMODE_RGBA_RGBA: break;
		case ROTATEMODE_RGBA_AGBR: rwt = 1.0f; break;
		case ROTATEMODE_RGBA_RABG: gwt = 1.0f; break;
		case ROTATEMODE_RGBA_RGAB: bwt = 1.0f; break;
		default: nvUnreachable();
		}

		// weigh the components
		err.x *= rwt;
		err.y *= gwt;
		err.z *= bwt;
	}

	return lengthSquared(err);
}

float Utils::metric1(const float a, const float b, int rotatemode)
{
	float err = a - b;

	// if nonuniform, select weights and weigh away
	if (AVPCL::flag_nonuniform || AVPCL::flag_nonuniform_ati)
	{
		float rwt, gwt, bwt, awt;
		if (AVPCL::flag_nonuniform)
		{
			rwt = 0.299f; gwt = 0.587f; bwt = 0.114f;
		}
		else if (AVPCL::flag_nonuniform_ati)
		{
			rwt = 0.3086f; gwt = 0.6094f; bwt = 0.0820f;
		}

		// adjust weights based on rotatemode
		switch(rotatemode)
		{
		case ROTATEMODE_RGBA_RGBA: awt = 1.0f; break;
		case ROTATEMODE_RGBA_AGBR: awt = rwt; break;
		case ROTATEMODE_RGBA_RABG: awt = gwt; break;
		case ROTATEMODE_RGBA_RGAB: awt = bwt; break;
		default: nvUnreachable();
		}

		// weigh the components
		err *= awt;
	}

	return err * err;
}

float Utils::premult(float r, float a)
{
	// note that the args are really integers stored in floats
	int R = int(r), A = int(a);

	nvAssert ((R==r) && (A==a));

	return float((R*A + 127)/255);
}

static void premult4(Vector4& rgba)
{
	rgba.x = Utils::premult(rgba.x, rgba.w);
	rgba.y = Utils::premult(rgba.y, rgba.w);
	rgba.z = Utils::premult(rgba.z, rgba.w);
}

static void premult3(Vector3& rgb, float a)
{
	rgb.x = Utils::premult(rgb.x, a);
	rgb.y = Utils::premult(rgb.y, a);
	rgb.z = Utils::premult(rgb.z, a);
}

float Utils::metric4premult(Vector4::Arg a, Vector4::Arg b)
{
	Vector4 pma = a, pmb = b;

	premult4(pma);
	premult4(pmb);

	Vector4 err = pma - pmb;

	// if nonuniform, select weights and weigh away
	if (AVPCL::flag_nonuniform || AVPCL::flag_nonuniform_ati)
	{
		float rwt, gwt, bwt;
		if (AVPCL::flag_nonuniform)
		{
			rwt = 0.299f; gwt = 0.587f; bwt = 0.114f;
		}
		else /*if (AVPCL::flag_nonuniform_ati)*/
		{
			rwt = 0.3086f; gwt = 0.6094f; bwt = 0.0820f;
		}

		// weigh the components
		err.x *= rwt;
		err.y *= gwt;
		err.z *= bwt;
	}

	return lengthSquared(err);
}

float Utils::metric3premult_alphaout(Vector3::Arg rgb0, float a0, Vector3::Arg rgb1, float a1)
{
	Vector3 pma = rgb0, pmb = rgb1;

	premult3(pma, a0);
	premult3(pmb, a1);

	Vector3 err = pma - pmb;

	// if nonuniform, select weights and weigh away
	if (AVPCL::flag_nonuniform || AVPCL::flag_nonuniform_ati)
	{
		float rwt, gwt, bwt;
		if (AVPCL::flag_nonuniform)
		{
			rwt = 0.299f; gwt = 0.587f; bwt = 0.114f;
		}
		else /*if (AVPCL::flag_nonuniform_ati)*/
		{
			rwt = 0.3086f; gwt = 0.6094f; bwt = 0.0820f;
		}

		// weigh the components
		err.x *= rwt;
		err.y *= gwt;
		err.z *= bwt;
	}

	return lengthSquared(err);
}

float Utils::metric3premult_alphain(Vector3::Arg rgb0, Vector3::Arg rgb1, int rotatemode)
{
	Vector3 pma = rgb0, pmb = rgb1;

	switch(rotatemode)
	{
	case ROTATEMODE_RGBA_RGBA:
		// this function isn't supposed to be called for this rotatemode
		nvUnreachable();
		break;
	case ROTATEMODE_RGBA_AGBR:
		pma.y = premult(pma.y, pma.x);
		pma.z = premult(pma.z, pma.x);
		pmb.y = premult(pmb.y, pmb.x);
		pmb.z = premult(pmb.z, pmb.x);
		break;
	case ROTATEMODE_RGBA_RABG:
		pma.x = premult(pma.x, pma.y);
		pma.z = premult(pma.z, pma.y);
		pmb.x = premult(pmb.x, pmb.y);
		pmb.z = premult(pmb.z, pmb.y);
		break;
	case ROTATEMODE_RGBA_RGAB:
		pma.x = premult(pma.x, pma.z);
		pma.y = premult(pma.y, pma.z);
		pmb.x = premult(pmb.x, pmb.z);
		pmb.y = premult(pmb.y, pmb.z);
		break;
	default: nvUnreachable();
	}

	Vector3 err = pma - pmb;

	// if nonuniform, select weights and weigh away
	if (AVPCL::flag_nonuniform || AVPCL::flag_nonuniform_ati)
	{
		float rwt, gwt, bwt;
		if (AVPCL::flag_nonuniform)
		{
			rwt = 0.299f; gwt = 0.587f; bwt = 0.114f;
		}
		else /*if (AVPCL::flag_nonuniform_ati)*/
		{
			rwt = 0.3086f; gwt = 0.6094f; bwt = 0.0820f;
		}

		// weigh the components
		err.x *= rwt;
		err.y *= gwt;
		err.z *= bwt;
	}

	return lengthSquared(err);
}

float Utils::metric1premult(float rgb0, float a0, float rgb1, float a1, int rotatemode)
{
	float err = premult(rgb0, a0) - premult(rgb1, a1);

	// if nonuniform, select weights and weigh away
	if (AVPCL::flag_nonuniform || AVPCL::flag_nonuniform_ati)
	{
		float rwt, gwt, bwt, awt;
		if (AVPCL::flag_nonuniform)
		{
			rwt = 0.299f; gwt = 0.587f; bwt = 0.114f;
		}
		else if (AVPCL::flag_nonuniform_ati)
		{
			rwt = 0.3086f; gwt = 0.6094f; bwt = 0.0820f;
		}

		// adjust weights based on rotatemode
		switch(rotatemode)
		{
		case ROTATEMODE_RGBA_RGBA: awt = 1.0f; break;
		case ROTATEMODE_RGBA_AGBR: awt = rwt; break;
		case ROTATEMODE_RGBA_RABG: awt = gwt; break;
		case ROTATEMODE_RGBA_RGAB: awt = bwt; break;
		default: nvUnreachable();
		}

		// weigh the components
		err *= awt;
	}

	return err * err;
}

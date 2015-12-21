/*
Copyright 2007 nVidia, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 

You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 

See the License for the specific language governing permissions and limitations under the License.
*/

// Utility and common routines

#include "zoh_utils.h"
#include "nvmath/vector.inl"
#include <math.h>

using namespace nv;
using namespace ZOH;

static const int denom7_weights_64[] = {0, 9, 18, 27, 37, 46, 55, 64};										// divided by 64
static const int denom15_weights_64[] = {0, 4, 9, 13, 17, 21, 26, 30, 34, 38, 43, 47, 51, 55, 60, 64};		// divided by 64

/*static*/ Format Utils::FORMAT;

int Utils::lerp(int a, int b, int i, int denom)
{
	nvDebugCheck (denom == 3 || denom == 7 || denom == 15);
	nvDebugCheck (i >= 0 && i <= denom);

	int round = 32, shift = 6;
	const int *weights;

	switch(denom)
	{
	case 3:		denom *= 5; i *= 5;	// fall through to case 15
	case 15:	weights = denom15_weights_64; break;
	case 7:		weights = denom7_weights_64; break;
	default:	nvDebugCheck(0);
	}

	return (a*weights[denom-i] +b*weights[i] + round) >> shift;
}

Vector3 Utils::lerp(const Vector3& a, const Vector3 &b, int i, int denom)
{
	nvDebugCheck (denom == 3 || denom == 7 || denom == 15);
	nvDebugCheck (i >= 0 && i <= denom);

	int shift = 6;
	const int *weights;

	switch(denom)
	{
	case 3:		denom *= 5; i *= 5;	// fall through to case 15
	case 15:	weights = denom15_weights_64; break;
	case 7:		weights = denom7_weights_64; break;
	default:	nvUnreachable();
	}

	// no need to round these as this is an exact division
	return (a*float(weights[denom-i]) +b*float(weights[i])) / float(1 << shift);
}


/*
	For unsigned f16, clamp the input to [0,F16MAX]. Thus u15.
	For signed f16, clamp the input to [-F16MAX,F16MAX]. Thus s16.

	The conversions proceed as follows:

	unsigned f16: get bits. if high bit set, clamp to 0, else clamp to F16MAX.
	signed f16: get bits. extract exp+mantissa and clamp to F16MAX. return -value if sign bit was set, else value
	unsigned int: get bits. return as a positive value.
	signed int. get bits. return as a value in -32768..32767.

	The inverse conversions are just the inverse of the above.
*/

// clamp the 3 channels of the input vector to the allowable range based on FORMAT
// note that each channel is a float storing the allowable range as a bit pattern converted to float
// that is, for unsigned f16 say, we would clamp each channel to the range [0, F16MAX]

void Utils::clamp(Vector3 &v)
{
	for (int i=0; i<3; ++i)
	{
		switch(Utils::FORMAT)
		{
		case UNSIGNED_F16:
			if (v.component[i] < 0.0) v.component[i] = 0;
			else if (v.component[i] > F16MAX) v.component[i] = F16MAX;
			break;

		case SIGNED_F16:
			if (v.component[i] < -F16MAX) v.component[i] = -F16MAX;
			else if (v.component[i] > F16MAX) v.component[i] = F16MAX;
			break;

		default:
			nvUnreachable();
		}
	}
}

// convert a u16 value to s17 (represented as an int) based on the format expected
int Utils::ushort_to_format(unsigned short input)
{
	int out, s;

	// clamp to the valid range we are expecting
	switch (Utils::FORMAT)
	{
	case UNSIGNED_F16:
		if (input & F16S_MASK) out = 0;
		else if (input > F16MAX) out = F16MAX;
		else out = input;
		break;

	case SIGNED_F16:
		s = input & F16S_MASK;
		input &= F16EM_MASK;
		if (input > F16MAX) out = F16MAX;
		else out = input;
		out = s ? -out : out;
		break;
	}
	return out;
}

// convert a s17 value to u16 based on the format expected
unsigned short Utils::format_to_ushort(int input)
{
	unsigned short out;

	// clamp to the valid range we are expecting
	switch (Utils::FORMAT)
	{
	case UNSIGNED_F16:
		nvDebugCheck (input >= 0 && input <= F16MAX);
		out = input;
		break;

	case SIGNED_F16:
		nvDebugCheck (input >= -F16MAX && input <= F16MAX);
		// convert to sign-magnitude
		int s;
		if (input < 0) { s = F16S_MASK; input = -input; }
		else           { s = 0; }
		out = s | input;
		break;
	}
	return out;
}

// quantize the input range into equal-sized bins
int Utils::quantize(float value, int prec)
{
	int q, ivalue, s;

	nvDebugCheck (prec > 1);	// didn't bother to make it work for 1

	value = (float)floor(value + 0.5);

	int bias = (prec > 10) ? ((1<<(prec-1))-1) : 0;	// bias precisions 11..16 to get a more accurate quantization

	switch (Utils::FORMAT)
	{
	case UNSIGNED_F16:
		nvDebugCheck (value >= 0 && value <= F16MAX);
		ivalue = (int)value;
		q = ((ivalue << prec) + bias) / (F16MAX+1);
		nvDebugCheck (q >= 0 && q < (1 << prec));
		break;

	case SIGNED_F16:
		nvDebugCheck (value >= -F16MAX && value <= F16MAX);
		// convert to sign-magnitude
		ivalue = (int)value;
		if (ivalue < 0) { s = 1; ivalue = -ivalue; } else s = 0;

		q = ((ivalue << (prec-1)) + bias) / (F16MAX+1);
		if (s)
			q = -q;
		nvDebugCheck (q > -(1 << (prec-1)) && q < (1 << (prec-1)));
		break;
	}

	return q;
}

int Utils::finish_unquantize(int q, int prec)
{
	if (Utils::FORMAT == UNSIGNED_F16)
		return (q * 31) >> 6;										// scale the magnitude by 31/64
	else if (Utils::FORMAT == SIGNED_F16)
		return (q < 0) ? -(((-q) * 31) >> 5) : (q * 31) >> 5;		// scale the magnitude by 31/32
	else
		return q;
}

// unquantize each bin to midpoint of original bin range, except
// for the end bins which we push to an endpoint of the bin range.
// we do this to ensure we can represent all possible original values.
// the asymmetric end bins do not affect PSNR for the test images.
//
// code this function assuming an arbitrary bit pattern as the encoded block
int Utils::unquantize(int q, int prec)
{
	int unq, s;

	nvDebugCheck (prec > 1);	// not implemented for prec 1

	switch (Utils::FORMAT)
	{
	// modify this case to move the multiplication by 31 after interpolation.
	// Need to use finish_unquantize.

	// since we have 16 bits available, let's unquantize this to 16 bits unsigned
	// thus the scale factor is [0-7c00)/[0-10000) = 31/64
	case UNSIGNED_F16:
		if (prec >= 15) 
			unq = q;
		else if (q == 0) 
			unq = 0;
		else if (q == ((1<<prec)-1)) 
			unq = U16MAX;
		else
			unq = (q * (U16MAX+1) + (U16MAX+1)/2) >> prec;
		break;

	// here, let's stick with S16 (no apparent quality benefit from going to S17)
	// range is (-7c00..7c00)/(-8000..8000) = 31/32
	case SIGNED_F16:
		// don't remove this test even though it appears equivalent to the code below
		// as it isn't -- the code below can overflow for prec = 16
		if (prec >= 16)
			unq = q;
		else
		{
			if (q < 0) { s = 1; q = -q; } else s = 0;

			if (q == 0)
				unq = 0;
			else if (q >= ((1<<(prec-1))-1))
				unq = s ? -S16MAX : S16MAX;
			else
			{
				unq = (q * (S16MAX+1) + (S16MAX+1)/2) >> (prec-1);
				if (s)
					unq = -unq;
			}
		}
		break;
	}
	return unq;
}



// pick a norm!
#define	NORM_EUCLIDEAN 1

float Utils::norm(const Vector3 &a, const Vector3 &b)
{
#ifdef	NORM_EUCLIDEAN
	return lengthSquared(a - b);
#endif
#ifdef	NORM_ABS
	Vector3 err = a - b;
	return fabs(err.x) + fabs(err.y) + fabs(err.z);
#endif
}

// parse <name>[<start>{:<end>}]{,}	
// the pointer starts here         ^
// name is 1 or 2 chars and matches field names. start and end are decimal numbers
void Utils::parse(const char *encoding, int &ptr, Field &field, int &endbit, int &len)
{
	if (ptr <= 0) return;
	--ptr;
	if (encoding[ptr] == ',') --ptr;
	nvDebugCheck (encoding[ptr] == ']');
	--ptr;
	endbit = 0;
	int scale = 1;
	while (encoding[ptr] != ':' && encoding[ptr] != '[')
	{
		nvDebugCheck(encoding[ptr] >= '0' && encoding[ptr] <= '9');
		endbit += (encoding[ptr--] - '0') * scale;
		scale *= 10;
	}
	int startbit = 0; scale = 1;
	if (encoding[ptr] == '[')
		startbit = endbit;
	else  
	{
		ptr--;
		while (encoding[ptr] != '[')
		{
			nvDebugCheck(encoding[ptr] >= '0' && encoding[ptr] <= '9');
			startbit += (encoding[ptr--] - '0') * scale;
			scale *= 10;
		}
	}
	len = startbit - endbit + 1;	// startbit>=endbit note
	--ptr;
	if (encoding[ptr] == 'm')		field = FIELD_M;
	else if (encoding[ptr] == 'd')	field = FIELD_D;
	else {
		// it's wxyz
		nvDebugCheck (encoding[ptr] >= 'w' && encoding[ptr] <= 'z');
		int foo = encoding[ptr--] - 'w';
		// now it is r g or b
		if (encoding[ptr] == 'r')		foo += 10;
		else if (encoding[ptr] == 'g')	foo += 20;
		else if (encoding[ptr] == 'b')	foo += 30;
		else nvDebugCheck(0);
		field = (Field) foo;
	}
}



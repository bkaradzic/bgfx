$input v_texcoord0, v_banding, v_glyph

// ===================================================
// Reference pixel shader for the Slug algorithm.
// This code is made available under the MIT License.
// Copyright 2017, by Eric Lengyel.
// ===================================================

#include "../common/common.sh"

// The curve and band textures use a fixed width of 4096 texels.

#define kLogBandTextureWidth 12

SAMPLER2D(s_curveData,  0);
SAMPLER2D(s_bandData,   1);

uniform vec4 u_params;

int calcRootCode(float _y1, float _y2, float _y3)
{
	// Calculate the root eligibility code for a sample-relative quadratic Bezier curve.
	// Extract the signs of the y coordinates of the three control points.

	int i1 = (_y1 < 0.0) ? 1 : 0;
	int i2 = (_y2 < 0.0) ? 2 : 0;
	int i3 = (_y3 < 0.0) ? 4 : 0;
	int shift = i1 + i2 + i3;

	// Eligibility is returned in bits 0 and 8.

	return (0x2E74 >> shift) & 0x0101;
}

vec2 solveHorizPoly(vec4 _p12, vec2 _p3)
{
	// Solve for the values of t where the curve crosses y = 0.
	// The quadratic polynomial in t is given by
	//
	//     a t^2 - 2b t + c,
	//
	// where a = p1.y - 2 p2.y + p3.y, b = p1.y - p2.y, and c = p1.y.
	// The discriminant b^2 - ac is clamped to zero, and imaginary
	// roots are treated as a double root at the global minimum
	// where t = b / a.

	vec2 a = _p12.xy - _p12.zw * 2.0 + _p3;
	vec2 b = _p12.xy - _p12.zw;
	float ra = 1.0 / a.y;
	float rb = 0.5 / b.y;

	float d = sqrt(max(b.y * b.y - a.y * _p12.y, 0.0) );
	float t1 = (b.y - d) * ra;
	float t2 = (b.y + d) * ra;

	// If the polynomial is nearly linear, then solve -2b t + c = 0.

	if (abs(a.y) < 1.0 / 65536.0)
	{
		t1 = t2 = _p12.y * rb;
	}

	// Return the x coordinates where C(t) = 0.

	return vec2( (a.x * t1 - b.x * 2.0) * t1 + _p12.x, (a.x * t2 - b.x * 2.0) * t2 + _p12.x);
}

vec2 solveVertPoly(vec4 _p12, vec2 _p3)
{
	// Solve for the values of t where the curve crosses x = 0.

	vec2 a = _p12.xy - _p12.zw * 2.0 + _p3;
	vec2 b = _p12.xy - _p12.zw;
	float ra = 1.0 / a.x;
	float rb = 0.5 / b.x;

	float d = sqrt(max(b.x * b.x - a.x * _p12.x, 0.0) );
	float t1 = (b.x - d) * ra;
	float t2 = (b.x + d) * ra;

	if (abs(a.x) < 1.0 / 65536.0) t1 = t2 = _p12.x * rb;

	return vec2(
		  (a.y * t1 - b.y * 2.0) * t1 + _p12.y
		, (a.y * t2 - b.y * 2.0) * t2 + _p12.y
		);
}

ivec2 calcBandLoc(ivec2 glyphLoc, int offset)
{
	// If the offset causes the x coordinate to exceed the texture width, then wrap to the next line.

	ivec2 bandLoc = ivec2(glyphLoc.x + offset, glyphLoc.y);
	bandLoc.y += bandLoc.x >> kLogBandTextureWidth;
	bandLoc.x &= (1 << kLogBandTextureWidth) - 1;
	return bandLoc;
}

float calcCoverage(float xcov, float ycov, float xwgt, float ywgt)
{
	// Combine coverages from the horizontal and vertical rays using their weights.
	// Absolute values ensure that either winding direction convention works.

	float coverage = max(abs(xcov * xwgt + ycov * ywgt) / max(xwgt + ywgt, 1.0 / 65536.0), min(abs(xcov), abs(ycov) ));

	// Using nonzero fill rule here.

	coverage = clamp(coverage, 0.0, 1.0);
	return coverage;
}

float slugRender(vec2 _renderCoord, vec4 _bandTransform, ivec2 _glyphLoc, ivec2 _bandMax)
{
	int curveIndex;

	// The effective pixel dimensions of the em square are computed
	// independently for x and y directions with texcoord derivatives.

	vec2 emsPerPixel = fwidth(_renderCoord);
	vec2 pixelsPerEm = 1.0 / emsPerPixel;

	// Determine what bands the current pixel lies in by applying a scale and offset
	// to the render coordinates. The scales are given by _bandTransform.xy, and the
	// offsets are given by _bandTransform.zw. Band indexes are clamped to [0, _bandMax.xy].

	ivec2 bandIndex = clamp(ivec2(_renderCoord * _bandTransform.xy + _bandTransform.zw), ivec2(0, 0), _bandMax);

	float xcov = 0.0;
	float xwgt = 0.0;

	// Fetch data for the horizontal band from the index texture. The number
	// of curves intersecting the band is in the x component, and the offset
	// to the list of locations for those curves is in the y component.

	vec4 hbandRaw = texelFetch(s_bandData, ivec2(_glyphLoc.x + bandIndex.y, _glyphLoc.y), 0);
	int hbandCount = int(hbandRaw.x + 0.5);
	int hbandOffset = int(hbandRaw.y + 0.5);
	ivec2 hbandLoc = calcBandLoc(_glyphLoc, hbandOffset);

	// Loop over all curves in the horizontal band.

	for (curveIndex = 0; curveIndex < hbandCount; curveIndex++)
	{
		// Fetch the location of the current curve from the index texture.

		vec4 locRaw = texelFetch(s_bandData, ivec2(hbandLoc.x + curveIndex, hbandLoc.y), 0);
		ivec2 curveLoc = ivec2(int(locRaw.x + 0.5), int(locRaw.y + 0.5) );

		// Fetch the three 2D control points for the current curve from the curve texture.
		// The first texel contains both p1 and p2 in the (x,y) and (z,w) components, respectively,
		// and the the second texel contains p3 in the (x,y) components. Subtracting the render
		// coordinates makes the curve relative to the sample position. The quadratic Bezier curve
		// C(t) is given by
		//
		//     C(t) = (1 - t)^2 p1 + 2t(1 - t) p2 + t^2 p3

		vec4 p12 = texelFetch(s_curveData, curveLoc, 0) - vec4(_renderCoord, _renderCoord);
		vec2 p3  = texelFetch(s_curveData, ivec2(curveLoc.x + 1, curveLoc.y), 0).xy - _renderCoord;

		// If the largest x coordinate among all three control points falls
		// left of the current pixel, then there are no more curves in the
		// horizontal band that can influence the result, so exit the loop.
		// (The curves are sorted in descending order by max x coordinate.)

		if (max(max(p12.x, p12.z), p3.x) * pixelsPerEm.x < -0.5) break;

		int code = calcRootCode(p12.y, p12.w, p3.y);
		if (code != 0)
		{
			vec2 r = solveHorizPoly(p12, p3) * pixelsPerEm.x;

			if ( (code & 1) != 0)
			{
				xcov += clamp(r.x + 0.5, 0.0, 1.0);
				xwgt = max(xwgt, clamp(1.0 - abs(r.x) * 2.0, 0.0, 1.0) );
			}

			if (code > 1)
			{
				xcov -= clamp(r.y + 0.5, 0.0, 1.0);
				xwgt = max(xwgt, clamp(1.0 - abs(r.y) * 2.0, 0.0, 1.0) );
			}
		}
	}

	float ycov = 0.0;
	float ywgt = 0.0;

	// Fetch data for the vertical band from the index texture. This follows
	// the data for all horizontal bands, so we have to add _bandMax.y + 1.

	vec4  vbandRaw    = texelFetch(s_bandData, ivec2(_glyphLoc.x + _bandMax.y + 1 + bandIndex.x, _glyphLoc.y), 0);
	int   vbandCount  = int(vbandRaw.x + 0.5);
	int   vbandOffset = int(vbandRaw.y + 0.5);
	ivec2 vbandLoc    = calcBandLoc(_glyphLoc, vbandOffset);

	// Loop over all curves in the vertical band.

	for (curveIndex = 0; curveIndex < vbandCount; curveIndex++)
	{
		vec4 locRaw = texelFetch(s_bandData, ivec2(vbandLoc.x + curveIndex, vbandLoc.y), 0);
		ivec2 curveLoc = ivec2(int(locRaw.x + 0.5), int(locRaw.y + 0.5) );

		vec4 p12 = texelFetch(s_curveData, curveLoc, 0) - vec4(_renderCoord, _renderCoord);
		vec2 p3  = texelFetch(s_curveData, ivec2(curveLoc.x + 1, curveLoc.y), 0).xy - _renderCoord;

		if (max(max(p12.y, p12.w), p3.y) * pixelsPerEm.y < -0.5) break;

		int code = calcRootCode(p12.x, p12.z, p3.x);
		if (code != 0)
		{
			vec2 r = solveVertPoly(p12, p3) * pixelsPerEm.y;

			if ( (code & 1) != 0)
			{
				ycov -= clamp(r.x + 0.5, 0.0, 1.0);
				ywgt  = max(ywgt, clamp(1.0 - abs(r.x) * 2.0, 0.0, 1.0) );
			}

			if (code > 1)
			{
				ycov += clamp(r.y + 0.5, 0.0, 1.0);
				ywgt  = max(ywgt, clamp(1.0 - abs(r.y) * 2.0, 0.0, 1.0) );
			}
		}
	}

	return calcCoverage(xcov, ycov, xwgt, ywgt);
}

vec4 unpackRGBA8(float _packed)
{
	uint rgba = floatBitsToUint(_packed);
	return vec4(
		  (rgba >> 24) & 0xffu
		, (rgba >> 16) & 0xffu
		, (rgba >>  8) & 0xffu
		, (rgba      ) & 0xffu
		) / 255.0
		;
}

void main()
{
	ivec2 glyphLoc = ivec2(v_glyph.xy);
	ivec2 bandMax  = ivec2(v_glyph.zw);
	bandMax.y &= 0x00FF;

	float coverage = slugRender(v_texcoord0, v_banding, glyphLoc, bandMax);
	vec4 fg = unpackRGBA8(u_params.x);
	vec4 bg = unpackRGBA8(u_params.y);

	gl_FragColor = mix(bg, fg, coverage);
}

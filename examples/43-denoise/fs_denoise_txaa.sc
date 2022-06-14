$input v_texcoord0

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

#include "../common/common.sh"
#include "parameters.sh"
#include "shared_functions.sh"

#define APPLY_TXAA_IN_LINEAR	0
#define DEBUG_HALF_SCREEN		0

SAMPLER2D(s_color,			0); // this frame's shaded color
SAMPLER2D(s_previousColor,	1); // previous frame's shaded color
SAMPLER2D(s_velocity,		2); // screenspace delta from previous to current frame
SAMPLER2D(s_depth,			3); // depth buffer

vec3 FindNearestDepth(sampler2D _depthSampler, vec2 _texCoord) {
	vec2 du = vec2(u_viewTexel.x, 0.0);
	vec2 dv = vec2(0.0, u_viewTexel.y);

	vec2 coord = _texCoord - du - dv;
	vec3 tcd0 = vec3(coord, texture2D(_depthSampler, coord).x);
	coord = _texCoord      - dv;
	vec3 tcd1 = vec3(coord, texture2D(_depthSampler, coord).x);
	coord = _texCoord + du - dv;
	vec3 tcd2 = vec3(coord, texture2D(_depthSampler, coord).x);
	coord = _texCoord + du;
	vec3 tcd3 = vec3(coord, texture2D(_depthSampler, coord).x);
	coord = _texCoord;
	vec3 tcd4 = vec3(coord, texture2D(_depthSampler, coord).x);
	coord = _texCoord - du;
	vec3 tcd5 = vec3(coord, texture2D(_depthSampler, coord).x);
	coord = _texCoord - du + dv;
	vec3 tcd6 = vec3(coord, texture2D(_depthSampler, coord).x);
	coord = _texCoord      + dv;
	vec3 tcd7 = vec3(coord, texture2D(_depthSampler, coord).x);
	coord = _texCoord + du + dv;
	vec3 tcd8 = vec3(coord, texture2D(_depthSampler, coord).x);
	
	vec3 minTcd = tcd0;
	if (tcd1.z < minTcd.z) minTcd = tcd1;
	if (tcd2.z < minTcd.z) minTcd = tcd2;
	if (tcd3.z < minTcd.z) minTcd = tcd3;
	if (tcd4.z < minTcd.z) minTcd = tcd4;
	if (tcd5.z < minTcd.z) minTcd = tcd5;
	if (tcd6.z < minTcd.z) minTcd = tcd6;
	if (tcd7.z < minTcd.z) minTcd = tcd7;
	if (tcd8.z < minTcd.z) minTcd = tcd8;

	return minTcd;
}

float Mitchell (float _b, float _c, float _x) {

	float v = 0.0;
	float x = abs(_x);
	float x2 = x*x;
	float x3 = x2*x;

	if (x < 1.0) {
		v = (12.0-9.0*_b-6.0*_c)*x3 + (-18.0+12.0*_b+6.0*_c)*x2 + (6.0-2.0*_b);
	}
	else if (x < 2.0) {
		v = (-_b-6.0*_c)*x3 + (6.0*_b+30.0*_c)*x2 + (-12.0*_b-48.0*_c)*x + (8.0*_b+24.0*_c);
	}

	return v*(1.0/6.0);
}


void main()
{
	vec2 texCoord = v_texcoord0;
	vec3 colorCurr = texture2D(s_color, texCoord).xyz;

#if DEBUG_HALF_SCREEN
	if (texCoord.x > 0.5) {
#endif

	vec3 nearestCoordAndDepth = FindNearestDepth(s_depth, texCoord);

	vec2 velocity = texture2D(s_velocity, nearestCoordAndDepth.xy).xy;
	vec2 texCoordPrev = GetTexCoordPrevious(texCoord, velocity);

	vec3 colorPrev = texture2D(s_previousColor, texCoordPrev).xyz;
	
	// Sample local neighborhood for variance clipping
	vec2 du = vec2(u_viewTexel.x, 0.0);
	vec2 dv = vec2(0.0, u_viewTexel.y);

	vec3 colorUL = texture2D(s_color, texCoord - du - dv).xyz;
	vec3 colorUp = texture2D(s_color, texCoord      - dv).xyz;
	vec3 colorUR = texture2D(s_color, texCoord + du - dv).xyz;
	vec3 colorRi = texture2D(s_color, texCoord + du     ).xyz;
	vec3 colorLe = texture2D(s_color, texCoord - du     ).xyz;
	vec3 colorDL = texture2D(s_color, texCoord - du + dv).xyz;
	vec3 colorDo = texture2D(s_color, texCoord      + dv).xyz;
	vec3 colorDR = texture2D(s_color, texCoord + du + dv).xyz;

	// in an ideal world, lighting and such is in linear space,
	// would possibly want to convert to gamma and apply txaa
	// there. but this sample isn't storing intermediate results
	// in linear space (or doing any reasonable lighting) so
	// would possibly want to do the opposite.
#if APPLY_TXAA_IN_LINEAR
	colorCurr = toLinear(colorCurr);
	colorPrev = toLinear(colorPrev);
	colorUL = toLinear(colorUL);
	colorUp = toLinear(colorUp);
	colorUR = toLinear(colorUR);
	colorLe = toLinear(colorLe);
	colorRi = toLinear(colorRi);
	colorDL = toLinear(colorDL);
	colorDo = toLinear(colorDo);
	colorDR = toLinear(colorDR);
#endif

	// Compute variance box on color neighborhood, clip to box
	float outVal = 0.0;
	{
		vec3 m1 = vec3_splat(0.0);
		vec3 m2 = vec3_splat(0.0);
		m1 += colorUL; m2 += colorUL*colorUL;
		m1 += colorUp; m2 += colorUp*colorUp;
		m1 += colorUR; m2 += colorUR*colorUR;
		m1 += colorLe; m2 += colorLe*colorLe;
		m1 += colorCurr; m2 += colorCurr*colorCurr;
		m1 += colorRi; m2 += colorRi*colorRi;
		m1 += colorDL; m2 += colorDL*colorDL;
		m1 += colorDo; m2 += colorDo*colorDo;
		m1 += colorDR; m2 += colorDR*colorDR;
		m1 *= (1.0/9.0);
		m2 *= (1.0/9.0);

		vec3 var = max(vec3_splat(0.0), m2 - m1*m1);
		vec3 sigma = sqrt(var);
		outVal = max(sigma.x, max(sigma.y, sigma.z));
		sigma *= 1.4;
		vec3 colorMin = m1 - sigma;
		vec3 colorMax = m1 + sigma;

		vec3 displacement = colorPrev - m1;
		vec3 units = abs(displacement / sigma);
		float maxUnit = max(max(units.x, units.y), max(units.z, 1.0));

		colorPrev = m1 + displacement * (1.0/maxUnit);
	}

	float lumaCurr = dot(colorCurr, vec3(0.3, 0.6, 0.1));
	float lumaPrev = dot(colorPrev, vec3(0.3, 0.6, 0.1));

	// adjust feedback/blend amount depending on color difference
	float r = abs(lumaCurr-lumaPrev) / max(max(lumaCurr, lumaPrev), 0.2);
	r = 1.0-r;
	r = r*r;
	float feedback = mix(u_feedbackMin, u_feedbackMax, r);

	vec3 colorOut = mix(colorCurr, colorPrev, feedback);

	// optionally blur current color, since we've already taken
	// the samples to build the variance window. could use more
	// blur when feedback is lower, to replace temporal accumulation
	// with spatial accumulation. or could use filter to sharpen.
	if (u_applyMitchellFilter > 0.0)
	{
		// adjust filter coefficients depending on color difference
		float b = mix(3.0/2.0, 1.0/3.0, r);
		float c = mix(-1.0/4.0, 1.0/3.0, r);

		float m0 = Mitchell(b, c, 0.0);
		float m1 = Mitchell(b, c, 1.0);
		float m2 = Mitchell(b, c, sqrt(2.0));

		vec3 colorFilter = m0 * colorCurr;
		colorFilter += m1 * colorLe;
		colorFilter += m1 * colorRi;
		colorFilter += m1 * colorUp;
		colorFilter += m1 * colorDo;
		colorFilter += m2 * colorUL;
		colorFilter += m2 * colorUR;
		colorFilter += m2 * colorDL;
		colorFilter += m2 * colorDR;
		colorFilter *= 1.0/(m0 + 4.0*m1 + 4.0*m2);

		colorOut = mix(colorFilter, colorPrev, feedback);
	}

	// in an ideal world, lighting and such is in linear space,
	// would possibly want to convert to gamma and apply txaa
	// there. but this sample isn't storing intermediate results
	// in linear space (or doing any reasonable lighting) so
	// would possibly want to do the opposite.
#if APPLY_TXAA_IN_LINEAR
	colorCurr = toGamma(colorOut);
#else
	colorCurr = colorOut;
#endif


#if DEBUG_HALF_SCREEN
	}
#endif

	gl_FragColor = vec4(colorCurr, 1.0);
}

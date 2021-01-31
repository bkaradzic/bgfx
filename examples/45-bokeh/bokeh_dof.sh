/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#ifndef BOKEH_DOF_SH
#define BOKEH_DOF_SH

#define TWO_PI			(6.28318531)
#define GOLDEN_ANGLE	(2.39996323)
#define MAX_BLUR_SIZE	(20.0)
#define RADIUS_SCALE	(0.5)

float ShadertoyNoise (vec2 uv) {
	return fract(sin(dot(uv.xy, vec2(12.9898,78.233))) * 43758.5453123);
}

float GetCircleOfConfusion (float depth, float focusPoint, float focusScale)
{
	// if depth is less than focusPoint, result will be negative. want to keep this
	// relationship so comparison of (signed) blur size is same as comparing depth.
	return clamp((1.0/focusPoint - 1.0/depth) * focusScale, -1.0, 1.0);
}

float GetBlurSize (float depth, float focusPoint, float focusScale)
{
	float circleOfConfusion = GetCircleOfConfusion(depth, focusPoint, focusScale);
	return circleOfConfusion * u_maxBlurSize;
}

// this is the function at bottom of blog post...
//vec3 OriginalDepthOfField (vec2 texCoord, float focusPoint, float focusScale)
//{
//	float depth = texture2D(s_depth, texCoord).x;
//	float centerSize = GetBlurSize(depth, focusPoint, focusScale);
//	vec3 color = texture2D(s_color, texCoord).xyz;
//
//	float total = 1.0;
//	float radius = RADIUS_SCALE;
//	for (float theta = 0.0; radius < MAX_BLUR_SIZE; theta += GOLDEN_ANGLE)
//	{
//		vec2 spiralCoord = texCoord + vec2(cos(theta), sin(theta)) * u_viewTexel.xy * radius;
//		vec3 sampleColor = texture2D(s_color, spiralCoord).xyz;
//		float sampleDepth = texture2D(s_depth, spiralCoord).x;
//
//		float sampleSize = GetBlurSize(sampleDepth, focusPoint, focusScale);
//		if (sampleDepth > depth)
//		{
//			sampleSize = clamp(sampleSize, 0.0, centerSize*2.0);
//		}
//		float m = smoothstep(radius-0.5, radius+0.5, sampleSize);
//		color += mix(color/total, sampleColor, m);
//		total += 1.0;
//		radius += RADIUS_SCALE/radius;
//	}
//	return color * (1.0/total);
//}


void GetColorAndBlurSize (
	sampler2D samplerColor,
	sampler2D samplerDepth,
	vec2 texCoord,
	float focusPoint,
	float focusScale,
	out vec3 outColor,
	out float outBlurSize
) {
#if USE_PACKED_COLOR_AND_BLUR
	vec4 colorAndBlurSize = texture2DLod(samplerColor, texCoord, 0);
	vec3 color = colorAndBlurSize.xyz;
	float blurSize = colorAndBlurSize.w;

	outColor = color;
	outBlurSize = blurSize;
#else
	vec3 color = texture2DLod(samplerColor, texCoord, 0).xyz;
	float depth = texture2DLod(samplerDepth, texCoord, 0).x;
	float blurSize = GetBlurSize(depth, focusPoint, focusScale);

	outColor = color;
	outBlurSize = blurSize;
#endif
}

vec4 DepthOfField(
	sampler2D samplerColor,
	sampler2D samplerDepth,
	vec2 texCoord,
	float focusPoint,
	float focusScale,
	float samplePattern
) {
	vec3 color;
	float centerSize;
	GetColorAndBlurSize(
		samplerColor,
		samplerDepth,
		texCoord,
		focusPoint,
		focusScale,
		/*out*/color,
		/*out*/centerSize);
	float absCenterSize = abs(centerSize);

	// as sample count gets lower, visible banding. disrupt with noise.
	// use a better random/noise/dither function than this..
	vec2 pixelCoord = texCoord.xy * u_viewRect.zw;
	float random = ShadertoyNoise(pixelCoord + vec2(314.0, 159.0)*u_frameIdx);
	float theta = random * TWO_PI;
	float thetaStep = GOLDEN_ANGLE;

	float total = 1.0;
	float totalSampleSize = 0.0;

	// support two options for sample distribution ===========================
	float loopValue;
	float loopEnd;
	if (0.5 < samplePattern)
	{
		// in sqrt distribution, take fixed number of steps, step count
		// is fraction of full radius, with curve adjusted by sqrt function
		loopValue = 0.5 / u_blurSteps; // radiusFraction
		loopEnd = 1.0;
	}
	else
	{
		// in original distribution, looping value is radius directly,
		// but radius grows in non-linear way
		loopValue = u_radiusScale;
		loopEnd = u_maxBlurSize;
	}
	//========================================================================

	while (loopValue < loopEnd)
	{
		//====================================================================
		float radius;
		if (0.5 < samplePattern) {
			radius = sqrt(loopValue) * u_maxBlurSize;
		}
		else
		{
			radius = loopValue;
		}
		//====================================================================

		vec2 spiralCoord = texCoord + vec2(cos(theta), sin(theta)) * u_viewTexel.xy * radius;

		vec3 sampleColor;
		float sampleSize;
		GetColorAndBlurSize(
			samplerColor,
			samplerDepth,
			spiralCoord,
			focusPoint,
			focusScale,
			/*out*/sampleColor,
			/*out*/sampleSize);
		float absSampleSize = abs(sampleSize);

		// using signed sample size as proxy for depth comparison
		if (sampleSize > centerSize)
		{
			absSampleSize = clamp(absSampleSize, 0.0, absCenterSize*2.0);
		}
		float m = smoothstep(radius-0.5, radius+0.5, absSampleSize);
		color += mix(color/total, sampleColor, m);
		totalSampleSize += absSampleSize;
		total += 1.0;
		theta += thetaStep;

		//====================================================================
		if (0.5 < samplePattern)
		{
			loopValue += (1.0 / u_blurSteps); // radiusFraction
		}
		else
		{
			loopValue += (u_radiusScale/loopValue); // radius
		}
		//====================================================================
	}

	color *= 1.0/total;
	float averageSampleSize = totalSampleSize / (total-1.0);
	return vec4(color, averageSampleSize);
}

#endif

$input v_texcoord0

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#include "../common/common.sh"
#include "parameters.sh"
#include "normal_encoding.sh"
#include "shared_functions.sh"

SAMPLER2D(s_color,			0);
SAMPLER2D(s_normal,			1);
SAMPLER2D(s_velocity,		2);
SAMPLER2D(s_previousColor,	3); // previous color
SAMPLER2D(s_previousNormal,	4); // previous normal

#define COS_PI_OVER_4   0.70710678118

void main()
{
	vec2 texCoord = v_texcoord0;

	// read center pixel
	vec4 color = texture2D(s_color, texCoord);
	vec3 normal = NormalDecode(texture2D(s_normal, texCoord).xyz);

	// offset to last pixel
	vec2 velocity = texture2D(s_velocity, texCoord).xy;
	vec2 texCoordPrev = GetTexCoordPreviousNoJitter(texCoord, velocity);

	// SVGF approach suggests sampling and test/rejecting 4 contributing
	// samples individually and then doing custom bilinear filter of result

	// multiply texCoordPrev by dimensions to get nearest pixels, produces (X.5, Y.5) coordinate
	// under no motion, so subtract half here to get correct weights for bilinear filter.
	// not thrilled by this, feels like something is wrong.
	vec2 screenPixelPrev = texCoordPrev * u_viewRect.zw - vec2_splat(0.5);
	vec2 screenPixelMin = floor(screenPixelPrev);
	vec2 screenPixelMix = fract(screenPixelPrev);

	float x0 = 1.0 - screenPixelMix.x;
	float x1 = screenPixelMix.x;
	float y0 = 1.0 - screenPixelMix.y;
	float y1 = screenPixelMix.y;

	float coordWeights[4];
	coordWeights[0] = x0*y0;
	coordWeights[1] = x1*y0;
	coordWeights[2] = x0*y1;
	coordWeights[3] = x1*y1;

	// adding a half texel here to correct the modification above, in addition to pixel offset
	// to grab adjacent pixels for bilinear filter. not thrilled by this, feels like something is wrong.
	vec2 coords[4];
	coords[0] = (screenPixelMin + vec2(0.5, 0.5)) * u_viewTexel.xy;
	coords[1] = (screenPixelMin + vec2(1.5, 0.5)) * u_viewTexel.xy;
	coords[2] = (screenPixelMin + vec2(0.5, 1.5)) * u_viewTexel.xy;
	coords[3] = (screenPixelMin + vec2(1.5, 1.5)) * u_viewTexel.xy;

	// SVGF paper mentions comparing depths and normals to establish
	// whether samples are similar enough to contribute, but does not
	// describe how. References the following paper, which uses threshold
	// of cos(PI/4) to accept/reject.
	// https://software.intel.com/content/www/us/en/develop/articles/streaming-g-buffer-compression-for-multi-sample-anti-aliasing.html
	// this paper also discusses using depth derivatives to estimate overlapping depth range

	vec4 accumulatedColor = vec4_splat(0.0);
	float accumulatedWeight = 0.0;
	for (int i = 0; i < 4; ++i)
	{
		vec3 sampleNormal = NormalDecode(texture2D(s_previousNormal, coords[i]).xyz);
		float normalSimilarity = dot(normal, sampleNormal);
		float weight = (normalSimilarity < COS_PI_OVER_4) ? 0.0 : 1.0;

		vec4 sampleColor = texture2D(s_previousColor, coords[i]);

		weight *= coordWeights[i];
		accumulatedColor += sampleColor * weight;
		accumulatedWeight += weight;
	}

	if (0.0 < accumulatedWeight)
	{
		accumulatedColor *= (1.0 / accumulatedWeight);
		color = mix(color, accumulatedColor, 0.8);
	}
	else
	{
		// debug colorize
		//color.xyz *= vec3(0.5, 0.01, 0.65);
	}

	gl_FragColor = color;
}

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#ifndef FS_DENOISE_SPATIAL_IMPLEMENTATION_SH
#define FS_DENOISE_SPATIAL_IMPLEMENTATION_SH

#include "../common/common.sh"
#include "parameters.sh"
#include "normal_encoding.sh"

SAMPLER2D(s_color,  0); // input color, signal to be denoised
SAMPLER2D(s_normal, 1); // scene's gbuffer normal, used for edge stopping function
SAMPLER2D(s_depth,  2); // scene's depth, used for edge stopping function

void main()
{
	vec2 texCoord = v_texcoord0;

	// read center pixel
	vec4 color = texture2D(s_color, texCoord);
	vec3 normal = NormalDecode(texture2D(s_normal, texCoord).xyz); // * 2.0 - 1.0;
	float depth = texture2D(s_depth, texCoord).x;
	// want depth gradient for edge stopping function
	float depthGradient = abs(dFdx(depth)) + abs(dFdy(depth));

	float du = u_texCoordStep * u_viewTexel.x;
	float dv = u_texCoordStep * u_viewTexel.y;

#if USE_SPATIAL_5X5
	float gaussianWeights[5];
	gaussianWeights[0] = 1.0/16.0;
	gaussianWeights[1] = 4.0/16.0;
	gaussianWeights[2] = 6.0/16.0;
	gaussianWeights[3] = 4.0/16.0;
	gaussianWeights[4] = 1.0/16.0;
	float initialWeight = (gaussianWeights[2]*gaussianWeights[2]);
	int centerIdx = 2;

	vec4 accumulateColor = color * initialWeight;
	float accumulateWeight = initialWeight;

	for (int yy = 0; yy < 5; ++yy)
	{
		for (int xx = 0; xx < 5; ++xx)
		{
#else
	float gaussianWeights[3];
	gaussianWeights[0] = 1.0/4.0;
	gaussianWeights[1] = 2.0/4.0;
	gaussianWeights[2] = 1.0/4.0;
	float initialWeight = (gaussianWeights[1]*gaussianWeights[1]);
	int centerIdx = 1;

	vec4 accumulateColor = color * initialWeight;
	float accumulateWeight = initialWeight;

	for (int yy = 0; yy < 3; ++yy)
	{
		for (int xx = 0; xx < 3; ++xx)
		{
#endif // USE_SPATIAL_5X5
			if ((centerIdx == xx) && (centerIdx == yy)) {
				continue;
			}

			float xOffset = float(xx) - float(centerIdx);
			float yOffset = float(yy) - float(centerIdx);
			vec2 sampleTexCoord = texCoord;
			sampleTexCoord.x += xOffset * du;
			sampleTexCoord.y += yOffset * dv;

			vec4 sampleColor = texture2D(s_color, sampleTexCoord);
			vec3 sampleNormal = NormalDecode(texture2D(s_normal, sampleTexCoord).xyz);
			float normalWeight = pow(saturate(dot(normal, sampleNormal)), u_sigmaNormal);
			
			float sampleDepth = texture2D(s_depth, sampleTexCoord).x;
			float depthDelta = depth - sampleDepth;
			float depthWeight = exp(-abs(depthDelta) / max(1e-5, u_sigmaDepth*u_sigmaDepth));

			float weight = depthWeight * normalWeight;

			// apply gaussian
			weight *= (gaussianWeights[xx]*gaussianWeights[yy]);

			accumulateColor += sampleColor * weight;
			accumulateWeight += weight;
		}
	}

	accumulateColor /= max(accumulateWeight, 1e-5);

	gl_FragColor = accumulateColor;
}

#endif // FS_DENOISE_SPATIAL_IMPLEMENTATION_SH

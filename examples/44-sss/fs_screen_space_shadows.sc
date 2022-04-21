$input v_texcoord0

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

#include "../common/common.sh"
#include "parameters.sh"

SAMPLER2D(s_depth, 0);

#define DEPTH_EPSILON	1e-4

// from assao sample, cs_assao_prepare_depths.sc
vec3 NDCToViewspace( vec2 pos, float viewspaceDepth )
{
	vec3 ret;

	ret.xy = (u_ndcToViewMul * pos.xy + u_ndcToViewAdd) * viewspaceDepth;

	ret.z = viewspaceDepth;

	return ret;
}

float ShadertoyNoise (vec2 uv) {
	return fract(sin(dot(uv.xy, vec2(12.9898,78.233))) * 43758.5453123);
}

void main()
{
	vec2 texCoord = v_texcoord0;
	float linearDepth = texture2D(s_depth, texCoord).x;
	vec3 viewSpacePosition = NDCToViewspace(texCoord, linearDepth);

	vec3 lightStep = normalize(u_lightPosition - viewSpacePosition);

	// screen space radius not usable directly. convert value given in pixels,
	// to world units. this is important later when comparing depth in world units
	float radius = u_shadowRadius;
	if (0.0 < u_useScreenSpaceRadius)
	{
		// is there a better way to do this calculation?
		float radiusTexCoordX = u_shadowRadius * u_viewTexel.x + texCoord.x;
		float radiusPositionX = u_ndcToViewMul.x * radiusTexCoordX + u_ndcToViewAdd.x;
		radius = abs(radiusPositionX * linearDepth - viewSpacePosition.x);
	}
	lightStep *= (radius / u_shadowSteps);

	vec3 samplePosition = viewSpacePosition;
	float random = ShadertoyNoise(gl_FragCoord.xy + vec2(314.0, 159.0)*u_frameIdx);
	float initialOffset = (0.0 < u_useNoiseOffset) ? (0.5+random) : 1.0;
	samplePosition += initialOffset * lightStep;

	mat4 viewToProj = mat4(
		u_viewToProj0,
		u_viewToProj1,
		u_viewToProj2,
		u_viewToProj3
	);

	float occluded = 0.0;
	float softOccluded = 0.0;
	float firstHit = u_shadowSteps;
	for (int i = 0; i < int(u_shadowSteps); ++i, samplePosition += lightStep)
	{
		vec3 psSamplePosition = instMul(viewToProj, vec4(samplePosition, 1.0)).xyw;
		psSamplePosition.xy *= (1.0/psSamplePosition.z);

		vec2 sampleCoord = psSamplePosition.xy * 0.5 + 0.5;
		sampleCoord.y = 1.0 - sampleCoord.y;

		// using texture2Dlod because dx9 compiler doesn't like
		// gradient instructions within this loop
		float sampleDepth = texture2DLod(s_depth, sampleCoord, 0).x;

		float delta = (samplePosition.z - sampleDepth);
		if (DEPTH_EPSILON < delta && delta < radius)
		{
			firstHit = min(firstHit, float(i));
			// for hard, soft occlusion
			occluded += 1.0;
			// for very soft occlusion
			softOccluded += saturate(radius - delta);
		}
	}

	float shadow;
	if (1.5 < u_contactShadowsMode)
	{
		// very soft occlusion, includes distance falloff above
		shadow = softOccluded * (1.0 - (firstHit / u_shadowSteps));
		shadow = 1.0 - saturate(shadow);
		shadow = shadow*shadow;
	}
	else if (0.5 < u_contactShadowsMode)
	{
		// soft occlusion
		shadow = occluded * (1.0 - (firstHit / u_shadowSteps));
		shadow = 1.0 - saturate(shadow);
		shadow = shadow*shadow;
	}
	else // == 0
	{
		// hard occlusion
		shadow = 0.0 < occluded ? 0.0 : 1.0;
	}

	gl_FragColor = vec4_splat(shadow);
}

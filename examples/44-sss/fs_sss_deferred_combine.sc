$input v_texcoord0

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#include "../common/common.sh"
#include "parameters.sh"
#include "normal_encoding.sh"

SAMPLER2D(s_color, 0);
SAMPLER2D(s_normal, 1);
SAMPLER2D(s_depth, 2);
SAMPLER2D(s_shadows, 3);

// from assao sample, cs_assao_prepare_depths.sc
vec3 NDCToViewspace( vec2 pos, float viewspaceDepth )
{
	vec3 ret;

	ret.xy = (u_ndcToViewMul * pos.xy + u_ndcToViewAdd) * viewspaceDepth;

	ret.z = viewspaceDepth;

	return ret;
}

void main()
{
	vec2 texCoord = v_texcoord0;

	vec4 colorId = texture2D(s_color, texCoord);
	vec3 color = toLinear(colorId.xyz);
	float materialId = colorId.w;

	if (0.0 < materialId)
	{
		vec4 normalRoughness = texture2D(s_normal, texCoord);
		vec3 normal = NormalDecode(normalRoughness.xyz);
		float roughness = normalRoughness.w;

		// transform normal into view space
		mat4 worldToView = mat4(
			u_worldToView0,
			u_worldToView1,
			u_worldToView2,
			u_worldToView3
		);
		vec3 vsNormal = instMul(worldToView, vec4(normal, 0.0)).xyz;

		// read depth and recreate position
		float linearDepth = texture2D(s_depth, texCoord).x;
		vec3 viewSpacePosition = NDCToViewspace(texCoord, linearDepth);

		float shadow = texture2D(s_shadows, texCoord).x;

		// need to get a valid view vector for any microfacet stuff :(
		float gloss = 1.0-roughness;
		float specPower = 62.0 * gloss + 2.0;

		vec3 light = (u_lightPosition - viewSpacePosition);
		float lightDistSq = dot(light, light) + 1e-5;
		light = normalize(light);
		float NdotL = saturate(dot(vsNormal, light));
		float diffuse = NdotL * (1.0/lightDistSq);
		float specular = 5.0 * pow(NdotL, specPower);

		float lightAmount = mix(diffuse, specular, 0.04) * shadow;

		color = (color * lightAmount);
		color = toGamma(color);

		// debug display shadows only
		if (0.0 < u_displayShadows)
		{
			color = vec3_splat(shadow);
		}
	}
	// else, assume color is unlit

	gl_FragColor = vec4(color, 1.0);
}

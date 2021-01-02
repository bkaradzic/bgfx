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

float ShadertoyNoise (vec2 uv) {
	return fract(sin(dot(uv.xy, vec2(12.9898,78.233))) * 43758.5453123);
}

int ModHelper (float a, float b)
{
	return int( a - (b*floor(a/b)));
}

void main()
{
	vec2 texCoord = v_texcoord0;

	// mess with result so there's something to denosie
	float sn = 1.0;
	if (1.5 < u_noiseType)
	{
		sn = ShadertoyNoise(gl_FragCoord.xy + vec2(314.0, 159.0)*u_frameIdx);
		sn = (sn < 0.5) ? 0.0 : 1.0;
	}
	else if (0.5 < u_noiseType)
	{
		// having trouble compiling for gles when using % or mod :(
		int modCoordX = ModHelper(gl_FragCoord.x, 2.0);
		int modCoordY = ModHelper(gl_FragCoord.y, 2.0);
		int frameSelect = modCoordY * 2 + modCoordX;
		int frameMod4 = ModHelper(u_frameIdx, 4.0);
		sn = (frameSelect == frameMod4) ? 1.0 : 0.0;
	}

	vec4 normalRoughness = texture2D(s_normal, texCoord).xyzw;
	vec3 normal = NormalDecode(normalRoughness.xyz);
	float roughness = 0.5;

	// need to get a valid view vector for any microfacet stuff :(
	float gloss = 1.0-roughness;
	float specPower = 1022.0 * gloss + 2.0;

	vec3 light = normalize(vec3(-0.2, 1.0, -0.2));
	float NdotL = saturate(dot(normal, light));
	float diff = NdotL*0.99 + 0.01;
	float spec = 5.0 * pow(NdotL, specPower);

	float lightAmt = (diff + spec) * sn;

	gl_FragColor = vec4(vec3_splat(lightAmt), 1.0);
}

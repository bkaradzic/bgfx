$input v_normal, v_texcoord0

/*
* Copyright 2017 Stanislav Pidhorskyi. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

#include "../common/common.sh"

SAMPLER2D(s_texLightmap,  0);
uniform vec4 u_sunDirection;
uniform vec4 u_sunLuminance;
uniform vec4 u_skyLuminance;
uniform vec4 u_parameters;

// Interleaved gradient noise (better for Metal)
// Reference: http://www.iryoku.com/next-generation-post-processing-in-call-of-duty-advanced-warfare
float interleavedGradientNoise(vec2 screenPos, float temporalFactor)
{
	vec3 magic = vec3(0.06711056, 0.00583715, 52.9829189);
	vec2 coord = screenPos + fract(temporalFactor) * vec2_splat(13.0);
	return fract(magic.z * fract(dot(coord, magic.xy)));
}

float toLinear(float _rgb)
{
	return pow(abs(_rgb), 2.2);
}

void main()
{
	vec3 normal = normalize(v_normal);

	float occulsion = toLinear(texture2D(s_texLightmap, v_texcoord0).r);

	vec3 skyDirection = vec3(0.0, 0.0, 1.0);

	float diffuseSun = max(0.0, dot(normal, normalize(u_sunDirection.xyz)));
	float diffuseSky = 1.0 + 0.5 * dot(normal, skyDirection);

	vec3 color = diffuseSun * u_sunLuminance.rgb + (diffuseSky * u_skyLuminance.rgb + 0.01) * occulsion;
	color *= 0.5;

	gl_FragColor.xyz = color * u_parameters.z;
	gl_FragColor.w = 1.0;

	float dither = interleavedGradientNoise(gl_FragCoord.xy, u_parameters.w);
	dither = (dither - 0.5) / 255.0;

	gl_FragColor.xyz = toGamma(gl_FragColor.xyz) + vec3_splat(dither);
}

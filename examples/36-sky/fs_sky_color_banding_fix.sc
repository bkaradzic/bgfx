$input v_skyColor, v_screenPos, v_viewDir

/*
* Copyright 2017 Stanislav Pidhorskyi. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

uniform vec4 	u_parameters; // x - sun size, y - sun bloom, z - exposition, w - time
uniform vec4 	u_sunDirection;
uniform vec4 	u_sunLuminance;

#include "../common/common.sh"

// Interleaved gradient noise (better for Metal)
// Reference: http://www.iryoku.com/next-generation-post-processing-in-call-of-duty-advanced-warfare
float interleavedGradientNoise(vec2 screenPos, float temporalFactor)
{
	vec3 magic = vec3(0.06711056, 0.00583715, 52.9829189);
	vec2 coord = screenPos + fract(temporalFactor) * vec2_splat(13.0);
	return fract(magic.z * fract(dot(coord, magic.xy)));
}

void main()
{
	float size2 = u_parameters.x * u_parameters.x;

	vec3 lightDir = normalize(u_sunDirection.xyz);
	float distance = 2.0 * (1.0 - dot(normalize(v_viewDir), lightDir));
	float sun = exp(-distance/ u_parameters.y / size2) + step(distance, size2);
	float sun2 = min(sun * sun, 1.0);
	vec3 color = v_skyColor + sun2;
	color = toGamma(color);

	float dither = interleavedGradientNoise(gl_FragCoord.xy, u_parameters.w);
	dither = (dither - 0.5) / 255.0;
	color += vec3_splat(dither);

	gl_FragColor = vec4(color, 1.0);
}

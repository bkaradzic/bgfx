$input v_texcoord0

/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

SAMPLER2D(s_albedo, 0);
SAMPLER2D(s_light, 1);

void main()
{
	vec3 hdrColor  = texture2D(s_albedo, v_texcoord0).rgb;

	hdrColor += texture2D(s_light, v_texcoord0).rgb;

	// instead of some fancy tonemapping operator, we just clamp it, to keep it simple.
	vec3 finalColor = clamp(hdrColor, 0.0, 1.0);

	float g = 2.2;
	gl_FragColor = vec4(pow(finalColor, vec3(1.0 / g, 1.0 / g, 1.0 / g) ), 1.0);
}

$input v_texcoord0

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#include "../common/common.sh"
#include "parameters.sh"

SAMPLER2D(s_color, 0);
SAMPLER2D(s_albedo, 1);

void main()
{
	vec2 texCoord = v_texcoord0;
	vec3 lightColor = texture2D(s_color, texCoord).xyz;
	vec3 albedo = texture2D(s_albedo, texCoord).xyz;
	albedo = toLinear(albedo);

	vec3 color = lightColor * albedo;
	color = toGamma(color);

	gl_FragColor = vec4(color, 1.0);
}

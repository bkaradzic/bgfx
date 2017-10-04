$input v_skyColor, v_screenPos, v_viewDir

/*
* Copyright 2017 Stanislav Pidhorskyi. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

uniform vec4 u_parameters; // x - sun size, y - sun bloom, z - exposition, w - time
uniform vec4 u_sunDirection;
uniform vec4 u_sunLuminance;

#include "../common/common.sh"

void main()
{
	float size2 = u_parameters.x * u_parameters.x;

	vec3 lightDir = normalize(u_sunDirection.xyz);
	float dist = 2.0 * (1.0 - dot(normalize(v_viewDir), lightDir));
	float sun  = exp(-dist/ u_parameters.y / size2) + step(dist, size2);
	float sun2 = min(sun * sun, 1.0);
	vec3 color = v_skyColor + sun2;
	color = toGamma(color);

	gl_FragColor = vec4(color, 1.0);
}

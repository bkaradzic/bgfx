$input v_dir

/*
 * Copyright 2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

SAMPLERCUBE(s_texCube, 0);

uniform vec4 u_params;
#define u_exposure  u_params.y

void main()
{
	vec3 dir = normalize(v_dir);

	vec4 color = textureCubeLod(s_texCube, dir, 0.0);
	color *= exp2(u_exposure);

	gl_FragColor = toFilmic(color);
}

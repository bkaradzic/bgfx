$input v_dir

/*
 * Copyright 2014 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"

SAMPLERCUBE(u_texCube, 4);

uniform vec4 u_params;
#define u_exposure  u_params.y

void main()
{
	vec3 dir = normalize(v_dir);

	vec4 color = textureCubeLod(u_texCube, dir, 0.0);
	color *= exp2(u_exposure);

	gl_FragColor = toFilmic(color);
}

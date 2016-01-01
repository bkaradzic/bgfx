$input v_world, v_color0

/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

void main()
{
	vec3 normal = normalize(cross(dFdx(v_world), dFdy(v_world) ) );
	vec3 lightDir = vec3(0.0, 0.0, 1.0);
	float ndotl = max(dot(normal, lightDir), 0.0);
	float spec = pow(ndotl, 30.0);
	gl_FragColor = pow(pow(v_color0, vec4_splat(2.2) ) * ndotl + spec, vec4_splat(1.0/2.2) );
}

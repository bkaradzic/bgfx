$input v_normal, v_color0

/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

void main()
{
	vec3 lightDir = vec3(0.0, 0.0, -1.0);
	float ndotl = dot(normalize(v_normal), lightDir);
	float spec = pow(ndotl, 30.0);
	gl_FragColor = vec4(pow(pow(v_color0.xyz, vec3_splat(2.2) ) * ndotl + spec, vec3_splat(1.0/2.2) ), 1.0);
}

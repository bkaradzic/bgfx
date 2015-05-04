$input v_normal, v_color0

/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"

void main()
{
	vec3 lightDir = vec3(0.0, 0.0, -1.0);
	float ndotl = dot(normalize(v_normal), lightDir);
	float spec = pow(ndotl, 30.0);
	gl_FragColor = vec4(pow(pow(v_color0.xyz, vec3_splat(2.2) ) * ndotl + spec, vec3_splat(1.0/2.2) ), 1.0);
}

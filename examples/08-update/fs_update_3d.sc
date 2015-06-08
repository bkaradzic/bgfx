$input v_texcoord0

/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"

SAMPLER3D(s_texColor, 0);
uniform vec4 u_time;

void main()
{
	vec3 uvw = vec3(v_texcoord0.xy*0.5+0.5,	sin(u_time.x)*0.5+0.5);
	gl_FragColor = vec4_splat(texture3D(s_texColor, uvw).x);
}

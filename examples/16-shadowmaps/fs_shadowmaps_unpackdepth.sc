$input v_texcoord0

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"
SAMPLER2D(s_shadowMap0, 4);

uniform vec4 u_params2;
#define u_depthValuePow u_params2.x

void main()
{
	float depth = unpackRgbaToFloat(texture2D(s_shadowMap0, v_texcoord0) );
	vec3 rgba = pow(vec3_splat(depth), vec3_splat(u_depthValuePow) );
	gl_FragColor = vec4(rgba, 1.0);
}

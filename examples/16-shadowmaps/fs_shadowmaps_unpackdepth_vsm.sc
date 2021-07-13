$input v_texcoord0

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"
SAMPLER2D(s_shadowMap0, 4);

BGFX_BEGIN_UNIFORM_BLOCK(UniformsMaterial)
uniform vec4 u_params2;
BGFX_END_UNIFORM_BLOCK

#define u_depthValuePow u_params2.x

void main()
{
	vec4 val = texture2D(s_shadowMap0, v_texcoord0);
	float depth = unpackHalfFloat(val.rg);
	vec3 rgba = pow(vec3_splat(depth), vec3_splat(u_depthValuePow) );
	gl_FragColor = vec4(rgba, 1.0);
}

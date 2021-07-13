$input a_position, a_texcoord0
$output v_texcoord0, v_texcoord1, v_texcoord2, v_texcoord3, v_texcoord4

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

BGFX_BEGIN_UNIFORM_BLOCK(UniformsMaterial)
uniform vec4 u_smSamplingParams;
BGFX_END_UNIFORM_BLOCK

#define u_yOffset u_smSamplingParams.w

void main()
{
	float offset = u_viewTexel.y*u_yOffset;

	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );
	v_texcoord0 = a_texcoord0;
	v_texcoord1 = vec4(a_texcoord0.x, a_texcoord0.y - offset*1.0,
					   a_texcoord0.x, a_texcoord0.y + offset*1.0
					  );
	v_texcoord2 = vec4(a_texcoord0.x, a_texcoord0.y - offset*2.0,
					   a_texcoord0.x, a_texcoord0.y + offset*2.0
					  );
	v_texcoord3 = vec4(a_texcoord0.x, a_texcoord0.y - offset*3.0,
					   a_texcoord0.x, a_texcoord0.y + offset*3.0
					  );
	v_texcoord4 = vec4(a_texcoord0.x, a_texcoord0.y - offset*4.0,
					   a_texcoord0.x, a_texcoord0.y + offset*4.0
					  );
}

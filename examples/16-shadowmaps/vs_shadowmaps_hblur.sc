$input a_position, a_texcoord0
$output v_texcoord0, v_texcoord1, v_texcoord2, v_texcoord3, v_texcoord4

/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

uniform vec4 u_smSamplingParams;
#define u_xOffset u_smSamplingParams.z

void main()
{
	float offset = u_viewTexel.x*u_xOffset;

	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );
	v_texcoord0 = a_texcoord0;
	v_texcoord1 = vec4(a_texcoord0.x - offset*1.0, a_texcoord0.y,
					   a_texcoord0.x + offset*1.0, a_texcoord0.y
					  );
	v_texcoord2 = vec4(a_texcoord0.x - offset*2.0, a_texcoord0.y,
					   a_texcoord0.x + offset*2.0, a_texcoord0.y
					  );
	v_texcoord3 = vec4(a_texcoord0.x - offset*3.0, a_texcoord0.y,
					   a_texcoord0.x + offset*3.0, a_texcoord0.y
					  );
	v_texcoord4 = vec4(a_texcoord0.x - offset*4.0, a_texcoord0.y,
					   a_texcoord0.x + offset*4.0, a_texcoord0.y
					  );
}

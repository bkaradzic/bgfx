$input a_position, a_texcoord0
$output v_texcoord0, v_texcoord1, v_texcoord2, v_texcoord3, v_texcoord4

/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

void main()
{
	float offset = u_viewTexel.x*8.0;

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

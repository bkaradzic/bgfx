$input a_position, a_texcoord0
$output v_texcoord0, v_texcoord1, v_texcoord2, v_texcoord3, v_texcoord4

/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );
	v_texcoord0 = a_texcoord0;
	v_texcoord1 = vec4(a_texcoord0.x, a_texcoord0.y - u_viewTexel.y*1.0,
					   a_texcoord0.x, a_texcoord0.y + u_viewTexel.y*1.0
					  );
	v_texcoord2 = vec4(a_texcoord0.x, a_texcoord0.y - u_viewTexel.y*2.0,
					   a_texcoord0.x, a_texcoord0.y + u_viewTexel.y*2.0
					  );
	v_texcoord3 = vec4(a_texcoord0.x, a_texcoord0.y - u_viewTexel.y*3.0,
					   a_texcoord0.x, a_texcoord0.y + u_viewTexel.y*3.0
					  );
	v_texcoord4 = vec4(a_texcoord0.x, a_texcoord0.y - u_viewTexel.y*4.0,
					   a_texcoord0.x, a_texcoord0.y + u_viewTexel.y*4.0
					  );
}

$input a_position, a_color0
$output v_world, v_color0

/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );
	v_world = mul(u_model[0], vec4(a_position, 1.0) ).xyz;
	v_color0 = a_color0;
}

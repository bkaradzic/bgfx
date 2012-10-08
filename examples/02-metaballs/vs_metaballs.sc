$input a_position, a_normal, a_color
$output v_normal, v_color0

/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );
	v_normal = mul(u_model, vec4(a_normal, 0.0) ).xyz;
	v_color0 = a_color;
}

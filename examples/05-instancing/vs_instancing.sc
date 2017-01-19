$input a_position, a_color0, i_data0, i_data1, i_data2, i_data3, i_data4
$output v_color0

/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

void main()
{
	mat4 model;
	model[0] = i_data0;
	model[1] = i_data1;
	model[2] = i_data2;
	model[3] = i_data3;

	vec4 worldPos = instMul(model, vec4(a_position, 1.0) );
	gl_Position = mul(u_viewProj, worldPos);
	v_color0 = a_color0*i_data4;
}

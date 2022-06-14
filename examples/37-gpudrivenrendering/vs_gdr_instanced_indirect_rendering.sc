$input a_position, i_data0, i_data1, i_data2, i_data3
$output v_materialID

/*
 * Copyright 2018 Kostas Anagnostou. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

void main()
{
	mat4 model;
	model[0] = vec4(i_data0.xyz, 0.0);
	model[1] = i_data1;
	model[2] = i_data2;
	model[3] = i_data3;

	v_materialID = i_data0.w;

	vec4 worldPos = instMul(model, vec4(a_position, 1.0) );
	gl_Position = mul(u_viewProj, worldPos);
}

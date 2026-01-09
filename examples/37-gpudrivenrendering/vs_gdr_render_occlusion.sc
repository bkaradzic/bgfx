$input a_position, i_data0, i_data1, i_data2, i_data3, i_data4

/*
 * Copyright 2018 Kostas Anagnostou. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

void main()
{
	mat4 model = mtxFromCols(i_data0, i_data1, i_data2, i_data3);

	vec4 worldPos = mul(model, vec4(a_position, 1.0) );
	gl_Position = mul(u_viewProj, worldPos);
}

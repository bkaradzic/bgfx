$input a_position, a_color0
$output v_color0

/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"
#include "instance_data.sh"

BUFFER_RO(instanceData, InstanceData, 0);

void main()
{
	mat4 model = instanceData[gl_InstanceID].transform;

	vec4 worldPos = mul(model, vec4(a_position, 1.0) );
	gl_Position = mul(u_viewProj, worldPos);
	v_color0 = a_color0*instanceData[gl_InstanceID].color;
}

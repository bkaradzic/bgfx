$input a_position, a_indices

/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bgfx_shader.sh>

void main()
{
	vec4 model = mul(u_model[int(a_indices.x)], vec4(a_position, 1.0) );
	gl_Position = mul(u_viewProj, model);
}

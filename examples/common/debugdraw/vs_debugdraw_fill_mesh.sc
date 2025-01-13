$input a_position

/*
 * Copyright 2011-2025 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <bgfx_shader.sh>

void main()
{
	vec4 model = mul(u_model[0], vec4(a_position, 1.0) );
	gl_Position = mul(u_viewProj, model);
}

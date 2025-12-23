$input a_position, a_indices

/*
 * Copyright 2011-2025 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#define BGFX_CONFIG_MAX_BONES 2
#include <bgfx_shader.sh>

void main()
{
	vec4 model = mul(u_model[int(a_indices.x)], vec4(a_position, 1.0) );
	gl_Position = mul(u_viewProj, model);
}

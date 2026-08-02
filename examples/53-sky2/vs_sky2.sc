$input a_position, a_normal
$output v_normal, v_wpos

/*
* Copyright 2026 Mateusz Kozdrowicki. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

#include <bgfx_shader.sh>

void main() {
	vec4 wpos   = mul(u_model[0], vec4(a_position, 1.0) );
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );

	v_normal = mul(u_model[0], vec4(a_normal, 0.0) ).xyz;
	v_wpos   = wpos.xyz;
}

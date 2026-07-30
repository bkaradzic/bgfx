$input a_position
$output v_shadowcoord

/*
* Copyright 2026 Mateusz Kozdrowicki. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

#include <bgfx_shader.sh>

uniform mat4 u_lightViewProj;
uniform mat4 u_lightMtx;

void main() {
	vec4 wpos = mul(u_model[0], vec4(a_position, 1.0) );

	gl_Position   = mul(u_lightViewProj, wpos);
	v_shadowcoord = mul(u_lightMtx, wpos);
}

$input a_position
$output v_texcoord0

/*
* Copyright 2026 Mateusz Kozdrowicki. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

#include <bgfx_shader.sh>

void main() {
	gl_Position = vec4(a_position.xy, 1.0, 1.0);
	v_texcoord0 = a_position.xy;
}

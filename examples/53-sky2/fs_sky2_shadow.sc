$input v_shadowcoord

/*
* Copyright 2026 Mateusz Kozdrowicki. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

#include <bgfx_shader.sh>

void main() {
	gl_FragColor = vec4(v_shadowcoord.z / v_shadowcoord.w, 0.0, 0.0, 1.0);
}

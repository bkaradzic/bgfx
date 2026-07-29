$input v_normal, v_wpos

/*
 * Copyright 2026 Mateusz Kozdrowicki. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <bgfx_shader.sh>

void main() {
    vec3 n = v_normal * 2.0 - 1.0;

    gl_FragColor = vec4(n.x, n.y, n.z, 1.0);
}

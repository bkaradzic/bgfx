$input v_texcoord0

/*
 * Copyright 2014 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx_shader.sh>

SAMPLER2D(u_texColor, 0);

void main()
{
    vec4 color = texture2D(u_texColor, v_texcoord0);

    gl_FragColor = vec4(color.xyz, 1.0);
}


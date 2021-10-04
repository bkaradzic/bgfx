/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bgfx_shader.sh>

uniform vec4 u_params[4];

#define u_lightDir     u_params[0].xyz
#define u_shininess    u_params[0].w
#define u_skyColor     u_params[1].xyz
#define u_groundColor  u_params[2].xyz
#define u_matColor     u_params[3]

void main()
{
	gl_FragColor = u_matColor;
}

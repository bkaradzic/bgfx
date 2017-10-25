/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bgfx_shader.sh>

uniform vec4 u_params;
#define u_textureLod   u_params.x
#define u_textureLayer u_params.y
#define u_ev           u_params.w

vec4 toEv(vec4 _color)
{
	return vec4(_color.xyz * pow(2.0, u_ev), _color.w);
}

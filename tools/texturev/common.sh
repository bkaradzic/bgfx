/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bgfx_shader.sh>

uniform vec4 u_params;
#define u_textureLod   u_params.x
#define u_textureLayer u_params.y
#define u_inLinear     u_params.z
#define u_ev           u_params.w

vec3 toLinear(vec3 _rgb)
{
	return pow(abs(_rgb), vec3_splat(2.2) );
}

vec3 toGamma(vec3 _rgb)
{
	return pow(abs(_rgb), vec3_splat(1.0/2.2) );
}

vec4 toEv(vec4 _color)
{
	vec3 rgb = mix(toLinear(_color.xyz), _color.xyz, u_inLinear);
	return vec4(toGamma(rgb * pow(2.0, u_ev) ), _color.w);
}

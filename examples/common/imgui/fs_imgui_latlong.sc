$input v_texcoord0

/*
 * Copyright 2014-2015 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bgfx_shader.sh>

uniform vec4 u_imageLodEnabled;
SAMPLERCUBE(s_texColor, 0);

#define u_imageLod     u_imageLodEnabled.x
#define u_imageEnabled u_imageLodEnabled.y

vec3 vecFromLatLong(vec2 _uv)
{
	float pi    = 3.14159265;
	float twoPi = 2.0*pi;
	float phi   = _uv.x * twoPi;
	float theta = _uv.y * pi;

	vec3 result;
	result.x = -sin(theta)*sin(phi);
	result.y = cos(theta);
	result.z = -sin(theta)*cos(phi);

	return result;
}

void main()
{
	vec3 dir = vecFromLatLong(v_texcoord0);
	vec3 color = textureCubeLod(s_texColor, dir, u_imageLod).xyz;
	float alpha = 0.2 + 0.8*u_imageEnabled;

	gl_FragColor = vec4(color, alpha);
}

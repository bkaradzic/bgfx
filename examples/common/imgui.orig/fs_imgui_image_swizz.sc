$input v_texcoord0

/*
 * Copyright 2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bgfx_shader.sh>

uniform vec4 u_imageLodEnabled;
uniform vec4 u_swizzle;
SAMPLER2D(s_texColor, 0);

#define u_imageLod     u_imageLodEnabled.x
#define u_imageEnabled u_imageLodEnabled.y

void main()
{
	float color = dot(texture2DLod(s_texColor, v_texcoord0, u_imageLod), u_swizzle);
	float alpha = 0.2 + 0.8*u_imageEnabled;
	gl_FragColor = vec4(vec3_splat(color), alpha);
}

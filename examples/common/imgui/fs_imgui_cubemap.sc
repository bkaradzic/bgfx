$input v_normal

/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bgfx_shader.sh>

uniform vec4 u_imageLodEnabled;
SAMPLERCUBE(s_texColor, 0);

#define u_imageLod     u_imageLodEnabled.x
#define u_imageEnabled u_imageLodEnabled.y

void main()
{
	vec3 color = textureCubeLod(s_texColor, v_normal, u_imageLod).xyz;
	float alpha = 0.2 + 0.8*u_imageEnabled;
	gl_FragColor = vec4(color, alpha);
}

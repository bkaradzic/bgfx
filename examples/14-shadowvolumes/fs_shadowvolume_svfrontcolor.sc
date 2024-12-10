/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"
uniform vec4 u_color;

void main()
{
	gl_FragColor.xyz = u_color.xyz;
	gl_FragColor.w = 0.98;
}

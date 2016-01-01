$input a_position

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );
}

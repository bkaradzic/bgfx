$input v_k

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

uniform vec4 u_svparams;

#define u_dfail u_svparams.y

vec4 stencilColor(float _k)
{
	return vec4(float(abs(_k - 1.0) < 0.0001)/255.0
			  , float(abs(_k + 1.0) < 0.0001)/255.0
			  , float(abs(_k - 2.0) < 0.0001)/255.0
			  , float(abs(_k + 2.0) < 0.0001)/255.0
			  );
}

void main()
{
	float k = v_k;

	if (!gl_FrontFacing)
		k = -k;

	if (u_dfail == 0.0)
		k = -k;

	gl_FragColor = stencilColor(k);
}

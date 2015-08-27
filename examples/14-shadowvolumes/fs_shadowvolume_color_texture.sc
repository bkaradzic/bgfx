$input v_texcoord0

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"
uniform vec4 u_color;
SAMPLER2D(s_texColor, 0);

void main()
{
	vec4 tcolor = toLinear(texture2D(s_texColor, v_texcoord0));

	if (tcolor.x < 0.1) //OK for now.
	{
		discard;
	}

	gl_FragColor = toGamma(tcolor + u_color);
}

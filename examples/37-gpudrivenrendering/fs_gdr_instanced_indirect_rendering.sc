$input v_materialID

/*
 * Copyright 2018 Kostas Anagnostou. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

uniform vec4 u_color[32];

void main()
{
	vec4 color = u_color[uint(v_materialID)];

	if (color.w < 1.0f)
	{
		//render dithered alpha
		if ( (int(gl_FragCoord.x) % 2) == (int(gl_FragCoord.y) % 2) )
		{
			discard;
		}
	}

	gl_FragColor = vec4(color.xyz, 1.0);
}

$input v_materialID

/*
 * Copyright 2018 Kostas Anagnostou. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

uniform vec4 u_colour[50];

void main()
{
	vec4 colour = u_colour[uint(v_materialID)];

	if ( colour.w < 1.0f )
	{
		//render dithered alpha
		if ( (int(gl_FragCoord.x) % 2) == (int(gl_FragCoord.y) % 2) )
			discard;
	}

	gl_FragColor = vec4( colour.xyz,1 );
}

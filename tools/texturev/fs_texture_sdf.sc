$input v_texcoord0, v_color0

/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.sh"

SAMPLER2D(s_texColor, 0);

void main()
{
	vec4 bgColor = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 fgColor = vec4(1.0, 1.0, 1.0, 1.0);

	float sigDist = texture2DLod(s_texColor, v_texcoord0.xy, u_textureLod).x;
	float width   = fwidth(sigDist);
	float edge    = 0.5;
	float opacity = clamp(smoothstep(edge - width, edge + width, sigDist), 0.0, 1.0);

	gl_FragColor  = mix(bgColor, fgColor, opacity);
}

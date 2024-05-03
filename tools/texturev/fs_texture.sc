$input v_texcoord0, v_color0

/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.sh"

SAMPLER2D(s_texColor, 0);

void main()
{
	vec4 color = texture2DLod(s_texColor, v_texcoord0.xy, u_textureLod);
	color.xyz = applyExposure(color.xyz);
	color *= v_color0;

	gl_FragColor = toOutput(color, u_outputFormat, u_sdrWhiteNits);
}

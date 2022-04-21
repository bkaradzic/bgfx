$input v_texcoord0

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

#include "../common/common.sh"
#include "parameters.sh"
#include "bokeh_dof.sh"

SAMPLER2D(s_color,			0);
SAMPLER2D(s_depth,			1);

void main()
{
	vec2 texCoord = v_texcoord0.xy;

	vec3 outColor = DepthOfField(s_color, s_depth, texCoord, u_focusPoint, u_focusScale).xyz;

	// this pass is writing directly out to backbuffer, convert from linear to gamma
	outColor = toGamma(outColor);

	gl_FragColor = vec4(outColor, 1.0);
}

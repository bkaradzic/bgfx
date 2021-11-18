$input v_texcoord0

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#include "../common/common.sh"
#include "parameters.sh"
#include "bokeh_dof.sh"

SAMPLER2D(s_color, 0);
SAMPLER2D(s_depth, 1);

void main()
{
	vec2 texCoord = v_texcoord0.xy;

	vec3 color = texture2D(s_color, texCoord).xyz;
	float depth = texture2D(s_depth, texCoord).x;
	float blurSize = GetBlurSize(depth, u_focusPoint, u_focusScale);

	gl_FragColor = vec4(color, blurSize);
}

$input v_texcoord0

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

#include "../common/common.sh"
#include "parameters.sh"
#include "bokeh_dof.sh"

SAMPLER2D(s_color, 0);
SAMPLER2D(s_depth, 1);

void main()
{
	vec2 texCoord = v_texcoord0.xy;

	// desaturate color to make tinted color stand out
	vec3 color = texture2D(s_color, texCoord).xyz;
	color = toGamma(color);
	color = vec3_splat(dot(color, vec3(0.33, 0.34, 0.33)));

	// get circle of confusion from depth
	float depth = texture2D(s_depth, texCoord).x;
	float circleOfConfusion = GetCircleOfConfusion(depth, u_focusPoint, u_focusScale);

	// apply tint color to debug where blur applied
	vec3 tintColor;
	if (circleOfConfusion < 0.0)
	{
		// tint foreground orange
		tintColor = vec3(187.0, 61.0, 7.0) / 255.0;
	}
	else
	{
		// tint background blue
		tintColor = vec3(11.0, 89.0, 138.0) / 255.0;
	}
	tintColor *= color;
	color = mix(color, tintColor, abs(circleOfConfusion));

	gl_FragColor = vec4(color, 1.0);
}

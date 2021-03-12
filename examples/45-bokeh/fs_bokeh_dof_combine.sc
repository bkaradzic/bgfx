$input v_texcoord0

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#include "../common/common.sh"
#include "parameters.sh"

SAMPLER2D(s_color,			0);
SAMPLER2D(s_blurredColor,	1);

void main()
{
	vec2 texCoord = v_texcoord0.xy;
	vec4 color = texture2D(s_color, texCoord);
	vec4 dofColorSize = texture2D(s_blurredColor, texCoord);
	vec3 dofColor = dofColorSize.xyz;
	float sampleSize = dofColorSize.w;

	float m = saturate(sampleSize-1.0);
	color.xyz = mix(color.xyz, dofColor, m);

	// this pass is writing directly out to backbuffer, convert from linear to gamma
	color.xyz = toGamma(color.xyz);

	gl_FragColor = color;
}

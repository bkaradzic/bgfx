$input v_texcoord0, v_color0

/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.sh"

SAMPLER2D(s_texColor, 0);

float median(vec3 _val)
{
	return max(min(_val.x, _val.y), min(max(_val.x, _val.y), _val.z) );
}

void main() {
	vec4 bgColor = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 fgColor = vec4(1.0, 1.0, 1.0, 1.0);

	vec3  sample  = texture2DLod(s_texColor, v_texcoord0.xy, u_textureLod).xyz;
	float sigDist = median(sample) - 0.5;
	float opacity = clamp(sigDist/fwidth(sigDist) + 0.5, 0.0, 1.0);
	gl_FragColor  = mix(bgColor, fgColor, opacity);
}

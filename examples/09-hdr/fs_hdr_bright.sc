$input v_texcoord0

/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.sh"

SAMPLER2D(s_texColor, 0);
SAMPLER2D(s_texLum, 1);

void main()
{
	float lum = clamp(decodeRE8(texture2D(s_texLum, v_texcoord0) ), 0.1, 0.7);

	vec3 rgb = vec3(0.0, 0.0, 0.0);
	rgb += decodeRGBE8(texture2D(s_texColor, v_texcoord0+u_offset[0].xy) );
	rgb += decodeRGBE8(texture2D(s_texColor, v_texcoord0+u_offset[1].xy) );
	rgb += decodeRGBE8(texture2D(s_texColor, v_texcoord0+u_offset[2].xy) );
	rgb += decodeRGBE8(texture2D(s_texColor, v_texcoord0+u_offset[3].xy) );
	rgb += decodeRGBE8(texture2D(s_texColor, v_texcoord0+u_offset[4].xy) );
	rgb += decodeRGBE8(texture2D(s_texColor, v_texcoord0+u_offset[5].xy) );
	rgb += decodeRGBE8(texture2D(s_texColor, v_texcoord0+u_offset[6].xy) );
	rgb += decodeRGBE8(texture2D(s_texColor, v_texcoord0+u_offset[7].xy) );
	rgb += decodeRGBE8(texture2D(s_texColor, v_texcoord0+u_offset[8].xy) );

	rgb *= 1.0/9.0;

	float middleGray = u_tonemap.x;
	float whiteSqr   = u_tonemap.y;
	float treshold   = u_tonemap.z;
	float offset     = u_tonemap.w;

	rgb = max(vec3_splat(0.0), rgb - treshold) * middleGray / (lum + 0.0001);
	rgb = reinhard2(rgb, whiteSqr);

	gl_FragColor = toGamma(vec4(rgb, 1.0) );
}

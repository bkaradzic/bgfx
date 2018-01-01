$input v_texcoord0

/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.sh"

SAMPLER2D(s_texColor, 0);

void main()
{
	float delta = 0.0001;

	vec3 rgb0 = decodeRGBE8(texture2D(s_texColor, v_texcoord0+u_offset[0].xy) );
	vec3 rgb1 = decodeRGBE8(texture2D(s_texColor, v_texcoord0+u_offset[1].xy) );
	vec3 rgb2 = decodeRGBE8(texture2D(s_texColor, v_texcoord0+u_offset[2].xy) );
	vec3 rgb3 = decodeRGBE8(texture2D(s_texColor, v_texcoord0+u_offset[3].xy) );
	vec3 rgb4 = decodeRGBE8(texture2D(s_texColor, v_texcoord0+u_offset[4].xy) );
	vec3 rgb5 = decodeRGBE8(texture2D(s_texColor, v_texcoord0+u_offset[5].xy) );
	vec3 rgb6 = decodeRGBE8(texture2D(s_texColor, v_texcoord0+u_offset[6].xy) );
	vec3 rgb7 = decodeRGBE8(texture2D(s_texColor, v_texcoord0+u_offset[7].xy) );
	vec3 rgb8 = decodeRGBE8(texture2D(s_texColor, v_texcoord0+u_offset[8].xy) );
	float avg = luma(rgb0).x
			  + luma(rgb1).x
			  + luma(rgb2).x
			  + luma(rgb3).x
			  + luma(rgb4).x
			  + luma(rgb5).x
			  + luma(rgb6).x
			  + luma(rgb7).x
			  + luma(rgb8).x
			  ;
	avg *= 1.0/9.0;

	gl_FragColor = encodeRE8(avg);
}

$input v_texcoord0

/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.sh"

SAMPLER2D(s_texColor, 0);

void main()
{
	float sum;
	sum  = decodeRE8(texture2D(s_texColor, v_texcoord0+u_offset[ 0].xy) );
	sum += decodeRE8(texture2D(s_texColor, v_texcoord0+u_offset[ 1].xy) );
	sum += decodeRE8(texture2D(s_texColor, v_texcoord0+u_offset[ 2].xy) );
	sum += decodeRE8(texture2D(s_texColor, v_texcoord0+u_offset[ 3].xy) );
	sum += decodeRE8(texture2D(s_texColor, v_texcoord0+u_offset[ 4].xy) );
	sum += decodeRE8(texture2D(s_texColor, v_texcoord0+u_offset[ 5].xy) );
	sum += decodeRE8(texture2D(s_texColor, v_texcoord0+u_offset[ 6].xy) );
	sum += decodeRE8(texture2D(s_texColor, v_texcoord0+u_offset[ 7].xy) );
	sum += decodeRE8(texture2D(s_texColor, v_texcoord0+u_offset[ 8].xy) );
	sum += decodeRE8(texture2D(s_texColor, v_texcoord0+u_offset[ 9].xy) );
	sum += decodeRE8(texture2D(s_texColor, v_texcoord0+u_offset[10].xy) );
	sum += decodeRE8(texture2D(s_texColor, v_texcoord0+u_offset[11].xy) );
	sum += decodeRE8(texture2D(s_texColor, v_texcoord0+u_offset[12].xy) );
	sum += decodeRE8(texture2D(s_texColor, v_texcoord0+u_offset[13].xy) );
	sum += decodeRE8(texture2D(s_texColor, v_texcoord0+u_offset[14].xy) );
	sum += decodeRE8(texture2D(s_texColor, v_texcoord0+u_offset[15].xy) );
	float avg = sum/16.0;
	gl_FragColor = encodeRE8(avg);
}

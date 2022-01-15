$input v_texcoord0

/*
 * Copyright 2018 Eric Arnebäck. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

SAMPLER2D(s_tex, 0);

uniform vec4 u_pixelSize;
uniform vec4 u_intensity;

void main()
{
	vec2 halfpixel = u_pixelSize.xy;
	vec2 uv = v_texcoord0.xy;

	vec4 sum = vec4_splat(0.0);

	sum += (2.0 / 16.0) * texture2D(s_tex, uv + vec2(-halfpixel.x,  0.0) );
	sum += (2.0 / 16.0) * texture2D(s_tex, uv + vec2( 0.0,          halfpixel.y) );
	sum += (2.0 / 16.0) * texture2D(s_tex, uv + vec2( halfpixel.x,  0.0) );
	sum += (2.0 / 16.0) * texture2D(s_tex, uv + vec2( 0.0,         -halfpixel.y) );

	sum += (1.0 / 16.0) * texture2D(s_tex, uv + vec2(-halfpixel.x, -halfpixel.y) );
	sum += (1.0 / 16.0) * texture2D(s_tex, uv + vec2(-halfpixel.x,  halfpixel.y) );
	sum += (1.0 / 16.0) * texture2D(s_tex, uv + vec2( halfpixel.x, -halfpixel.y) );
	sum += (1.0 / 16.0) * texture2D(s_tex, uv + vec2( halfpixel.x,  halfpixel.y) );

	sum += (4.0 / 16.0) * texture2D(s_tex, uv);

	gl_FragColor = u_intensity.x * sum;
}

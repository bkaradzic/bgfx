$input v_texcoord0

/*
 * Copyright 2018 Eric Arnebäck. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

SAMPLER2D(s_tex, 0);

// pixel size of the target texture.
uniform vec4 u_pixelSize;

void main()
{
	vec2 halfpixel = 0.5 * vec2(u_pixelSize.x, u_pixelSize.y);
	vec2 oneepixel = 1.0 * vec2(u_pixelSize.x, u_pixelSize.y);

	vec2 uv = v_texcoord0.xy;

	vec4 sum = vec4(0.0, 0.0, 0.0, 0.0);

	sum += (4.0/32.0) * texture2D(s_tex, uv).rgba;

	sum += (4.0/32.0) * texture2D(s_tex, uv + vec2(-halfpixel.x, -halfpixel.y) );
	sum += (4.0/32.0) * texture2D(s_tex, uv + vec2(+halfpixel.x, +halfpixel.y) );
	sum += (4.0/32.0) * texture2D(s_tex, uv + vec2(+halfpixel.x, -halfpixel.y) );
	sum += (4.0/32.0) * texture2D(s_tex, uv + vec2(-halfpixel.x, +halfpixel.y) );

	sum += (2.0/32.0) * texture2D(s_tex, uv + vec2(+oneepixel.x, 0.0) );
	sum += (2.0/32.0) * texture2D(s_tex, uv + vec2(-oneepixel.x, 0.0) );
	sum += (2.0/32.0) * texture2D(s_tex, uv + vec2(0.0, +oneepixel.y) );
	sum += (2.0/32.0) * texture2D(s_tex, uv + vec2(0.0, -oneepixel.y) );

	sum += (1.0/32.0) * texture2D(s_tex, uv + vec2(+oneepixel.x, +oneepixel.y) );
	sum += (1.0/32.0) * texture2D(s_tex, uv + vec2(-oneepixel.x, +oneepixel.y) );
	sum += (1.0/32.0) * texture2D(s_tex, uv + vec2(+oneepixel.x, -oneepixel.y) );
	sum += (1.0/32.0) * texture2D(s_tex, uv + vec2(-oneepixel.x, -oneepixel.y) );

	gl_FragColor.xyzw = sum;
}

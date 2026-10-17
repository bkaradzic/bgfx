/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef IMGUI_OUTPUT_SH_HEADER_GUARD
#define IMGUI_OUTPUT_SH_HEADER_GUARD

uniform vec4 u_imguiOutput;

#define u_imguiOutputMode  u_imguiOutput.x
#define u_imguiOutputWhite u_imguiOutput.y

vec3 imguiOutput(vec3 _rgb)
{
	if (u_imguiOutputMode < 0.5)
	{
		return _rgb;
	}

	vec3 lo  = _rgb / 12.92;
	vec3 hi  = pow( (_rgb + 0.055) / 1.055, vec3_splat(2.4) );
	vec3 rgb = mix(hi, lo, vec3(lessThanEqual(_rgb, vec3_splat(0.04045) ) ) ) * u_imguiOutputWhite;

	if (u_imguiOutputMode < 1.5)
	{
		return rgb;
	}

	vec3 bt2020 = vec3(
		  dot(vec3(0.6274, 0.3293, 0.0433), rgb)
		, dot(vec3(0.0691, 0.9195, 0.0114), rgb)
		, dot(vec3(0.0164, 0.0880, 0.8956), rgb)
		);

	const float m1 = 2610.0/16384.0;
	const float m2 = 2523.0/4096.0*128.0;
	const float c1 = 3424.0/4096.0;
	const float c2 = 2413.0/4096.0*32.0;
	const float c3 = 2392.0/4096.0*32.0;

	vec3 yy = pow(clamp(bt2020, 0.0, 1.0), vec3_splat(m1) );
	return pow( (c1 + c2*yy) / (1.0 + c3*yy), vec3_splat(m2) );
}

#endif // IMGUI_OUTPUT_SH_HEADER_GUARD

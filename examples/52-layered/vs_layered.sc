$input a_position, a_color0
$output v_color0, v_eye

/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <bgfx_shader.sh>

uniform vec4 u_eyeParams; // x = eye separation

void main()
{
	// Layered path: draw once with one instance per layer and route each
	// instance to its own array layer via gl_Layer.
#if BGFX_SHADER_LANGUAGE_ESSL || BGFX_SHADER_LANGUAGE_WGSL
	// gl_Layer / layered rendering is not available on these targets, so the
	// layered program is never used there (BGFX_CAPS_VIEWPORT_LAYER_ARRAY is
	// not advertised). Keep it compiling as a single-layer fallback.
	float eyeIndex = 0.0;
#else
	float eyeIndex = float(gl_InstanceID);
	gl_Layer = int(gl_InstanceID);
#endif

	vec4 pos = mul(u_modelViewProj, vec4(a_position, 1.0) );
	pos.x += (eyeIndex * 2.0 - 1.0) * u_eyeParams.x * pos.w;
	gl_Position = pos;

	v_color0 = a_color0;
	v_eye = eyeIndex;
}

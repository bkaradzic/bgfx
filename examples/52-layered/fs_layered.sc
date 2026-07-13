$input v_color0, v_eye

/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <bgfx_shader.sh>

void main()
{
	// Strongly tint each eye so it is obvious that both array layers hold
	// independent content: left layer red, right layer blue.
	vec3 tint = mix(vec3(1.0, 0.15, 0.15), vec3(0.15, 0.4, 1.0), v_eye);
	gl_FragColor = vec4(v_color0.xyz * tint, 1.0);
}

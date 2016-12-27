$input v_texcoord0, v_color0

/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx_shader.sh>

SAMPLER2D(s_texColor, 0);

uniform vec4 u_params;
#define u_textureLod u_params.x

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

void main() {
	vec4 bgColor = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 fgColor = vec4(0.0, 0.0, 0.0, 1.0);

    vec3 sample = texture2DLod(s_texColor, v_texcoord0, u_textureLod).rgb;
    float sigDist = median(sample.r, sample.g, sample.b) - 0.5;
    float opacity = clamp(sigDist/fwidth(sigDist) + 0.5, 0.0, 1.0);
    gl_FragColor = mix(bgColor, fgColor, opacity);
}

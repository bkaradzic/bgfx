$input v_color0, v_texcoord0

#include "../common/common.sh"
#include "s2h/s2h_bgfx.sh"

uniform vec4 u_s2hTime;

void main()
{
	vec2 uv = v_texcoord0;
	float grid = step(0.96f, fract(uv.x * 10.0f)) + step(0.96f, fract(uv.y * 10.0f));
	float wave = 0.5f + 0.5f * sin(u_s2hTime.x + uv.x * 8.0f + uv.y * 5.0f);
	vec3 color = mix(vec3(0.06f, 0.1f, 0.25f), vec3(0.9f, 0.25f, 0.1f), wave);
	gl_FragColor = vec4(mix(color, vec3(1.0f, 1.0f, 1.0f), grid), 1.0f);
}

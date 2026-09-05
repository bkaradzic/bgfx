$input v_color0, v_texcoord0

#include "../common/common.sh"
#include "s2h/s2h_bgfx.sh"

SAMPLER2D(s_quadPostColor, 0);
uniform vec4 u_s2hMouse;

void main()
{
	vec2 uv = v_texcoord0;
	vec3 color = texture2D(s_quadPostColor, uv).rgb;
	vec2 mouseUv = u_s2hMouse.xy / u_viewRect.zw;
	vec2 delta = uv - mouseUv;
	float highlight = 1.0f - smoothstep(0.02f, 0.025f, length(delta));
	color = mix(color, vec3(1.0f, 1.0f, 0.0f), highlight);
	gl_FragColor = vec4(color, 1.0f);
}

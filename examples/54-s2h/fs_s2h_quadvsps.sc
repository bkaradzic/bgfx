$input v_color0, v_texcoord0

#include "../common/common.sh"
#include "s2h_bgfx.sh"
#include "s2h.hlsl"

uniform vec4 u_s2hTime;
uniform vec4 u_s2hMouse;

void main()
{
	vec2 edge = min(v_texcoord0, 1.0f - v_texcoord0);
	float border = 1.0f - smoothstep(0.008f, 0.018f, min(edge.x, edge.y));
	vec3 color = lerp(vec3(0.03f, 0.04f, 0.08f), vec3(1.0f, 0.0f, 1.0f), border * 0.4f);

	ContextGather ui;
	s2h_init(ui, s2h_getPixelCoord(gl_FragCoord.xy));
	s2h_setCursor(ui, vec2(10.0f, 10.0f));
	s2h_setScale(ui, 2);
	s2h_printTxt(ui, _Q, _u, _a, _d);
	s2h_printTxt(ui, _V, _S, _P, _S);
	s2h_printLF(ui);
	s2h_printLF(ui);
	vec2 mouseUv = u_s2hMouse.xy / u_viewRect.zw;
	s2h_printTxt(ui, _u, _v, _COLON, _SPACE);
	s2h_printFloat(ui, mouseUv.x); s2h_printTxt(ui, _COMMA); s2h_printFloat(ui, mouseUv.y);
	s2h_printLF(ui);
	s2h_printTxt(ui, _t, _i, _m, _e, _COLON, _SPACE); s2h_printFloat(ui, u_s2hTime.x);

	color = lerp(color, ui.dstColor.rgb, ui.dstColor.a);
	gl_FragColor = vec4(color, 1.0f);
}

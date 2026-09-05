$input v_color0, v_texcoord0

// Port of ShaderToHuman-bgfx/examples/HelloScreenVSPS/HelloWorldPS.hlsl.
#include "../common/common.sh"
#include "s2h_bgfx.sh"
#include "s2h.hlsl"

void main()
{
	vec2 pxPos = s2h_getPixelCoord(gl_FragCoord.xy);
	vec2 dimensions = u_viewRect.zw;
	vec2 uv = pxPos / dimensions;

	ContextGather ui;
	s2h_init(ui, pxPos);
	s2h_setCursor(ui, vec2(10.0f, 10.0f));
	s2h_setScale(ui, 3.0f);
	s2h_printTxt(ui, _H, _e, _l, _l, _o);
	s2h_printLF(ui);
	s2h_printTxt(ui, _S, _c, _r, _e, _e);
	s2h_printTxt(ui, _n);
	s2h_drawSRGBRamp(ui, vec2(10.0f, 100.0f));

	vec4 background = vec4(uv.x, uv.y, 0.0f, 1.0f);
	gl_FragColor = lerp(background, vec4(ui.dstColor.rgb, 1.0f), ui.dstColor.a);
}

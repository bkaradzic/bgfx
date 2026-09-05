$input v_color0, v_texcoord0

// Port of ShaderToHuman-bgfx/examples/Features/2D_CoordinateSystem.hlsl.
#include "../common/common.sh"
#include "s2h_bgfx.sh"
#include "s2h.hlsl"

void main()
{
	vec4 background = vec4(0.01f, 0.01f, 0.1f, 1.0f);

	ContextGather ui;
	vec2 pixelPosition = floor(s2h_getPixelCoord(gl_FragCoord.xy)) + 0.5f;
	s2h_init(ui, pixelPosition);
	s2h_setScale(ui, 2);
	s2h_setCursor(ui, vec2(10.0f, 10.0f));

	s2h_coordinateSystem(ui, vec2(50.0f, 130.0f), vec4(-30.0f, -30.0f, 250.0f, 250.0f), 1.0f, 20.0f, vec4(1.0f, 1.0f, 1.0f, 0.25f), 0);
	ui.lineWidth = 1.0f;
	s2h_coordinateSystem(ui, vec2(440.0f, 150.0f), vec4(-10.0f, -120.0f, 150.0f, 10.0f), 1.0f, 20.0f, vec4(1.0f, 1.0f, 1.0f, 0.25f), 3);

	s2h_printTxt(ui, _s, _2, _h, _UNDERSCORE);
	s2h_printTxt(ui, _c, _o, _o, _r, _d, _i);
	s2h_printTxt(ui, _n, _a, _t, _e, _S, _y);
	s2h_printTxt(ui, _s, _t, _e, _m);

	gl_FragColor = lerp(background, vec4(ui.dstColor.rgb, 1.0f), ui.dstColor.a);
}

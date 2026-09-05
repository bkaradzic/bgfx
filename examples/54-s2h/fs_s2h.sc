$input v_color0, v_texcoord0

#include "../common/common.sh"
#include "s2h/s2h.sh"

void main()
{
	ContextGather ui;
	s2h_init(ui, s2h_getPixelCoord(gl_FragCoord.xy));
	s2h_setCursor(ui, vec2(16.0f, 16.0f));
	s2h_setScale(ui, 2.0f);

	// s2h_printTxt accepts up to six characters per call.
	s2h_printTxt(ui, _H, _e, _l, _l, _o, _SPACE);
	s2h_printTxt(ui, _W, _o, _r, _l, _d);

	vec4 background = vec4(0.02f, 0.02f, 0.02f, 1.0f);
	vec4 linearColor = background * (1.0f - ui.dstColor.a) + ui.dstColor;
	gl_FragColor = vec4(s2h_accurateLinearToSRGB(linearColor.rgb), linearColor.a);
}

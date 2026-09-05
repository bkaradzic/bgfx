// Port of ShaderToHuman-bgfx/examples/Features/Scatter_example.hlsl.
#include "bgfx_compute.sh"
#include "s2h_bgfx.sh"
#include "s2h.hlsl"
#include "s2h_scatter.hlsl"

IMAGE2D_WO(s_scatterColor, rgba8, 0);
uniform vec4 u_s2hScatterSize;

void onGfxForAllScatter(ivec2 _pixel, vec4 _color)
{
	if (_pixel.x >= 0 && _pixel.y >= 0
	&& _pixel.x < int(u_s2hScatterSize.x) && _pixel.y < int(u_s2hScatterSize.y) )
	{
		ivec2 outputPixel = _pixel;
		if (u_s2hScatterSize.z != 0.0f)
		{
			outputPixel.y = int(u_s2hScatterSize.y) - 1 - outputPixel.y;
		}
		imageStore(s_scatterColor, outputPixel, _color);
	}
}

void printDiscEx(inout ContextScatter _ui, vec4 _color)
{
	s2h_printDisc(_ui, _color);
	s2h_printTxt(_ui, _SPACE);
	s2h_printInt(_ui, int(_color.r * 255.9f));
	s2h_printTxt(_ui, _COMMA);
	s2h_printInt(_ui, int(_color.g * 255.9f));
	s2h_printTxt(_ui, _COMMA);
	s2h_printInt(_ui, int(_color.b * 255.9f));
}

void showColorContent(inout ContextScatter _ui)
{
	_ui.pxLeftX += 4;
	s2h_setScale(_ui, 2);
	for (int ii = 0; ii < 4; ++ii) { s2h_printLF(_ui); }

	vec4 a = vec4(1.0, 0.0, 0.0, 1.0);
	vec4 b = vec4(0.0, 1.0, 0.0, 1.0);
	printDiscEx(_ui, a);     s2h_printTxt(_ui, _EQUAL, _A); s2h_printLF(_ui);
	printDiscEx(_ui, b);     s2h_printTxt(_ui, _EQUAL, _B); s2h_printLF(_ui);
	printDiscEx(_ui, a + b); s2h_printTxt(_ui, _EQUAL, _A, _PLUS, _B); s2h_printLF(_ui);
	printDiscEx(_ui, a * b); s2h_printTxt(_ui, _EQUAL, _A, _ASTERISK, _B);
}

NUM_THREADS(8, 8, 1)
void main()
{
	if (gl_GlobalInvocationID.x != 0 || gl_GlobalInvocationID.y != 0)
	{
		return;
	}

	ContextScatter ui;
	s2h_init(ui);
	s2h_setCursor(ui, vec2(10.0, 10.0));
	ui.textColor.rgb = vec3(1.0, 1.0, 1.0);
	s2h_setScale(ui, 3);
	s2h_printTxt(ui, _S, _2, _H, _UNDERSCORE, _S, _c);
	s2h_printTxt(ui, _a, _t, _t, _e, _r);
	s2h_printLF(ui); s2h_printLF(ui);

	ui.textColor.rgb = vec3(0.0, 0.0, 0.0);
	s2h_setScale(ui, 2);
	s2h_printTxt(ui, _S, _i, _n, _g, _l, _e);
	s2h_printTxt(ui, _SPACE, _T, _h, _r, _e, _a);
	s2h_printTxt(ui, _d); s2h_printLF(ui);

	ui.textColor.rgb = vec3(1.0, 0.0, 0.0); s2h_printTxt(ui, _R);
	ui.textColor.rgb = vec3(0.0, 1.0, 0.0); s2h_printTxt(ui, _G);
	ui.textColor.rgb = vec3(0.0, 0.0, 1.0); s2h_printTxt(ui, _B, _SPACE);
	ui.textColor.rgb = vec3(0.0, 0.0, 0.0); s2h_printTxt(ui, _X, _Y, _Z, _COLON); s2h_printLF(ui);
	s2h_printInt(ui, 12345); s2h_printLF(ui);
	s2h_printInt(ui, -12345); s2h_printLF(ui);
	s2h_printHex(ui, 0x1297abu); s2h_printLF(ui); s2h_printLF(ui);
	s2h_printFloat(ui, -12.34); s2h_printTxt(ui, _COMMA); s2h_printFloat(ui, 0.34); s2h_printLF(ui);
	s2h_printBlock(ui, vec4(1.0, 0.7, 0.3, 1.0));
	s2h_printBlock(ui, vec4(1.0, 0.0, 0.0, 1.0));
	s2h_printDisc(ui, vec4(0.0, 1.0, 0.0, 1.0));
	s2h_printDisc(ui, vec4(1.0, 1.0, 0.0, 1.0));
	showColorContent(ui);
}

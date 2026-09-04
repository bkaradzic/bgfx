$input v_color0, v_texcoord0

// Port of ShaderToHuman-bgfx/examples/Features/2D_Arrow.hlsl.
#include "../common/common.sh"
#include "s2h_bgfx.sh"
#include "s2h.hlsl"

uniform vec4 u_s2hMouse;

#define PI 3.14159265f

void testDrawArrow(inout ContextGather _ui, vec2 _start, vec2 _end, float _headLength, float _headWidth)
{
	s2h_drawArrow(_ui, _start, _end, vec4(0.0f, 0.0f, 0.0f, 1.0f), _ui.lineWidth * _headLength, _ui.lineWidth * _headWidth);

	float lineWidth = _ui.lineWidth;
	_ui.lineWidth = 1.0f;
	s2h_drawCrosshair(_ui, _start, 5.0f, vec4(1.0f, 0.0f, 0.0f, 0.5f));
	s2h_drawCrosshair(_ui, _end,   5.0f, vec4(0.0f, 1.0f, 0.0f, 0.5f));
	_ui.lineWidth = lineWidth;
}

void main()
{
	ContextGather ui;
	s2h_init(ui, s2h_getPixelCoord(gl_FragCoord.xy));
	ui.mouseInput = u_s2hMouse;

	for (float width = 0.0f; width < 8.0f; width += 1.0f)
	{
		ui.lineWidth = width;
		float y = 50.0f + width * 20.0f;
		testDrawArrow(ui, vec2(20.0f,  y), vec2(60.0f,  y), 0.0f, 0.0f);
		testDrawArrow(ui, vec2(120.0f, y), vec2(160.0f, y), 4.0f, 1.5f);
		testDrawArrow(ui, vec2(220.0f, y), vec2(260.0f, y), 8.0f, 1.5f);
		testDrawArrow(ui, vec2(320.0f, y), vec2(360.0f, y), 8.0f, 0.5f);
		testDrawArrow(ui, vec2(420.0f, y), vec2(560.0f, y), 8.0f, 1.5f);
	}

	ui.lineWidth = 5.0f;
	const uint count = 12u;
	const vec2 center = vec2(700.0f, 120.0f);
	for (uint ii = 0u; ii < count; ++ii)
	{
		float angle = float(ii) / float(count) * PI * 2.0f;
		vec2 direction = vec2(sin(angle), cos(angle));
		testDrawArrow(ui, center + direction * 24.0f, center + direction * 80.0f, 8.0f, 1.5f);
	}

	s2h_setCursor(ui, vec2(20.0f, 20.0f));  s2h_printTxt(ui, _0, _COMMA, _SPACE, _0);
	s2h_setCursor(ui, vec2(120.0f, 20.0f)); s2h_printTxt(ui, _4, _COMMA, _SPACE, _1, _PERIOD, _5);
	s2h_setCursor(ui, vec2(220.0f, 20.0f)); s2h_printTxt(ui, _8, _COMMA, _SPACE, _1, _PERIOD, _5);
	s2h_setCursor(ui, vec2(320.0f, 20.0f)); s2h_printTxt(ui, _8, _COMMA, _SPACE, _0, _PERIOD, _5);
	s2h_setCursor(ui, vec2(470.0f, 20.0f)); s2h_printTxt(ui, _8, _COMMA, _SPACE, _1, _PERIOD, _5);

	ui.lineWidth = 10.0f;
	vec2 screenCenter = u_viewRect.zw * 0.5f;
	float lineLength = length(ui.mouseInput.xy - screenCenter);
	float arrowHeadLength = max(0.25f * lineLength, 40.0f);
	float arrowHeadWidth = max(0.5f * arrowHeadLength, 20.0f);
	s2h_drawArrow(ui, screenCenter, ui.mouseInput.xy, vec4(0.0f, 0.0f, 1.0f, 1.0f), arrowHeadLength, arrowHeadWidth);

	vec2 oppositeOffset = screenCenter - ui.mouseInput.xy;
	vec2 oppositeDirection = oppositeOffset / max(length(oppositeOffset), 0.0001f);
	s2h_drawArrow(ui, screenCenter, screenCenter + oppositeDirection * lineLength, vec4(1.0f, 0.0f, 0.0f, 1.0f), arrowHeadLength, arrowHeadWidth);

	vec4 background = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	gl_FragColor = lerp(background, vec4(ui.dstColor.rgb, 1.0f), ui.dstColor.a);
}

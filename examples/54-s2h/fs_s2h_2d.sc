$input v_color0, v_texcoord0

// Fragment-renderer port of ShaderToHuman-bgfx/examples/Features/2D_example.hlsl.
#include "../common/common.sh"
#include "s2h_bgfx.sh"
#include "s2h.hlsl"

uniform vec4 u_s2hTime;
uniform vec4 u_s2hMouse;

#define PI 3.14159265f

void drawEye(inout ContextGather _ui, float2 _center)
{
	float2 offset = _ui.mouseInput.xy - _center;
	float offsetLength = length(offset);
	if (offsetLength > 11.0f)
	{
		offset *= 11.0f / offsetLength;
	}

	s2h_drawDisc(_ui, _center, 30.0f, float4(0.0f, 0.0f, 0.0f, 1.0f));
	s2h_drawDisc(_ui, _center, 25.0f, float4(1.0f, 1.0f, 1.0f, 1.0f));
	s2h_drawDisc(_ui, _center + offset, 15.0f, float4(0.0f, 0.0f, 0.0f, 1.0f));
}

void drawBlendingExample(inout ContextGather _ui)
{
	float3 backgroundColor = float3(0.3f, 0.6f, 0.9f);
	float3 overColor = backgroundColor;
	float4 underAccumulator = float4(0.0f, 0.0f, 0.0f, 0.0f);

	for (int peelId = 0; peelId < 5; ++peelId)
	{
		float angle = float(peelId) * 0.6f;
		float3 color = s2h_indexToColor(uint(peelId));
		float2 center = float2(sin(angle), cos(angle)) * 60.0f + float2(105.0f, 450.0f);
		float alpha = saturate(2.0f - length(_ui.pxPos - center) / 25.0f);
		overColor = lerp(overColor, color, alpha);
		underAccumulator.rgb += color * alpha * (1.0f - underAccumulator.a);
		underAccumulator.a = 1.0f - (1.0f - alpha) * (1.0f - underAccumulator.a);
	}

	float3 underColor = backgroundColor * (1.0f - underAccumulator.a) + underAccumulator.rgb;
	const float4 rectangle = float4(10.0f, 300.0f, 290.0f, 590.0f);
	s2h_drawRectangle(_ui, rectangle.xy - 3.0f, rectangle.zw + 3.0f, float4(0.0f, 0.0f, 0.0f, 1.0f));

	float3 color = float3(1.0f, 0.0f, 0.0f);
	if (_ui.pxPos.x >= rectangle.x && _ui.pxPos.y >= rectangle.y && _ui.pxPos.x < rectangle.z && _ui.pxPos.y < rectangle.w)
	{
		float comparison = floor(_ui.pxPos.x) - floor(_ui.mouseInput.x);
		color = comparison < -2.0f ? underColor : (comparison > 2.0f ? overColor : float3(1.0f, 1.0f, 0.0f));
	}
	s2h_drawRectangle(_ui, rectangle.xy, rectangle.zw, float4(color, 1.0f));
}

void main()
{
	ContextGather ui;
	s2h_init(ui, s2h_getPixelCoord(gl_FragCoord.xy));
	ui.mouseInput = u_s2hMouse;
	s2h_setCursor(ui, float2(10.0f, 10.0f));

	float4 topColor = float4(0.95f, 0.25f, 0.25f, 0.8f);
	float4 bottomColor = float4(0.25f, 0.45f, 0.95f, 0.8f);
	float2 borderSizes = float2(4.0f, 8.0f);

	ui.textColor.rgb = float3(1.0f, 1.0f, 1.0f);
	s2h_setScale(ui, 3);
	s2h_printTxt(ui, _2, _D, _T, _e, _s, _t);
	s2h_printLF(ui);
	s2h_printLF(ui);
	ui.textColor.rgb = float3(0.0f, 0.0f, 0.0f);
	s2h_setScale(ui, 2);
	s2h_printTxt(ui, _w, _i, _t, _h, _SPACE);
	s2h_printTxt(ui, _A, _A);

	ui.pxCursor = float2(200.0f, 5.0f);
	ui.pxLeftX = ui.pxCursor.x;
	s2h_sliderRGBA(ui, 8u, topColor); s2h_printSpace(ui, 1.0f); s2h_printTxt(ui, _t, _o, _p); s2h_printTxt(ui, _SPACE, _l, _a, _y, _e, _r);
	s2h_printLF(ui); s2h_printLF(ui); s2h_printLF(ui); s2h_printLF(ui); s2h_printLF(ui);
	s2h_sliderRGBA(ui, 8u, bottomColor); s2h_printSpace(ui, 1.0f); s2h_printTxt(ui, _b, _o, _t, _t, _o, _m); s2h_printTxt(ui, _SPACE, _l, _a, _y, _e, _r);
	s2h_printLF(ui); s2h_printLF(ui); s2h_printLF(ui); s2h_printLF(ui); s2h_printLF(ui);
	s2h_sliderFloat(ui, 8u, borderSizes.x, 0.0f, 20.0f); s2h_printTxt(ui, _SPACE, _t, _o, _p); s2h_printTxt(ui, _SPACE, _b, _o, _r, _d, _e); s2h_printTxt(ui, _r);
	s2h_printLF(ui);
	s2h_sliderFloat(ui, 8u, borderSizes.y, 0.0f, 20.0f); s2h_printTxt(ui, _SPACE, _b, _o, _t, _t, _o); s2h_printTxt(ui, _m); s2h_printTxt(ui, _SPACE, _b, _o, _r, _d, _e); s2h_printTxt(ui, _r);

	s2h_drawRectangleAA(ui, float2(250.0f, 240.0f), float2(350.0f, 300.0f), float4(1.0f, 1.0f, 1.0f, 1.0f), bottomColor, borderSizes.y);
	s2h_drawRectangleAA(ui, float2(220.0f, 210.0f), float2(280.0f, 280.0f), float4(1.0f, 1.0f, 1.0f, 1.0f), topColor, borderSizes.x);

	float lineWidth = ui.lineWidth;
	ui.lineWidth = 2.0f; s2h_drawCircle(ui, float2(50.0f, 120.0f), 20.0f, float4(1.0f, 0.0f, 0.0f, 1.0f));
	ui.lineWidth = 4.0f; s2h_drawCircle(ui, float2(50.0f, 120.0f), 30.0f, float4(0.0f, 1.0f, 0.0f, 1.0f));
	ui.lineWidth = 3.0f; s2h_drawCrosshair(ui, float2(50.0f, 120.0f), 10.0f, float4(0.0f, 0.0f, 1.0f, 1.0f));
	ui.lineWidth = 12.0f;
	float2 animatedOffset = float2(sin(u_s2hTime.x), cos(u_s2hTime.x)) * 20.0f;
	s2h_drawLine(ui, float2(50.0f, 200.0f) + animatedOffset, float2(50.0f, 200.0f) - animatedOffset, float4(0.0f, 0.0f, 1.0f, 1.0f));
	ui.lineWidth = lineWidth;

	drawEye(ui, float2(450.0f, 240.0f));
	drawEye(ui, float2(510.0f, 240.0f));
	s2h_drawSRGBRamp(ui, float2(520.0f, 10.0f));

	for (int ii = 0; ii < 3; ++ii)
	{
		float angle = float(ii) * PI * 2.0f / 3.0f;
		float3 halfSpace = float3(sin(angle), cos(angle), 0.0f);
		halfSpace.z -= dot(halfSpace, float3(450.0f, 340.0f, 1.0f));
		s2h_drawHalfSpace(ui, halfSpace, ui.mouseInput.xy, float4(s2h_indexToColor(uint(ii + 1)), 1.0f), 20.0f, 40.0f);
	}

	drawBlendingExample(ui);
	float4 background = float4(0.7f, 0.4f, 0.4f, 1.0f);
	gl_FragColor = lerp(background, float4(ui.dstColor.rgb, 1.0f), ui.dstColor.a);
}

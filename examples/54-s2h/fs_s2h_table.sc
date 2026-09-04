$input v_color0, v_texcoord0

// Port of ShaderToHuman-bgfx/examples/Features/Table_example.hlsl.
#include "../common/common.sh"
#include "s2h_bgfx.sh"
#include "s2h.hlsl"

uniform vec4 u_s2hTime;

bool s2h_tableLookupInt(uint _column, uint _row, out int _value)
{
	if (1u == _column)
	{
		if (_row > 10u)
		{
			return false;
		}
		_value = 2 + int(_row * _row);
	}
	else
	{
		if (_row > 12u)
		{
			return false;
		}
		_value = int(_row);
	}
	return true;
}

bool s2h_tableLookupFloat(uint _column, uint _row, out float _value)
{
	if (_column == 2u && _row <= 10u)
	{
		_value = sin(u_s2hTime.x + float(_row) * 0.5f);
		return true;
	}
	if (_column == 3u && _row <= 10u)
	{
		_value = cos(u_s2hTime.x + float(_row) * 0.5f);
		return true;
	}
	return false;
}

float s2h_floatLookupFloat(uint _functionId, float _x)
{
	return sin(_x) + cos(u_s2hTime.x * 3.0f + _x * 15.0f) * 0.1f;
}

void main()
{
	ContextGather ui;
	s2h_init(ui, s2h_getPixelCoord(gl_FragCoord.xy));
	s2h_setCursor(ui, vec2(10.0f, 10.0f));

	ui.textColor.rgb = vec3(1.0f, 1.0f, 1.0f);
	s2h_setScale(ui, 3);
	s2h_printTxt(ui, _T, _a, _b, _l, _e);
	s2h_printTxt(ui, _T, _e, _s, _t);
	s2h_printLF(ui);
	s2h_printLF(ui);
	ui.textColor.rgb = vec3(0.0f, 0.0f, 0.0f);
	s2h_setScale(ui, 2);
	s2h_printTxt(ui, _P, _i, _x, _e, _l, _EQUAL);
	s2h_printTxt(ui, _T, _h, _r, _e, _a, _d);
	s2h_setScale(ui, 3);
	s2h_printLF(ui);
	s2h_printLF(ui);

	s2h_setScale(ui, 2);
	s2h_printTxt(ui, _s, _2, _h, _UNDERSCORE);
	s2h_printTxt(ui, _t, _a, _b, _l, _e);
	s2h_printLF(ui);
	s2h_printLF(ui);

	s2h_printSpace(ui, 0.5f); s2h_printTxt(ui, _I, _d); s2h_printSpace(ui, 0.5f); s2h_frame(ui, 3);
	s2h_printSpace(ui, 1.0f); s2h_printTxt(ui, _C, _n, _t); s2h_printSpace(ui, 1.0f); s2h_frame(ui, 5);
	s2h_printSpace(ui, 3.0f); s2h_printTxt(ui, _x); s2h_printSpace(ui, 3.0f); s2h_frame(ui, 7);
	s2h_printSpace(ui, 3.0f); s2h_printTxt(ui, _y); s2h_printSpace(ui, 3.0f); s2h_frame(ui, 7);
	s2h_printLF(ui);

	s2h_tableInt(ui, 0u, vec4(1.0f, 1.0f, 1.0f, 0.35f), ivec2(3, 15), true);
	s2h_tableInt(ui, 1u, vec4(0.4f, 0.4f, 0.4f, 0.75f), ivec2(5, 15), true);
	s2h_tableFloat(ui, 2u, vec4(1.0f, 0.0f, 0.0f, 0.35f), ivec2(7, 15), true);
	s2h_tableFloat(ui, 3u, vec4(0.0f, 1.0f, 0.0f, 0.25f), ivec2(7, 15), false);

	s2h_printLF(ui);
	s2h_printTxt(ui, _s, _2, _h, _UNDERSCORE, _f, _u);
	s2h_printTxt(ui, _n, _c, _t, _i, _o, _n);
	s2h_printLF(ui);

	s2h_setScale(ui, 2);
	ui.textColor.rgb = vec3(1.0f, 1.0f, 1.0f);
	vec2 rangeX = vec2(0.0f, 3.14159265f * 2.0f);
	vec2 rangeY = vec2(-1.3f, 1.3f);
	s2h_function(ui, 0u, vec4(0.0f, 0.0f, 0.0f, 0.45f), ivec2(22, 8), rangeX, rangeY);

	ui.textColor.rgb = vec3(0.0f, 0.0f, 0.0f);
	s2h_printTxt(ui, _x, _COLON, _SPACE); s2h_printFloat(ui, rangeX.x); s2h_printTxt(ui, _SPACE, _PERIOD, _PERIOD, _SPACE); s2h_printFloat(ui, rangeX.y);
	s2h_printLF(ui);
	s2h_printTxt(ui, _y, _COLON, _SPACE); s2h_printFloat(ui, rangeY.x); s2h_printTxt(ui, _SPACE, _PERIOD, _PERIOD, _SPACE); s2h_printFloat(ui, rangeY.y);

	vec4 background = vec4(0.4f, 0.7f, 0.4f, 1.0f);
	gl_FragColor = lerp(background, vec4(ui.dstColor.rgb, 1.0f), ui.dstColor.a);
}

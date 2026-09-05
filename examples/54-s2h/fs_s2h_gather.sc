$input v_color0, v_texcoord0

// Port of ShaderToHuman-bgfx/examples/Features/Gather_example.hlsl.
// Widget state comes from the ImGui host controls, not a UAV as in the original.
#include "../common/common.sh"
#include "s2h/s2h.sh"

uniform vec4 u_s2hTime;
uniform vec4 u_s2hUiState;
uniform vec4 u_s2hColor;
uniform vec4 u_s2hMouse;

void printDiscEx(inout ContextGather _ui, vec4 _color)
{
	s2h_printDisc(_ui, _color);
	s2h_printTxt(_ui, _SPACE);
	s2h_printInt(_ui, int(_color.r * 255.9f));
	s2h_printTxt(_ui, _COMMA);
	s2h_printInt(_ui, int(_color.g * 255.9f));
	s2h_printTxt(_ui, _COMMA);
	s2h_printInt(_ui, int(_color.b * 255.9f));
}

void main()
{
	ContextGather ui;
	s2h_init(ui, s2h_getPixelCoord(gl_FragCoord.xy));
	ui.mouseInput = u_s2hMouse;
	s2h_setCursor(ui, vec2(10.0f, 10.0f));

	ui.textColor.rgb = vec3(1.0f, 1.0f, 1.0f);
	s2h_setScale(ui, 3.0f);
	s2h_printTxt(ui, _G, _a, _t, _h, _e, _r);
	s2h_printTxt(ui, _T, _e, _s, _t);
	s2h_printLF(ui);
	s2h_printLF(ui);

	ui.textColor.rgb = vec3(0.0f, 0.0f, 0.0f);
	s2h_setScale(ui, 2.0f);
	s2h_printTxt(ui, _P, _i, _x, _e, _l, _EQUAL);
	s2h_printTxt(ui, _T, _h, _r, _e, _a, _d);
	s2h_setScale(ui, 3.0f);
	s2h_printLF(ui);

	s2h_setScale(ui, 1.0f);
	ui.textColor.rgb = vec3(1.0f, 0.0f, 0.0f); s2h_printTxt(ui, _R);
	ui.textColor.rgb = vec3(0.0f, 1.0f, 0.0f); s2h_printTxt(ui, _G);
	ui.textColor.rgb = vec3(0.0f, 0.0f, 1.0f); s2h_printTxt(ui, _B);
	s2h_printTxt(ui, _SPACE);
	ui.textColor.rgb = vec3(0.0f, 0.0f, 0.0f);
	s2h_printTxt(ui, _X, _Y, _Z, _COLON);
	s2h_printLF(ui);
	s2h_printInt(ui, 12345);
	s2h_printLF(ui);
	s2h_printInt(ui, -12345);
	s2h_printLF(ui);
	s2h_printHex(ui, 0x1297ABu);
	s2h_printLF(ui);
	s2h_printLF(ui);

	s2h_setScale(ui, 2.0f);
	s2h_printFloat(ui, -12.34f);
	s2h_printTxt(ui, _COMMA);
	s2h_printFloat(ui, 0.34f);
	s2h_printLF(ui);
	s2h_printBox(ui, vec4(1.0f, 0.7f, 0.3f, 1.0f));
	s2h_printBox(ui, vec4(1.0f, 0.0f, 0.0f, 1.0f));
	s2h_printDisc(ui, vec4(0.0f, 1.0f, 0.0f, 1.0f));
	s2h_printDisc(ui, vec4(1.0f, 1.0f, 0.0f, 1.0f));

	uint radioState = uint(u_s2hUiState.x);
	uint checkboxState = uint(u_s2hUiState.y);
	float sliderAlpha = u_s2hUiState.z;
	vec3 sliderColor = u_s2hColor.rgb;

#if BGFX_SHADER_LANGUAGE_WGSL
	// shaderc's WGSL backend overflows its compiler stack on the full port.
	s2h_printLF(ui);
	s2h_printLF(ui);
	s2h_printTxt(ui, _U, _I, _SPACE, _S, _t, _a);
	s2h_printTxt(ui, _t, _e, _COLON);
	s2h_printLF(ui);
	s2h_printTxt(ui, _SPACE, _SPACE);
	s2h_printInt(ui, int(radioState));
	s2h_printTxt(ui, _SPACE, _EQUAL, _SPACE);
	s2h_radioButton(ui, radioState == 1u);
	s2h_radioButton(ui, radioState == 2u);
	s2h_radioButton(ui, radioState == 3u);
	s2h_printTxt(ui, _SPACE, _r, _a, _d, _i, _o);
	s2h_printLF(ui);
	s2h_printTxt(ui, _SPACE, _SPACE);
	s2h_checkBox(ui, checkboxState != 0u);
	s2h_printTxt(ui, _SPACE, _c, _h, _e, _c, _k);
	s2h_printLF(ui);
	s2h_printTxt(ui, _SPACE, _SPACE);
	s2h_progress(ui, 5u, fract(u_s2hTime.x));
	s2h_printLF(ui);
	s2h_printTxt(ui, _SPACE, _SPACE);
	s2h_sliderFloat(ui, 8u, sliderAlpha, 0.0f, 1.0f);
	s2h_printLF(ui);
	s2h_printTxt(ui, _SPACE, _SPACE);
	s2h_sliderRGB(ui, 8u, sliderColor);
#else
	s2h_setScale(ui, 2.0f);
	s2h_printLF(ui);
	s2h_printLF(ui);
	s2h_printLF(ui);
	s2h_printTxt(ui, _U, _I, _S, _t, _a, _t);
	s2h_printTxt(ui, _e, _COLON, _SPACE, _LESS, _MINUS, _MINUS);
	s2h_printTxt(ui, _SPACE, _T, _o, _u, _c, _h);
	s2h_printTxt(ui, _SPACE, _M, _e);
	s2h_printLF(ui);
	s2h_printLF(ui);
	s2h_printTxt(ui, _SPACE, _SPACE);
	s2h_printInt(ui, int(radioState));
	s2h_printTxt(ui, _SPACE, _EQUAL, _SPACE);
	vec4 buttonColor = ui.buttonColor;
	ui.buttonColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); s2h_radioButton(ui, radioState == 1u);
	ui.buttonColor = vec4(0.0f, 1.0f, 0.0f, 1.0f); s2h_radioButton(ui, radioState == 2u);
	ui.buttonColor = vec4(0.0f, 0.0f, 1.0f, 1.0f); s2h_radioButton(ui, radioState == 3u);
	ui.buttonColor = buttonColor;
	s2h_printTxt(ui, _SPACE, _s, _2, _h, _UNDERSCORE, _r);
	s2h_printTxt(ui, _a, _d, _i, _o, _B, _u);
	s2h_printTxt(ui, _t, _t, _o, _n);
	s2h_printLF(ui);
	s2h_printLF(ui);
	s2h_printTxt(ui, _SPACE, _SPACE);
	s2h_printInt(ui, int(radioState));
	s2h_printTxt(ui, _SPACE, _EQUAL, _SPACE);
	s2h_printTxt(ui, _C, _l, _e, _a, _r);
	s2h_button(ui, 5u);
	s2h_printTxt(ui, _SPACE, _s, _2, _h, _UNDERSCORE, _b);
	s2h_printTxt(ui, _u, _t, _t, _o, _n);
	s2h_printLF(ui);
	s2h_printLF(ui);
	s2h_printTxt(ui, _SPACE, _SPACE);
	s2h_printInt(ui, int(checkboxState));
	s2h_printTxt(ui, _SPACE, _EQUAL, _SPACE);
	s2h_checkBox(ui, checkboxState != 0u);
	s2h_printTxt(ui, _SPACE, _s, _2, _h, _UNDERSCORE, _c);
	s2h_printTxt(ui, _h, _e, _c, _k, _B, _o);
	s2h_printTxt(ui, _x);
	s2h_printLF(ui);
	s2h_printLF(ui);
	s2h_printTxt(ui, _SPACE, _SPACE);
	s2h_progress(ui, 5u, fract(u_s2hTime.x));
	s2h_printTxt(ui, _SPACE, _s, _2, _h, _UNDERSCORE, _p);
	s2h_printTxt(ui, _r, _o, _g, _r, _e, _s);
	s2h_printTxt(ui, _s);
	s2h_printLF(ui);
	s2h_printLF(ui);
	s2h_printTxt(ui, _SPACE, _SPACE);
	s2h_sliderFloat(ui, 8u, sliderAlpha, 0.0f, 1.0f);
	s2h_printTxt(ui, _SPACE, _s, _2, _h, _UNDERSCORE, _s);
	s2h_printTxt(ui, _l, _i, _d, _e, _r, _F);
	s2h_printTxt(ui, _l, _o, _a, _t);
	s2h_printLF(ui);
	s2h_printLF(ui);
	s2h_printTxt(ui, _SPACE, _SPACE);
	s2h_sliderRGB(ui, 8u, sliderColor);
	s2h_printTxt(ui, _SPACE, _s, _2, _h, _UNDERSCORE, _s);
	s2h_printTxt(ui, _l, _i, _d, _e, _r, _R);
	s2h_printTxt(ui, _G, _B);
#endif

	vec4 background = vec4(0.4f, 0.7f, 0.4f, 1.0f);
	gl_FragColor = mix(background, vec4(ui.dstColor.rgb, 1.0f), ui.dstColor.a);
}

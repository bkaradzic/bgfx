$input v_color0, v_texcoord0

// Port of ShaderToHuman-bgfx/examples/Features/GenUserFont_example.hlsl.
#include "../common/common.sh"
#include "s2h_bgfx.sh"
#include "s2h.hlsl"

uniform vec4 u_s2hTime;

vec3 myMod(vec3 _x, vec3 _period)
{
	return frac(_x / _period) * _period;
}

vec3 hsb2rgb(vec3 _color)
{
	vec3 rgb = saturate(abs(myMod(_color.x * 6.0f + vec3(0.0f, 4.0f, 2.0f), vec3(6.0f, 6.0f, 6.0f)) - 3.0f) - 1.0f);
	rgb = rgb * rgb * (3.0f - 2.0f * rgb);
	return _color.z * lerp(vec3(1.0f, 1.0f, 1.0f), rgb, _color.y);
}

void main()
{
	vec2 pixelPosition = floor(s2h_getPixelCoord(gl_FragCoord.xy));
	ContextGather ui;
	s2h_init(ui, vec2(mod(pixelPosition.x, 8.0f), pixelPosition.y));

	ui.textColor.rgb = hsb2rgb(vec3(u_s2hTime.x + (pixelPosition.x + pixelPosition.y) / 16.0f * 0.1f, 1.0f, 1.0f));
	uint character = uint(pixelPosition.x / 8.0f) + _SPACE;
	s2h_printTxt(ui, character);

	gl_FragColor = vec4(ui.dstColor.rgb, 1.0f);
}

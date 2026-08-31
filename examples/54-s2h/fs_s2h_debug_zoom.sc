$input v_color0, v_texcoord0

#include "../common/common.sh"
#include "s2h_bgfx.sh"

SAMPLER2D(s_quadPostColor, 0);
uniform vec4 u_s2hMouse;

void main()
{
	float2 pixel = s2h_getPixelCoord(gl_FragCoord.xy);
	float2 resolution = u_viewRect.zw;
	float2 mouse = u_s2hMouse.xy;
	float3 color = texture2D(s_quadPostColor, v_texcoord0).rgb;
	float2 panelLocal = pixel - mouse - float2(24.0f, 24.0f);
	if (panelLocal.x >= 0.0f && panelLocal.y >= 0.0f && panelLocal.x < 160.0f && panelLocal.y < 160.0f)
	{
		float2 sourcePixel = floor(mouse - float2(8.0f, 8.0f) + panelLocal / 10.0f);
		color = texture2D(s_quadPostColor, (sourcePixel + 0.5f) / resolution).rgb;
		float2 cell = frac(panelLocal / 10.0f);
		if (cell.x < 0.08f || cell.y < 0.08f) color = float3(0.0f, 0.0f, 0.0f);
	}
	float crosshair = 1.0f - smoothstep(0.0f, 1.0f, min(abs(pixel.x - mouse.x), abs(pixel.y - mouse.y)));
	color = lerp(color, float3(1.0f, 1.0f, 1.0f), crosshair);
	gl_FragColor = float4(color, 1.0f);
}

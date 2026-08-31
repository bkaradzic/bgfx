$input v_color0, v_texcoord0

// Self-contained fragment-renderer port of Features/Clear_example.hlsl.
#include "../common/common.sh"
#include "s2h_bgfx.sh"
#include "s2h.hlsl"
#include "s2h_3d.hlsl"

uniform vec4 u_s2hTime;

float3 safeNormalize(float3 _value)
{
	return _value / max(length(_value), 0.0001f);
}

void main()
{
	float2 resolution = u_viewRect.zw;
	float2 fragmentPixel = s2h_getPixelCoord(gl_FragCoord.xy);
	float2 pixel = floor(fragmentPixel);
	uint2 gridPosition = uint2(pixel) / 16u;
	bool checker = (gridPosition.x % 2u) == (gridPosition.y % 2u);
	float3 fallbackColor = checker ? float3(0.29f, 0.29f, 0.348f) : float3(0.27f, 0.27f, 0.324f);

	float2 screen = fragmentPixel / resolution * 2.0f - 1.0f;
	screen.x *= resolution.x / resolution.y;
	screen.y = -screen.y;
	float orbit = u_s2hTime.x * 0.2f;
	float3 cameraPosition = float3(sin(orbit) * 3.0f, 1.5f, cos(orbit) * 3.0f);
	float3 forward = safeNormalize(float3(0.0f, 0.4f, 0.0f) - cameraPosition);
	float3 right = safeNormalize(cross(float3(0.0f, 1.0f, 0.0f), forward));
	float3 up = cross(forward, right);
	float3 rayDirection = safeNormalize(forward + screen.x * right * 0.8f + screen.y * up * 0.8f);

	Context3D context;
	s2h_init(context, cameraPosition, rayDirection);
	s2h_drawSkybox(context);
	float3 color = context.dstColor.a > 0.0f ? context.dstColor.rgb : fallbackColor;
	gl_FragColor = float4(color, 1.0f);
}

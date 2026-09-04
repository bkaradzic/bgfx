$input v_color0, v_texcoord0

// Self-contained fragment-renderer port of Features/Clear_example.hlsl.
#include "../common/common.sh"
#include "s2h_bgfx.sh"
#include "s2h.hlsl"
#include "s2h_3d.hlsl"

uniform vec4 u_s2hTime;

vec3 safeNormalize(vec3 _value)
{
	return _value / max(length(_value), 0.0001f);
}

void main()
{
	vec2 resolution = u_viewRect.zw;
	vec2 fragmentPixel = s2h_getPixelCoord(gl_FragCoord.xy);
	vec2 pixel = floor(fragmentPixel);
	uvec2 gridPosition = uvec2(pixel) / 16u;
	bool checker = (gridPosition.x % 2u) == (gridPosition.y % 2u);
	vec3 fallbackColor = checker ? vec3(0.29f, 0.29f, 0.348f) : vec3(0.27f, 0.27f, 0.324f);

	vec2 screen = fragmentPixel / resolution * 2.0f - 1.0f;
	screen.x *= resolution.x / resolution.y;
	screen.y = -screen.y;
	float orbit = u_s2hTime.x * 0.2f;
	vec3 cameraPosition = vec3(sin(orbit) * 3.0f, 1.5f, cos(orbit) * 3.0f);
	vec3 forward = safeNormalize(vec3(0.0f, 0.4f, 0.0f) - cameraPosition);
	vec3 right = safeNormalize(cross(vec3(0.0f, 1.0f, 0.0f), forward));
	vec3 up = cross(forward, right);
	vec3 rayDirection = safeNormalize(forward + screen.x * right * 0.8f + screen.y * up * 0.8f);

	Context3D context;
	s2h_init(context, cameraPosition, rayDirection);
	s2h_drawSkybox(context);
	vec3 color = context.dstColor.a > 0.0f ? context.dstColor.rgb : fallbackColor;
	gl_FragColor = vec4(color, 1.0f);
}

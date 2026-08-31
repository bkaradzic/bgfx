$input v_color0, v_texcoord0

#include "../common/common.sh"
#include "s2h_bgfx.sh"

SAMPLER2D(s_quadPostColor, 0);

uint userFontCharacter(uint _index)
{
	if (0u == _index) return 85u; // U
	if (1u == _index) return 115u; // s
	if (2u == _index) return 101u; // e
	if (3u == _index) return 114u; // r
	if (4u == _index) return 70u; // F
	if (5u == _index) return 111u; // o
	if (6u == _index) return 110u; // n
	return 116u; // t
}

void main()
{
	float2 pixel = floor(s2h_getPixelCoord(gl_FragCoord.xy));
	float3 background = float3(0.02f, 0.02f, 0.03f);
	float3 color = background;
	const float scale = 8.0f;
	float2 origin = float2(32.0f, 48.0f);
	float2 local = pixel - origin;
	if (local.x >= 0.0f && local.y >= 0.0f && local.x < 8.0f * 8.0f * scale && local.y < 8.0f * scale)
	{
		uint characterIndex = uint(local.x / (8.0f * scale));
		float2 glyphPixel = floor(float2(mod(local.x / scale, 8.0f), local.y / scale));
		uint character = userFontCharacter(characterIndex);
		float2 atlasPixel = float2(float(character - 32u) * 8.0f + glyphPixel.x, glyphPixel.y);
		float2 atlasUv = (atlasPixel + 0.5f) / u_viewRect.zw;
		color = texture2D(s_quadPostColor, atlasUv).rgb;
	}
	gl_FragColor = float4(color, 1.0f);
}

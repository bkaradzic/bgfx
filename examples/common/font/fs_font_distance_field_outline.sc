$input v_color0, v_color1, v_texcoord0, v_texcoord1

#include "../../common/common.sh"

SAMPLERCUBE(s_texColor, 0);

uniform vec4 u_params;

#define u_distanceMultiplier     u_params.y
#define u_outlineWidth           u_params.w

void main()
{
	vec4 color = textureCube(s_texColor, v_texcoord0.xyz);

	int index = int(v_texcoord0.w*4.0 + 0.5);
	float rgba[4];
	rgba[0] = color.z;
	rgba[1] = color.y;
	rgba[2] = color.x;
	rgba[3] = color.w;
	float distance = rgba[index];

	float smoothing = 16.0 * length(fwidth(v_texcoord0.xyz)) / sqrt(2.0) * u_distanceMultiplier;

	float outlineWidth = u_outlineWidth * smoothing;
	float outerEdgeCenter = 0.5 - outlineWidth;
	float alpha = smoothstep(outerEdgeCenter - smoothing, outerEdgeCenter + smoothing, distance);
	float border = smoothstep(0.5 - smoothing, 0.5 + smoothing, distance);
	vec4 sdfColor = vec4( mix(v_color1.xyz, v_color0.xyz, border), alpha * v_color0.w );
	gl_FragColor = sdfColor;
}

$input v_color0, v_color1, v_texcoord0, v_texcoord1, v_texcoord2

#include "../../common/common.sh"

SAMPLERCUBE(s_texColor, 0);

uniform vec4 u_dropShadowColor;
uniform vec4 u_params;

#define u_distanceMultiplier     u_params.y
#define u_dropShadowSoftener     u_params.z
#define u_outlineWidth           u_params.w

void main()
{
	if (!any(equal(v_texcoord1.xyz, vec3(0.0, 0.0, 0.0))))
	{
		vec4 imageColor = textureCube(s_texColor, v_texcoord1.xyz);
		gl_FragColor = vec4(imageColor.xyz, imageColor.w * v_color0.w);
		return;
	}

	if (!any(equal(v_texcoord2.xyz, vec3(0.0, 0.0, 0.0))))
	{
		vec4 shadowTexCoord = v_texcoord2;
		vec4 shadowDistanceColor = textureCube(s_texColor, shadowTexCoord.xyz);
		int index2 = int(shadowTexCoord.w*4.0 + 0.5);
		float rgba2[4];
		rgba2[0] = shadowDistanceColor.z;
		rgba2[1] = shadowDistanceColor.y;
		rgba2[2] = shadowDistanceColor.x;
		rgba2[3] = shadowDistanceColor.w;
		float shadowDistance = rgba2[index2];

		float shadowSmoothing = 16.0 * length(fwidth(shadowTexCoord.xyz)) / sqrt(2.0) * u_distanceMultiplier;

		float outlineWidth = u_outlineWidth * shadowSmoothing;
		float outerEdgeCenter = 0.5 - outlineWidth;

		shadowSmoothing = shadowSmoothing * u_dropShadowSoftener;
		float shadowAlpha = smoothstep(outerEdgeCenter - shadowSmoothing, outerEdgeCenter + shadowSmoothing, shadowDistance);
		vec4 shadowColor = vec4(v_color0.xyz, shadowAlpha * v_color0.w);
		gl_FragColor = shadowColor;
		return;
	}

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

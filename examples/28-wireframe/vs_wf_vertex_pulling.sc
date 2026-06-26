$output v_color

/*
 * Copyright 2026 Alessandro Muntoni. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"
#include "uniforms.sh"

#include <bgfx_compute.sh>

BUFFER_RO(positions, float, 0);
BUFFER_RO(indices, uint, 1);

uint getIndex(uint i)
{
	uint idx32 = indices[i / 2u];
	if (i % 2u == 0u)
	{
		return idx32 & 0xFFFFu;
	}
	else
	{
		return idx32 >> 16u;
	}
}

vec3 getPosition(uint index)
{
	uint strideFloats = uint(u_wfStride);
	uint offset = index * strideFloats;
	return vec3(
		positions[offset + 0u],
		positions[offset + 1u],
		positions[offset + 2u]
	);
}

#define NEAR_EPSILON 0.001
#define LENGTH_EPSILON 0.0001

void main()
{
	uint lineIndex = gl_VertexID / 6u;
	uint localVertex = gl_VertexID % 6u;

	uint edgeIndex = lineIndex % 3u;
	uint triFirstIndex = lineIndex - edgeIndex;

	uint idx0_loc = triFirstIndex + edgeIndex;
	uint idx1_loc = triFirstIndex + ((edgeIndex + 1u) % 3u);

	uint vertexIndex0 = getIndex(idx0_loc);
	uint vertexIndex1 = getIndex(idx1_loc);

	vec3 p0 = getPosition(vertexIndex0);
	vec3 p1 = getPosition(vertexIndex1);

	vec4 p0_NDC = mul(u_modelViewProj, vec4(p0, 1.0));
	vec4 p1_NDC = mul(u_modelViewProj, vec4(p1, 1.0));

	vec4 c0 = vec4(u_wfColor, u_wfOpacity);
	vec4 c1 = vec4(u_wfColor, u_wfOpacity);

	vec4 clippedP0 = p0_NDC;
	vec4 clippedP1 = p1_NDC;
	vec4 clippedColor0 = c0;
	vec4 clippedColor1 = c1;

	if (p0_NDC.w < NEAR_EPSILON)
	{
		float t = (NEAR_EPSILON - p0_NDC.w) / (p1_NDC.w - p0_NDC.w);
		clippedP0 = mix(p0_NDC, p1_NDC, t);
		clippedColor0 = mix(c0, c1, t);
	}
	if (p1_NDC.w < NEAR_EPSILON)
	{
		float t = (NEAR_EPSILON - p1_NDC.w) / (p0_NDC.w - p1_NDC.w);
		clippedP1 = mix(p1_NDC, p0_NDC, t);
		clippedColor1 = mix(c1, c0, t);
	}

	const vec2 offsets[6] = 
	{
		vec2(-1.0, -1.0), vec2(-1.0,  1.0), vec2( 1.0, -1.0),
		vec2( 1.0, -1.0), vec2(-1.0,  1.0), vec2( 1.0,  1.0)
	};
	vec2 offset = offsets[localVertex];
	vec2 uv = offset * 0.5 + 0.5;

	vec4 p = mix(clippedP0, clippedP1, uv.x);
	vec4 color = mix(clippedColor0, clippedColor1, uv.x);

	vec2 ndp0 = clippedP0.xy / clippedP0.w;
	vec2 ndp1 = clippedP1.xy / clippedP1.w;
	vec2 screenDir = ndp1 - ndp0;
	float screenDirLen = length(screenDir);

	if (screenDirLen > LENGTH_EPSILON)
	{
		vec2 T = screenDir / screenDirLen;
		vec2 N = vec2(-T.y, T.x);

		float pixelsToNDCX = 2.0 / u_viewRect.z;
		float pixelsToNDCY = 2.0 / u_viewRect.w;

		float side = 2.0 * uv.y - 1.0;
		vec2 offsetNDC = N * (0.5 * u_wfThickness) * side * vec2(pixelsToNDCX, pixelsToNDCY);

		p.xy = p.xy + (offsetNDC * p.w);
	}

	v_color = color;
	gl_Position = p;
}


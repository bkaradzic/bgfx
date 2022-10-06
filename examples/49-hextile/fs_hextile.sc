$input v_position, v_texcoord0

/*
 * Copyright 2022 Preetish Kakkar. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */
 
 /*

	Most of the code is inspired/ported from https://github.com/mmikk/hextile-demo/blob/main/hextile-demo/shader_lighting.hlsl
	
	The basic idea behind the algorithm is to use tiling & blending schema but instead of regular linear blending, the algorithm uses blending operator that prevents visual artifacts caused by linear blending
	
	We partition the uv-space on a triangle grid and compute the local triangle and the barycentric coordinates inside the triangle. We use a hash function to associate a random offset with each vertex of the triangle
	grid and use this random offset to fetch the example texture.
	
	Finally, we blend the result using the barycentric coordinates as blending weights.
 
 */

#include "../common/common.sh"

#define M_PI 3.1415926535897932384626433832795

SAMPLER2D(s_trx_d, 0);

uniform vec4 u_params;

#ifndef fmod
#define fmod(x, y) (x - y * trunc(x / y))
#endif

#define moduleOper(a, b) a - (float(b) * floor(a/float(b)))

#define u_showWeights u_params.x
#define u_tileRate u_params.y
#define u_tileRotStrength u_params.z
#define u_useRegularTiling u_params.w

vec3 Gain3(vec3 x, float r)
{
	// increase contrast when r>0.5 and
	// reduce contrast if less
	float k = log(1.0 - r) / log(0.5);

	vec3 s = 2.0 * step(0.5, x);
	vec3 m = 2.0 * (1.0 - s);

	vec3 res = 0.5 * s + 0.25 * m * pow(max(vec3_splat(0.0), s + x * m), vec3_splat(k));

	return res.xyz / (res.x + res.y + res.z);
}

mat2 LoadRot2x2(vec2 idx, float rotStrength)
{
	float angle = abs(idx.x * idx.y) + abs(idx.x + idx.y) + M_PI;

	// remap to +/-pi
	//angle = fmod(angle, 2.0*M_PI); 
	if (angle < 0.0) angle += 2.0 * M_PI;
	if (angle > M_PI) angle -= 2.0 * M_PI;

	angle *= rotStrength;

	float cs = cos(angle);
	float si = sin(angle);

	return mat2(cs, -si, si, cs);
}

vec2 MakeCenST(vec2 Vertex)
{
	mat2 invSkewMat = mat2(1.0, 0.5, 0.0, 1.0 / 1.15470054);

	return mul(invSkewMat, Vertex) / (2.0 * sqrt(3.0));
}


vec3 ProduceHexWeights(vec3 W, vec2 vertex1, vec2 vertex2, vec2 vertex3)
{
	vec3 res = vec3_splat(0.0);

	float v1 = moduleOper(((vertex1.x - vertex1.y)), 3.0);
	if (v1 < 0.0) v1 += 3.0;

	float vh = v1 < 2.0 ? (v1 + 1.0) : 0.0;
	float vl = v1 > 0.0 ? (v1 - 1.0) : 2.0;
	float v2 = vertex1.x < vertex3.x ? vl : vh;
	float v3 = vertex1.x < vertex3.x ? vh : vl;

	res.x = v3 == 0.0 ? W.z : (v2 == 0.0 ? W.y : W.x);
	res.y = v3 == 1.0 ? W.z : (v2 == 1.0 ? W.y : W.x);
	res.z = v3 == 2.0 ? W.z : (v2 == 2.0 ? W.y : W.x);

	return res;
}

vec2 hash(vec2 p)
{
	vec2 r = mul(mat2(127.1, 311.7, 269.5, 183.3), p);

	return fract(sin(r) * 43758.5453);
}

// Given a point in UV, compute local triangle barycentric coordinates and vertex IDs
void TriangleGrid(out float w1, out float w2, out float w3,
	out vec2 vertex1, out vec2 vertex2, out vec2 vertex3,
	vec2 uv)
{
	// Scaling of the input
	uv *= 2.0 * sqrt(3.0); // controls the size of the input with respect to the size of the tiles. 

	// Skew input space into simplex triangle grid
	const mat2 gridToSkewedGrid =
		mat2(1.0, -0.57735027, 0.0, 1.15470054);
	vec2 skewedCoord = mul(gridToSkewedGrid, uv);

	vec2 baseId = floor(skewedCoord);
	vec3 temp = vec3(fract(skewedCoord), 0.0);
	temp.z = 1.0 - temp.x - temp.y;

	float s = step(0.0, -temp.z);
	float s2 = 2.0 * s - 1.0;

	w1 = -temp.z * s2;
	w2 = s - temp.y * s2;
	w3 = s - temp.x * s2;

	vertex1 = baseId + vec2(s, s);
	vertex2 = baseId + vec2(s, 1.0 - s);
	vertex3 = baseId + vec2(1.0 - s, s);
}

void hex2colTex(out vec4 color, out vec3 weights, vec2 uv,
	float rotStrength, float r)
{
	// compute uv derivatives
	vec2 dSTdx = dFdx(uv), dSTdy = dFdy(uv);

	// Get triangle info
	float w1, w2, w3;
	vec2 vertex1, vertex2, vertex3;
	TriangleGrid(w1, w2, w3, vertex1, vertex2, vertex3, uv);

	mat2 rot1 = LoadRot2x2(vertex1, rotStrength);
	mat2 rot2 = LoadRot2x2(vertex2, rotStrength);
	mat2 rot3 = LoadRot2x2(vertex3, rotStrength);

	vec2 cen1 = MakeCenST(vertex1);
	vec2 cen2 = MakeCenST(vertex2);
	vec2 cen3 = MakeCenST(vertex3);

	// assign random offset to each triangle vertex
	// this is used later to fetch from texture
	vec2 uv1 = mul(uv - cen1, rot1) + cen1 + hash(vertex1);
	vec2 uv2 = mul(uv - cen2, rot2) + cen2 + hash(vertex2);
	vec2 uv3 = mul(uv - cen3, rot3) + cen3 + hash(vertex3);

	// Fetch input
	// We could simply use texture2D function, however, the sreen space derivatives could be broken 
	// since we are using random offsets, we use texture2DGrad to make sure that we pass correct derivatives explicitly.
	vec4 c1 = texture2DGrad(s_trx_d, uv1,
		mul(dSTdx, rot1), mul(dSTdy, rot1));
	vec4 c2 = texture2DGrad(s_trx_d, uv2,
		mul(dSTdx, rot2), mul(dSTdy, rot2));
	vec4 c3 = texture2DGrad(s_trx_d, uv3,
		mul(dSTdx, rot3), mul(dSTdy, rot3));

	// use luminance as weight
	vec3 Lw = vec3(0.299, 0.587, 0.114);
	vec3 Dw = vec3(dot(c1.xyz, Lw), dot(c2.xyz, Lw), dot(c3.xyz, Lw));

	Dw = mix(vec3_splat(1.0), Dw, 0.6); // 0.6 is fall off constant
	vec3 W = Dw * pow(vec3(w1, w2, w3), vec3_splat(7.0));	// 7 is g_exp
	W /= (W.x + W.y + W.z);
	if (r != 0.5) W = Gain3(W, r);

	// blend weights with color linearly 
	// histogram preserving blending will be better but requires precompution step to create histogram texture
	color = W.x * c1 + W.y * c2 + W.z * c3;
	weights = ProduceHexWeights(W.xyz, vertex1, vertex2, vertex3);
}


float GetTileRate()
{
	return 0.05 * u_tileRate;
}

void FetchColorAndWeight(out vec3 color, out vec3 weights, vec2 uv)
{
	vec4 col4;
	hex2colTex(col4, weights, uv, u_tileRotStrength, 0.7);
	color = col4.xyz;
}

void main()
{
	// actual world space position
	vec3 surfPosInWorld = v_position.xyz;

	vec3 sp = GetTileRate() * surfPosInWorld;

	vec2 uv0 = vec2(sp.x, sp.z);
		
	if(u_useRegularTiling > 0.0) 
	{
		gl_FragColor = vec4(texture2D(s_trx_d, uv0.xy));
	} 
	else 
	{
		vec3 color, weights;
		FetchColorAndWeight(color, weights, uv0);
		
		if (u_showWeights > 0.0)
		{
			gl_FragColor = vec4(weights, 1.0);
		}
		else
		{
			gl_FragColor = vec4(color, 1.0);
		}
	}

	
}

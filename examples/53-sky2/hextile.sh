#ifndef HEXTILE_SH
#define HEXTILE_SH

// Hextiling
// Adapted from bgfx example 49-hextile (Copyright 2022 Preetish Kakkar).

#define HEXTILE_PI 3.14159265359

vec3 hextile_gain3(vec3 x, float r) {
	float k = log(1.0 - r) / log(0.5);

	vec3 s = 2.0 * step(0.5, x);
	vec3 m = 2.0 * (1.0 - s);

	vec3 res = 0.5 * s + 0.25 * m * pow(max(vec3_splat(0.0), s + x * m), vec3_splat(k) );

	return res.xyz / (res.x + res.y + res.z);
}

mat2 hextile_rot2x2(vec2 idx, float rotStrength) {
	float angle = abs(idx.x * idx.y) + abs(idx.x + idx.y) + HEXTILE_PI;

	if (angle < 0.0)        angle += 2.0 * HEXTILE_PI;
	if (angle > HEXTILE_PI) angle -= 2.0 * HEXTILE_PI;

	angle *= rotStrength;

	float cs = cos(angle);
	float si = sin(angle);

	return mat2(cs, -si, si, cs);
}

vec2 hextile_cen_st(vec2 vertex) {
	mat2 invSkewMat = mat2(1.0, 0.5, 0.0, 1.0 / 1.15470054);

	return mul(invSkewMat, vertex) / (2.0 * sqrt(3.0) );
}

vec2 hextile_hash(vec2 p) {
	vec2 r = mul(mat2(127.1, 311.7, 269.5, 183.3), p);

	return fract(sin(r) * 43758.5453);
}

void hextile_grid(
	  out float w1, out float w2, out float w3
	, out vec2 vertex1, out vec2 vertex2, out vec2 vertex3
	, vec2 uv
	) {
	uv *= 2.0 * sqrt(3.0);

	const mat2 gridToSkewedGrid = mat2(1.0, -0.57735027, 0.0, 1.15470054);
	vec2 skewedCoord = mul(gridToSkewedGrid, uv);

	vec2 baseId = floor(skewedCoord);
	vec3 temp   = vec3(fract(skewedCoord), 0.0);
	temp.z = 1.0 - temp.x - temp.y;

	float s  = step(0.0, -temp.z);
	float s2 = 2.0 * s - 1.0;

	w1 = -temp.z * s2;
	w2 = s - temp.y * s2;
	w3 = s - temp.x * s2;

	vertex1 = baseId + vec2(s, s);
	vertex2 = baseId + vec2(s, 1.0 - s);
	vertex3 = baseId + vec2(1.0 - s, s);
}

void hextile_setup(
	  vec2 uv, float rotStrength
	, out vec2 uv1,  out vec2 uv2,  out vec2 uv3
	, out mat2 rot1, out mat2 rot2, out mat2 rot3
	, out vec3 bary
	) {
	float w1, w2, w3;
	vec2 vertex1, vertex2, vertex3;
	hextile_grid(w1, w2, w3, vertex1, vertex2, vertex3, uv);

	rot1 = hextile_rot2x2(vertex1, rotStrength);
	rot2 = hextile_rot2x2(vertex2, rotStrength);
	rot3 = hextile_rot2x2(vertex3, rotStrength);

	vec2 cen1 = hextile_cen_st(vertex1);
	vec2 cen2 = hextile_cen_st(vertex2);
	vec2 cen3 = hextile_cen_st(vertex3);

	uv1 = mul(uv - cen1, rot1) + cen1 + hextile_hash(vertex1);
	uv2 = mul(uv - cen2, rot2) + cen2 + hextile_hash(vertex2);
	uv3 = mul(uv - cen3, rot3) + cen3 + hextile_hash(vertex3);

	bary = vec3(w1, w2, w3);
}

vec3 hextile_blend(vec3 c1, vec3 c2, vec3 c3, vec3 bary) {
	vec3 Lw = vec3(0.299, 0.587, 0.114);
	vec3 Dw = vec3(dot(c1, Lw), dot(c2, Lw), dot(c3, Lw) );

	Dw = mix(vec3_splat(1.0), Dw, 0.6);

	vec3 W = Dw * pow(bary, vec3_splat(7.0) );
	W /= (W.x + W.y + W.z);
	W = hextile_gain3(W, 0.7);

	return W.x * c1 + W.y * c2 + W.z * c3;
}

#endif // HEXTILE_SH

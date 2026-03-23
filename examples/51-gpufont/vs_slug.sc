$input a_position, a_texcoord0, a_texcoord1
$output v_texcoord0, v_banding, v_glyph

// ===================================================
// Reference vertex shader for the Slug algorithm.
// This code is made available under the MIT License.
// Copyright 2017, by Eric Lengyel.
// ===================================================

#include "../common/common.sh"

uniform vec4 u_params;

// The per-vertex input data consists of 5 attributes all having 4 floating-point components:
//
// 0 - pos
// 1 - tex
// 2 - jac
// 3 - bnd
// 4 - col

// pos.xy = object-space vertex coordinates.
// pos.zw = object-space normal vector.

// tex.xy = em-space sample coordinates.

// tex.z = location of glyph data in band texture (interpreted as integer):

// | 31                         24 | 23                         16 | 15                          8 | 7                           0 |
// +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
// |           y coordinate of glyph data in band texture          |           x coordinate of glyph data in band texture          |
// +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+

// tex.w = max band indexes and flags (interpreted as integer):

// | 31                         24 | 23                         16 | 15                          8 | 7                           0 |
// +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
// | 0   0   0 | E | 0   0   0   0 |           band max y          | 0   0   0   0   0   0   0   0 |           band max x          |
// +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+

// jac = inverse Jacobian matrix entries (00, 01, 10, 11).
// bnd = (band scale x, band scale y, band offset x, band offset y).
// col = vertex color (red, green, blue, alpha).

void slugUnpack(vec4 _bnd, vec2 _bits, out vec4 _outBanding, out vec4 _outGlyph)
{
	uvec2 g = floatBitsToUint(_bits);
	_outGlyph   = vec4(g.x & 0xffffu, g.x >> 16u, g.y & 0xffffu, g.y >> 16u);
	_outBanding = _bnd;
}

vec2 slugDilate(vec2 _pos, vec2 _normal, vec2 _tex, vec4 _jac, vec2 _dim, out vec2 _outPos)
{
	vec2 n = normalize(_normal);

	vec4 pClip = mul(u_modelViewProj, vec4(_pos, 0.0, 1.0) );
	vec4 nClip = mul(u_modelViewProj, vec4(n, 0.0, 0.0) );

	float s = pClip.w;
	float t = nClip.w;

	float u = (s * nClip.x - t * pClip.x) * _dim.x;
	float v = (s * nClip.y - t * pClip.y) * _dim.y;

	float s2 = s * s;
	float st = s * t;
	float uv = u * u + v * v;
	vec2  d  = _normal * (s2 * (st + sqrt(uv) ) / (uv - st * st) );

	_outPos = _pos + d;
	return vec2(_tex.x + dot(d, _jac.xy), _tex.y + dot(d, _jac.zw) );
}

void main()
{
	vec2 p;
	vec4 jacobian = vec4(u_params.w, 0.0, 0.0, u_params.w);

	// Apply dynamic dilation to vertex position. Returns new em-space sample position.

	vec2 pos    = a_position.xy;
	vec2 normal = a_position.zw;
	vec2 uv     = a_texcoord0.xy;
	vec2 bits   = a_texcoord0.zw;

	v_texcoord0 = slugDilate(pos, normal, uv, jacobian, u_viewRect.zw, p);

	// Apply MVP matrix to dilated vertex position.

	gl_Position = mul(u_modelViewProj, vec4(p, 0.0, 1.0) );

	// Unpack or pass through remaining vertex data.

	slugUnpack(a_texcoord1, bits, v_banding, v_glyph);
}

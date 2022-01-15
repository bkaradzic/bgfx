$input v_color0, v_texcoord0

/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

// References:
// Sphere tracing: a geometric method for the antialiased ray tracing of implicit surfaces - John C. Hart
// http://web.archive.org/web/20110331200546/http://graphics.cs.uiuc.edu/~jch/papers/zeno.pdf
//
// Modeling with distance functions
// http://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm

#include "../common/common.sh"
#include "iq_sdf.sh"

uniform mat4 u_mtx;
uniform vec4 u_lightDirTime;

#define u_lightDir u_lightDirTime.xyz
#define u_time     u_lightDirTime.w

float sceneDist(vec3 _pos)
{
	float d1 = udRoundBox(_pos, vec3(2.5, 2.5, 2.5), 0.5);
	float d2 = sdSphere(_pos + vec3( 4.0, 0.0, 0.0), 1.0);
	float d3 = sdSphere(_pos + vec3(-4.0, 0.0, 0.0), 1.0);
	float d4 = sdSphere(_pos + vec3( 0.0, 4.0, 0.0), 1.0);
	float d5 = sdSphere(_pos + vec3( 0.0,-4.0, 0.0), 1.0);
	float d6 = sdSphere(_pos + vec3( 0.0, 0.0, 4.0), 1.0);
	float d7 = sdSphere(_pos + vec3( 0.0, 0.0,-4.0), 1.0);
	float dist = min(min(min(min(min(min(d1, d2), d3), d4), d5), d6), d7);
	return dist;
}

vec3 calcNormal(vec3 _pos)
{
	const vec2 delta = vec2(0.002, 0.0);
	float nx = sceneDist(_pos + delta.xyy) - sceneDist(_pos - delta.xyy);
	float ny = sceneDist(_pos + delta.yxy) - sceneDist(_pos - delta.yxy);
	float nz = sceneDist(_pos + delta.yyx) - sceneDist(_pos - delta.yyx);
	return normalize(vec3(nx, ny, nz) );
}

float calcAmbOcc(vec3 _pos, vec3 _normal)
{
	float occ = 0.0;
	float aostep = 0.2;
	for (int ii = 1; ii < 4; ii++)
	{
		float fi = float(ii);
		float dist = sceneDist(_pos + _normal * fi * aostep);
		occ += (fi * aostep - dist) / pow(2.0, fi);
	}

	return 1.0 - occ;
}

float trace(vec3 _ray, vec3 _dir, float _maxd)
{
	float tt = 0.0;
	float epsilon = 0.001;

	for (int ii = 0; ii < 64; ii++)
	{
		float dist = sceneDist(_ray + _dir*tt);
		if (dist > epsilon)
		{
			tt += dist;
		}
	}

	return tt < _maxd ? tt : 0.0;
}

vec2 blinn(vec3 _lightDir, vec3 _normal, vec3 _viewDir)
{
	float ndotl = dot(_normal, _lightDir);
	vec3 reflected = _lightDir - 2.0*ndotl*_normal; // reflect(_lightDir, _normal);
	float rdotv = dot(reflected, _viewDir);
	return vec2(ndotl, rdotv);
}

float fresnel(float _ndotl, float _bias, float _pow)
{
	float facing = (1.0 - _ndotl);
	return max(_bias + (1.0 - _bias) * pow(facing, _pow), 0.0);
}

vec4 lit(float _ndotl, float _rdotv, float _m)
{
	float diff = max(0.0, _ndotl);
	float spec = step(0.0, _ndotl) * max(0.0, _rdotv * _m);
	return vec4(1.0, diff, spec, 1.0);
}

void main()
{
	vec4 tmp;
	tmp = mul(u_mtx, vec4(v_texcoord0.xy, 0.0, 1.0) );
	vec3 eye = tmp.xyz/tmp.w;

	tmp = mul(u_mtx, vec4(v_texcoord0.xy, 1.0, 1.0) );
	vec3 at = tmp.xyz/tmp.w;

	float maxd = length(at - eye);
	vec3 dir = normalize(at - eye);

	float dist = trace(eye, dir, maxd);

	if (dist > 0.5)
	{
		vec3 pos = eye + dir*dist;
		vec3 normal = calcNormal(pos);

		vec2 bln = blinn(u_lightDir, normal, dir);
		vec4 lc = lit(bln.x, bln.y, 1.0);
		float fres = fresnel(bln.x, 0.2, 5.0);

		float val = 0.9*lc.y + pow(lc.z, 128.0)*fres;
		val *= calcAmbOcc(pos, normal);
		val = pow(val, 1.0/2.2);

		gl_FragColor = vec4(val, val, val, 1.0);
		gl_FragDepth = dist/maxd;
	}
	else
	{
		gl_FragColor = v_color0;
		gl_FragDepth = 1.0;
	}
}

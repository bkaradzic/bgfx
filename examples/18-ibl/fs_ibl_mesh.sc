$input v_view, v_normal

/*
 * Copyright 2014 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"

uniform vec4 u_params;
uniform mat4 u_mtx;
uniform vec4 u_flags;
uniform vec4 u_rgbDiff;
uniform vec4 u_rgbSpec;

SAMPLERCUBE(s_texCube, 0);
SAMPLERCUBE(s_texCubeIrr, 1);

#define u_glossiness u_params.x
#define u_exposure   u_params.y
#define u_diffspec   u_params.z

#define u_doDiffuse     u_flags.x
#define u_doSpecular    u_flags.y
#define u_doDiffuseIbl  u_flags.z
#define u_doSpecularIbl u_flags.w

vec3 fresnel(vec3 _cspec, float _dot)
{
	return _cspec + (1.0 - _cspec) * pow(1.0 - _dot, 5);
}

void main()
{
	vec3 light  = vec3(0.0, 0.0, -1.0);
	vec3 clight = vec3(1.0, 1.0,  1.0);

	vec3 v = v_view;
	vec3 n = normalize(v_normal);
	vec3 l = normalize(light);
	vec3 h = normalize(v + l);

	float ndotl = clamp(dot(n, l), 0.0, 1.0); //diff
	float ndoth = clamp(dot(n, h), 0.0, 1.0); //spec
	float vdoth = clamp(dot(v, h), 0.0, 1.0); //spec fresnel
	float ndotv = clamp(dot(n, v), 0.0, 1.0); //env spec fresnel

	vec3 r = 2.0*ndotv*n - v; // reflect(v, n);

	vec3 cubeR = normalize(mul(u_mtx, vec4(r, 0.0)).xyz);
	vec3 cubeN = normalize(mul(u_mtx, vec4(n, 0.0)).xyz);

	float mipLevel = min((1.0 - u_glossiness)*11.0 + 1.0, 8.0);
	vec3 cenv = textureCubeLod(s_texCube, cubeR, mipLevel).xyz;

	vec3 kd = u_rgbDiff.xyz;
	vec3 ks = u_rgbSpec.xyz;

	vec3 cs = ks * u_diffspec;
	vec3 cd = kd * (1.0 - cs);

	vec3 diff = cd;
	float pwr = exp2(u_glossiness * 11.0 + 1.0);
	vec3 spec = cs * pow(ndoth, pwr) * ( (pwr + 8.0)/8.0) * fresnel(cs, vdoth);

	vec3 ambspec = fresnel(cs, ndotv) * cenv;
	vec3 ambdiff = cd * textureCube(s_texCubeIrr, cubeN).xyz;

	vec3 lc = (   diff * u_doDiffuse    +    spec * u_doSpecular   ) * ndotl * clight;
	vec3 ec = (ambdiff * u_doDiffuseIbl + ambspec * u_doSpecularIbl);

	vec3 color = lc + ec;
	color = color * exp2(u_exposure);

	gl_FragColor.xyz = toFilmic(color);
	gl_FragColor.w = 1.0;
}

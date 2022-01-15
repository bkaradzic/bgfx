$input v_normal, v_view, v_texcoord0

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"
uniform vec4 u_params;
uniform vec4 u_svparams;
uniform vec4 u_ambient;
uniform vec4 u_diffuse;
uniform vec4 u_specular_shininess;
uniform vec4 u_fog;
uniform vec4 u_lightPosRadius;
uniform vec4 u_lightRgbInnerR;
SAMPLER2D(s_texColor,   0);
SAMPLER2D(s_texStencil, 1);

#define u_ambientPass   u_params.x
#define u_lightingPass  u_params.y
#define u_texelHalf     u_params.z
#define u_specular      u_specular_shininess.xyz
#define u_shininess     u_specular_shininess.w

#define u_fogColor      u_fog.xyz
#define u_fogDensity    u_fog.w

#define u_useStencilTex u_svparams.x

vec2 blinn(vec3 _lightDir, vec3 _normal, vec3 _viewDir)
{
	float ndotl = dot(_normal, _lightDir);
	vec3 reflected = 2.0*ndotl*_normal - _lightDir; // reflect(_lightDir, _normal);
	float rdotv = dot(reflected, _viewDir);
	return vec2(ndotl, rdotv);
}

vec4 lit(float _ndotl, float _rdotv, float _m)
{
	float diff = max(0.0, _ndotl);
	float spec = step(0.0, _ndotl) * pow(max(0.0, _rdotv), _m);
	return vec4(1.0, diff, spec, 1.0);
}

vec3 calcLight(vec3 _view, vec3 _normal, vec3 _viewDir)
{
	vec3 lightPos = mul(u_view, vec4(u_lightPosRadius.xyz, 1.0)).xyz;
	vec3 toLight = lightPos - _view;
	vec3 lightDir = normalize(toLight);

	vec2 bln = blinn(lightDir, _normal, _viewDir);
	vec4 lc = lit(bln.x, bln.y, u_shininess);

	float dist = max(length(toLight), u_lightPosRadius.w);
	float attn = 50.0 * pow(dist, -2.0);
	vec3 rgb = (lc.y * u_diffuse.xyz + lc.z * u_specular) * u_lightRgbInnerR.rgb * attn;

	return rgb;
}

void main()
{
	vec3 ambientColor = u_ambient.xyz * u_ambientPass;

	vec3 normal = normalize(v_normal);
	vec3 viewDir = -normalize(v_view);
	vec3 lightColor = calcLight(v_view, normal, viewDir) * u_lightingPass;

	vec2 ndc = gl_FragCoord.xy * u_viewTexel.xy + u_viewTexel.xy * u_texelHalf;
	vec4 texcolor = texture2D(s_texStencil, ndc);
	float s = (texcolor.x - texcolor.y) + 2.0 * (texcolor.z - texcolor.w);
	s *= u_useStencilTex;

	const float LOG2 = 1.442695;
	float z = length(v_view);
	float fogFactor = 1.0/exp2(u_fogDensity*u_fogDensity*z*z*LOG2);
	fogFactor = clamp(fogFactor, 0.0, 1.0);

	vec3 color = toLinear(texture2D(s_texColor, v_texcoord0)).xyz;

	vec3 ambient = toGamma(ambientColor * color);
	vec3 diffuse = toGamma(lightColor * color);
	vec3 final   = mix(ambient, ambient + diffuse, float((abs(s) < 0.0001)));

	gl_FragColor.xyz = mix(u_fogColor, final, fogFactor);
	gl_FragColor.w   = 1.0;
}


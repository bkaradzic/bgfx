$input v_normal, v_view, v_texcoord0

/*
 * Copyright 2013 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"
uniform vec4 u_params;
uniform vec3 u_ambient;
uniform vec3 u_diffuse;
uniform vec4 u_color;
uniform vec4 u_specular_shininess;
uniform vec4 u_lightPosRadius[5];
uniform vec4 u_lightRgbInnerR[5];
SAMPLER2D(u_texColor, 0);

#define u_ambientPass   u_params.x
#define u_lightningPass u_params.y
#define u_alpha         u_params.z
#define u_lightCount    u_params.w
#define u_specular      u_specular_shininess.xyz
#define u_shininess     u_specular_shininess.w

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

vec3 calcLight(int _idx, vec3 _view, vec3 _normal, vec3 _viewDir)
{
	if (float(_idx) >= u_lightCount)
		return vec3_splat(0.0);

	vec3 lightPos = mul(u_view, vec4(u_lightPosRadius[_idx].xyz, 1.0)).xyz;
	vec3 toLight = lightPos - _view;
	vec3 lightDir = normalize(toLight);

	vec2 bln = blinn(lightDir, _normal, _viewDir);
	vec4 lc = lit(bln.x, bln.y, u_shininess);

	float dist = max(length(toLight), u_lightPosRadius[_idx].w);
	float attn = 100.0 * pow(dist, -2.0);
	vec3 rgb = (lc.y * u_diffuse + lc.z * u_specular) * u_lightRgbInnerR[_idx].rgb * attn;

	return rgb;
}

void main()
{
	vec3 normal = normalize(v_normal);
	vec3 viewDir = -normalize(v_view);

	vec3 ambientColor = u_ambient * u_ambientPass;

	vec3 lightColor = vec3_splat(0.0);
	for(int ii = 0; ii < 5; ++ii)
	{
		lightColor += calcLight(ii, v_view, normal, viewDir);
	}
	lightColor *= u_lightningPass;

	vec3 color = toLinear(texture2D(u_texColor, v_texcoord0)).xyz;

	vec3 ambient = toGamma(ambientColor * color);
	vec3 diffuse = toGamma(lightColor * color);
	gl_FragColor.xyz = clamp(ambient + diffuse, 0.0, 1.0);

	gl_FragColor.w = u_alpha;
}

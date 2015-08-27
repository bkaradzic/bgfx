$input v_normal, v_view, v_texcoord0

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"

#define MAX_NUM_LIGHTS 5

uniform vec4 u_params;
uniform vec4 u_ambient;
uniform vec4 u_diffuse;
uniform vec4 u_color;
uniform vec4 u_specular_shininess;
uniform vec4 u_lightPosRadius[MAX_NUM_LIGHTS];
uniform vec4 u_lightRgbInnerR[MAX_NUM_LIGHTS];
SAMPLER2D(u_texColor, 0);

#define u_ambientPass  u_params.x
#define u_lightingPass u_params.y
#define u_lightCount   u_params.z
#define u_lightIndex   u_params.w
#define u_specular     u_specular_shininess.xyz
#define u_shininess    u_specular_shininess.w

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
	vec3 lightPos = mul(u_view, vec4(u_lightPosRadius[_idx].xyz, 1.0)).xyz;
	vec3 toLight = lightPos - _view;
	vec3 lightDir = normalize(toLight);

	vec2 bln = blinn(lightDir, _normal, _viewDir);
	vec4 lc = lit(bln.x, bln.y, u_shininess);

	float dist = max(length(toLight), u_lightPosRadius[_idx].w);
	float attn = 250.0 * pow(dist, -2.0);
	vec3 rgb = (lc.y * u_diffuse.xyz + lc.z * u_specular) * u_lightRgbInnerR[_idx].rgb * attn;

	return rgb;
}

void main()
{
	vec3 normal = normalize(v_normal);
	vec3 viewDir = -normalize(v_view);

	vec3 ambientColor = u_ambient.xyz * u_ambientPass;

	vec3 lightColor = vec3_splat(0.0);
	for(int ii = 0; ii < MAX_NUM_LIGHTS; ++ii)
	{
		float condition = 0.0;
		if (u_lightCount > 1.0) // Stencil Reflection Scene.
		{
			condition = 1.0 - step(u_lightCount, float(ii)); // True for every light up to u_lightCount.
		}
		else // Projection Shadows Scene.
		{
			condition = float(float(ii) == u_lightIndex); // True only for current light.
		}

		lightColor += calcLight(ii, v_view, normal, viewDir) * condition;
	}
	lightColor *= u_lightingPass;

	vec3 color = toLinear(texture2D(u_texColor, v_texcoord0)).xyz;

	vec3 ambient = toGamma(ambientColor * color);
	vec3 diffuse = toGamma(lightColor * color);
	gl_FragColor.xyz = clamp(ambient + diffuse, 0.0, 1.0);

	gl_FragColor.w = u_color.w;
}

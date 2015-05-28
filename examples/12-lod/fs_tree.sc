$input v_pos, v_view, v_normal, v_texcoord0

/*
 * Copyright 2013 Milos Tosic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"

SAMPLER2D(u_texColor, 0);
SAMPLER2D(u_texStipple, 1);
uniform vec4 u_stipple;

vec2 blinn(vec3 _lightDir, vec3 _normal, vec3 _viewDir)
{
	float ndotl = dot(_normal, _lightDir);
	vec3 reflected = _lightDir - 2.0*ndotl*_normal; // reflect(_lightDir, _normal);
	float rdotv = dot(reflected, _viewDir);
	return vec2(ndotl, rdotv);
}

void main()
{
	vec2 viewport = (u_viewRect.zw - u_viewRect.xy) * vec2(1.0/8.0, 1.0/4.0);
	vec2 stippleUV = viewport*(v_pos.xy*0.5 + 0.5);
	vec4 color = texture2D(u_texColor, v_texcoord0);
	if ( (u_stipple.x - texture2D(u_texStipple,stippleUV).x)*u_stipple.y > u_stipple.z
	||   color.w < 0.5)
	{
		discard;
	}

	vec3 lightDir = vec3(0.0, 0.0, -1.0);
	vec3 normal = normalize(v_normal);
	vec3 view = normalize(v_view);
	vec2 bln = blinn(lightDir, normal, view);
	float l = saturate(bln.y);

	color.xyz = toLinear(color.xyz)*l;
	gl_FragColor = toGamma(color);
}


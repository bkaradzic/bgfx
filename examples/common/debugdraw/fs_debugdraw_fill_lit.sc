$input v_view, v_world

/*
 * Copyright 2011-2025 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <bgfx_shader.sh>

uniform vec4 u_params[4];

#define u_lightDir     u_params[0].xyz
#define u_shininess    u_params[0].w
#define u_skyColor     u_params[1].xyz
#define u_groundColor  u_params[2].xyz
#define u_matColor     u_params[3]

void main()
{
	vec3 normal  =  normalize(cross(dFdx(v_world), dFdy(v_world) ) );
	vec3 viewDir = -normalize(v_view);

	float ndotl   = dot(normal, u_lightDir);
	vec3  diffuse = mix(u_groundColor, u_skyColor, ndotl*0.5 + 0.5) * u_matColor.xyz;

#if 0
	vec3  reflected = 2.0*ndotl*normal - u_lightDir;
	float rdotv     = dot(reflected, viewDir);
	float spec      = step(0.0, ndotl) * pow(max(0.0, rdotv), u_shininess);
#else
	float spec = 0.0;
#endif

	gl_FragColor = vec4(diffuse + vec3_splat(spec), u_matColor.w);
}

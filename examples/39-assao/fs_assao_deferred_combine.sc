$input v_texcoord0

/*
 * Copyright 2018 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

SAMPLER2D(s_color, 0);
SAMPLER2D(s_normal, 1);
SAMPLER2D(s_ao, 2);

uniform vec4 u_combineParams[2];

void main()
{
	vec2 tc0 = v_texcoord0 * u_combineParams[1].xy + u_combineParams[1].zw;
	vec3 albedoColor = vec3(1.0,1.0,1.0);
	if (u_combineParams[0].x > 0.0)
	{
		albedoColor = texture2D(s_color, tc0).rgb;
	}

	float light = 1.0;
	if (u_combineParams[0].x > 0.0)
	{
		vec3 n  = texture2D(s_normal, tc0).xyz;
		// Expand out normal
		n = n*2.0-1.0;
		vec3 l = normalize(vec3(-0.8,0.75,-1.0));
		light = max(0.0,dot(n,l)) * 1.2+ 0.3; 
	}

	float ao = 1.0;
	if ( u_combineParams[0].y > 0.0)
	{
		ao = texture2D(s_ao, tc0).x;
	}

	gl_FragColor = vec4(albedoColor * light * ao, 1.0f);
} 
 
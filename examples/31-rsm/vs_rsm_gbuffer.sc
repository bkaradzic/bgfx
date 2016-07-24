$input a_position, a_normal
$output v_normal

/*
 * Copyright 2016 Joseph Cherlin. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */


#include "../common/common.sh"

uniform vec4 u_tint;

void main()
{
	// Calculate vertex position
	vec3 pos = a_position;
	gl_Position = mul(u_modelViewProj, vec4(pos, 1.0) );

	// Calculate normal.  Note that compressed normal is stored in the vertices
	vec3 normalObjectSpace = a_normal.xyz*2.0+-1.0; // Normal is stored in [0,1], remap to [-1,1].

	// Transform normal into world space.  
	vec3 normalWorldSpace = mul(u_model[0], vec4(normalObjectSpace, 0.0) ).xyz;
	// Normalize to remove (uniform...) scaling, however, recompress
	v_normal.xyz = normalize(normalWorldSpace)*0.5+0.5;
}

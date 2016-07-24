$input a_position, a_normal
$output v_normal // RSM shadow

/*
 * Copyright 2016 Joseph Cherlin. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

uniform vec4 u_tint;

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );

	// Calculate normal.  Note that compressed normal is stored in the vertices
	vec3 normalObjectSpace = a_normal.xyz*2.0+-1.0; // Normal is stored in [0,1], remap to [-1,1].

	// Transform normal into view space.  
	v_normal = mul(u_modelView, vec4(normalObjectSpace, 0.0) ).xyz;
	// Normalize to remove (uniform...) scaling
	v_normal = normalize(v_normal);
}

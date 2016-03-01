$input v_view, v_bc

/*
 * Copyright 2016 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"
#include "uniforms.sh"

void main()
{
	vec3  color   = u_wfColor;
	float opacity = u_wfOpacity;
	float thickness = u_wfThickness;

	if (gl_FrontFacing) { opacity *= 0.5; }

	vec3 fw = abs(dFdx(v_bc)) + abs(dFdy(v_bc));
	vec3 val = smoothstep(vec3_splat(0.0), fw*thickness, v_bc);
	float edge = min(min(val.x, val.y), val.z); // Gets to 0.0 around the edges.

	vec4 rgba = vec4(color, (1.0-edge)*opacity);
	gl_FragColor = rgba;
}


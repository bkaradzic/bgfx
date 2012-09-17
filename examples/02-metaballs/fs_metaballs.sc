$input v_normal, v_color0

/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

void main()
{
	vec3 lightDir = vec3(0.0, 0.0, -1.0);
	float ndotl = max(dot(normalize(v_normal), lightDir), 0.0);
	float spec = pow(ndotl, 30.0);
	gl_FragColor = v_color0 * ndotl + spec;
}

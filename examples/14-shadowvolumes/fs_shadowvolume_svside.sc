$input v_k

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"

void main()
{
	float k = v_k;
	if (!gl_FrontFacing)
	{
		k = -k;
	}

	gl_FragColor.xyzw =
		vec4( float(abs(k - 1.0) < 0.0001)/255.0
			, float(abs(k + 1.0) < 0.0001)/255.0
			, float(abs(k - 2.0) < 0.0001)/255.0
			, float(abs(k + 2.0) < 0.0001)/255.0
			);
}

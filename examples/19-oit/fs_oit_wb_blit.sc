$input v_texcoord0

/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"

SAMPLER2D(s_texColor0, 0);
SAMPLER2D(s_texColor1, 1);

void main()
{
	vec4  accum   = texture2D(s_texColor0, v_texcoord0);
	float opacity = texture2D(s_texColor1, v_texcoord0).x;
	gl_FragColor  = vec4(accum.xyz / clamp(accum.w, 1e-4, 5e4), opacity);
}

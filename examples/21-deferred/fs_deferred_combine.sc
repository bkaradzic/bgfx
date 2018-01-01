$input v_texcoord0

/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

SAMPLER2D(s_albedo, 0);
SAMPLER2D(s_light,  1);

void main()
{
	vec4 albedo  = toLinear(texture2D(s_albedo, v_texcoord0) );
	vec4 light   = toLinear(texture2D(s_light,  v_texcoord0) );
	gl_FragColor = toGamma(albedo*light);
}

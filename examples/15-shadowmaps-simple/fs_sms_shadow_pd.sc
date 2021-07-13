$input v_position

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

BGFX_BEGIN_UNIFORM_BLOCK(UniformsMaterial)
uniform vec4 u_depthScaleOffset;  // for GL, map depth values into [0, 1] range
BGFX_END_UNIFORM_BLOCK

#define u_depthScale u_depthScaleOffset.x
#define u_depthOffset u_depthScaleOffset.y

void main()
{
	float depth = v_position.z/v_position.w * u_depthScale + u_depthOffset;
	gl_FragColor = packFloatToRgba(depth);
}

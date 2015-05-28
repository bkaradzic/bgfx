/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"

uniform vec4 u_offset[16];
uniform vec4 u_tonemap;
#define u_time u_tonemap.w

float reinhard(float _x)
{
	return _x / (_x + 1.0);
}

vec3 reinhard(vec3 _x)
{
	return _x / (_x + 1.0);
}

float reinhard2(float _x, float _whiteSqr)
{
	return (_x * (1.0 + _x/_whiteSqr) ) / (1.0 + _x);
}

vec3 reinhard2(vec3 _x, float _whiteSqr)
{
	return (_x * (1.0 + _x/_whiteSqr) ) / (1.0 + _x);
}

vec4 blur9(sampler2D _sampler, vec2 _uv0, vec4 _uv1, vec4 _uv2, vec4 _uv3, vec4 _uv4)
{
#define _BLUR9_WEIGHT_0 1.0
#define _BLUR9_WEIGHT_1 0.9
#define _BLUR9_WEIGHT_2 0.55
#define _BLUR9_WEIGHT_3 0.18
#define _BLUR9_WEIGHT_4 0.1
#define _BLUR9_NORMALIZE (_BLUR9_WEIGHT_0+2.0*(_BLUR9_WEIGHT_1+_BLUR9_WEIGHT_2+_BLUR9_WEIGHT_3+_BLUR9_WEIGHT_4) )
#define BLUR9_WEIGHT(_x) (_BLUR9_WEIGHT_##_x/_BLUR9_NORMALIZE)

	vec4 blur;
	blur  = texture2D(_sampler, _uv0)*BLUR9_WEIGHT(0);
	blur += texture2D(_sampler, _uv1.xy)*BLUR9_WEIGHT(1);
	blur += texture2D(_sampler, _uv1.zw)*BLUR9_WEIGHT(1);
	blur += texture2D(_sampler, _uv2.xy)*BLUR9_WEIGHT(2);
	blur += texture2D(_sampler, _uv2.zw)*BLUR9_WEIGHT(2);
	blur += texture2D(_sampler, _uv3.xy)*BLUR9_WEIGHT(3);
	blur += texture2D(_sampler, _uv3.zw)*BLUR9_WEIGHT(3);
	blur += texture2D(_sampler, _uv4.xy)*BLUR9_WEIGHT(4);
	blur += texture2D(_sampler, _uv4.zw)*BLUR9_WEIGHT(4);
	return blur;
}

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

#ifndef PARAMETERS_SH
#define PARAMETERS_SH

// struct PassUniforms
uniform vec4 u_params[13];

#define u_depthUnpackConsts			(u_params[0].xy)
#define u_frameIdx					(u_params[0].z)
#define u_lobeRotation				(u_params[0].w)
#define u_ndcToViewMul				(u_params[1].xy)
#define u_ndcToViewAdd				(u_params[1].zw)

#define u_blurSteps					(u_params[2].x)
#define u_lobeCount					(u_params[2].y)
#define u_lobeRadiusMin				(u_params[2].z)
#define u_lobeRadiusDelta2x			(u_params[2].w)
#define u_samplePattern				(u_params[2].y)
#define u_maxBlurSize				(u_params[3].x)
#define u_focusPoint				(u_params[3].y)
#define u_focusScale				(u_params[3].z)
#define u_radiusScale				(u_params[3].w)

#endif // PARAMETERS_SH

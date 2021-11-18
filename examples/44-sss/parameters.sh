/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#ifndef PARAMETERS_SH
#define PARAMETERS_SH

uniform vec4 u_params[12];

#define u_frameIdx					(u_params[0].x)
#define u_shadowRadius				(u_params[0].y)
#define u_shadowSteps				(u_params[0].z)
#define u_useNoiseOffset			(u_params[0].w)

#define u_depthUnpackConsts			(u_params[1].xy)
#define u_contactShadowsMode		(u_params[1].z)
#define u_useScreenSpaceRadius		(u_params[1].w)
#define u_ndcToViewMul				(u_params[2].xy)
#define u_ndcToViewAdd				(u_params[2].zw)
#define u_lightPosition				(u_params[3].xyz)
#define u_displayShadows			(u_params[3].w)

#define u_worldToView0				(u_params[4])
#define u_worldToView1				(u_params[5])
#define u_worldToView2				(u_params[6])
#define u_worldToView3				(u_params[7])
#define u_viewToProj0				(u_params[8])
#define u_viewToProj1				(u_params[9])
#define u_viewToProj2				(u_params[10])
#define u_viewToProj3				(u_params[11])

#endif // PARAMETERS_SH

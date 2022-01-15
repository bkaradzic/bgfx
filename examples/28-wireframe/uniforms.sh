/*
 * Copyright 2016 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

uniform vec4 u_params[3];
#define u_camPos       u_params[0].xyz
#define u_unused0      u_params[0].w
#define u_wfColor      u_params[1].xyz
#define u_wfOpacity    u_params[1].w
#define u_drawEdges    u_params[2].x
#define u_wfThickness  u_params[2].y

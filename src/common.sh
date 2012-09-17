/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __SHADER_COMMON_H__
#define __SHADER_COMMON_H__

#include "bgfx_shader.sh"

uniform mat4 u_view;
uniform mat4 u_viewProj;
uniform mat4 u_model;
uniform mat4 u_modelView;
uniform mat4 u_modelViewProj;
uniform mat4 u_modelViewProjX;
uniform mat4 u_viewProjX;

SAMPLER2D(u_texColor, 0);

#endif // __SHADER_COMMON_H__

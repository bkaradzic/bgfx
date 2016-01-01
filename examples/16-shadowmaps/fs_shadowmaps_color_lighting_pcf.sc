$input v_normal, v_view, v_shadowcoord

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#define SM_PCF 1

#include "fs_shadowmaps_color_lighting.sh"

void main()
{
#include "fs_shadowmaps_color_lighting_main.sh"
}

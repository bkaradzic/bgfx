$input v_texcoord0

/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */
 
#include "../common/common.sh"
#include "virtualtexture.sh"

void main()
{
   gl_FragColor = VirtualTexture(v_texcoord0.xy);
}


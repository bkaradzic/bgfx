$input v_texcoord0

/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

/*
 * Reference(s):
 * - Based on Virtual Texture Demo by Brad Blanchard
 *   http://web.archive.org/web/20190103162638/http://linedef.com/virtual-texture-demo.html
 */ 
 
#include "../common/common.sh"
#include "virtualtexture.sh"

void main()
{
   gl_FragColor = VirtualTexture(v_texcoord0.xy);
}


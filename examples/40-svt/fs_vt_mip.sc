$input v_texcoord0

/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"
#include "virtualtexture.sh"

void main()
{
   float mipCount = log2(PageTableSize);
	float mip = floor(MipLevel(v_texcoord0.xy, VirtualTextureSize) - MipBias);
	mip = clamp(mip, 0, mipCount);
	vec2 offset = floor(v_texcoord0.xy * PageTableSize);
   gl_FragColor = vec4(floor(vec3(offset / exp2(mip), mip)) / 255.0, 1.0);   
}

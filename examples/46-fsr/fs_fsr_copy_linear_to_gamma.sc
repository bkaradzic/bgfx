$input v_texcoord0

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

#include "../common/common.sh"

SAMPLER2D(s_color, 0);

void main()
{
	vec2 texCoord = v_texcoord0;
	vec4 linearColor = texture2D(s_color, texCoord);

	// this pass is writing directly out to backbuffer, convert from linear to gamma
	vec4 color = vec4(toGamma(linearColor.xyz), linearColor.w);

	gl_FragColor = color;
}

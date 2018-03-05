/*
 * Copyright 2018 Kostas Anagnostou. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

//dummy shader for occlusion buffer pass until bgfx supports rendering with null shader 
void main()
{
	gl_FragColor = vec4(0, 0, 0, 0);
}

$input v_wpos, v_view, v_normal, v_tangent, v_bitangent, v_texcoord0

/*
 * Copyright 2018 Eric Arnebäck. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

uniform vec4 u_color;

void main()
{
	// the albedo-buffer of the g-buffer.
	gl_FragData[0] = u_color;

	// for convenience, we also output the same color, to the first texture of the texture chain used for bloom.
	// this color will now be bloomed, in the following passes.
	gl_FragData[1] = u_color;
}

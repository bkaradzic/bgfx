$input v_color0

/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_shader.sh"

void main()
{
	gl_FragData[0] = v_color0;
	gl_FragData[1] = v_color0;
	gl_FragData[2] = v_color0;
}

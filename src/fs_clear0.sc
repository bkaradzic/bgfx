/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

uniform vec4 bgfx_clear_color[8];

void main()
{
	gl_FragColor = bgfx_clear_color[0];
}

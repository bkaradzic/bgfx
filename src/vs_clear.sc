$input a_position, a_color
$output v_color0

/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.sh"

void main()
{
	gl_Position = vec4(a_position, 1.0);
	v_color0 = a_color;
}

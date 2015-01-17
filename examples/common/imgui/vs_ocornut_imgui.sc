$input a_position, a_texcoord0, a_color0
$output v_color0, v_texcoord0

// 

#include "../common.sh"

#define viewSize u_viewRect.zw

void main()
{
	gl_Position = vec4(2.0 * a_position.x/viewSize.x - 1.0, 1.0 - 2.0 * a_position.y/viewSize.y, 0.0, 1.0);
	v_texcoord0 = a_texcoord0;
	v_color0 = a_color0;
}


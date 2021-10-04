$input a_position, a_texcoord0, a_color0
$output v_color0, v_texcoord0

#include "../common.sh"

void main()
{
	vec2 pos = 2.0*a_position.xy*u_viewTexel.xy;
	gl_Position = vec4(pos.x - 1.0, 1.0 - pos.y, 0.0, 1.0);
	v_texcoord0 = a_texcoord0;
	v_color0    = a_color0;
}

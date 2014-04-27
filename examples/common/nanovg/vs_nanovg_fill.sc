$input a_position, a_texcoord0
$output v_position, v_texcoord0

uniform vec2 u_viewSize;

void main()
{
	v_position  = a_position;
	v_texcoord0 = a_texcoord0;
	gl_Position = vec4(2.0*v_position.x/u_viewSize.x - 1.0, 1.0 - 2.0*v_position.y/u_viewSize.y, 0.0, 1.0);
}

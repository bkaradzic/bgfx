$input a_position, a_texcoord0
$output v_position, v_texcoord0

#include "../common.sh"

#define NEED_HALF_TEXEL (BGFX_SHADER_LANGUAGE_HLSL < 4)

uniform vec4 u_viewSize;

#if NEED_HALF_TEXEL
uniform vec4 u_halfTexel;
#endif // NEED_HALF_TEXEL

void main()
{
#if !NEED_HALF_TEXEL
	const vec4 u_halfTexel = vec4_splat(0.0);
#endif // !NEED_HALF_TEXEL

	v_position  = a_position;
	v_texcoord0 = a_texcoord0+u_halfTexel.xy;
	gl_Position = vec4(2.0*v_position.x/u_viewSize.x - 1.0, 1.0 - 2.0*v_position.y/u_viewSize.y, 0.0, 1.0);
}

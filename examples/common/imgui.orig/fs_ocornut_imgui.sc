$input v_color0, v_texcoord0

#include "../common.sh"

SAMPLER2D(s_tex, 0);

void main()
{
	vec4 texel = texture2D(s_tex, v_texcoord0);
	gl_FragColor = texel * v_color0; 
}

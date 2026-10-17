$input v_color0, v_texcoord0

#include "../common.sh"
#include "imgui_output.sh"

SAMPLER2D(s_tex, 0);

void main()
{
	vec4 texel = texture2D(s_tex, v_texcoord0);
	vec4 color = texel * v_color0;
	gl_FragColor = vec4(imguiOutput(color.xyz), color.w);
}

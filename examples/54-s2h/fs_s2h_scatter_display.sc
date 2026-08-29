$input v_color0, v_texcoord0

#include "../common/common.sh"

SAMPLER2D(s_scatterColor, 0);

void main()
{
	gl_FragColor = texture2D(s_scatterColor, v_texcoord0);
}

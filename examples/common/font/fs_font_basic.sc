$input v_color0, v_texcoord0

#include "../../common/common.sh"

SAMPLERCUBE(s_texColor, 0);

void main()
{
	vec4 color = textureCube(s_texColor, v_texcoord0.xyz);
	int index = int(v_texcoord0.w*4.0 + 0.5);
	float rgba[4];
	rgba[0] = color.z;
	rgba[1] = color.y;
	rgba[2] = color.x;
	rgba[3] = color.w;
	float alpha = rgba[index];
	gl_FragColor = vec4(v_color0.xyz, v_color0.a * alpha);
}

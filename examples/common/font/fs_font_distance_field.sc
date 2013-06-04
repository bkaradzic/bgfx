$input v_color0, v_texcoord0

#include "../../common/common.sh"

SAMPLERCUBE(u_texColor, 0);

uniform float u_inverse_gamma;

void main()
{	
	vec4 color = textureCube(u_texColor, v_texcoord0.xyz);
	int index = int(v_texcoord0.w*4.0 + 0.5);
	float distance = color.bgra[index];

	float dx = length(dFdx(v_texcoord0.xyz) );
	float dy = length(dFdy(v_texcoord0.xyz) );
	float w = 16.0*0.5*(dx+dy);

	float a = smoothstep(0.5-w, 0.5+w, distance);
	gl_FragColor = vec4(v_color0.rgb, v_color0.a*a);
}

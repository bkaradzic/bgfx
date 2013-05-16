$input v_color0, v_texcoord0

#include "../../common/common.sh"

SAMPLERCUBE(u_texColor, 0);

uniform float u_inverse_gamma;

void main()
{		
	vec4 color = textureCube(u_texColor, v_texcoord0.xyz);
    int index = int(v_texcoord0.w*4.0 + 0.5);
    float a = color.bgra[index];	
	//a = pow(a, u_inverse_gamma); //I'll deal with gamma later
	gl_FragColor = vec4(v_color0.rgb, v_color0.a * a);    
}

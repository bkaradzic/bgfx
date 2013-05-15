$input v_color0, v_texcoord0

#include "../../common/common.sh"

SAMPLERCUBE(u_texColor, 0);

uniform float u_inverse_gamma;

void main()
{	
    vec4 color = textureCube(u_texColor, v_texcoord0.xyz);
    int index = int(v_texcoord0.w*4.0 + 0.5);
    float distance = color.bgra[index];
    
    float dx = length(dFdx(v_texcoord0.xyz));
    float dy = length(dFdy(v_texcoord0.xyz));       
    float w = 16.0*0.5*(dx+dy);

    // alternatives that seems to give identical results
    //float w = 16.0*max(dx,dy); 
    //float w = 16.0*length(vec2(dx,dy))/sqrt(2.0);
    //float w = 16.0*length(fwidth(v_texcoord0.xyz))/sqrt(2.0);

    float a = smoothstep(0.5-w, 0.5+w, distance);
    //a = pow(a, u_inverse_gamma); //I'll deal with gamma later
    gl_FragColor = vec4(v_color0.rgb, v_color0.a*a);
}
$input v_texcoord0

#include "../common/common.sh"

SAMPLER2D(s_tex, 0);
//SAMPLER2D(s_target_tex, 1);

uniform vec4 u_pixelSize;
uniform vec4 u_intensity;

void main()
{
    vec2 halfpixel = 1.0 * vec2(u_pixelSize.x, u_pixelSize.y);
    vec2 uv = v_texcoord0.xy;
	
	vec4 sum = vec4(0.0, 0.0, 0.0, 0.0);
	
	sum += (2.0 / 16.0) * texture2D(s_tex, uv + vec2(-halfpixel.x , 0.0));
    sum += (2.0 / 16.0) * texture2D(s_tex, uv + vec2(0.0, halfpixel.y));
    sum += (2.0 / 16.0) * texture2D(s_tex, uv + vec2(halfpixel.x , 0.0));
    sum += (2.0 / 16.0) * texture2D(s_tex, uv + vec2(0.0, -halfpixel.y));
    
	sum += (1.0 / 16.0) * texture2D(s_tex, uv + vec2(-halfpixel.x, -halfpixel.y));
	sum += (1.0 / 16.0) * texture2D(s_tex, uv + vec2(-halfpixel.x, halfpixel.y));
    sum += (1.0 / 16.0) * texture2D(s_tex, uv + vec2(halfpixel.x, -halfpixel.y));
    sum += (1.0 / 16.0) * texture2D(s_tex, uv + vec2(halfpixel.x, halfpixel.y));

    sum += (4.0 / 16.0) * texture2D(s_tex, uv);
		
	gl_FragColor.xyzw = u_intensity.x * sum;
}

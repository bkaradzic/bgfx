$input v_color0, v_texcoord0

#include <bgfx_shader.sh>

SAMPLER2D(tex1,  0);

uniform vec2      u_scale;

uniform float     u_alpha;
uniform float     u_mult;

void main() {
   vec4 color = texture2D(tex1, vec2(v_texcoord0.x-4.0*u_scale.x, v_texcoord0.y-4.0*u_scale.y))*0.05;
   color += texture2D(tex1, vec2(v_texcoord0.x-3.0*u_scale.x, v_texcoord0.y-3.0*u_scale.y))*0.09;
   color += texture2D(tex1, vec2(v_texcoord0.x-2.0*u_scale.x, v_texcoord0.y-2.0*u_scale.y))*0.12;
   color += texture2D(tex1, vec2(v_texcoord0.x-1.0*u_scale.x, v_texcoord0.y-1.0*u_scale.y))*0.15;
   color += texture2D(tex1, vec2(v_texcoord0.x+0.0*u_scale.x, v_texcoord0.y+0.0*u_scale.y))*0.16;
   color += texture2D(tex1, vec2(v_texcoord0.x+1.0*u_scale.x, v_texcoord0.y+1.0*u_scale.y))*0.15;
   color += texture2D(tex1, vec2(v_texcoord0.x+2.0*u_scale.x, v_texcoord0.y+2.0*u_scale.y))*0.12;
   color += texture2D(tex1, vec2(v_texcoord0.x+3.0*u_scale.x, v_texcoord0.y+3.0*u_scale.y))*0.09;
   color += texture2D(tex1, vec2(v_texcoord0.x+4.0*u_scale.x, v_texcoord0.y+4.0*u_scale.y))*0.05;
   gl_FragColor = color * vec4(u_mult, u_mult, u_mult, u_alpha*u_mult);
}

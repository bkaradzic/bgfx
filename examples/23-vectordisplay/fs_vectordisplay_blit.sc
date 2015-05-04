$input v_color0, v_texcoord0

#include <bgfx_shader.sh>

SAMPLER2D(s_textureSampler,  0);

uniform float u_compose_alpha;
uniform float u_compose_mult;

void main() {
  gl_FragColor = texture2D(s_textureSampler, v_texcoord0.xy) *
                 vec4(u_compose_mult, u_compose_mult, u_compose_mult, u_compose_alpha*u_compose_mult);
}

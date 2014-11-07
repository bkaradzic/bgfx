$input v_color0, v_texcoord0

#include <bgfx_shader.sh>

SAMPLER2D(tex1,  0);

uniform float u_alpha;
uniform float u_mult;

void main() {
  gl_FragColor = texture2D(tex1, v_texcoord0.xy) * vec4(u_mult, u_mult, u_mult, u_alpha*u_mult);
}

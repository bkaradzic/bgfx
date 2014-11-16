$input v_color0, v_texcoord0

#include <bgfx_shader.sh>

SAMPLER2D(s_lineTexture,  0);

uniform float u_compose_alpha;

void main() {
  vec4 texColor = texture2D(s_lineTexture, v_texcoord0.xy);
  gl_FragColor = v_color0 * texColor * vec4(1.0, 1.0, 1.0, u_compose_alpha);
}

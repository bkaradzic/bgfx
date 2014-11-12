$input v_color0, v_texcoord0

#include <bgfx_shader.sh>

SAMPLER2D(u_linetexid,  0);

uniform float u_alpha;

void main() {
  vec4 texColor = texture2D(u_linetexid, v_texcoord0.xy);
  gl_FragColor = v_color0 * texColor * vec4(1.0, 1.0, 1.0, u_alpha);
}

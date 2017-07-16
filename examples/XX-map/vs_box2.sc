$input a_position, a_color0, a_texcoord0
$output v_color0

#include <bgfx_shader.sh>

void main() {
  vec2 xy = a_position.xy * a_texcoord0.x;
  gl_Position = mul(u_modelViewProj, vec4(xy, 0.0, 1.0) );
  v_color0 = a_color0;
}

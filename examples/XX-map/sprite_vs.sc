$input a_position, a_texcoord0, a_normal
$output v_texcoord0

#include <bgfx_shader.sh>

mat2 rotate2d(float ang)
{
    return mat2(-cos(ang),sin(ang),
                sin(ang), cos(ang));
}

void main() {
  //
  // a_position.xy = SpriteVertex.x/y i.e. the world X,Y of the sprite center
  // a_position.ba = SpriteVertex.ox/oy i.e. the offset of this corner
  // e.g. if the sprite is centered then ox,oy of the bottom right corner
  // would be (+spriteWidth/2, -spriteHeight/2)
  //
  vec4 pos = vec4(a_position.xy + mul(a_position.ba,rotate2d(a_normal.x)), 0.0, 1.0);
  gl_Position = mul(u_modelViewProj, pos);
  v_texcoord0 = a_texcoord0;
}
